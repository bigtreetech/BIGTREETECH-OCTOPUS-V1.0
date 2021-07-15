/*
 * MessageFormats.h
 *
 *  Created on: 2 Apr 2017
 *      Author: David
 */

#ifndef SRC_MESSAGEFORMATS_H_
#define SRC_MESSAGEFORMATS_H_

// Message formats exchanged over the SPI link between the SAM4E processor and the ESP8266 on the Duet WiFi
// The ESP is the SPI master because it doesn't have a DMA facility. In practice, the ESP initiates an SPI transaction only when the SAM asks it to.
// The SAM and the ESP first exchange headers. Then the ESP looks at the header, decodes the command from the SAM, and exchanges a response dword.
// If the ESP accepted the command, it then does an appropriate data transfer.
// The SAM uses DMA to transfer the whole message, so it can only transfer the entire message.

// First the message header formats
const size_t SsidLength = 32;
const size_t PasswordLength = 64;
const size_t HostNameLength = 64;
const size_t MaxDataLength = 2048;						// maximum length of the data part of an SPI exchange
#if defined(LPCRRF) || defined(__LPC17xx__)
#if defined(EXTENDED_LISTEN)
const size_t MaxConnections = 8;						// the number of simultaneous connections we support
const size_t MaxPublicConnections = 2;					// the number of simultaneous connections we make availble to RRF
#else
const size_t MaxConnections = 2;						// the number of simultaneous connections we support
#endif
#else
const size_t MaxConnections = 8;						// the number of simultaneous connections we support
#endif

#if defined(EXTENDED_LISTEN)
const unsigned int NumWiFiTcpSockets = MaxPublicConnections;	// the number of concurrent TCP/IP connections supported
#else
const unsigned int NumWiFiTcpSockets = MaxConnections;	// the number of concurrent TCP/IP connections supported
#endif

static_assert(MaxDataLength % sizeof(uint32_t) == 0, "MaxDataLength must be a whole number of dwords");

const uint8_t MyFormatVersion = 0x3E;
const uint8_t InvalidFormatVersion = 0xC9;				// must be different from any format version we have ever used

const uint32_t AnyIp = 0;

// Return a size rounded up to to a whole number of dwords
static inline constexpr size_t NumDwords(size_t arg)
{
	return (arg + sizeof(uint32_t) - 1)/sizeof(uint32_t);
}

// Commands from the SAM to the ESP
enum class NetworkCommand : uint8_t
{
	nullCommand = 0,			// no command being sent
	connAbort,					// terminate a connection rudely
	connClose,					// close a connection gracefully
	connCreate,					// create a new connection
	connRead,					// read data from a connection
	connWrite,					// write data to a connection
	connGetStatus,				// get the status of a connection

	networkListen,				// listen for incoming connections to a port, or stop listening
	unused_networkStopListening, // stop listening for connections to a port

	networkGetStatus,			// get the network connection status
	networkAddSsid,				// add to our known access point list
	networkDeleteSsid,			// delete a network from our access point list
	networkListSsids_deprecated, // list the access points we know about - DEPRECATED
	networkConfigureAccessPoint, // configure our own access point details
	networkStartClient,			// connect to an access point
	networkStartAccessPoint,	// run as an access point
	networkStop,				// disconnect from an access point, or close down our own access point
	networkFactoryReset,		// delete all SSID/password info and reset factory settings in EEPROM
	networkSetHostName,			// set the host name
	networkGetLastError,		// get the result of the last deferred command we sent

	diagnostics,				// print LwIP stats and possibly more values over the UART line
	networkRetrieveSsidData,	// retrieve all the SSID data we have except the passwords

	// Added at version 1.24
	networkSetTxPower,			// set transmitter power in units of 0.25db, max 82 = 20.5db
	networkSetClockControl		// set clock control word - only provided because the ESP8266 documentation is not only crap but seriously wrong
};

// Message header sent from the SAM to the ESP
struct MessageHeaderSamToEsp
{
	uint8_t formatVersion;
	NetworkCommand command;		// see above
	uint8_t socketNumber;		// socket number if it is a socket command, unused if it is a network command
	uint8_t flags;				// 8-bit parameter specific to some commands e.g. close-after-write

	uint16_t dataLength;		// how long the data part of the request is
	uint16_t dataBufferAvailable;	// how much data the SAM can receive
	uint32_t param32;			// this gets sent while the ESP is sending its response

	static const uint8_t FlagCloseAfterWrite = 0x01;
	static const uint8_t FlagPush = 0x02;
};

const size_t headerDwords = NumDwords(sizeof(MessageHeaderSamToEsp));

// Message data sent from SAM to ESP for a connCreate, networkListen or networkStopListening command
// For a networkStopListening command, only the port number is used
struct ListenOrConnectData
{
	uint32_t remoteIp;			// IP address to listen for, 0 means any
	uint8_t protocol;			// Protocol for this connection (0 = HTTP, 1 = FTP, 2 = TELNET, 3 = FTP-DATA) - also see NetworkDefs.h
	uint8_t dummy;				// To ensure alignment is the same on ESP8266 and SAM
	uint16_t port;				// port number to listen on
	uint16_t maxConnections;	// maximum number of connections to accept if listening
};

const uint8_t protocolHTTP = 0;
const uint8_t protocolFTP = 1;
const uint8_t protocolTelnet = 2;
const uint8_t protocolFtpData = 3;

// Message data sent from SAM to ESP to add an SSID or set the access point configuration. This is also the format of a remembered SSID entry.
struct WirelessConfigurationData
{
	uint32_t ip;					// IP address. 0 means use DHCP (only valid in client mode)
	uint32_t gateway;
	uint32_t netmask;
	uint8_t channel;				// channel number to use if running as an access point, 0 means auto
	int8_t security;				// what type of network security if running in access point mode
	int8_t dummy[2];
	char ssid[SsidLength];			// the SSID
	char password[PasswordLength];	// the WiFi password
};

const size_t ReducedWirelessConfigurationDataSize = offsetof(WirelessConfigurationData, password);

struct NetworkStartClientData
{
	char ssid[SsidLength];			// name of the SSID to connect to, or empty string for auto
};

// Codes to represent the state of the network connection
enum class WiFiState : uint8_t
{
	disabled = 0,					// WiFi module held in reset state (not used by ESP code)
	idle = 1,						// neither connected nor running as an access point
	runningAsAccessPoint = 2,
	connecting = 3,
	connected = 4,
	autoReconnecting = 5,
	reconnecting = 6
};

// Message header sent from the ESP to the SAM
// Note that the last word is sent concurrently with the response from the ESP. This means that it doesn't get seen by the ESP before it decides what response to send.
struct MessageHeaderEspToSam
{
	uint8_t formatVersion;
	WiFiState state;
	uint8_t dummy[2];
	uint32_t dummy32;
	int32_t response;				// response length if positive, or error code if negative
};

static_assert(sizeof(MessageHeaderSamToEsp) == sizeof(MessageHeaderEspToSam), "Message header sizes don't match");

// Now the message data formats

struct NetworkStatusResponse
{
	// No need to include the network state here because that is included in the header
	uint32_t ipAddress;				// our own IP address
	uint32_t freeHeap;				// free heap memory in bytes
	uint32_t resetReason;
	uint32_t flashSize;				// flash size in bytes
	int8_t rssi;					// received signal strength (if operating as a wifi client)
	uint8_t numClients;				// the number of connected clients (if operating as an AP)
	uint8_t sleepMode : 2,			// the wifi sleep mode, 0 = unknown, 1 = none, 2 = light, 3 = modem
			phyMode: 2,				// the connection mode to the AP, 1 = B, 2 = G, 3 = N
			zero1 : 4;				// unused, set to zero
	uint8_t zero2;					// unused, set to zero
	uint16_t vcc;					// ESP Vcc voltage according to its ADC
    uint8_t macAddress[6];			// MAC address
	char versionText[16];			// WiFi firmware version
	char ssid[SsidLength];			// SSID of the router we are connected to, or our own SSDI
	char hostName[64];				// name of the access point we are connected to, or our own access point name
	uint32_t clockReg;				// the SPI clock register
};
//		4 bytes of IP address
//		4 bytes of free heap
//		4 bytes of reset reason
//		4 bytes of flash chip size
//		4 bytes of RSSI (added for info version 2)
//		2 bytes of ESP8266 Vcc according to its ADC
//		16 chars of WiFi firmware version
//		32 chars of ssid (either ssid we are connected to or our own AP name), null terminated
//		64 chars of host name, null terminated

// State of a connection
// The table of state names in Connection.cpp must be kept in step with this
enum class ConnState : uint8_t
{
	free = 0,			// not active
	connecting,			// socket is trying to connect
	connected,			// socket is connected
	otherEndClosed,		// the remote end has closed the connection
	aborted,			// an error has occurred

	// The remaining states are not of interest to clients
	closePending,		// close this socket when sending is complete
	closeReady			// other end has closed and we were already closePending
};

// Connection status response. This includes 32-bit fields, so it will be 32-bit aligned.
struct ConnStatusResponse
{
	ConnState state;
	uint8_t socketNumber;
	uint8_t dummy[2];
	uint16_t localPort;
	uint16_t remotePort;
	uint32_t remoteIp;
	uint16_t bytesAvailable;
	uint16_t writeBufferSpace;
	uint16_t connectedSockets;			// bitmap of sockets that are in state 'connected'
	uint16_t otherEndClosedSockets;		// bitmap of sockets that are in state 'otherEndClosed'
};

// Response error codes. A non-negative code is the number of bytes of returned data.
const int32_t ResponseEmpty = 0;				// used when there is no error and no data to return
const int32_t ResponseUnknownCommand = -1;
const int32_t ResponseBadRequestFormatVersion = -2;
const int32_t ResponseTooManySsids = -3;
const int32_t ResponseWrongState = -4;
const int32_t ResponseBadDataLength = -5;
const int32_t ResponseNetworkDisabled = -6;		// this is not returned by the ESP, it indicates that the SAM hasn't enabled the ESP yet
const int32_t ResponseTimeout = -7;
const int32_t ResponseBusy = -8;
const int32_t ResponseBufferTooSmall = -9;
const int32_t ResponseBadReplyFormatVersion = -10;
const int32_t ResponseBadParameter = -11;
const int32_t ResponseUnknownError = -12;

const size_t MaxRememberedNetworks = 20;
static_assert((MaxRememberedNetworks + 1) * ReducedWirelessConfigurationDataSize <= MaxDataLength, "Too many remembered networks");

const unsigned int WiFiBaudRate = 74880;		// this is the default baud rate for the ESP8266

#endif /* SRC_MESSAGEFORMATS_H_ */
