/*
 * TwoWire.h - TWI/I2C library for Arduino Due
 * Copyright (c) 2011 Cristian Maglie <c.maglie@bug.st>.
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <Wire.h>

#if SAME70
// TWI disabled for now
#else

#if SAME70
#include "twihs/twihs.h"
#else
#include "twi/twi.h"
#endif

#include <cstring>

void TwoWire::ErrorCounts::Clear() noexcept
{
	naks = sendTimeouts = recvTimeouts = finishTimeouts = resets = 0;
}

// This is the default wait-for-status function.
// It wait until either 2 clock ticks have passed (so we have waited for at least 1ms) or one or more of the status bits we are interested in has been set.
// Reading some status bits clears them, so we return the status.
/*static*/ uint32_t TwoWire::DefaultWaitForStatusFunc(Twi *twi, uint32_t bitsToWaitFor) noexcept
{
	const uint32_t startMillis = millis();
	bool timedOut;
	uint32_t sr;
	do
	{
		timedOut = (millis() - startMillis > 2);
		sr = twi->TWI_SR;							// read this after checking for timeout, in case we get descheduled between the two statements
	} while (!timedOut && (sr & bitsToWaitFor) == 0);
	return sr;
}

// Wait for a status bit or NAK to be set, returning true if successful and it wasn't NAK
bool TwoWire::WaitForStatus(uint32_t statusBit, uint32_t& timeoutErrorCounter, WaitForStatusFunc statusWaitFunc) noexcept
{
	const uint32_t sr = statusWaitFunc(twi, statusBit | TWI_SR_NACK);
	if ((sr & TWI_SR_NACK) != 0)
	{
		++errorCounts.naks;
		return false;
	}
	if ((sr & statusBit) != 0)
	{
		return true;
	}
	++timeoutErrorCounter;
	return false;
}

inline bool TwoWire::WaitTransferComplete(WaitForStatusFunc statusWaitFunc) noexcept
{
	return WaitForStatus(TWI_SR_TXCOMP, errorCounts.finishTimeouts, statusWaitFunc);
}

inline bool TwoWire::WaitByteSent(WaitForStatusFunc statusWaitFunc) noexcept
{
	return WaitForStatus(TWI_SR_TXRDY, errorCounts.sendTimeouts, statusWaitFunc);
}

inline bool TwoWire::WaitByteReceived(WaitForStatusFunc statusWaitFunc) noexcept
{
	return WaitForStatus(TWI_SR_RXRDY, errorCounts.recvTimeouts, statusWaitFunc);
}

TwoWire::TwoWire(Twi *_twi, void(*_beginCb)(void) noexcept) noexcept : twi(_twi), onBeginCallback(_beginCb), clockFrequency(100000)
{
}

void TwoWire::ReInit()
{
	twi->TWI_PTCR = UART_PTCR_RXTDIS | UART_PTCR_TXTDIS;	// disable PDC channel

	twi_options_t opt;
	opt.speed = clockFrequency;
	opt.master_clk = SystemPeripheralClock();
	opt.chip = opt.smbus = 0;
	twi_master_init(twi, &opt);
}

// Begin in master mode
void TwoWire::BeginMaster(uint32_t p_clockFrequency) noexcept
{
	clockFrequency = p_clockFrequency;
	if (onBeginCallback != nullptr)
	{
		onBeginCallback();
	}
	errorCounts.Clear();
	ReInit();
}

// Write then read data
size_t TwoWire::Transfer(uint16_t address, uint8_t *buffer, size_t numToWrite, size_t numToRead, WaitForStatusFunc statusWaitFunc) noexcept
{
	// If an empty transfer, nothing to do
	if (numToRead + numToWrite == 0)
	{
		return 0;
	}

	size_t bytesTransferred;
	for (unsigned int triesDone = 0; triesDone < 3; ++triesDone)
	{
		bytesTransferred = InternalTransfer(address, buffer, numToWrite, numToRead, statusWaitFunc);
		if (bytesTransferred == numToRead + numToWrite)
		{
			break;
		}

		// Had an I2C error, so re-initialise and try again
		ReInit();
		++errorCounts.resets;
	}
	return bytesTransferred;
}

size_t TwoWire::InternalTransfer(uint16_t address, uint8_t *buffer, size_t numToWrite, size_t numToRead, WaitForStatusFunc statusWaitFunc) noexcept
{
	// Set up the mode register and address
	if (address >= 0x80)
	{
		// 10-bit address
		const uint32_t topAddress = 0b01111000 | ((address >> 8) & 3);
	    twi->TWI_MMR = (1 << 8) | (topAddress << 16);
	    twi->TWI_IADR = address & 0x00FF;
	}
	else
	{
		// 7-bit address
	    twi->TWI_MMR = (uint32_t)address << 16;
	    twi->TWI_IADR = 0;
	}

	size_t bytesSent = 0;
	if (numToWrite != 0)
	{
		// Send all bytes except the last one.
		// Ideally, if there are bytes to read as well as write, we would not send a STOP after sending all the bytes.
		// Unfortunately, the SAM TWI peripheral doesn't provide any means of reporting when the transmission is complete if we don't send STOP after it.
		while (bytesSent + 1 < numToWrite)
		{
			twi->TWI_THR = *buffer++;
			if (!WaitByteSent(statusWaitFunc))
			{
				twi->TWI_CR = TWI_CR_STOP;
				(void)WaitTransferComplete(statusWaitFunc);
				return bytesSent;
			}
			++bytesSent;
		}

		twi->TWI_THR = *buffer++;
		twi->TWI_CR = TWI_CR_STOP;
		if (WaitByteSent(statusWaitFunc))
		{
			++bytesSent;
		}
		(void)WaitTransferComplete(statusWaitFunc);
		if (bytesSent < numToWrite || numToRead == 0)
		{
			return bytesSent;
		}
	}

	// There are bytes to read, and if there were any bytes to send then we have sent them all
    twi->TWI_MMR |= TWI_MMR_MREAD;							// change the mode to read
	size_t bytesReceived = 0;
	if (numToRead == 1)
	{
		twi->TWI_CR = TWI_CR_START | TWI_CR_STOP;
		if (WaitByteReceived(statusWaitFunc))
		{
			*buffer = twi->TWI_RHR;
			++bytesReceived;
		}

		(void)WaitTransferComplete(statusWaitFunc);
		return bytesSent + bytesReceived;
	}

	// Multi-byte read. We must set the STOP flag before we read the penultimate byte from the RHR.
	twi->TWI_CR = TWI_CR_START;
	for (;;)
	{
		if (!WaitByteReceived(statusWaitFunc))
		{
			twi->TWI_CR = TWI_CR_STOP;						// this may not do any good
			(void)WaitTransferComplete(statusWaitFunc);		// neither may this
			return bytesSent + bytesReceived;
		}

		++bytesReceived;
		if (bytesReceived + 1 == numToRead)
		{
			break;
		}

		*buffer++ = twi->TWI_RHR;
	}

	// The penultimate byte is in the RHR
	twi->TWI_CR = TWI_CR_STOP;
	*buffer++ = twi->TWI_RHR;
	if (WaitByteReceived(statusWaitFunc))
	{
		*buffer++ = twi->TWI_RHR;
		++bytesReceived;
	}
	(void)WaitTransferComplete(statusWaitFunc);
	return bytesSent + bytesReceived;

}

TwoWire::ErrorCounts TwoWire::GetErrorCounts(bool clear) noexcept
{
	const irqflags_t flags = IrqSave();
	const ErrorCounts ret = errorCounts;
	if (clear)
	{
		errorCounts.Clear();
	}
	IrqRestore(flags);
	return ret;
}

#endif

// End
