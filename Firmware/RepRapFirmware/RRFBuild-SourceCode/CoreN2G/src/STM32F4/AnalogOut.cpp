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

#include <CoreImp.h>
#include <AnalogOut.h>
#include <HybridPWM.h>
extern "C" void debugPrintf(const char* fmt, ...) __attribute__ ((format (printf, 1, 2)));
// Initialise this module
extern void AnalogOut::Init()
{
	// Nothing to do yet
}

// Analog write to DAC, PWM, TC or plain output pin
// Setting the frequency of a TC or PWM pin to zero resets it so that the next call to AnalogOut with a non-zero frequency
// will re-initialise it. The pinMode function relies on this.
void AnalogOut::Write(Pin pin, float ulValue, PwmFrequency freq) noexcept
{
	if (pin == NoPin) return;
	ulValue = constrain<float>(ulValue, 0.0, 1.0);
	HybridPWMPin* hp = HybridPWMPin::find(pin);
	if (hp == nullptr)
	{
		debugPrintf("Trying set set analog value for unallocated pin %x\n", static_cast<int>(pin));
		return;
	}
	hp->set(ulValue, freq);
}

void AnalogOut::ReleasePWMPin(Pin pin)
{
	HybridPWMPin* hp = HybridPWMPin::find(pin);
	if (hp == nullptr)
	{
		debugPrintf("Release of unallocated PWM pin %x\n", static_cast<int>(pin));
		return;
	}
	debugPrintf("Release of allocated PWM pin %x\n", static_cast<int>(pin));
	hp->free();
}
// End
