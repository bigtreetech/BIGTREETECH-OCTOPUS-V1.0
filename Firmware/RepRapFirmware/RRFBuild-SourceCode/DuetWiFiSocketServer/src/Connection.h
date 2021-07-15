/*
 * Socket.h
 *
 *  Created on: 11 Apr 2017
 *      Author: David
 *
 * Simplified socket class to run in ESP8266 in Duet WiFi
 */

#ifndef SRC_CONNECTION_H_
#define SRC_CONNECTION_H_

#include <cstdint>
#include <cstddef>
#include "include/MessageFormats.h"			// for ConnState

// If we #include "tcp.h" here we get clashes between two different ip_addr.h files, so don't do that here
class tcp_pcb;
class pbuf;

class Connection
{
public:
	Connection(uint8_t num);

	// Public interface
	ConnState GetState() const { return state; }
	void GetStatus(ConnStatusResponse& resp) const;

	void Close();
	void Terminate(bool external);
	size_t Write(const uint8_t *data, size_t length, bool doPush, bool closeAfterSending);
	size_t CanWrite() const;
	size_t Read(uint8_t *data, size_t length);
	size_t CanRead() const;
	void Poll();

	// Callback functions
	int Accept(tcp_pcb *pcb);
	void ConnError(int err);
	int ConnRecv(pbuf *p, int err);
	int ConnSent(uint16_t len);

	// Static functions
	static void Init();
	static Connection *Allocate();
	#ifdef EXTENDED_LISTEN
	static Connection& Get(uint8_t num) { return *publicConnections[num]; }
	#else
	static Connection& Get(uint8_t num) { return *connectionList[num]; }
	#endif
	static uint16_t CountConnectionsOnPort(uint16_t port);
	static void PollOne();
	static void ReportConnections();
	static void GetSummarySocketStatus(uint16_t& connectedSockets, uint16_t& otherEndClosedSockets);
	static void TerminateAll();

private:
	void FreePbuf();
	void Report();
	void MakePublic();

	void SetState(ConnState st)
	{
		state = st;
	}

	uint8_t number;
	volatile ConnState state;

	uint16_t localPort;
	uint16_t remotePort;

	uint32_t remoteIp;
	uint32_t writeTimer;
	uint32_t closeTimer;
	volatile size_t unAcked;	// how much data we have sent but hasn't been acknowledged
	size_t readIndex;			// how much data we have already read from the current pbuf
	size_t alreadyRead;			// how much data we read from previous pbufs and didn't tell LWIP about yet
	tcp_pcb *ownPcb;			// the pcb that corresponds to this connection
	pbuf *pb;					// the buffers holding data we have received that has not yet been taken

	static Connection *connectionList[MaxConnections];
#ifdef EXTENDED_LISTEN
	static Connection *publicConnections[MaxPublicConnections];
#endif
	static size_t nextConnectionToPoll;
};

#endif /* SRC_CONNECTION_H_ */
