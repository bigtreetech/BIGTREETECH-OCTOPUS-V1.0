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

//SD: Modified to support LPC

#include "AnalogOut.h"
#include "CoreImp.h"

extern "C" void debugPrintf(const char* fmt, ...) __attribute__ ((format (printf, 1, 2)));

// Initialise this module
extern void AnalogOut::Init() noexcept
{
	// Nothing to do yet
}

// Analog write to DAC, PWM, TC or plain output pin
// Setting the frequency of a TC or PWM pin to zero resets it so that the next call to AnalogOut with a non-zero frequency
// will re-initialise it. The pinMode function relies on this.
void AnalogOut::Write(Pin pin, float ulValue, uint16_t freq) noexcept
{
	if (pin > NumTotalPins || std::isnan(ulValue))
	{
		return;
	}

    ulValue = constrain<float>(ulValue, 0.0, 1.0);

    //is the pin configured as a Software PWM?
    if (AnalogWriteSoftwarePWM(ulValue, freq, pin))
    {
        return;
    }

    
    //is the pin configured as a Servo?
    if (AnalogWriteServo(ulValue, freq, pin))
    {
        return;
    }
        
	// Fall back to digital write
	pinMode(pin, (ulValue < 0.5) ? OUTPUT_LOW : OUTPUT_HIGH);
}


 // Return true if this pin exists and can do PWM
bool IsPwmCapable(Pin pin) noexcept
{
    if (pin > NumTotalPins || pin == NoPin) return false;
    return CanDoSoftwarePWM(pin);
}

bool ConfigurePinForPWM(Pin pin, bool outputHigh) noexcept
{
    return ConfigurePinForSoftwarePWM(pin);
}

void AnalogOut::ReleasePWMPin(Pin pin) noexcept
{
    ReleaseSoftwarePWMPin(pin);
}


// End
