/*
 * RTOSPlusTCPEthernetInterface.cpp
 *
 * SD: RTOSPlusTCPEthernet adapted from W5500Interface class to work with FreeRTOS+TCP
 
 */

#include "RTOSPlusTCPEthernetInterface.h"
#include "RTOSPlusTCPEthernetSocket.h"
#include "RTOSPlusTCPEthernetServerSocket.h"
#include "NetworkBuffer.h"
#include "Platform.h"
#include "RepRap.h"
#include "HttpResponder.h"
#include "FtpResponder.h"
#include "TelnetResponder.h"
#include "General/IP4String.h"

#include <FreeRTOS.h>
#include "task.h"
#include "FreeRTOS_IP.h"
#include "FreeRTOS_IP_Private.h"
#include "NetworkBufferManagement.h"

#include "FreeRTOS_Sockets.h"
#include "FreeRTOS_DHCP.h"
#include "RTOSIface/RTOSIface.h"
#include "TaskPriorities.h"

#include "lpc_phy.h"

constexpr size_t TcpPlusStackWords = 100; // needs to be around 240 when debugging with debugPrintf
static Task<TcpPlusStackWords> tcpPlusTask;

constexpr size_t EmacStackWords = 65;// needs to be around 170 when debugging with debugPrintf
static Task<EmacStackWords> emacTask;

static uint32_t lastIPTaskTime = 0;
RTOSPlusTCPEthernetInterface *rtosTCPEtherInterfacePtr; //pointer to the clas instance so we can call from the "c" hooks



RTOSPlusTCPEthernetInterface::RTOSPlusTCPEthernetInterface(Platform& p) noexcept
: platform(p), lastTickMillis(0), state(NetworkState::disabled), activated(false), initialised(false), linkUp(false), usingDHCP(false)
{
    //setup our pointer to access our class methods from the +TCP "C" callbacks
    rtosTCPEtherInterfacePtr = this;
        
	// Create the sockets
	for (RTOSPlusTCPEthernetSocket*& skt : sockets)
	{
		skt = new RTOSPlusTCPEthernetSocket(this);
	}

	for (size_t i = 0; i < NumProtocols; ++i)
	{
		portNumbers[i] = DefaultPortNumbers[i];
		protocolEnabled[i] = (i == HttpProtocol);
	}
}


#if SUPPORT_OBJECT_MODEL

// Object model table and functions
// Note: if using GCC version 7.3.1 20180622 and lambda functions are used in this table, you must compile this file with option -std=gnu++17.
// Otherwise the table will be allocated in RAM instead of flash, which wastes too much RAM.

// Macro to build a standard lambda function that includes the necessary type conversions
#define OBJECT_MODEL_FUNC(_ret) OBJECT_MODEL_FUNC_BODY(RTOSPlusTCPEthernetInterface, _ret)

constexpr ObjectModelTableEntry RTOSPlusTCPEthernetInterface::objectModelTable[] =
{
    // These entries must be in alphabetical order
    { "actualIP",           OBJECT_MODEL_FUNC(self->ipAddress),     ObjectModelEntryFlags::none },
    { "gateway",            OBJECT_MODEL_FUNC(self->gateway),       ObjectModelEntryFlags::none },
    { "mac",                OBJECT_MODEL_FUNC(self->macAddress),    ObjectModelEntryFlags::none },
    { "subnet",             OBJECT_MODEL_FUNC(self->netmask),       ObjectModelEntryFlags::none },
    { "type",               OBJECT_MODEL_FUNC_NOSELF("ethernet"),   ObjectModelEntryFlags::none },
};

constexpr uint8_t RTOSPlusTCPEthernetInterface::objectModelTableDescriptor[] = { 1, 5 };

DEFINE_GET_OBJECT_MODEL_TABLE(RTOSPlusTCPEthernetInterface)

#endif

void RTOSPlusTCPEthernetInterface::Init() noexcept
{
	interfaceMutex.Create("RTOSPlusTCPEthernet");
	SetIPAddress(DefaultIpAddress, DefaultNetMask, DefaultGateway);
    macAddress = platform.GetDefaultMacAddress();
}

GCodeResult RTOSPlusTCPEthernetInterface::EnableProtocol(NetworkProtocol protocol, int port, int secure, const StringRef& reply) noexcept
{
	if (secure != 0 && secure != -1)
	{
		reply.copy("this firmware does not support TLS");
		return GCodeResult::error;
	}

	if (protocol < NumProtocols)
	{
		MutexLocker lock(interfaceMutex);

		const TcpPort portToUse = (port < 0) ? DefaultPortNumbers[protocol] : port;
		if (portToUse != portNumbers[protocol] && state == NetworkState::active)
		{
			// We need to shut down and restart the protocol if it is active because the port number has changed
			ShutdownProtocol(protocol);
			protocolEnabled[protocol] = false;
		}
		portNumbers[protocol] = portToUse;
		if (!protocolEnabled[protocol])
		{
			protocolEnabled[protocol] = true;
			if (state == NetworkState::active)
			{
				StartProtocol(protocol);
			}
		}
		ReportOneProtocol(protocol, reply);
		return GCodeResult::ok;
	}

	reply.copy("Invalid protocol parameter");
	return GCodeResult::error;
}

GCodeResult RTOSPlusTCPEthernetInterface::DisableProtocol(NetworkProtocol protocol, const StringRef& reply) noexcept
{
	if (protocol < NumProtocols)
	{
		MutexLocker lock(interfaceMutex);

		if (state == NetworkState::active)
		{
			ShutdownProtocol(protocol);
		}
		protocolEnabled[protocol] = false;
		ReportOneProtocol(protocol, reply);
		return GCodeResult::ok;
	}
	reply.copy("Invalid protocol parameter");
	return GCodeResult::error;
}

void RTOSPlusTCPEthernetInterface::StartProtocol(NetworkProtocol protocol) noexcept
{
	MutexLocker lock(interfaceMutex);
	switch(protocol)
	{
	case HttpProtocol:

		for (SocketNumber skt = 0; skt < NumHttpSockets; ++skt)
		{
			sockets[skt]->Init(skt, portNumbers[protocol], protocol);
		}
		break;

	case FtpProtocol:
#if ENABLE_FTP
		sockets[FtpSocketNumber]->Init(FtpSocketNumber, portNumbers[protocol], protocol);
#endif
		break;

	case TelnetProtocol:
#if ENABLE_TELNET
		sockets[TelnetSocketNumber]->Init(TelnetSocketNumber, portNumbers[protocol], protocol);
#endif
		break;

	default:
		break;
	}
}

void RTOSPlusTCPEthernetInterface::ShutdownProtocol(NetworkProtocol protocol) noexcept
{
	MutexLocker lock(interfaceMutex);

    switch(protocol)
	{
	case HttpProtocol:
		for (SocketNumber skt = 0; skt < NumHttpSockets; ++skt)
		{
			sockets[skt]->TerminateAndDisable();
		}
		break;

	case FtpProtocol:
#if ENABLE_FTP
		sockets[FtpSocketNumber]->TerminateAndDisable();
		sockets[FtpDataSocketNumber]->TerminateAndDisable();
#endif
		break;

	case TelnetProtocol:
#if ENABLE_TELNET
		sockets[TelnetSocketNumber]->TerminateAndDisable();
#endif
		break;

	default:
		break;
	}
}

// Report the protocols and ports in use
GCodeResult RTOSPlusTCPEthernetInterface::ReportProtocols(const StringRef& reply) const noexcept
{
    reply.Clear();
	for (size_t i = 0; i < NumProtocols; ++i)
	{
		if (i != 0)
		{
			reply.cat('\n');
		}
		ReportOneProtocol(i, reply);
	}
	return GCodeResult::ok;
}

void RTOSPlusTCPEthernetInterface::ReportOneProtocol(NetworkProtocol protocol, const StringRef& reply) const noexcept
{
	if (protocolEnabled[protocol])
	{
		reply.catf("%s is enabled on port %u", ProtocolNames[protocol], portNumbers[protocol]);
	}
	else
	{
		reply.catf("%s is disabled", ProtocolNames[protocol]);
	}
}

// This is called at the end of config.g processing.
// Start the network if it was enabled
void RTOSPlusTCPEthernetInterface::Activate() noexcept
{
	if (!activated)
	{
		activated = true;
        
        
		if (state == NetworkState::enabled)
		{
			Start();
            
		}
		else
		{
			platform.Message(NetworkInfoMessage, "Network disabled.\n");
		}
	}
}

void RTOSPlusTCPEthernetInterface::Exit() noexcept
{
	Stop();
}

// Get the network state into the reply buffer, returning true if there is some sort of error
GCodeResult RTOSPlusTCPEthernetInterface::GetNetworkState(const StringRef& reply) noexcept
{
	IPAddress config_ip = platform.GetIPAddress();
	const int enableState = EnableState();
	reply.printf("Network is %s, configured IP address: %s, actual IP address: %s",
			(enableState == 0) ? "disabled" : "enabled",
					IP4String(config_ip).c_str(), IP4String(ipAddress).c_str());
	return GCodeResult::ok;
}

// Update the MAC address
GCodeResult RTOSPlusTCPEthernetInterface::SetMacAddress(const MacAddress& mac, const StringRef& reply) noexcept
{
    macAddress = mac;
    return GCodeResult::ok;
}

// Start up the network
void RTOSPlusTCPEthernetInterface::Start() noexcept
{
	MutexLocker lock(interfaceMutex);
    
    if(initialised == true)
    {
        platform.Message(NetworkInfoMessage, "FreeRTOS+TCP already started. If changing IP or from static to dhpc then a reset is required.\n");
        FreeRTOS_NetworkDown(); //send a network down event
    }
    else
    {
        initialised = true;
        
        SetIPAddress(platform.GetIPAddress(), platform.NetMask(), platform.GateWay());

        uint8_t ip[4], nm[4], gw[4], dns[4];
        ipAddress.UnpackV4(ip);
        netmask.UnpackV4(nm);
        gateway.UnpackV4(gw);
        
        if(ipAddress.GetV4LittleEndian() == 0)
        {
            usingDHCP = true;
        }
        
        //FreeRTOS_IPInit should only be called once
        BaseType_t ret = FreeRTOS_IPInit( ip, nm, gw, dns, macAddress.bytes );
        if(ret == pdFALSE)
        {
            platform.Message(NetworkInfoMessage, "Failed to Init FreeRTOS+TCP\n");
            state = NetworkState::disabled;
            return;
        }

    }
    state = NetworkState::establishingLink;
}

// Stop the network
void RTOSPlusTCPEthernetInterface::Stop() noexcept
{
	if (state != NetworkState::disabled)
	{
		MutexLocker lock(interfaceMutex);
        TerminateSockets();
        state = NetworkState::disabled;
        //todo: how to stop FreeRTOS+TCP ? (perhaps suspend the IP-Task and EMAC task
	}
}

// Main spin loop. If 'full' is true then we are being called from the main spin loop. If false then we are being called during HSMCI idle time.
void RTOSPlusTCPEthernetInterface::Spin() noexcept
{
    switch(state)
	{
        case NetworkState::enabled:
        case NetworkState::disabled:
        case NetworkState::establishingLink: //establishingLink state is handled by the callback handlers from RTOS +TCP
        case NetworkState::obtainingIP:      //obtainingIP state is handled by the callback handlers from RTOS +TCP
        default:
            // Nothing to do
            break;

        case NetworkState::connected:
        {
            MutexLocker lock(interfaceMutex);
            InitSockets();
            platform.MessageF(NetworkInfoMessage, "Network running, IP address = %s\n", IP4String(ipAddress).c_str());
            state = NetworkState::active;
        }
        break;
            
        case NetworkState::active:
        {
            MutexLocker lock(interfaceMutex);
            
            if(FreeRTOS_IsNetworkUp() == pdTRUE)
            {
                // Poll the next TCP socket
                sockets[nextSocketToPoll]->Poll();
                
                // Move on to the next TCP socket for next time
                ++nextSocketToPoll;
                if (nextSocketToPoll == NumRTOSPlusTCPEthernetTcpSockets)
                {
                    nextSocketToPoll = 0;
                }
            }
            else
            {
                //down event should be handled by the callbacks
                if (reprap.Debug(moduleNetwork))
                {
                    debugPrintf("RTOSPlusEthernetInterface: Network Down while active\n");
                }
            }
        }
        break;
    }
}

void RTOSPlusTCPEthernetInterface::Diagnostics(MessageType mtype) noexcept
{
	platform.MessageF(mtype, "Interface state: ");
    switch (state)
    {
        case NetworkState::disabled:
            platform.MessageF(mtype, "disabled\n");
            return;
            break;
        case NetworkState::enabled:
            platform.MessageF(mtype, "enabled");
            break;
        case NetworkState::establishingLink:
            platform.MessageF(mtype, "establishing link");
            break;
        case NetworkState::obtainingIP:
            platform.MessageF(mtype, "obtaining IP");
            break;
        case NetworkState::connected:
            platform.MessageF(mtype, "connected");
            break;
        case NetworkState::active:
            platform.MessageF(mtype, "active");
            break;
        default:
            break;
    }
    
    extern uint32_t ulPHYLinkStatus; //defined in NetworkInterface.c
    const char * const linkSpeed = ((ulPHYLinkStatus & PHY_LINK_CONNECTED) == 0) ? "down" : ((ulPHYLinkStatus & PHY_LINK_SPEED100) != 0) ? "100Mbps" : "10Mbps";
    const char * const linkDuplex = ((ulPHYLinkStatus & PHY_LINK_CONNECTED) == 0) ? "" : ((ulPHYLinkStatus & PHY_LINK_FULLDUPLX) != 0) ? " full duplex" : " half duplex";
    platform.MessageF(mtype, ", link %s%s\n", linkSpeed, linkDuplex);
    
    //Report Socket States
    platform.MessageF(mtype, "Socket States: ");
    for (RTOSPlusTCPEthernetSocket*& skt : sockets)
    {
        if(skt != nullptr) skt->Diagnostics(mtype);
    }
    platform.MessageF(mtype, "\n");
    
#if( ipconfigCHECK_IP_QUEUE_SPACE != 0 )
    platform.MessageF(mtype, "NetBuffers: %lu lowest: %lu\n", uxGetNumberOfFreeNetworkBuffers(), uxGetMinimumFreeNetworkBuffers() );
    //Print out the minimum IP Queue space left since boot
    platform.MessageF(mtype, "IP Event Queue lowest: %d\n", (int)uxGetMinimumIPQueueSpace());
#endif
    
#if defined(COLLECT_NETDRIVER_ERROR_STATS)
    //defined in driver for debugging
    extern uint32_t numNetworkRXIntOverrunErrors; //hardware producted overrun error
    extern uint32_t numNetworkDroppedRXPacketsDueToNoBuffer;
    extern uint32_t numNetworkDroppedTXPacketsDueToNoBuffer;
    extern uint32_t numRejectedStackPackets;

    if(numRejectedStackPackets>0) platform.MessageF(mtype, "EthDrv: Rejected packets by IPStack: %lu\n",  numRejectedStackPackets );
    if(numNetworkRXIntOverrunErrors>0) platform.MessageF(mtype, "EthDrv: RX IntOverrun Errors: %lu\n", numNetworkRXIntOverrunErrors);
    if(numNetworkDroppedRXPacketsDueToNoBuffer>0) platform.MessageF(mtype, "EthDrv: Dropped Rx packets (no buffer): %lu\n",  numNetworkDroppedRXPacketsDueToNoBuffer );
    if(numNetworkDroppedTXPacketsDueToNoBuffer>0) platform.MessageF(mtype, "EthDrv: Dropped Tx packets (no buffer): %lu\n",  numNetworkDroppedTXPacketsDueToNoBuffer );

    extern uint32_t numNetworkCRCErrors;
    extern uint32_t numNetworkSYMErrors;
    extern uint32_t numNetworkLENErrors;
    extern uint32_t numNetworkALIGNErrors;
    extern uint32_t numNetworkOVERRUNErrors;
    
    bool errors = false;
    if(numNetworkCRCErrors || numNetworkSYMErrors || numNetworkLENErrors || numNetworkALIGNErrors || numNetworkOVERRUNErrors) errors=true;
    if(errors)
    {
        platform.MessageF(mtype, "EthDrv RX Errors: %s", (errors)?"":"none");
        if(numNetworkCRCErrors > 0) platform.MessageF(mtype, "CRC(%lu) ", numNetworkCRCErrors);
        if(numNetworkSYMErrors > 0) platform.MessageF(mtype, "SYM(%lu) ", numNetworkSYMErrors);
        if(numNetworkLENErrors > 0) platform.MessageF(mtype, "LEN(%lu) ", numNetworkLENErrors);
        if(numNetworkALIGNErrors > 0) platform.MessageF(mtype, "ALIGN(%lu) ", numNetworkALIGNErrors);
        if(numNetworkOVERRUNErrors > 0) platform.MessageF(mtype, "OVERRUN(%lu) ", numNetworkOVERRUNErrors);
        platform.MessageF(mtype, "\n");
    }
#endif

    if(millis() - lastIPTaskTime > 5000)
    {
        platform.MessageF(mtype, "IPTask has not been running for over 5 seconds\n");
    }
}

// Enable or disable the network
GCodeResult RTOSPlusTCPEthernetInterface::EnableInterface(int mode, const StringRef& ssid, const StringRef& reply) noexcept
{
	if (!activated)
	{
		state = (mode == 0) ? NetworkState::disabled : NetworkState::enabled;
	}
	else if (mode == 0)
	{
		if (state != NetworkState::disabled)
		{
			Stop();
			platform.Message(NetworkInfoMessage, "Network stopped\n");
		}

	}
	else if (state == NetworkState::disabled)
	{
		state = NetworkState::enabled;
		Start();
	}
    
	return GCodeResult::ok;
}

int RTOSPlusTCPEthernetInterface::EnableState() const noexcept
{
	return (state == NetworkState::disabled) ? 0 : 1;
}

void RTOSPlusTCPEthernetInterface::SetIPAddress(IPAddress p_ip, IPAddress p_netmask, IPAddress p_gateway) noexcept
{
    ipAddress = p_ip;
    netmask = p_netmask;
    gateway = p_gateway;
}

void RTOSPlusTCPEthernetInterface::OpenDataPort(TcpPort port) noexcept
{
#if ENABLE_FTP
	sockets[FtpDataSocketNumber]->Init(FtpDataSocketNumber, port, FtpDataProtocol);
#endif
}

// Close FTP data port and purge associated resources
void RTOSPlusTCPEthernetInterface::TerminateDataPort() noexcept
{
    if(NumFtpResponders > 0)
    {
        sockets[FtpDataSocketNumber]->Terminate();
    }
}

void RTOSPlusTCPEthernetInterface::InitSockets() noexcept
{
	for (size_t i = 0; i < NumProtocols; ++i)
	{
		if (protocolEnabled[i])
		{
			StartProtocol(i);
		}
	}
	nextSocketToPoll = 0;
}

void RTOSPlusTCPEthernetInterface::TerminateSockets() noexcept
{
	for (SocketNumber skt = 0; skt < NumRTOSPlusTCPEthernetTcpSockets; ++skt)
	{
		sockets[skt]->Terminate();
	}
    // Close the Server Socket
    RTOSPlusTCPEthernetServerSocket::Instance()->CloseAllProtocols();
}



//*******  Handlers called from +TCP callbacks *******
//
//**Note** These hooks are called from within the IP Task.


//get the hostname
const char *RTOSPlusTCPEthernetInterface::ProcessApplicationHostnameHook( void ) noexcept
{
    return reprap.GetNetwork().GetHostname();//printerHostName;
}

/* Called by FreeRTOS+TCP when the network connects or disconnects.  Disconnect events are only received if implemented in the MAC driver. */
void RTOSPlusTCPEthernetInterface::ProcessIPApplication( eIPCallbackEvent_t eNetworkEvent ) noexcept
{
    //variables to hold IP information from +TCP layer (either from static assignment or DHCP)
    uint32_t ulIPAddress, ulNetMask, ulGatewayAddress, ulDNSServerAddress;
    MutexLocker lock(interfaceMutex);

    /* If the network has just come up...*/
    if( eNetworkEvent == eNetworkUp )
    {
        linkUp = true;

        /* Print out the network configuration, which may have come from a DHCP
         server. */
        FreeRTOS_GetAddressConfiguration( &ulIPAddress, &ulNetMask, &ulGatewayAddress, &ulDNSServerAddress );
        
        if( ulIPAddress == 0 ) //ulIPAddress is in 32bit format
        {
            //IP address equals 0.0.0.0 here. DHCP has Failed.
            //since the user has started networking, keep trying
            FreeRTOS_NetworkDown(); //send a network down event to retry connecting
            state = NetworkState::establishingLink;
        }
        else
        {
            //update the class private vars with the values we got from +tcp
            ipAddress.SetV4LittleEndian(ulIPAddress);
            netmask.SetV4LittleEndian(ulNetMask);
            gateway.SetV4LittleEndian(ulGatewayAddress);
            state = NetworkState::connected; //set connected state (we have IP address)
        }

    }
    else if (eNetworkEvent == eNetworkDown)
    {
        if(linkUp == true)
        {
            linkUp = false;
            //Link was previously up but has gone down. We need to close all sockets including server socket
            //and Reinitialise after link comes back up
            TerminateSockets();
        }
        
        state = NetworkState::establishingLink; //back to establishing link
    }
    else {
        
    }

}


/* RTOS+TCP DHCP Hook.... this allows us to control the DHCP process.
   +TCP will automatically start a DHCP process (if DHCP is configured in config) and
   we need to use this hook to prevent DHCP starting if we have a static address set in config.g
*/
eDHCPCallbackAnswer_t RTOSPlusTCPEthernetInterface::ProcessDHCPHook( eDHCPCallbackPhase_t eDHCPPhase, uint32_t ulIPAddress ) noexcept
{
    eDHCPCallbackAnswer_t eReturn;
    
    /* This hook is called in a couple of places during the DHCP process, as identified by the eDHCPPhase parameter. */
    switch( eDHCPPhase )
    {
        case eDHCPPhasePreDiscover  :
        {
            MutexLocker lock(interfaceMutex);

            state = NetworkState::obtainingIP; // obtaining IP state
            
            /* A DHCP discovery is about to be sent out.  eDHCPContinue is returned to allow the discovery to go out.
             
             If eDHCPUseDefaults had been returned instead then the DHCP process would be stopped and the statically configured IP address would be used.
             
             If eDHCPStopNoChanges had been returned instead then the DHCP process would be stopped and
             whatever the current network configuration was would continue to be used.
             */
            if(usingDHCP == true)
            {
                eReturn = eDHCPContinue; //use DHCP
            }
            else
            {
                //RRF has been configured to use a static address, so dont attempt to use DHCP
                eReturn = eDHCPUseDefaults; //use Static
            }
        }
            break;
            
        case eDHCPPhasePreRequest  :
            //            /* An offer has been received from the DHCP server, and the offered
            //             IP address is passed in the ulIPAddress parameter.  Convert the
            //             offered and statically allocated IP addresses to 32-bit values. */
            
            eReturn = eDHCPContinue; //continue with dhcp assigned address
            
            break;
            
        default :
            /* Cannot be reached, but set eReturn to prevent compiler warnings
             where compilers are disposed to generating one. */
            eReturn = eDHCPContinue;
            break;
    }
    
    return eReturn;

}

//Call back to check if the Queried Name from Netbios or LLNMR matches our hostname
BaseType_t RTOSPlusTCPEthernetInterface::ProcessDNSQueryHook(const char *pcName) noexcept
{
    if(StringEqualsIgnoreCase(pcName, reprap.GetNetwork().GetHostname()) ) return pdPASS;
    return pdFAIL;
}




//Called by modified FreeRTOS +TCP to create tasks for EMAC and IP using RRF task management methods


extern "C" TaskHandle_t RRfInitialiseIPTask(TaskFunction_t pxTaskCode)
{
    tcpPlusTask.Create(pxTaskCode, "IP-task", nullptr, ( UBaseType_t ) TaskPriority::TcpPriority);
    return tcpPlusTask.GetHandle();
}

extern "C" TaskHandle_t RRfInitialiseEMACTask(TaskFunction_t pxTaskCode)
{
    emacTask.Create(pxTaskCode, "EMAC", nullptr, TaskPriority::TcpPriority);
    return emacTask.GetHandle();
}



//FreeRTOS +TCP "C" application Hooks



/* Called by FreeRTOS+TCP when the network connects or disconnects.  Disconnect events are only received if implemented in the MAC driver. */
extern "C" void vApplicationIPNetworkEventHook( eIPCallbackEvent_t eNetworkEvent )
{
    (rtosTCPEtherInterfacePtr)->ProcessIPApplication(eNetworkEvent); //call the c++ class to handle the callback
}

// FreeRTOS+TCP DHCP Hook.... this allows us to control over the DHCP process.
extern "C" eDHCPCallbackAnswer_t xApplicationDHCPHook( eDHCPCallbackPhase_t eDHCPPhase, uint32_t ulIPAddress )
{
    return (rtosTCPEtherInterfacePtr)->ProcessDHCPHook(eDHCPPhase, ulIPAddress);
}

extern "C" const char *pcApplicationHostnameHook( void )
{
    return (rtosTCPEtherInterfacePtr)->ProcessApplicationHostnameHook();
}

extern "C" BaseType_t xApplicationDNSQueryHook( const char *pcName )
{
    return (rtosTCPEtherInterfacePtr)->ProcessDNSQueryHook(pcName);
}

//called every iteration of IP Task
extern "C" void IPTaskWatchDogTimer()
{
    lastIPTaskTime = millis();
}


/*
 * Callback that provides the inputs necessary to generate a randomized TCP
 * Initial Sequence Number per RFC 6528.  In this case just a psuedo random
 * number is used so THIS IS NOT RECOMMENDED FOR PRODUCTION SYSTEMS.
 */
extern "C" uint32_t ulApplicationGetNextSequenceNumber( uint32_t
                                                   ulSourceAddress,
                                                   uint16_t usSourcePort,
                                                   uint32_t ulDestinationAddress,
                                                   uint16_t usDestinationPort )
{
    ( void ) ulSourceAddress;
    ( void ) usSourcePort;
    ( void ) ulDestinationAddress;
    ( void ) usDestinationPort;
    
    return (int32_t)millis();
}


// End
