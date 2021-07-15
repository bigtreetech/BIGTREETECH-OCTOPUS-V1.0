/*
 * ThermocoupleSensor6675.cpp
 *
 *  Created on: 8 Jun 2017
 *      Author: David
 */

// MAX6675 thermocouple chip
//
// The MAX6675 continuously samples a Type K thermocouple.  When the MAX6675
// is selected via its chip select (CS) pin, it unconditionally writes a 16 bit
// sequence onto the bus. 
//
// Bits  -- Interpretation
// -----    -----------------------------------------------------------------
//    15 -- Dummy always 0
// 14:03 -- 12 bit, unsigned temperature 0-1023.75
//    02 -- Open connection if 1
//    01 -- Device ID always 0
//    00 -- Three-State?

#include "ThermocoupleSensor6675.h"
#include "Platform/RepRap.h"
#include "Platform/Platform.h"
#include "GCodes/GCodeBuffer/GCodeBuffer.h"

const uint32_t MAX6675_Frequency = 4000000;	// maximum for MAX6675 is 5MHz

// SPI modes:
// If the inactive state of SCL is LOW (CPOL = 0) (in the case of the MAX6675, this is sampled on the falling edge of CS):
// The MAX6675 sets up the first data bit after the falling edge of CLK, and changes the data on each falling clock edge.
// So the SAM needs to sample data on the rising clock edge. This requires NCPHA = 1.
const SpiMode MAX6675_SpiMode = SPI_MODE_0;

// Define the minimum interval between readings
const uint32_t MinimumReadInterval = 250;		// minimum interval between reads, in milliseconds

ThermocoupleSensor6675::ThermocoupleSensor6675(unsigned int sensorNum) noexcept
	: SpiTemperatureSensor(sensorNum, "Thermocouple (MAX6675)", MAX6675_SpiMode, MAX6675_Frequency)
{
}

// Configure this temperature sensor
GCodeResult ThermocoupleSensor6675::Configure(GCodeBuffer& gb, const StringRef& reply, bool& changed)
{
	if (!ConfigurePort(gb, reply, changed))
	{
		return GCodeResult::error;
	}

	TryConfigureSensorName(gb, changed);

	if (changed)
	{
		// Initialise the sensor
		InitSpi();
		lastReadingTime = millis();
	}
	else
	{
		CopyBasicDetails(reply);
	}
	return GCodeResult::ok;
}

void ThermocoupleSensor6675::Poll() noexcept
{
	uint32_t rawVal;
	TemperatureError sts = DoSpiTransaction(nullptr, 2, rawVal);
	if (sts != TemperatureError::success)
	{
		SetResult(sts);
	}
	else
	{
		if ((rawVal & 0x00008002) != 0)
		{
			// These two bits should always read 0. Likely the entire read was 0xFF 0xFF which is not uncommon when first powering up
			lastResult = TemperatureError::ioError;
		}
		else if ((rawVal & 0x00000004) != 0)		// check the fault bits
		{
			// Open Circuit
			SetResult(TemperatureError::openCircuit);
		}
		else
		{
			rawVal >>= 3;							// shift the 12-bit temperature data to the bottom of the word
			// And convert to from units of 1/4C to 1C
			SetResult((float)(0.25 * (float)(int32_t)rawVal), TemperatureError::success);
		}
	}
}

// End
