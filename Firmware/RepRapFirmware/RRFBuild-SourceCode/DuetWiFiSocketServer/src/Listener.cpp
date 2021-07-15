/*
 * Listener.cpp
 *
 *  Created on: 12 Apr 2017
 *      Author: David
 */

#include "Listener.h"
#include "Connection.h"
#include "Config.h"

#include <HardwareSerial.h>

// C interface functions
extern "C"
{
	#include "lwip/tcp.h"
	#include "lwip/err.h"

	static err_t conn_accept(void *arg, tcp_pcb *pcb, err_t err)
	{
		LWIP_UNUSED_ARG(err);
		if (arg != nullptr)
		{
			return ((Listener*)arg)->Accept(pcb);
		}
		tcp_abort(pcb);
		return ERR_ABRT;
	}
}

// Static member data
Listener *Listener::activeList = nullptr;
Listener *Listener::freeList = nullptr;

// Member functions
Listener::Listener()
	: next(nullptr), listeningPcb(nullptr), ip(0), port(0), maxConnections(0), protocol(0)
{
}

int Listener::Accept(tcp_pcb *pcb)
{
	if (listeningPcb != nullptr)
	{
		// Allocate a free socket for this connection
		const uint16_t numConns = Connection::CountConnectionsOnPort(port);
		if (numConns < maxConnections)
		{
			Connection * const conn = Connection::Allocate();
			if (conn != nullptr)
			{
				tcp_accepted(listeningPcb);		// tell the listening PCB we have accepted the connection
				const int rslt = conn->Accept(pcb);
				if (protocol == protocolFtpData)
				{
					debugPrintf("accept conn, stop listen on port %u\n", port);
					Stop();						// don't listen for further connections
				}
				return rslt;
			}
			debugPrintfAlways("refused conn on port %u no free conn\n", port);
		}
		else
		{
			debugPrintfAlways("refused conn on port %u already %u conns\n", port, numConns);
		}
	}
	else
	{
		debugPrintfAlways("refused conn on port %u no pcb\n", port);
	}
	tcp_abort(pcb);
	return ERR_ABRT;
}

void Listener::Stop()
{
	if (listeningPcb != nullptr)
	{
		tcp_arg(listeningPcb, nullptr);
		tcp_close(listeningPcb);			// stop listening and free the PCB
		listeningPcb = nullptr;
	}
	Unlink(this);
	Release(this);
}

// Set up a listener on a port, returning true if successful, or stop listening of maxConnections = 0
/*static*/ bool Listener::Listen(uint32_t ip, uint16_t port, uint8_t protocol, uint16_t maxConns)
{
	// See if we are already listing for this
	for (Listener *p = activeList; p != nullptr; )
	{
		Listener *n = p->next;
		if (p->port == port)
		{
			if (maxConns != 0 && (p->ip == IPADDR_ANY || p->ip == ip))
			{
				// already listening, so nothing to do
				debugPrintf("already listening on port %u\n", port);
				return true;
			}
			if (maxConns == 0 || ip == IPADDR_ANY)
			{
				p->Stop();
				debugPrintf("stopped listening on port %u\n", port);
			}
		}
		p = n;
	}

	if (maxConns == 0)
	{
		return true;
	}

	// If we get here then we need to set up a new listener
	Listener * const p = Allocate();
	if (p == nullptr)
	{
		debugPrintAlways("can't allocate listener\n");
		return false;
	}
	p->ip = ip;
	p->port = port;
	p->protocol = protocol;
	p->maxConnections = maxConns;

	// Call LWIP to set up a listener
	tcp_pcb* const tempPcb = tcp_new();
	if (tempPcb == nullptr)
	{
		Release(p);
		debugPrintAlways("can't allocate PCB\n");
		return false;
	}

	ip_addr_t tempIp;
	tempIp.addr = ip;
	tempPcb->so_options |= SOF_REUSEADDR;			// not sure we need this, but the Arduino HTTP server does it
	err_t rc = tcp_bind(tempPcb, &tempIp, port);
	if (rc != ERR_OK)
	{
		tcp_close(tempPcb);
		Release(p);
		debugPrintfAlways("can't bind PCB: %d\n", (int)rc);
		return false;
	}
	p->listeningPcb = tcp_listen_with_backlog(tempPcb, Backlog);
	if (p->listeningPcb == nullptr)
	{
		tcp_close(tempPcb);
		Release(p);
		debugPrintAlways("tcp_listen failed\n");
		return false;
	}
	tcp_arg(p->listeningPcb, p);
	tcp_accept(p->listeningPcb, conn_accept);
	// Don't call tcp_err in the LISTEN state because lwip gives us an assertion failure at tcp.s(1760)
	p->next = activeList;
	activeList = p;
	debugPrintf("listening on port %u\n", port);
	return true;
}

// Stop listening on the specified port, or on all ports if 'port' is zero
/*static*/ void Listener::StopListening(uint16_t port)
{
	for (Listener *p = activeList; p != nullptr; )
	{
		Listener *n = p->next;
		if (port == 0 || port == p->port)
		{
			p->Stop();
		}
		p = n;
	}
}

/*static*/ uint16_t Listener::GetPortByProtocol(uint8_t protocol)
{
	for (Listener *p = activeList; p != nullptr; p = p->next)
	{
		if (p->protocol == protocol)
		{
			return p->port;
		}
	}
	return 0;
}

/*static*/ Listener *Listener::Allocate()
{
	Listener *ret = freeList;
	if (ret != nullptr)
	{
		freeList = ret->next;
		ret->next = nullptr;
	}
	else
	{
		ret = new Listener;
	}
	return ret;
}

/*static*/ void Listener::Unlink(Listener *lst)
{
	Listener **pp = &activeList;
	while (*pp != nullptr)
	{
		if (*pp == lst)
		{
			*pp = lst->next;
			lst->next = nullptr;
			return;
		}
	}
}

/*static*/ void Listener::Release(Listener *lst)
{
	lst->next = freeList;
	freeList = lst;
}

// End
