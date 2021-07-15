#ifndef NETWORK_H
#define NETWORK_H

#include "RepRapFirmware.h"
#include "MessageType.h"
#include "GCodes/GCodeResult.h"
#include "General/IPAddress.h"
#include <ObjectModel/ObjectModel.h>
#include "Networking/NetworkDefs.h"
//forward declarations
class NetworkInterface;
const size_t NumNetworkInterfaces = 0;



// The main network class that drives the network.
class Network INHERIT_OBJECT_MODEL
{
public:
    Network(Platform& p) noexcept { };
    void Init() const noexcept { };
    void Activate() const noexcept  { };
    void Exit() const noexcept { };
    void Spin(bool full) const noexcept { };
    void Interrupt() const noexcept { };
    void Diagnostics(MessageType mtype) const noexcept { };
    bool IsWiFiInterface(unsigned int interface) const noexcept { return false; };

    GCodeResult EnableInterface(unsigned int interface, int mode, const StringRef& ssid, const StringRef& reply) noexcept;
    GCodeResult EnableProtocol(unsigned int interface, NetworkProtocol protocol, int port, int secure, const StringRef& reply) noexcept;
    GCodeResult DisableProtocol(unsigned int interface, NetworkProtocol protocol, const StringRef& reply) noexcept;
    GCodeResult ReportProtocols(unsigned int interface, const StringRef& reply) const noexcept;

    // Global settings
    GCodeResult GetNetworkState(unsigned int interface, const StringRef& reply) noexcept;
    int EnableState(unsigned int interface) const noexcept;

    void SetEthernetIPAddress(IPAddress p_ipAddress, IPAddress p_netmask, IPAddress p_gateway) noexcept { };
    IPAddress GetIPAddress(unsigned int interface) const noexcept { return DefaultIpAddress; };
    const char *GetHostname() const noexcept { return ""; }
    void SetHostname(const char *name) noexcept { };
    GCodeResult SetMacAddress(unsigned int interface, const MacAddress& mac, const StringRef& reply) noexcept { return GCodeResult::ok;};
    const MacAddress& GetMacAddress(unsigned int interface) const noexcept { return macAddress; };

    

	void HandleHttpGCodeReply(const char *msg) noexcept { }
	void HandleTelnetGCodeReply(const char *msg) noexcept { }
	void HandleHttpGCodeReply(OutputBuffer *buf) noexcept;
	void HandleTelnetGCodeReply(OutputBuffer *buf) noexcept;
	uint32_t GetHttpReplySeq() noexcept { return 0; }
    
protected:
    DECLARE_OBJECT_MODEL
    OBJECT_MODEL_ARRAY(interfaces)

  
private:
    NetworkInterface *interfaces[NumNetworkInterfaces];
    MacAddress macAddress;

};

#endif
