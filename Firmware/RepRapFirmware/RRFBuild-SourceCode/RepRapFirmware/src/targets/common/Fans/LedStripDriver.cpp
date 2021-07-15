/*
 * LedStripDriver.cpp
 *
 *  Created on: 18 Jul 2018
 *      Author: David/GA
 * This is a simplified version of the standard Duet3D code that only supports NeoPixels
 * and which reduces the memory required.
 */

#include "LedStripDriver.h"

#if SUPPORT_LED_STRIPS

#include <GCodes/GCodeBuffer/GCodeBuffer.h>
#include <Movement/StepTimer.h>
#include <Platform/RepRap.h>
#include <GCodes/GCodes.h>


namespace LedStripDriver
{
	constexpr uint32_t MinNeoPixelResetTicks = (250 * StepTimer::StepClockRate)/1000000;		// 250us minimum Neopixel reset time

	constexpr size_t ChunkBufferSize = 180;								// the size of our buffer NeoPixels use 3 bytes per pixel

	static uint32_t ledType = 1;										// 0 = DotStar (not supported on Duet 3 Mini), 1 = NeoPixel, 2 = NeoPixel on Mini 12864 display (Duet 3 Mini only)
	static unsigned int numAlreadyInBuffer = 0;							// number of pixels already store in the buffer (NeoPixel only)
	static uint8_t *chunkBuffer = nullptr;								// buffer for sending data to LEDs
	constexpr size_t MaxLeds = ChunkBufferSize/3;

	// Send data to NeoPixel LEDs by bit banging
	static GCodeResult BitBangNeoPixelData(uint8_t red, uint8_t green, uint8_t blue, uint32_t numLeds, bool following) noexcept
	{
		if (NeopixelOutPin == NoPin) return GCodeResult::ok;

		uint8_t *p = chunkBuffer + (3 * numAlreadyInBuffer);
		while (numLeds != 0 && p <= chunkBuffer + ChunkBufferSize - 3)
		{
			*p++ = green;
			*p++ = red;
			*p++ = blue;
			--numLeds;
			++numAlreadyInBuffer;
		}

		if (!following)
		{
			const uint32_t T0H = NanosecondsToCycles(300);
			const uint32_t T0L = NanosecondsToCycles(850);
			const uint32_t T1H = NanosecondsToCycles(800);
			const uint32_t T1L = NanosecondsToCycles(475);
			const uint8_t *q = chunkBuffer;
			uint32_t nextDelay = T0L;
			IrqDisable();
			uint32_t lastTransitionTime = GetCurrentCycles();

			while (q < p)
			{
				uint8_t c = *q++;
				for (unsigned int i = 0; i < 8; ++i)
				{
					if (c & 0x80)
					{
						lastTransitionTime = DelayCycles(lastTransitionTime, nextDelay);
						fastDigitalWriteHigh(NeopixelOutPin);
						lastTransitionTime = DelayCycles(lastTransitionTime, T1H);
						fastDigitalWriteLow(NeopixelOutPin);
						nextDelay = T1L;
					}
					else
					{
						lastTransitionTime = DelayCycles(lastTransitionTime, nextDelay);
						fastDigitalWriteHigh(NeopixelOutPin);
						lastTransitionTime = DelayCycles(lastTransitionTime, T0H);
						fastDigitalWriteLow(NeopixelOutPin);
						nextDelay = T0L;
					}
					c <<= 1;
				}
			}
			IrqEnable();
			numAlreadyInBuffer = 0;
		}
		return GCodeResult::ok;
	}
}

void LedStripDriver::Init() noexcept
{
	if (NeopixelOutPin != NoPin)
	{
		IoPort::SetPinMode(NeopixelOutPin, PinMode::OUTPUT_LOW);
		chunkBuffer = new uint8_t[ChunkBufferSize];
	}
}

// This function handles M150
// For DotStar LEDs:
// 	We can handle an unlimited length LED strip, because we can send the data in multiple chunks.
//	So whenever we receive a m150 command, we send the data immediately, in multiple chunks if our DMA buffer is too small to send it as a single chunk.
//	To send multiple chunks, we process the command once per chunk, using numRemaining to keep track of how many more LEDs need to be written to
// For NeoPixel LEDs:
//	If there is a gap or more then about 9us in transmission, the string will reset and the next command will be taken as applying to the start of the strip.
//  Therefore we need to DMA the data for all LEDs in one go. So the maximum strip length is limited by the size of our DMA buffer.
//	We buffer up incoming data until we get a command with the Following parameter missing or set to zero, then we DMA it all.
GCodeResult LedStripDriver::SetColours(GCodeBuffer& gb, const StringRef& reply) THROWS(GCodeException)
{
	bool seen = false;

	// Deal with changing the LED type first
	if (gb.Seen('X'))
	{
		seen = true;
		const uint32_t newType = gb.GetLimitedUIValue('X', 2, 3); 
		const bool typeChanged = (newType != ledType);
		if (newType != 2)
		{
			return GCodeResult::ok;
		}

		if (typeChanged)
		{
			ledType = newType;
			numAlreadyInBuffer = 0;
			if (ledType == 2)
			{
				return GCodeResult::notFinished;
			}
		}
	}

	if (ledType == 2)
	{
		// Interrupts are disabled while bit-banging the data, so make sure movement has stopped
		if (!reprap.GetGCodes().LockMovementAndWaitForStandstill(gb))
		{
			return GCodeResult::notFinished;
		}
	}

	// Get the RGB and brightness values
	uint32_t red = 0, green = 0, blue = 0, brightness = 128, numLeds = MaxLeds;
	bool following = false;
	gb.TryGetLimitedUIValue('R', red, seen, 256);
	gb.TryGetLimitedUIValue('U', green, seen, 256);
	gb.TryGetLimitedUIValue('B', blue, seen, 256);
	if (gb.Seen('P'))
	{
		brightness = gb.GetLimitedUIValue('P', 256);						// valid P values are 0-255
	}
	else if (gb.Seen('Y'))
	{
		brightness = gb.GetLimitedUIValue('Y',  32) << 3;					// valid Y values are 0-31
	}
	gb.TryGetUIValue('S', numLeds, seen);
	gb.TryGetBValue('F', following, seen);
	if (!seen || (numLeds == 0 && !following))
	{
		return GCodeResult::ok;
	}

	switch (ledType)
	{
	case 2:
		// Scale RGB by the brightness
		return BitBangNeoPixelData(	(uint8_t)((red * brightness + 255) >> 8),
									(uint8_t)((green * brightness + 255) >> 8),
									(uint8_t)((blue * brightness + 255) >> 8),
									numLeds, following
							      );
	}
	return GCodeResult::ok;													// should never get here
}

#endif

// End
