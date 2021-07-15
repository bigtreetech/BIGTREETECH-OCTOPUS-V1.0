/*
 *
 *
 *
 * Author: Stephen
 */

#include "RTOSPlusTCPEthernetServerSocket.h"
#include "RTOSPlusTCPEthernetInterface.h"
#include "Network.h"
#include "Networking/NetworkInterface.h"
#include "NetworkBuffer.h"
#include "RepRap.h"

RTOSPlusTCPEthernetServerSocket *RTOSPlusTCPEthernetServerSocket::serverSocketInstance = nullptr;


//***************************************************************************************************

/*static*/ RTOSPlusTCPEthernetServerSocket *RTOSPlusTCPEthernetServerSocket::Instance() noexcept
{
    
    if( serverSocketInstance == nullptr ){
        //setup instance
        serverSocketInstance = new RTOSPlusTCPEthernetServerSocket();
    }

    return serverSocketInstance;
    
}


RTOSPlusTCPEthernetServerSocket::RTOSPlusTCPEthernetServerSocket() noexcept
{
    for(NetworkProtocol i=0; i<NumProtocols; i++)
    {
        protocolServerSockets[i] = nullptr;
    }
}

// Initialise a TCP socket
Socket_t RTOSPlusTCPEthernetServerSocket::GetServerSocket(TcpPort serverPort, NetworkProtocol p) noexcept
{
    static const TickType_t xReceiveTimeOut = 1; // time (in ticks) to wait for FreeRTOS_accept .. portMax_DELAY would wait indefinetly (block until client connection)
    static const TickType_t xSendTimeOut = 1;

    struct freertos_sockaddr xBindAddress;
    BaseType_t maxClients = 1; //max number of simultaneous connections allowed
    BaseType_t reuseSocket = pdFALSE; //

    
    if(p == HttpProtocol){
        maxClients = NumHttpSockets;
    }

    BaseType_t ret = FreeRTOS_issocketconnected(protocolServerSockets[p]);
    if( protocolServerSockets[p] != nullptr &&  ret >= 0 )
    {
        //we already have a non-reused Socket Setup for this protocol and its running
        return protocolServerSockets[p];
    }
    else
    {
        if(protocolServerSockets[p] != nullptr){
            if (reprap.Debug(moduleNetwork))
            {
                debugPrintf( "+TCPServerSocket::GetServerSocket(): Had non-resue socket but there is a problem: Error code: %d\n", (int)ret);
            }
            CloseProtocol(p);
        }
        
    }
    
    if (reprap.Debug(moduleNetwork))
    {
        debugPrintf("+TCPServerSocket::GetServerSocket(): Create Socket (port: %d, Protocol: %s, maxConnections: %d)\n", (int)serverPort, ProtocolNames[p], (int)maxClients);
    }
    //attempt to create the socket
    protocolServerSockets[p] = FreeRTOS_socket( FREERTOS_AF_INET, FREERTOS_SOCK_STREAM, FREERTOS_IPPROTO_TCP );
    
    if(protocolServerSockets[p] != FREERTOS_INVALID_SOCKET ){
        
        /* Set a time out so accept() will just wait for a connection. portMAX_DELAY will wait indefinetly */
        // set to a 1 tick... accept a connection if waiting or continue (non-blocking) - receive
        // set to 1 tick ... read from socket and wait 1 tick for data before continuing
        // This to be compatible with the existing Polled Networking
        FreeRTOS_setsockopt( protocolServerSockets[p], 0, FREERTOS_SO_RCVTIMEO, &xReceiveTimeOut, sizeof( xReceiveTimeOut ) );
        FreeRTOS_setsockopt( protocolServerSockets[p], 0, FREERTOS_SO_SNDTIMEO, &xSendTimeOut, sizeof( xSendTimeOut ) );
        
        //Configure the socket reuse
        //If reuse is False (default) then the connecting sockect(s) will make a copy of the socket for simultaneous connected clients
        //else the same socket will be used at the accept socket and when closed, must be recreated again
        //
        FreeRTOS_setsockopt( protocolServerSockets[p], 0, FREERTOS_SO_REUSE_LISTEN_SOCKET, &reuseSocket, sizeof( reuseSocket ) );
        
        /* Set the listening port. */
        xBindAddress.sin_port = ( uint16_t ) serverPort;
        xBindAddress.sin_port = FreeRTOS_htons( xBindAddress.sin_port );
        
        /* Bind the socket to the port */
        if(FreeRTOS_bind( protocolServerSockets[p], &xBindAddress, sizeof( xBindAddress ) ) < 0 )
        {
            //error binding socket
            if (reprap.Debug(moduleNetwork))
            {
                debugPrintf("+TCPServerSocket::GetServerSocket(): Failed to bind socket\n");
                CloseProtocol(p);
                return nullptr;

            }

        }
        
        /* Set the socket into a listening state so it can accept connections.
         The maximum number of simultaneous connections is limited to value of backlog. */
        if( FreeRTOS_listen( protocolServerSockets[p], maxClients ) < 0){
            //Unable to set listen state
            if (reprap.Debug(moduleNetwork))
            {
                debugPrintf("+TCPServerSocket::GetServerSocket(): Failed to set socket to listen state\n");
                CloseProtocol(p);
                return nullptr;
            }

        }
        
        return protocolServerSockets[p];
        
    }
    else
    {
        //failed to create socket
        debugPrintf( "Failed to create Protocol Server Socket for %s on port %d\n", ProtocolNames[p], serverPort );
        protocolServerSockets[p] = nullptr;

    }
    
    
    return nullptr;
}


void RTOSPlusTCPEthernetServerSocket::CloseProtocol(NetworkProtocol p) noexcept
{
    
    FreeRTOS_shutdown( protocolServerSockets[p], FREERTOS_SHUT_RDWR ); //perform graceful shutdown
    FreeRTOS_closesocket( protocolServerSockets[p] );
    protocolServerSockets[p] = nullptr;
}

void RTOSPlusTCPEthernetServerSocket::CloseAllProtocols() noexcept
{
    for(NetworkProtocol i=0; i<NumProtocols; i++ )
    {
        CloseProtocol(i);
    }
}

