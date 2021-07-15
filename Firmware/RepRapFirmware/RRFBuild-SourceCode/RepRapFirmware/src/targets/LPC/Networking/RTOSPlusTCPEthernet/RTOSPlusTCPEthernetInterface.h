
#ifndef RTOSPLUSTCPETHERNET_H
#define RTOSPLUSTCPETHERNET_H

#include "Networking/NetworkInterface.h"
#include "NetworkDefs.h"
#include "MessageType.h"

#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"
#include "FreeRTOS_DHCP.h"
#include "FreeRTOS_DNS.h"

class NetworkResponder;
class HttpResponder;
class FtpResponder;
class TelnetResponder;
class RTOSPlusTCPEthernetSocket;


#if LPC17xx
const size_t NumHttpSockets = 2;				// sockets 0-3 are for HTTP
#else
const size_t NumHttpSockets = 4;                // sockets 0-3 are for HTTP
#endif
const SocketNumber FtpSocketNumber = 4;
const SocketNumber FtpDataSocketNumber = 5;		// TODO can we allocate this dynamically when required, to allow more http sockets most of the time?
const SocketNumber TelnetSocketNumber = 6;
const SocketNumber DhcpSocketNumber = 7;		// TODO can we allocate this dynamically when required, to allow more http sockets most of the time?

const size_t NumRTOSPlusTCPEthernetTcpSockets = NumHttpSockets
#if ENABLE_TELNET
                    + 1
#endif
#if ENABLE_FTP
                    + 2 //ftp + ftpdata ports
#endif
; //end of NumRTOSPlusTCPEthernetTcpSockets



class Platform;

// The main network class that drives the network.
class RTOSPlusTCPEthernetInterface : public NetworkInterface
{
public:
	RTOSPlusTCPEthernetInterface(Platform& p) noexcept;

	void Init() noexcept override;
	void Activate() noexcept override;
	void Exit() noexcept override;
	void Spin() noexcept override;
	void Diagnostics(MessageType mtype) noexcept override;

	GCodeResult EnableInterface(int mode, const StringRef& ssid, const StringRef& reply) noexcept override;			// enable or disable the network
	GCodeResult EnableProtocol(NetworkProtocol protocol, int port, int secure, const StringRef& reply) noexcept override;
	GCodeResult DisableProtocol(NetworkProtocol protocol, const StringRef& reply) noexcept override;
	GCodeResult ReportProtocols(const StringRef& reply) const noexcept override;

	GCodeResult GetNetworkState(const StringRef& reply) noexcept override;
	int EnableState() const noexcept override;
	bool IsWiFiInterface() const noexcept override { return false; }

	void UpdateHostname(const char *name) noexcept override { }
	//const uint8_t *GetIPAddress() const override { return ipAddress; }
    IPAddress GetIPAddress() const noexcept override { return ipAddress; }
    void SetIPAddress(IPAddress p_ip, IPAddress p_netmask, IPAddress p_gateway) noexcept override;

    GCodeResult SetMacAddress(const MacAddress& mac, const StringRef& reply) noexcept override;
    const MacAddress& GetMacAddress() const noexcept override { return macAddress; }

	void OpenDataPort(TcpPort port) noexcept override;
	void TerminateDataPort() noexcept override;
    
protected:
    DECLARE_OBJECT_MODEL

    
private:
	enum class NetworkState
	{
		disabled,					// Network disabled
		enabled,					// Network enabled but not started yet
		establishingLink,			// starting up, waiting for link
		obtainingIP,				// link established, waiting for DHCP
		connected,					// just established a connection
		active						// network running
	};

	void Start() noexcept;
	void Stop() noexcept;
	void InitSockets() noexcept;
	void TerminateSockets() noexcept;

	void StartProtocol(NetworkProtocol protocol) noexcept
	pre(protocol < NumProtocols);

	void ShutdownProtocol(NetworkProtocol protocol) noexcept
	pre(protocol < NumProtocols);

	void ReportOneProtocol(NetworkProtocol protocol, const StringRef& reply) const  noexcept
	pre(protocol < NumProtocols);

	void SetIPAddress(const uint8_t p_ipAddress[], const uint8_t p_netmask[], const uint8_t p_gateway[]) noexcept;

    void ProcessIPApplication( eIPCallbackEvent_t eNetworkEvent )  noexcept;
    eDHCPCallbackAnswer_t ProcessDHCPHook( eDHCPCallbackPhase_t eDHCPPhase, uint32_t ulIPAddress ) noexcept;
    const char *ProcessApplicationHostnameHook() noexcept;
    BaseType_t ProcessDNSQueryHook(const char *pcName) noexcept;
    
    friend void vApplicationIPNetworkEventHook( eIPCallbackEvent_t eNetworkEvent );
    friend eDHCPCallbackAnswer_t xApplicationDHCPHook( eDHCPCallbackPhase_t eDHCPPhase, uint32_t ulIPAddress );
    friend const char *pcApplicationHostnameHook( void );
    friend BaseType_t xApplicationDNSQueryHook( const char *pcName );
    
    Platform& platform;
    uint32_t lastTickMillis;

    RTOSPlusTCPEthernetSocket *sockets[NumRTOSPlusTCPEthernetTcpSockets];
    size_t nextSocketToPoll;                        // next TCP socket number to poll for read/write operations

    TcpPort portNumbers[NumProtocols];                    // port number used for each protocol
    bool protocolEnabled[NumProtocols];                // whether each protocol is enabled

	NetworkState state;
	bool activated;
    bool initialised;
    bool linkUp;
	bool usingDHCP;

    IPAddress ipAddress;
    IPAddress netmask;
    IPAddress gateway;
    MacAddress macAddress;
};

#endif //RTOSPLUSTCPETHERNET_H
