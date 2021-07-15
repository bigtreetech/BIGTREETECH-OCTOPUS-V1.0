/*
 *  
 *
 * Author: Stephen
 */

#ifndef SRC_NETWORKING_RTOSPlusTCPEthernetSERVERSOCKET_H_
#define SRC_NETWORKING_RTOSPlusTCPEthernetSERVERSOCKET_H_

#include "RepRapFirmware.h"
#include "NetworkDefs.h"
#include "Socket.h"

#include <FreeRTOS.h>
#include "task.h"
#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"


// Server socket
class RTOSPlusTCPEthernetServerSocket
{
public:
    
    static RTOSPlusTCPEthernetServerSocket *Instance() noexcept;
    Socket_t GetServerSocket(TcpPort serverPort, NetworkProtocol p) noexcept;
	void CloseServerSocket(NetworkProtocol p) noexcept;
    void CloseProtocol(NetworkProtocol p) noexcept;
    void CloseAllProtocols() noexcept;
    
    
private:
    RTOSPlusTCPEthernetServerSocket() noexcept;

    Socket_t protocolServerSockets[NumProtocols]; // Server for each Protocol (assuming socket reuse is false (default in +tcp))
    static RTOSPlusTCPEthernetServerSocket *serverSocketInstance;
};

#endif /* SRC_NETWORKING_RTOSPlusTCPEthernetSERVERSOCKET_H_ */
