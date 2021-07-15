/*
 * SocketServer.cpp
 *
 *  Created on: 25 Mar 2017
 *      Author: David
 */

#include "ecv.h"
#undef yield
#undef array
#undef out

extern "C"
{
	#include "user_interface.h"     // for struct rst_info
	#include "lwip/init.h"			// for version info
	#include "lwip/stats.h"			// for stats_display()

#if LWIP_VERSION_MAJOR == 2
	#include "lwip/apps/mdns.h"
	#include "lwip/apps/netbiosns.h"
#else
	#include "lwip/app/netbios.h"	// for NetBIOS support
#endif
}

#include <cstdarg>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <EEPROM.h>
#include "SocketServer.h"
#include "Config.h"
#include "PooledStrings.h"
#include "HSPI.h"
// There is a name clash between this code and the ESP8266 Arduino core framework. Both use WiFiState. Rename
// ours to avoid the clash. Better ways to do this, but this requires minimal change.
#define WiFiState SSWiFiState
#include "include/MessageFormats.h"
#include "Connection.h"
#include "Listener.h"
#include "Misc.h"

const unsigned int ONBOARD_LED = D4;				// GPIO 2
const bool ONBOARD_LED_ON = false;					// active low
const uint32_t ONBOARD_LED_BLINK_INTERVAL = 500;	// ms
const uint32_t TransferReadyTimeout = 5;			// how many milliseconds we allow for the Duet to set TransferReady low after the end of a transaction, before we assume that we missed seeing it

#if LWIP_VERSION_MAJOR == 2
const char * const MdnsProtocolNames[3] = { "HTTP", "FTP", "Telnet" };
const char * const MdnsServiceStrings[3] = { "_http", "_ftp", "_telnet" };
const char * const MdnsTxtRecords[2] = { "product=DuetWiFi", "version=" VERSION_MAIN };
const unsigned int MdnsTtl = 10 * 60;			// same value as on the Duet 0.6/0.8.5
#else
# include <ESP8266mDNS.h>
#endif

#define array _ecv_array

const uint32_t MaxConnectTime = 40 * 1000;		// how long we wait for WiFi to connect in milliseconds
const uint32_t StatusReportMillis = 200;

const int DefaultWiFiChannel = 6;

// Global data
char currentSsid[SsidLength + 1];
char webHostName[HostNameLength + 1] = "Duet-WiFi";
uint8_t currentBssid[6];
uint8_t *currentBssidPtr;
DNSServer dns;

static const char* lastError = nullptr;
static const char* prevLastError = nullptr;
static uint32_t whenLastTransactionFinished = 0;
static bool connectErrorChanged = false;
static bool transferReadyChanged = false;

static char lastConnectError[100];

static WiFiState currentState = WiFiState::idle,
				prevCurrentState = WiFiState::disabled,
				lastReportedState = WiFiState::disabled;
static uint32_t lastBlinkTime = 0;

ADC_MODE(ADC_VCC);          // need this for the ESP.getVcc() call to work

static HSPIClass hspi;
static uint32_t connectStartTime;
static uint32_t lastStatusReportTime;
static uint32_t transferBuffer[NumDwords(MaxDataLength + 1)];

static const WirelessConfigurationData *ssidData = nullptr;

// Look up a SSID in our remembered network list, return pointer to it if found
const WirelessConfigurationData *RetrieveSsidData(const char *ssid, int *index = nullptr)
{
	for (size_t i = 1; i <= MaxRememberedNetworks; ++i)
	{
		const WirelessConfigurationData *wp = reinterpret_cast<const WirelessConfigurationData*>(EEPROM.getConstDataPtr()+(i * sizeof(WirelessConfigurationData)));

		if (wp != nullptr && strncmp(ssid, wp->ssid, sizeof(wp->ssid)) == 0)
		{
			if (index != nullptr)
			{
				*index = i;
			}
			return wp;
		}
	}
	return nullptr;
}

// Find an empty entry in the table of known networks
bool FindEmptySsidEntry(int *index)
{
	for (size_t i = 1; i <= MaxRememberedNetworks; ++i)
	{
		const WirelessConfigurationData *wp = reinterpret_cast<const WirelessConfigurationData*>(EEPROM.getConstDataPtr()+(i * sizeof(WirelessConfigurationData)));
		if (wp != nullptr && wp->ssid[0] == 0xFF)
		{
			*index = i;
			return true;
		}
	}
	return false;
}

// Check socket number in range, returning true if yes. Otherwise, set lastError and return false;
bool ValidSocketNumber(uint8_t num)
{
#ifdef EXTENDED_LISTEN
	if (num < MaxPublicConnections)
#else
	if (num < MaxConnections)
#endif
	{
		return true;
	}
	lastError = "socket number out of range";
	return false;
}

// Reset to default settings
void FactoryReset()
{
	WirelessConfigurationData temp;
	memset(&temp, 0xFF, sizeof(temp));
	for (size_t i = 0; i <= MaxRememberedNetworks; ++i)
	{
		EEPROM.put(i * sizeof(WirelessConfigurationData), temp);
	}
	EEPROM.commit();
}

// Try to connect using the specified SSID and password
void ConnectToAccessPoint(const WirelessConfigurationData& apData, uint8_t *bssid, bool isRetry)
pre(currentState == NetworkState::idle)
{
	SafeStrncpy(currentSsid, apData.ssid, ARRAY_SIZE(currentSsid));
	if (bssid != nullptr)
	{
		memcpy(currentBssid, bssid, ARRAY_SIZE(currentBssid));
		currentBssidPtr = currentBssid;
	}
	else
		currentBssidPtr = nullptr;
	WiFi.mode(WIFI_STA);
	wifi_station_set_hostname(webHostName);     				// must do this before calling WiFi.begin()
	WiFi.setAutoConnect(false);
//	WiFi.setAutoReconnect(false);								// auto reconnect NEVER works in our configuration so disable it, it just wastes time
	WiFi.setAutoReconnect(true);
#if NO_WIFI_SLEEP
	wifi_set_sleep_type(NONE_SLEEP_T);
#else
	wifi_set_sleep_type(MODEM_SLEEP_T);
#endif
	WiFi.config(IPAddress(apData.ip), IPAddress(apData.gateway), IPAddress(apData.netmask), IPAddress(), IPAddress());
	debugPrintf("Trying to connect to ssid \"%s\" with password \"%s\"\n", apData.ssid, apData.password);
	WiFi.begin(apData.ssid, apData.password, 0, currentBssidPtr);

	if (isRetry)
	{
		currentState = WiFiState::reconnecting;
	}
	else
	{
		currentState = WiFiState::connecting;
		connectStartTime = millis();
	}
}

void ConnectPoll()
{
	// The Arduino WiFi.status() call is fairly useless here because it discards too much information, so use the SDK API call instead
	const uint8_t status = wifi_station_get_connect_status();
	const char *error = nullptr;
	bool retry = false;

	switch (currentState)
	{
	case WiFiState::connecting:
	case WiFiState::reconnecting:
		// We are trying to connect or reconnect, so check for success or failure
		switch (status)
		{
		case STATION_IDLE:
			error = "Unexpected WiFi state 'idle'";
			break;

		case STATION_CONNECTING:
			if (millis() - connectStartTime >= MaxConnectTime)
			{
				error = "Timed out";
			}
			break;

		case STATION_WRONG_PASSWORD:
			error = "Wrong password";
			break;

		case STATION_NO_AP_FOUND:
			error = "Didn't find access point";
			retry = (currentState == WiFiState::reconnecting);
			break;

		case STATION_CONNECT_FAIL:
			error = "Failed";
			retry = (currentState == WiFiState::reconnecting);
			break;

		case STATION_GOT_IP:
			if (currentState == WiFiState::reconnecting)
			{
				lastError = "Reconnect succeeded";
			}
			else
			{
#if LWIP_VERSION_MAJOR == 2
				mdns_resp_netif_settings_changed(netif_list);	// STA is on first interface
#else
				MDNS.begin(webHostName);
#endif
			}

			debugPrint("Connected to AP\n");
			currentState = WiFiState::connected;
			digitalWrite(ONBOARD_LED, ONBOARD_LED_ON);
			break;

		default:
			error = "Unknown WiFi state";
			break;
		}

		if (error != nullptr)
		{
			strcpy(lastConnectError, error);
			SafeStrncat(lastConnectError, " while trying to connect to ", ARRAY_SIZE(lastConnectError));
			SafeStrncat(lastConnectError, currentSsid, ARRAY_SIZE(lastConnectError));
			lastError = lastConnectError;
			connectErrorChanged = true;
			debugPrintf("Failed to connect to AP error '%s'\n", lastConnectError);

			if (!retry)
			{
				WiFi.mode(WIFI_OFF);
				currentState = WiFiState::idle;
				digitalWrite(ONBOARD_LED, !ONBOARD_LED_ON);
			}
		}
		break;

	case WiFiState::connected:
		if (status != STATION_GOT_IP)
		{
			// We have just lost the connection
			connectStartTime = millis();						// start the auto reconnect timer

			switch (status)
			{
			case STATION_CONNECTING:							// auto reconnecting
				error = "auto reconnecting";
				currentState = WiFiState::autoReconnecting;
				break;

			case STATION_IDLE:
				error = "state 'idle'";
				retry = true;
				break;

			case STATION_WRONG_PASSWORD:
				error = "state 'wrong password'";
				currentState = WiFiState::idle;
				digitalWrite(ONBOARD_LED, !ONBOARD_LED_ON);
				break;

			case STATION_NO_AP_FOUND:
				error = "state 'no AP found'";
				retry = true;
				break;

			case STATION_CONNECT_FAIL:
				error = "state 'fail'";
				retry = true;
				break;

			default:
				error = "unknown WiFi state";
				currentState = WiFiState::idle;
				digitalWrite(ONBOARD_LED, !ONBOARD_LED_ON);
				break;
			}

			strcpy(lastConnectError, "Lost connection, ");
			SafeStrncat(lastConnectError, error, ARRAY_SIZE(lastConnectError));
			lastError = lastConnectError;
			connectErrorChanged = true;
			debugPrintf("Lost connection to AP status '%s'\n", lastConnectError);
			break;
		}
		break;

	case WiFiState::autoReconnecting:
		if (status == STATION_GOT_IP)
		{
			lastError = "Auto reconnect succeeded";
			currentState = WiFiState::connected;
		}
		else if (status != STATION_CONNECTING && lastError == nullptr)
		{
			lastError = "Auto reconnect failed, trying manual reconnect";
			connectStartTime = millis();						// start the manual reconnect timer
			retry = true;
		}
		else if (millis() - connectStartTime >= MaxConnectTime)
		{
			lastError = "Timed out trying to auto-reconnect";
			retry = true;
		}
		debugPrintf("Autoreconnect to AP status '%s'\n", lastError);
		break;

	default:
		break;
	}

	if (retry)
	{
		ConnectToAccessPoint(*ssidData, currentBssidPtr, true);
	}
}

void StartClient(const char * array ssid)
pre(currentState == WiFiState::idle)
{
	uint8_t *ssidPtr = (ssid != nullptr && ssid[0] != 0 ? (uint8_t *)ssid : nullptr);
	ssidData = nullptr;

	if (ssidPtr != nullptr)
	{
		// we have a target ssid
		ssidData = RetrieveSsidData(ssid, nullptr);
		if (ssidData == nullptr)
		{
			lastError = "no data found for requested SSID";
			return;
		}
	}
	// Auto scan for strongest known network, then try to connect to it
	const int8_t num_ssids = WiFi.scanNetworks(false, true, 0, ssidPtr, 500, 750);
	debugPrintf("Scan found %d SSIDs\n", num_ssids);
	if (num_ssids < 0)
	{
		lastError = "network scan failed";
		currentState = WiFiState::idle;
		digitalWrite(ONBOARD_LED, !ONBOARD_LED_ON);
		return;
	}

	// Find the strongest network that we know about
	int8_t strongestNetwork = -1;
	for (int8_t i = 0; i < num_ssids; ++i)
	{
		debugPrintfAlways("found network %s BSSID %s RSSI %d\n", WiFi.SSID(i).c_str(), WiFi.BSSIDstr(i).c_str(), WiFi.RSSI(i));
		if (strongestNetwork < 0 || WiFi.RSSI(i) > WiFi.RSSI(strongestNetwork))
		{
			const WirelessConfigurationData *wp = RetrieveSsidData(WiFi.SSID(i).c_str(), nullptr);
			if (wp != nullptr)
			{
				strongestNetwork = i;
				ssidData = wp;
			}
		}
	}
	if (ssidData == nullptr)
	{
		lastError = "no known networks found";
		debugPrint("No network found\n");
		return;
	}
	if (strongestNetwork >= 0)
	{
		debugPrintf("Selected AP SSID \"%s\", BSSID %s RSSI %d\n", WiFi.SSID(strongestNetwork).c_str(), WiFi.BSSIDstr(strongestNetwork).c_str(), WiFi.RSSI(strongestNetwork));
		// ssidData contains the details of the strongest known access point
		ConnectToAccessPoint(*ssidData, WiFi.BSSID(strongestNetwork), false);
	}
	else
	{
		debugPrint("Search did not find requested AP, trying to connect anyway\n");
		ConnectToAccessPoint(*ssidData, nullptr, false);
	}
}

bool CheckValidSSID(const char * array s)
{
	size_t len = 0;
	while (*s != 0)
	{
		if (*s < 0x20 || *s == 0x7F)
		{
			return false;					// bad character
		}
		++s;
		++len;
		if (len == SsidLength)
		{
			return false;					// ESP8266 core requires strlen(ssid) <= 31
		}
	}
	return len != 0;
}

bool CheckValidPassword(const char * array s)
{
	size_t len = 0;
	while (*s != 0)
	{
		if (*s < 0x20 || *s == 0x7F)
		{
			return false;					// bad character
		}
		++s;
		++len;
		if (len == PasswordLength)
		{
			return false;					// ESP8266 core requires strlen(password) <= 63
		}
	}
	return len == 0 || len >= 8;			// password must be empty or at least 8 characters (WPA2 restriction)
}

// Check that the access point data is valid
bool ValidApData(const WirelessConfigurationData &apData)
{
	// Check the IP address
	if (apData.ip == 0 || apData.ip == 0xFFFFFFFF)
	{
		return false;
	}

	// Check the channel. 0 means auto so it OK.
	if (apData.channel > 13)
	{
		return false;
	}

	return CheckValidSSID(apData.ssid) && CheckValidPassword(apData.password);
}

void StartAccessPoint()
{
	WirelessConfigurationData apData;
	EEPROM.get(0, apData);

	if (ValidApData(apData))
	{
		SafeStrncpy(currentSsid, apData.ssid, ARRAY_SIZE(currentSsid));
		bool ok = WiFi.mode(WIFI_AP);
		if (ok)
		{
			IPAddress apIP(apData.ip);
			ok = WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
			if (ok)
			{
				debugPrintf("Starting AP %s with password \"%s\"\n", currentSsid, apData.password);
				ok = WiFi.softAP(currentSsid, apData.password, (apData.channel == 0) ? DefaultWiFiChannel : apData.channel);
				if (!ok)
				{
					debugPrintAlways("Failed to start AP\n");
				}
			}
			else
			{
				debugPrintAlways("Failed to set AP config\n");
			}
		}
		else
		{
			debugPrintAlways("Failed to set AP mode\n");
		}

		if (ok)
		{
			debugPrintAlways("AP started\n");
			dns.setErrorReplyCode(DNSReplyCode::NoError);
			if (!dns.start(53, "*", apData.ip))
			{
				lastError = "Failed to start DNS\n";
				debugPrintf("%s\n", lastError);
			}
			SafeStrncpy(currentSsid, apData.ssid, ARRAY_SIZE(currentSsid));
			currentState = WiFiState::runningAsAccessPoint;
			digitalWrite(ONBOARD_LED, ONBOARD_LED_ON);
#if LWIP_VERSION_MAJOR == 2
			mdns_resp_netif_settings_changed(netif_list->next);		// AP is on second interface
#else
			MDNS.begin(webHostName);
#endif
		}
		else
		{
			WiFi.mode(WIFI_OFF);
			lastError = "Failed to start access point";
			debugPrintf("%s\n", lastError);
			currentState = WiFiState::idle;
			digitalWrite(ONBOARD_LED, !ONBOARD_LED_ON);
		}
	}
	else
	{
		lastError = "invalid access point configuration";
		debugPrintf("%s\n", lastError);
		currentState = WiFiState::idle;
		digitalWrite(ONBOARD_LED, !ONBOARD_LED_ON);
	}
}

static union
{
	MessageHeaderSamToEsp hdr;			// the actual header
	uint32_t asDwords[headerDwords];	// to force alignment
} messageHeaderIn;

static union
{
	MessageHeaderEspToSam hdr;
	uint32_t asDwords[headerDwords];	// to force alignment
} messageHeaderOut;

#if LWIP_VERSION_MAJOR == 2

void GetServiceTxtEntries(struct mdns_service *service, void *txt_userdata)
{
	for (size_t i = 0; i < ARRAY_SIZE(MdnsTxtRecords); i++)
	{
		mdns_resp_add_service_txtitem(service, MdnsTxtRecords[i], strlen(MdnsTxtRecords[i]));
	}
}

// Rebuild the mDNS services
void RebuildServices()
{
	for (struct netif *item = netif_list; item != nullptr; item = item->next)
	{
		mdns_resp_remove_netif(item);
		mdns_resp_add_netif(item, webHostName, MdnsTtl);
		mdns_resp_add_service(item, "echo", "_echo", DNSSD_PROTO_TCP, 0, 0, nullptr, nullptr);

		for (size_t protocol = 0; protocol < 3; protocol++)
		{
			const uint16_t port = Listener::GetPortByProtocol(protocol);
			if (port != 0)
			{
				service_get_txt_fn_t txtFunc = (protocol == 0/*HttpProtocol*/) ? GetServiceTxtEntries : nullptr;
				mdns_resp_add_service(item, webHostName, MdnsServiceStrings[protocol], DNSSD_PROTO_TCP, port, MdnsTtl, txtFunc, nullptr);
			}
		}

		mdns_resp_netif_settings_changed(item);
	}
}

void RemoveMdnsServices()
{
	for (struct netif *item = netif_list; item != nullptr; item = item->next)
	{
		mdns_resp_remove_netif(item);
	}
}

#else

// Rebuild the MDNS server to advertise a single service
void AdvertiseService(int service, uint16_t port)
{
	static int currentService = -1;
	static const char * const serviceNames[] = { "http", "tcp", "ftp" };

	if (service != currentService)
	{
		currentService = service;
		MDNS.deleteServices();
		if (service >= 0 && service < (int)ARRAY_SIZE(serviceNames))
		{
			const char* serviceName = serviceNames[service];
			MDNS.addService(serviceName, "tcp", port);
			MDNS.addServiceTxt(serviceName, "tcp", "product", "DuetWiFi");
			MDNS.addServiceTxt(serviceName, "tcp", "version", firmwareVersion);
		}
	}
}

// Rebuild the mDNS services
void RebuildServices()
{
	if (currentState == WiFiState::connected)		// MDNS server only works in station mode
	{
		// Unfortunately the official ESP8266 mDNS library only reports one service.
		// I (chrishamm) tried to use the old mDNS responder, which is also capable of sending
		// mDNS broadcasts, but the packets it generates are broken and thus not of use.
		for (int service = 0; service < 3; ++service)
		{
			const uint16_t port = Listener::GetPortByProtocol(service);
			if (port != 0)
			{
				AdvertiseService(service, port);
				return;
			}
		}

		AdvertiseService(-1, 0);		// no services to advertise
	}
}

#endif

// Send a response.
// 'response' is the number of byes of response if positive, or the error code if negative.
// Use only to respond to commands which don't include a data block, or when we don't want to read the data block.
void ICACHE_RAM_ATTR SendResponse(int32_t response)
{
	(void)hspi.transfer32(response);
	if (response > 0)
	{
		hspi.transferDwords(transferBuffer, nullptr, NumDwords((size_t)response));
	}
}

// This is called when the SAM is asking to transfer data
void ICACHE_RAM_ATTR ProcessRequest()
{
	// Set up our own headers
	messageHeaderIn.hdr.formatVersion = InvalidFormatVersion;
	messageHeaderOut.hdr.formatVersion = MyFormatVersion;
	messageHeaderOut.hdr.state = currentState;
	bool deferCommand = false;

	// Begin the transaction
	digitalWrite(SamSSPin, LOW);            // assert CS to SAM
	hspi.beginTransaction();
	// Exchange headers, except for the last dword which will contain our response
	hspi.transferDwords(messageHeaderOut.asDwords, messageHeaderIn.asDwords, headerDwords - 1);

	if (messageHeaderIn.hdr.formatVersion != MyFormatVersion)
	{
		SendResponse(ResponseBadRequestFormatVersion);
	}
	else if (messageHeaderIn.hdr.dataLength > MaxDataLength)
	{
		SendResponse(ResponseBadDataLength);
	}
	else
	{
		const size_t dataBufferAvailable = std::min<size_t>(messageHeaderIn.hdr.dataBufferAvailable, MaxDataLength);
		// See what command we have received and take appropriate action
		switch (messageHeaderIn.hdr.command)
		{
		case NetworkCommand::nullCommand:					// no command being sent, SAM just wants the network status
			SendResponse(ResponseEmpty);
			break;

		case NetworkCommand::networkStartClient:			// connect to an access point
			if (currentState == WiFiState::idle)
			{
				deferCommand = true;
				messageHeaderIn.hdr.param32 = hspi.transfer32(ResponseEmpty);
				if (messageHeaderIn.hdr.dataLength != 0 && messageHeaderIn.hdr.dataLength <= SsidLength + 1)
				{
					hspi.transferDwords(nullptr, transferBuffer, NumDwords(messageHeaderIn.hdr.dataLength));
					reinterpret_cast<char *>(transferBuffer)[messageHeaderIn.hdr.dataLength] = 0;
				}
			}
			else
			{
				SendResponse(ResponseWrongState);
			}
			break;

		case NetworkCommand::networkStartAccessPoint:		// run as an access point
			if (currentState == WiFiState::idle)
			{
				deferCommand = true;
				messageHeaderIn.hdr.param32 = hspi.transfer32(ResponseEmpty);
			}
			else
			{
				SendResponse(ResponseWrongState);
			}
			break;

		case NetworkCommand::networkFactoryReset:			// clear remembered list, reset factory defaults
			deferCommand = true;
			messageHeaderIn.hdr.param32 = hspi.transfer32(ResponseEmpty);
			break;

		case NetworkCommand::networkStop:					// disconnect from an access point, or close down our own access point
			deferCommand = true;
			messageHeaderIn.hdr.param32 = hspi.transfer32(ResponseEmpty);
			break;

		case NetworkCommand::networkGetStatus:				// get the network connection status
			{
				const bool runningAsAp = (currentState == WiFiState::runningAsAccessPoint);
				const bool runningAsStation = (currentState == WiFiState::connected);
				NetworkStatusResponse * const response = reinterpret_cast<NetworkStatusResponse*>(transferBuffer);
				response->ipAddress = (runningAsAp)
										? static_cast<uint32_t>(WiFi.softAPIP())
										: (runningAsStation)
										  ? static_cast<uint32_t>(WiFi.localIP())
											  : 0;
				response->freeHeap = system_get_free_heap_size();
				response->resetReason = system_get_rst_info()->reason;
				response->flashSize = 1u << ((spi_flash_get_id() >> 16) & 0xFF);
				response->rssi = (runningAsStation) ? wifi_station_get_rssi() : 0;
				response->numClients = (runningAsAp) ? wifi_softap_get_station_num() : 0;
				response->sleepMode = (uint8_t)wifi_get_sleep_type() + 1;
				response->phyMode = (uint8_t)wifi_get_phy_mode();
				response->zero1 = 0;
				response->zero2 = 0;
				response->vcc = system_get_vdd33();
				// if connected return BSSID of AP to help identification
				if (runningAsStation)
					memcpy(response->macAddress, WiFi.BSSID(), 6);
				else
					wifi_get_macaddr((runningAsAp) ? SOFTAP_IF : STATION_IF, response->macAddress);
				SafeStrncpy(response->versionText, firmwareVersion, sizeof(response->versionText));
				SafeStrncpy(response->hostName, webHostName, sizeof(response->hostName));
				SafeStrncpy(response->ssid, currentSsid, sizeof(response->ssid));
				response->clockReg = SPI1CLK;
				SendResponse(sizeof(NetworkStatusResponse));
			}
			break;

		case NetworkCommand::networkAddSsid:				// add to our known access point list
		case NetworkCommand::networkConfigureAccessPoint:	// configure our own access point details
			if (messageHeaderIn.hdr.dataLength == sizeof(WirelessConfigurationData))
			{
				messageHeaderIn.hdr.param32 = hspi.transfer32(ResponseEmpty);
				hspi.transferDwords(nullptr, transferBuffer, NumDwords(sizeof(WirelessConfigurationData)));
				const WirelessConfigurationData * const receivedClientData = reinterpret_cast<const WirelessConfigurationData *>(transferBuffer);
				int index;
				if (messageHeaderIn.hdr.command == NetworkCommand::networkConfigureAccessPoint)
				{
					index = 0;
				}
				else
				{
					index = -1;
					(void)RetrieveSsidData(receivedClientData->ssid, &index);
					if (index < 0)
					{
						(void)FindEmptySsidEntry(&index);
					}
				}

				if (index >= 0)
				{
					EEPROM.put(index * sizeof(WirelessConfigurationData), *receivedClientData);
					EEPROM.commit();
				}
				else
				{
					lastError = "SSID table full";
				}
			}
			else
			{
				SendResponse(ResponseBadDataLength);
			}
			break;

		case NetworkCommand::networkDeleteSsid:				// delete a network from our access point list
			if (messageHeaderIn.hdr.dataLength == SsidLength)
			{
				messageHeaderIn.hdr.param32 = hspi.transfer32(ResponseEmpty);
				hspi.transferDwords(nullptr, transferBuffer, NumDwords(SsidLength));

				int index;
				if (RetrieveSsidData(reinterpret_cast<char*>(transferBuffer), &index) != nullptr)
				{
					WirelessConfigurationData localSsidData;
					memset(&localSsidData, 0xFF, sizeof(localSsidData));
					EEPROM.put(index * sizeof(WirelessConfigurationData), localSsidData);
					EEPROM.commit();
				}
				else
				{
					lastError = "SSID not found";
				}
			}
			else
			{
				SendResponse(ResponseBadDataLength);
			}
			break;

		case NetworkCommand::networkRetrieveSsidData:	// list the access points we know about, including our own access point details
			if (dataBufferAvailable < ReducedWirelessConfigurationDataSize)
			{
				SendResponse(ResponseBufferTooSmall);
			}
			else
			{
				char *p = reinterpret_cast<char*>(transferBuffer);
				for (size_t i = 0; i <= MaxRememberedNetworks && (i + 1) * ReducedWirelessConfigurationDataSize <= dataBufferAvailable; ++i)
				{
					const WirelessConfigurationData * const tempData = reinterpret_cast<const WirelessConfigurationData*>(EEPROM.getConstDataPtr()+(i * sizeof(WirelessConfigurationData)));
					if (tempData->ssid[0] != 0xFF)
					{
						memcpy(p, tempData, ReducedWirelessConfigurationDataSize);
						p += ReducedWirelessConfigurationDataSize;
					}
					else if (i == 0)
					{
						memset(p, 0, ReducedWirelessConfigurationDataSize);
						p += ReducedWirelessConfigurationDataSize;
					}
				}
				const size_t numBytes = p - reinterpret_cast<char*>(transferBuffer);
				SendResponse(numBytes);
			}
			break;

		case NetworkCommand::networkListSsids_deprecated:	// list the access points we know about, plus our own access point details
			{
				char *p = reinterpret_cast<char*>(transferBuffer);
				for (size_t i = 0; i <= MaxRememberedNetworks; ++i)
				{
					const WirelessConfigurationData * const tempData = reinterpret_cast<const WirelessConfigurationData*>(EEPROM.getConstDataPtr()+(i * sizeof(WirelessConfigurationData)));
					if (tempData->ssid[0] != 0xFF)
					{
						for (size_t j = 0; j < SsidLength && tempData->ssid[j] != 0; ++j)
						{
							*p++ = tempData->ssid[j];
						}
						*p++ = '\n';
					}
					else if (i == 0)
					{
						// Include an empty entry for our own access point SSID
						*p++ = '\n';
					}
				}
				*p++ = 0;
				const size_t numBytes = p - reinterpret_cast<char*>(transferBuffer);
				if (numBytes <= dataBufferAvailable)
				{
					SendResponse(numBytes);
				}
				else
				{
					SendResponse(ResponseBufferTooSmall);
				}
			}
			break;

		case NetworkCommand::networkSetHostName:			// set the host name
			if (messageHeaderIn.hdr.dataLength == HostNameLength)
			{
				messageHeaderIn.hdr.param32 = hspi.transfer32(ResponseEmpty);
				hspi.transferDwords(nullptr, transferBuffer, NumDwords(HostNameLength));
				memcpy(webHostName, transferBuffer, HostNameLength);
				webHostName[HostNameLength] = 0;			// ensure null terminator
#if LWIP_VERSION_MAJOR == 2
				netbiosns_set_name(webHostName);
#endif
			}
			else
			{
				SendResponse(ResponseBadDataLength);
			}
			break;

		case NetworkCommand::networkGetLastError:
			if (lastError == nullptr)
			{
				SendResponse(0);
			}
			else
			{
				const size_t len = strlen(lastError) + 1;
				if (dataBufferAvailable >= len)
				{
					strcpy(reinterpret_cast<char*>(transferBuffer), lastError);		// copy to 32-bit aligned buffer
					SendResponse(len);
				}
				else
				{
					SendResponse(ResponseBufferTooSmall);
				}
				lastError = nullptr;
			}
			lastReportedState = currentState;
			break;

		case NetworkCommand::networkListen:				// listen for incoming connections
			if (messageHeaderIn.hdr.dataLength == sizeof(ListenOrConnectData))
			{
				messageHeaderIn.hdr.param32 = hspi.transfer32(ResponseEmpty);
				ListenOrConnectData lcData;
				hspi.transferDwords(nullptr, reinterpret_cast<uint32_t*>(&lcData), NumDwords(sizeof(lcData)));
				const bool ok = Listener::Listen(lcData.remoteIp, lcData.port, lcData.protocol, lcData.maxConnections);
				if (ok)
				{
					if (lcData.protocol < 3)			// if it's FTP, HTTP or Telnet protocol
					{
						RebuildServices();				// update the MDNS services
					}
					debugPrintf("%sListening on port %u\n", (lcData.maxConnections == 0) ? "Stopped " : "", lcData.port);
				}
				else
				{
					lastError = "Listen failed";
					debugPrint("Listen failed\n");
				}
			}
			break;

#if 0	// We don't use the following command, instead we use networkListen with maxConnections = 0
		case NetworkCommand::unused_networkStopListening:
			if (messageHeaderIn.hdr.dataLength == sizeof(ListenOrConnectData))
			{
				messageHeaderIn.hdr.param32 = hspi.transfer32(ResponseEmpty);
				ListenOrConnectData lcData;
				hspi.transferDwords(nullptr, reinterpret_cast<uint32_t*>(&lcData), NumDwords(sizeof(lcData)));
				Listener::StopListening(lcData.port);
				RebuildServices();						// update the MDNS services
				debugPrintf("Stopped listening on port %u\n", lcData.port);
			}
			break;
#endif

		case NetworkCommand::connAbort:					// terminate a socket rudely
			if (ValidSocketNumber(messageHeaderIn.hdr.socketNumber))
			{
				messageHeaderIn.hdr.param32 = hspi.transfer32(ResponseEmpty);
				Connection::Get(messageHeaderIn.hdr.socketNumber).Terminate(true);
			}
			else
			{
				messageHeaderIn.hdr.param32 = hspi.transfer32(ResponseBadParameter);
			}
			break;

		case NetworkCommand::connClose:					// close a socket gracefully
			if (ValidSocketNumber(messageHeaderIn.hdr.socketNumber))
			{
				messageHeaderIn.hdr.param32 = hspi.transfer32(ResponseEmpty);
				Connection::Get(messageHeaderIn.hdr.socketNumber).Close();
			}
			else
			{
				messageHeaderIn.hdr.param32 = hspi.transfer32(ResponseBadParameter);
			}
			break;

		case NetworkCommand::connRead:					// read data from a connection
			if (ValidSocketNumber(messageHeaderIn.hdr.socketNumber))
			{
				Connection& conn = Connection::Get(messageHeaderIn.hdr.socketNumber);
				const size_t amount = conn.Read(reinterpret_cast<uint8_t *>(transferBuffer), std::min<size_t>(messageHeaderIn.hdr.dataBufferAvailable, MaxDataLength));
				messageHeaderIn.hdr.param32 = hspi.transfer32(amount);
				hspi.transferDwords(transferBuffer, nullptr, NumDwords(amount));
			}
			else
			{
				messageHeaderIn.hdr.param32 = hspi.transfer32(ResponseBadParameter);
			}
			break;

		case NetworkCommand::connWrite:					// write data to a connection
			if (ValidSocketNumber(messageHeaderIn.hdr.socketNumber))
			{
				Connection& conn = Connection::Get(messageHeaderIn.hdr.socketNumber);
				const size_t requestedlength = messageHeaderIn.hdr.dataLength;
				const size_t acceptedLength = std::min<size_t>(conn.CanWrite(), std::min<size_t>(requestedlength, MaxDataLength));
				const bool closeAfterSending = (acceptedLength == requestedlength) && (messageHeaderIn.hdr.flags & MessageHeaderSamToEsp::FlagCloseAfterWrite) != 0;
				const bool push = (acceptedLength == requestedlength) && (messageHeaderIn.hdr.flags & MessageHeaderSamToEsp::FlagPush) != 0;
				messageHeaderIn.hdr.param32 = hspi.transfer32(acceptedLength);
				hspi.transferDwords(nullptr, transferBuffer, NumDwords(acceptedLength));
				const size_t written = conn.Write(reinterpret_cast<uint8_t *>(transferBuffer), acceptedLength, push, closeAfterSending);
				if (written != acceptedLength)
				{
					lastError = "incomplete write";
				}
			}
			else
			{
				messageHeaderIn.hdr.param32 = hspi.transfer32(ResponseBadParameter);
			}
			break;

		case NetworkCommand::connGetStatus:				// get the status of a socket, and summary status for all sockets
			if (ValidSocketNumber(messageHeaderIn.hdr.socketNumber))
			{
				messageHeaderIn.hdr.param32 = hspi.transfer32(sizeof(ConnStatusResponse));
				Connection& conn = Connection::Get(messageHeaderIn.hdr.socketNumber);
				ConnStatusResponse resp;
				conn.GetStatus(resp);
				Connection::GetSummarySocketStatus(resp.connectedSockets, resp.otherEndClosedSockets);
				hspi.transferDwords(reinterpret_cast<const uint32_t *>(&resp), nullptr, NumDwords(sizeof(resp)));
			}
			else
			{
				messageHeaderIn.hdr.param32 = hspi.transfer32(ResponseBadParameter);
			}
			break;

		case NetworkCommand::diagnostics:					// print some debug info over the UART line
			SendResponse(ResponseEmpty);
			deferCommand = true;							// we need to send the diagnostics after we have sent the response, so the SAM is ready to receive them
			break;

		case NetworkCommand::networkSetTxPower:
			{
				const uint8_t txPower = messageHeaderIn.hdr.flags;
				if (txPower <= 82)
				{
					system_phy_set_max_tpw(txPower);
					SendResponse(ResponseEmpty);
				}
				else
				{
					SendResponse(ResponseBadParameter);
				}
			}
			break;

		case NetworkCommand::networkSetClockControl:
			messageHeaderIn.hdr.param32 = hspi.transfer32(ResponseEmpty);
			deferCommand = true;
			break;

		case NetworkCommand::connCreate:					// create a connection
			// Not implemented yet
		default:
			SendResponse(ResponseUnknownCommand);
			break;
		}
	}

	digitalWrite(SamSSPin, HIGH);     						// de-assert CS to SAM to end the transaction and tell SAM the transfer is complete
	hspi.endTransaction();

	// If we deferred the command until after sending the response (e.g. because it may take some time to execute), complete it now
	if (deferCommand)
	{
		// The following functions must set up lastError if an error occurs
		lastError = nullptr;								// assume no error
		switch (messageHeaderIn.hdr.command)
		{
		case NetworkCommand::networkStartClient:			// connect to an access point
			if (messageHeaderIn.hdr.dataLength == 0 || reinterpret_cast<const char*>(transferBuffer)[0] == 0)
			{
				StartClient(nullptr);						// connect to strongest known access point
			}
			else
			{
				StartClient(reinterpret_cast<const char*>(transferBuffer));		// connect to specified access point
			}
			break;

		case NetworkCommand::networkStartAccessPoint:		// run as an access point
			StartAccessPoint();
			break;

		case NetworkCommand::networkStop:					// disconnect from an access point, or close down our own access point
			Connection::TerminateAll();						// terminate all connections
			Listener::StopListening(0);						// stop listening on all ports
			RebuildServices();								// remove the MDNS services
			switch (currentState)
			{
			case WiFiState::connected:
			case WiFiState::connecting:
			case WiFiState::reconnecting:
#if LWIP_VERSION_MAJOR == 2
				RemoveMdnsServices();
#endif
#if LWIP_VERSION_MAJOR == 1
				MDNS.deleteServices();
#endif
				delay(20);									// try to give lwip time to recover from stopping everything
				WiFi.disconnect(true);
				break;

			case WiFiState::runningAsAccessPoint:
				dns.stop();
				delay(20);									// try to give lwip time to recover from stopping everything
				WiFi.softAPdisconnect(true);
				break;

			default:
				break;
			}
			delay(100);
			currentState = WiFiState::idle;
			digitalWrite(ONBOARD_LED, !ONBOARD_LED_ON);
			break;

		case NetworkCommand::networkFactoryReset:			// clear remembered list, reset factory defaults
			FactoryReset();
			break;

		case NetworkCommand::diagnostics:
			Connection::ReportConnections();
			delay(20);										// give the Duet main processor time to digest that
			stats_display();
			break;

		case NetworkCommand::networkSetClockControl:
			hspi.setClockDivider(messageHeaderIn.hdr.param32);
			break;

		default:
			lastError = "bad deferred command";
			break;
		}
	}
}

void ICACHE_RAM_ATTR TransferReadyIsr()
{
	transferReadyChanged = true;
}

void setup()
{
	// Enable serial port for debugging
	Serial.begin(WiFiBaudRate);
	Serial.setDebugOutput(true);

	// Turn off LED
	pinMode(ONBOARD_LED, OUTPUT);
	digitalWrite(ONBOARD_LED, !ONBOARD_LED_ON);

	WiFi.mode(WIFI_OFF);
	WiFi.persistent(false);

	// If we started abnormally, send the exception details to the serial port
	const rst_info *resetInfo = system_get_rst_info();
	if (resetInfo->reason != 0 && resetInfo->reason != 6)	// if not power up or external reset
	{
		debugPrintfAlways("Restart after exception:%d flag:%d epc1:0x%08x epc2:0x%08x epc3:0x%08x excvaddr:0x%08x depc:0x%08x\n",
			resetInfo->exccause, resetInfo->reason, resetInfo->epc1, resetInfo->epc2, resetInfo->epc3, resetInfo->excvaddr, resetInfo->depc);
	}

	// Reserve some flash space for use as EEPROM. The maximum EEPROM supported by the core is SPI_FLASH_SEC_SIZE (4Kb).
	const size_t eepromSizeNeeded = (MaxRememberedNetworks + 1) * sizeof(WirelessConfigurationData);
	static_assert(eepromSizeNeeded <= SPI_FLASH_SEC_SIZE, "Insufficient EEPROM");
	EEPROM.begin(eepromSizeNeeded);
	// Set up the SPI subsystem
    pinMode(SamTfrReadyPin, INPUT);
    pinMode(EspReqTransferPin, OUTPUT);
    digitalWrite(EspReqTransferPin, LOW);				// not ready to transfer data yet
    pinMode(SamSSPin, OUTPUT);
    digitalWrite(SamSSPin, HIGH);

    // Set up the fast SPI channel
    hspi.InitMaster(SPI_MODE1, defaultClockControl, true);

    Connection::Init();
    Listener::Init();
#if LWIP_VERSION_MAJOR == 2
    mdns_resp_init();
	for (struct netif *item = netif_list; item != nullptr; item = item->next)
	{
		mdns_resp_add_netif(item, webHostName, MdnsTtl);
	}
    netbiosns_init();
#else
    netbios_init();
#endif
    lastError = nullptr;
    debugPrint("Init completed\n");
	attachInterrupt(SamTfrReadyPin, TransferReadyIsr, CHANGE);
	whenLastTransactionFinished = millis();
	lastStatusReportTime = millis();
	digitalWrite(EspReqTransferPin, HIGH);				// tell the SAM we are ready to receive a command
}

void loop()
{
	digitalWrite(EspReqTransferPin, HIGH);				// tell the SAM we are ready to receive a command
	system_soft_wdt_feed();								// kick the watchdog

	if (   (lastError != prevLastError || connectErrorChanged || currentState != prevCurrentState)
		|| ((lastError != nullptr || currentState != lastReportedState) && millis() - lastStatusReportTime > StatusReportMillis)
	   )
	{
		delayMicroseconds(2);							// make sure the pin stays high for long enough for the SAM to see it
		digitalWrite(EspReqTransferPin, LOW);			// force a low to high transition to signal that an error message is available
		delayMicroseconds(2);							// make sure it is low enough to create an interrupt when it goes high
		digitalWrite(EspReqTransferPin, HIGH);			// tell the SAM we are ready to receive a command
		prevLastError = lastError;
		prevCurrentState = currentState;
		connectErrorChanged = false;
		lastStatusReportTime = millis();
	}
	// See whether there is a request from the SAM.
	// Duet WiFi 1.04 and earlier have hardware to ensure that TransferReady goes low when a transaction starts.
	// Duet 3 Mini doesn't, so we need to see TransferReady go low and then high again. In case that happens so fast that we dn't get the interrupt, we have a timeout.
	if (digitalRead(SamTfrReadyPin) == HIGH)
	{
		// now check to see if we have seen a change in the trasnfer ready pin. Note that we check again the state of the pin
		// just in case it has gone low just after the above check. Not doing this will result in spurious read operations.
		if ((transferReadyChanged && digitalRead(SamTfrReadyPin) == HIGH) || (millis() - whenLastTransactionFinished > TransferReadyTimeout))
		{
			transferReadyChanged = false;
			ProcessRequest();
			whenLastTransactionFinished = millis();
		}
	}
	else
		transferReadyChanged = true;

	ConnectPoll();
	Connection::PollOne();

	if (currentState == WiFiState::runningAsAccessPoint)
	{
		dns.processNextRequest();
	}
	else if (	(currentState == WiFiState::autoReconnecting ||
				 currentState == WiFiState::connecting ||
				 currentState == WiFiState::reconnecting) &&
				(millis() - lastBlinkTime > ONBOARD_LED_BLINK_INTERVAL))
	{
		lastBlinkTime = millis();
		digitalWrite(ONBOARD_LED, !digitalRead(ONBOARD_LED));
	}
}

// End
