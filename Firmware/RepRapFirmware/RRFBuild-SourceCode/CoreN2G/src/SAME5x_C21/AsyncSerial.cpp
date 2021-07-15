/*
 * Uart.cpp
 *
 *  Created on: 19 Jun 2020
 *      Author: David
 */

#include "AsyncSerial.h"
#include <algorithm>		// for std::swap

AsyncSerial::AsyncSerial(uint8_t sercomNum, uint8_t rxp, size_t numTxSlots, size_t numRxSlots, OnBeginFn p_onBegin, OnEndFn p_onEnd) noexcept
	: sercom(Serial::GetSercom(sercomNum)),
#ifdef RTOS
	  txWaitingTask(nullptr),
#endif
	  interruptCallback(nullptr), onBegin(p_onBegin), onEnd(p_onEnd),
	  sercomNumber(sercomNum), rxPad(rxp)
{
	txBuffer.Init(numTxSlots);
	rxBuffer.Init(numRxSlots);
}

// Initialise the UART. numRxSlots may be zero if we don't wish to receive.
void AsyncSerial::begin(uint32_t baudRate) noexcept
{
	txBuffer.Clear();
	rxBuffer.Clear();
	bufferOverrunPending = false;
	onBegin(this);
	Serial::InitUart(sercomNumber, baudRate, rxPad);
	errors.all = 0;
	numInterruptBytesMatched = 0;
	sercom->USART.INTENSET.reg = SERCOM_USART_INTENSET_RXC | SERCOM_USART_INTENSET_ERROR;

	const IRQn irqNumber = Serial::GetSercomIRQn(sercomNumber);
	NVIC_EnableIRQ(irqNumber);
#if SAME5x
	NVIC_EnableIRQ((IRQn)(irqNumber + 2));
	NVIC_EnableIRQ((IRQn)(irqNumber + 3));
#endif
}

void AsyncSerial::end() noexcept
{
	// Clear any received data
	rxBuffer.Clear();

	// Wait for any outstanding data to be sent
	flush();

	// Disable UART interrupt in NVIC
	const IRQn irqNumber = Serial::GetSercomIRQn(sercomNumber);
	NVIC_DisableIRQ(irqNumber);
#if SAME5x
	NVIC_DisableIRQ((IRQn)(irqNumber + 2));
	NVIC_DisableIRQ((IRQn)(irqNumber + 3));
#endif
	onEnd(this);
}

// Non-blocking read, return 0 if no character available
int AsyncSerial::read() noexcept
{
	uint8_t c;
	return (rxBuffer.GetItem(c)) ? c : -1;
}

int AsyncSerial::available() noexcept
{
	return rxBuffer.ItemsPresent();
}

void AsyncSerial::flush() noexcept
{
	// If we have never transmitted then the TXC bit never gets set, so we mustn't wait for it
	if (!txBuffer.IsEmpty() || !sercom->USART.INTFLAG.bit.DRE)
	{
		while (!txBuffer.IsEmpty()) { }
		while (!sercom->USART.INTFLAG.bit.TXC) { }
	}
}

size_t AsyncSerial::canWrite() noexcept
{
	return txBuffer.SpaceLeft();
}

// Write single character, blocking
size_t AsyncSerial::write(uint8_t c) noexcept
{
	if (txBuffer.IsEmpty() && sercom->USART.INTFLAG.bit.DRE)
	{
		sercom->USART.DATA.reg = c;
	}
	else
	{
		for (;;)
		{
			if (txBuffer.PutItem(c))
			{
				sercom->USART.INTENSET.reg = SERCOM_USART_INTENSET_DRE;
				break;
			}
#ifdef RTOS
			txWaitingTask = RTOSIface::GetCurrentTask();
#endif
			sercom->USART.INTENSET.reg = SERCOM_USART_INTENSET_DRE;
#ifdef RTOS
			TaskBase::Take(50);
#endif
		}
	}
	return 1;
}

#if 0
// Nonblocking write block
size_t AsyncSerial::TryPutBlock(const uint8_t* buffer, size_t buflen) noexcept
{
	const size_t written = txBuffer.PutBlock(buffer, buflen);
	sercom->USART.INTENSET.reg = SERCOM_USART_INTENSET_DRE;
	return written;
}
#endif

// Blocking write block
size_t AsyncSerial::write(const uint8_t* buffer, size_t buflen) noexcept
{
	const size_t ret = buflen;
	for (;;)
	{
		buflen -= txBuffer.PutBlock(buffer, buflen);
		if (buflen == 0)
		{
			sercom->USART.INTENSET.reg = SERCOM_USART_INTENSET_DRE;
			break;
		}
#ifdef RTOS
		txWaitingTask = RTOSIface::GetCurrentTask();
#endif
		sercom->USART.INTENSET.reg = SERCOM_USART_INTENSET_DRE;
#ifdef RTOS
		TaskBase::Take(50);
#endif
	}
	return ret;
}

// Get and clear the errors
AsyncSerial::Errors AsyncSerial::GetAndClearErrors() noexcept
{
	Errors errs;
	std::swap(errs, errors);
	return errs;
}

#if SAME5x

// Interrupts from the SERCOM arrive here
// Interrupt 0 means transmit data register empty
void AsyncSerial::Interrupt0() noexcept
{
	uint8_t c;
	if (txBuffer.GetItem(c))
	{
		sercom->USART.DATA.reg = c;
#ifdef RTOS
		if (txWaitingTask != nullptr && txBuffer.SpaceLeft() >= txBuffer.GetCapacity()/2)
		{
			TaskBase::GiveFromISR(txWaitingTask);
			txWaitingTask = nullptr;
		}
#endif
	}
	else
	{
		sercom->USART.INTENCLR.reg = SERCOM_USART_INTENCLR_DRE;
#ifdef RTOS
		if (txWaitingTask != nullptr)
		{
			TaskBase::GiveFromISR(txWaitingTask);
			txWaitingTask = nullptr;
		}
#endif
	}
}

// We don't use interrupt 1, it signals transmit complete
// Interrupt 2 means receive character available
void AsyncSerial::Interrupt2() noexcept
{
	const char c = sercom->USART.DATA.reg;
	if (c == interruptSeq[numInterruptBytesMatched])
	{
		++numInterruptBytesMatched;
		if (numInterruptBytesMatched == ARRAY_SIZE(interruptSeq))
		{
			numInterruptBytesMatched = 0;
			if (interruptCallback != nullptr)
			{
				interruptCallback(this);
			}
		}
	}
	else
	{
		numInterruptBytesMatched = 0;
	}

	if (bufferOverrunPending)
	{
		if (txBuffer.PutItem(0x7F))
		{
			bufferOverrunPending = false;
			(void)rxBuffer.PutItem(c);					// we don't much care whether this succeeds or not
		}
	}
	else if (!rxBuffer.PutItem(c))
	{
		++errors.bufferOverrun;
		bufferOverrunPending = true;
	}
}

// Interrupt 3 means error or break or CTS change or receive start, but we only enable error
void AsyncSerial::Interrupt3() noexcept
{
	const uint16_t stat2 = sercom->USART.STATUS.reg;
	if (stat2 & SERCOM_USART_STATUS_BUFOVF)
	{
		++errors.uartOverrun;
	}
	if (stat2 & SERCOM_USART_STATUS_FERR)
	{
		++errors.framing;
	}
	if (stat2 && (SERCOM_USART_STATUS_BUFOVF || SERCOM_USART_STATUS_FERR))
	{
		rxBuffer.PutItem(0x7F);
	}
	sercom->USART.STATUS.reg = stat2;
	sercom->USART.INTFLAG.reg = SERCOM_USART_INTFLAG_ERROR;			// clear the error
}

#elif SAMC21

void AsyncSerial::Interrupt() noexcept
{
	const uint8_t status = sercom->USART.INTFLAG.reg;

	// Check for received character
	if (status & SERCOM_USART_INTFLAG_RXC)
	{
		const char c = sercom->USART.DATA.reg;
		if (c == interruptSeq[numInterruptBytesMatched])
		{
			++numInterruptBytesMatched;
			if (numInterruptBytesMatched == ARRAY_SIZE(interruptSeq))
			{
				numInterruptBytesMatched = 0;
				if (interruptCallback != nullptr)
				{
					interruptCallback(this);
				}
			}
		}
		else
		{
			numInterruptBytesMatched = 0;
		}

		if (!rxBuffer.PutItem(c))
		{
			++errors.bufferOverrun;
		}
	}

	// Check for transmit buffer empty
	if (status & SERCOM_USART_INTFLAG_DRE)
	{
		uint8_t c;
		if (txBuffer.GetItem(c))
		{
			sercom->USART.DATA.reg = c;
#ifdef RTOS
			if (txWaitingTask != nullptr && txBuffer.SpaceLeft() >= txBuffer.GetCapacity()/2)
			{
				TaskBase::GiveFromISR(txWaitingTask);
				txWaitingTask = nullptr;
			}
#endif
		}
		else
		{
			sercom->USART.INTENCLR.reg = SERCOM_USART_INTENCLR_DRE;
#ifdef RTOS
			if (txWaitingTask != nullptr)
			{
				TaskBase::GiveFromISR(txWaitingTask);
				txWaitingTask = nullptr;
			}
#endif
		}
	}

	// Check for error
	if (status & SERCOM_USART_INTFLAG_ERROR)
	{
		const uint16_t stat2 = sercom->USART.STATUS.reg;
		if (stat2 & SERCOM_USART_STATUS_BUFOVF)
		{
			++errors.uartOverrun;
		}
		if (stat2 & SERCOM_USART_STATUS_FERR)
		{
			++errors.framing;
		}
		if (stat2 && (SERCOM_USART_STATUS_BUFOVF || SERCOM_USART_STATUS_FERR))
		{
			rxBuffer.PutItem(0x7F);
		}
		sercom->USART.STATUS.reg = stat2;
		sercom->USART.INTFLAG.reg = SERCOM_USART_INTFLAG_ERROR;			// clear the error
	}
}

#endif

AsyncSerial::InterruptCallbackFn AsyncSerial::SetInterruptCallback(InterruptCallbackFn f) noexcept
{
	const InterruptCallbackFn ret = interruptCallback;
	interruptCallback = f;
	return ret;
}

void AsyncSerial::setInterruptPriority(uint32_t rxPrio, uint32_t txAndErrorPrio) const noexcept
{
	const IRQn irqNumber = Serial::GetSercomIRQn(sercomNumber);
	NVIC_SetPriority(irqNumber, txAndErrorPrio);
	NVIC_SetPriority((IRQn)(irqNumber + 2), rxPrio);
	NVIC_SetPriority((IRQn)(irqNumber + 3), txAndErrorPrio);
}

// End
