/*
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

#ifndef TwoWire_h
#define TwoWire_h

#include "CoreIO.h"
#if LPC17xx
#include "Wire/Wire.h"
#else
#if SAME70
// TWI disabled for now
#else

#include "Stream.h"

#define BUFFER_LENGTH 32

#if SAME70
# define Twi Twihs
#endif

class TwoWire
{
public:
	struct ErrorCounts
	{
		uint32_t naks;
		uint32_t sendTimeouts;
		uint32_t recvTimeouts;
		uint32_t finishTimeouts;
		uint32_t resets;

		void Clear() noexcept;
	};

	typedef uint32_t (*WaitForStatusFunc)(Twi *twi, uint32_t bitsToWaitFor) noexcept;

	TwoWire(Twi *twi, void(*begin_cb)(void) noexcept) noexcept;

	void BeginMaster(uint32_t p_clockFrequency) noexcept;
	size_t Transfer(uint16_t address, uint8_t *buffer, size_t numToWrite, size_t numToRead, WaitForStatusFunc statusWaitFunc = DefaultWaitForStatusFunc) noexcept;
	ErrorCounts GetErrorCounts(bool clear) noexcept;

	static uint32_t DefaultWaitForStatusFunc(Twi *twi, uint32_t bitsToWaitFor) noexcept;

private:
	void ReInit() noexcept;
	bool WaitForStatus(uint32_t statusBit, uint32_t& timeoutErrorCounter, WaitForStatusFunc statusWaitFunc) noexcept;
	bool WaitTransferComplete(WaitForStatusFunc statusWaitFunc) noexcept;
	bool WaitByteSent(WaitForStatusFunc statusWaitFunc) noexcept;
	bool WaitByteReceived(WaitForStatusFunc statusWaitFunc) noexcept;
	size_t InternalTransfer(uint16_t address, uint8_t *buffer, size_t numToWrite, size_t numToRead, WaitForStatusFunc statusWaitFunc) noexcept;

	Twi *twi;							// TWI instance
	void (*onBeginCallback)(void) noexcept;		// called before initialization
	ErrorCounts errorCounts;			// error counts
	uint32_t clockFrequency;			// the clock frequency we were asked for
};

#endif
#endif
#endif

