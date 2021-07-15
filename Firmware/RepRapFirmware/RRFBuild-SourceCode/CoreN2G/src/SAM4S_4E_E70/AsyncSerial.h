/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef SRC_HARDWARE_SAME4S_4E_E70_ASYNC_SERIAL_H_
#define SRC_HARDWARE_SAME4S_4E_E70_ASYNC_SERIAL_H_

#include <Stream.h>
#include <General/RingBuffer.h>

#ifdef RTOS
# include <RTOSIface/RTOSIface.h>
#endif

#if SAM4E || SAME70
#include "component/usart.h"
#else
#include "component/component_usart.h"
#endif

#define SERIAL_8N1 UARTClass::Mode_8N1
#define SERIAL_8E1 UARTClass::Mode_8E1
#define SERIAL_8O1 UARTClass::Mode_8O1
#define SERIAL_8M1 UARTClass::Mode_8M1
#define SERIAL_8S1 UARTClass::Mode_8S1


class AsyncSerial : public Stream
{
  public:
	typedef void (*InterruptCallbackFn)(AsyncSerial*) noexcept;
	typedef void (*OnBeginFn)(AsyncSerial*) noexcept;
	typedef void (*OnEndFn)(AsyncSerial*) noexcept;

	union Errors
	{
		uint32_t all;
		struct
		{
			uint32_t uartOverrun : 11,
					 framing : 11,
					 bufferOverrun : 10;
		};

		Errors() noexcept { all = 0; }
	};

    enum UARTModes {
      Mode_8N1 = US_MR_CHRL_8_BIT | US_MR_NBSTOP_1_BIT | UART_MR_PAR_NO,
      Mode_8E1 = US_MR_CHRL_8_BIT | US_MR_NBSTOP_1_BIT | UART_MR_PAR_EVEN,
      Mode_8O1 = US_MR_CHRL_8_BIT | US_MR_NBSTOP_1_BIT | UART_MR_PAR_ODD,
      Mode_8M1 = US_MR_CHRL_8_BIT | US_MR_NBSTOP_1_BIT | UART_MR_PAR_MARK,
      Mode_8S1 = US_MR_CHRL_8_BIT | US_MR_NBSTOP_1_BIT | UART_MR_PAR_SPACE,
    };

    AsyncSerial(Uart* pUart, IRQn_Type p_irqn, uint32_t p_id, size_t numTxSlots, size_t numRxSlots, OnBeginFn p_onBegin, OnEndFn p_onEnd) noexcept;

    void begin(const uint32_t dwBaudRate) noexcept;
    void begin(const uint32_t dwBaudRate, const UARTModes config) noexcept;
    void end() noexcept;
    int available(void) noexcept;
    int read() noexcept;
    void flush() noexcept;
    size_t write(const uint8_t c) noexcept override;
    size_t write(const uint8_t *buffer, size_t buflen) noexcept override;

    using Print::write;				// pull in write(str) and write(buf, size) from Print
    size_t canWrite() noexcept override;

    void setInterruptPriority(uint32_t priority) noexcept;
    uint32_t getInterruptPriority() noexcept;

    void IrqHandler() noexcept;

    operator bool() noexcept { return true; }; // UART always active

    InterruptCallbackFn SetInterruptCallback(InterruptCallbackFn f) noexcept;

	// Get and clear the errors
	Errors GetAndClearErrors() noexcept;

  protected:
    void init(const uint32_t dwBaudRate, const uint32_t config) noexcept;

	RingBuffer<uint8_t> txBuffer;
	RingBuffer<uint8_t> rxBuffer;

	Uart* const _pUart;
	const IRQn_Type irqn;
	const uint32_t id;
#ifdef RTOS
	volatile TaskHandle txWaitingTask;
#endif
	InterruptCallbackFn interruptCallback;
	OnBeginFn onBegin;
	OnEndFn onEnd;
	Errors errors;
	size_t numInterruptBytesMatched;
	bool bufferOverrunPending;

	static constexpr uint8_t interruptSeq[2] = { 0xF0, 0x0F };
};

#endif // SRC_HARDWARE_SAME4S_4E_E70_ASYNC_SERIAL_H_
