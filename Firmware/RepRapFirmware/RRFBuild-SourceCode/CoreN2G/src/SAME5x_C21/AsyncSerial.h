/*
 * Uart.h
 *
 *  Created on: 19 Jun 2020
 *      Author: David
 */

#ifndef SRC_HARDWARE_SAME5X_C21_ASYNCSERIAL_H_
#define SRC_HARDWARE_SAME5X_C21_ASYNCSERIAL_H_

#include <Stream.h>
#include <General/RingBuffer.h>
#include "Serial.h"

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

	AsyncSerial(uint8_t sercomNum, uint8_t rxp, size_t numTxSlots, size_t numRxSlots, OnBeginFn p_onBegin, OnEndFn p_onEnd) noexcept;

	// Overridden virtual functions
	int available() noexcept override;
	int read() noexcept override;
	void flush() noexcept override;
	size_t canWrite() noexcept override;

    size_t write(uint8_t) noexcept override;
    size_t write(const uint8_t *buffer, size_t size) noexcept override;		// this has a default implementation, but can be overridden for efficiency

    using Print::write; // pull in write(str) and write(buf, size) from Print

	// Compatibility functions
	void begin(uint32_t baudRate) noexcept;
	void end() noexcept;
	void setInterruptPriority(uint32_t rxPrio, uint32_t txAndErrorPrio) const noexcept;
    InterruptCallbackFn SetInterruptCallback(InterruptCallbackFn f) noexcept;

#if 0
	// Non-blocking block write
	size_t TryPutBlock(const uint8_t *buffer, size_t buflen) noexcept;
#endif

	// ISRs, must be called by the ISRs for the SERCOM

#if SAME5x
	void Interrupt0() noexcept;
	// We don't use interrupt 1
	void Interrupt2() noexcept;
	void Interrupt3() noexcept;
#elif SAMC21
	void Interrupt() noexcept;
#endif

	// Get and clear the errors
	Errors GetAndClearErrors() noexcept;

private:
	RingBuffer<uint8_t> txBuffer;
	RingBuffer<uint8_t> rxBuffer;
	Sercom * const sercom;
#ifdef RTOS
	volatile TaskHandle txWaitingTask;
#endif
    InterruptCallbackFn interruptCallback;
    OnBeginFn onBegin;
    OnEndFn onEnd;
	Errors errors;
	const uint8_t sercomNumber;
	const uint8_t rxPad;
    uint8_t numInterruptBytesMatched;
    bool bufferOverrunPending;

    static constexpr uint8_t interruptSeq[2] = { 0xF0, 0x0F };
};

#endif /* SRC_HARDWARE_SAME5X_C21_ASYNCSERIAL_H_ */
