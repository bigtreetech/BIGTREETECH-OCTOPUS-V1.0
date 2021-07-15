/*
 * Socket.h
 *
 *  Created on: 25 Dec 2016
 *      Author: David
 */

#ifndef SRC_NETWORKING_RTOSPlusTCPEthernetSOCKET_H_
#define SRC_NETWORKING_RTOSPlusTCPEthernetSOCKET_H_

#include "RepRapFirmware.h"
#include "NetworkDefs.h"
#include "Socket.h"

#include <FreeRTOS.h>
#include "task.h"
#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"

 #include "MessageType.h"

// Socket structure that we use to track TCP connections
class RTOSPlusTCPEthernetSocket : public Socket
{
public:
	RTOSPlusTCPEthernetSocket(NetworkInterface *iface) noexcept;
	void Init(SocketNumber s, TcpPort serverPort, NetworkProtocol p) noexcept;

	void Poll() noexcept override;
	void Close() noexcept override;
	void Terminate() noexcept override;
	void TerminateAndDisable() noexcept override;
	bool ReadChar(char& c) noexcept override;
	bool ReadBuffer(const uint8_t *&buffer, size_t &len) noexcept override;
	void Taken(size_t len) noexcept override;
	bool CanRead() const noexcept override;
	bool CanSend() const noexcept override;
	size_t Send(const uint8_t *data, size_t length) noexcept override;
	void Send() noexcept override;
    void Diagnostics(MessageType mt) const  noexcept;
    
private:
	void ReInit() noexcept;
	void ReceiveData() noexcept;
	void DiscardReceivedData() noexcept;

	NetworkBuffer *receivedData;						// List of buffers holding received data
	uint32_t whenConnected;
    bool closingTimeoutStarted;
	SocketNumber socketNum;								// The RTOSPlusTCPEthernet socket number we are using

//TCP+
    Socket_t xListeningSocket;  // server socket 
    Socket_t xConnectedSocket;  //connected client socket
    bool CheckSocketError(BaseType_t val) noexcept; 

};

#endif /* SRC_NETWORKING_RTOSPlusTCPEthernetSOCKET_H_ */
