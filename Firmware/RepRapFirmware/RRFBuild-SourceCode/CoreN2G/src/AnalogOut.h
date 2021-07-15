/*
 * AnalogOut.h
 *
 *  Created on: 9 Jul 2019
 *      Author: David
 */

#ifndef SRC_HARDWARE_ANALOGOUT_H_
#define SRC_HARDWARE_ANALOGOUT_H_

#include <CoreIO.h>

namespace AnalogOut
{
	// Initialise this module
	extern void Init() noexcept;

	// Write a PWM value to the specified pin. 'val' will be constrained to be between 0.0 and 1.0 in this module.
	extern void Write(Pin pin, float val, PwmFrequency freq = 500) noexcept;

#if STM32F4 || LPC17xx
	extern void ReleasePWMPin(Pin pin) noexcept;
#endif
}

#endif /* SRC_HARDWARE_ANALOGOUT_H_ */
