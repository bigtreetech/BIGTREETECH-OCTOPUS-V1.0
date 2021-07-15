/*
  Copyright (c) 2011-2012 Arduino.  All right reserved.

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

#include <Interrupts.h>
#include <pmc/pmc.h>

struct InterruptCallback
{
	StandardCallbackFunction func;
	CallbackParameter param;

	InterruptCallback() : func(nullptr) { }
};

static InterruptCallback callbacksPioA[32];
static InterruptCallback callbacksPioB[32];
static InterruptCallback callbacksPioC[32];
#ifdef ID_PIOD
static InterruptCallback callbacksPioD[32];
#endif
#ifdef ID_PIOE
static InterruptCallback callbacksPioE[32];
#endif

/* Configure PIO interrupt sources */
static void __initialize()
{
	pmc_enable_periph_clk(ID_PIOA);
	NVIC_DisableIRQ(PIOA_IRQn);
	NVIC_ClearPendingIRQ(PIOA_IRQn);
	NVIC_EnableIRQ(PIOA_IRQn);

	pmc_enable_periph_clk(ID_PIOB);
	NVIC_DisableIRQ(PIOB_IRQn);
	NVIC_ClearPendingIRQ(PIOB_IRQn);
	NVIC_EnableIRQ(PIOB_IRQn);

	pmc_enable_periph_clk(ID_PIOC);
	NVIC_DisableIRQ(PIOC_IRQn);
	NVIC_ClearPendingIRQ(PIOC_IRQn);
	NVIC_EnableIRQ(PIOC_IRQn);

#ifdef ID_PIOD
	pmc_enable_periph_clk(ID_PIOD);
	NVIC_DisableIRQ(PIOD_IRQn);
	NVIC_ClearPendingIRQ(PIOD_IRQn);
	NVIC_EnableIRQ(PIOD_IRQn);
#endif

#ifdef ID_PIOE
	pmc_enable_periph_clk(ID_PIOE);
	NVIC_DisableIRQ(PIOE_IRQn);
	NVIC_ClearPendingIRQ(PIOE_IRQn);
	NVIC_EnableIRQ(PIOE_IRQn);
#endif
}

// Attach an interrupt to the specified pin returning true if successful
bool attachInterrupt(Pin pin, StandardCallbackFunction callback, InterruptMode mode, CallbackParameter param) noexcept
{
	const PinDescriptionBase * const pinDesc = AppGetPinDescription(pin);
	if (pinDesc == nullptr)
	{
		return false;
	}

	static bool enabled = false;
	if (!enabled)
	{
		__initialize();
		enabled = true;
	}

	// Retrieve pin information
	Pio * const pio = GpioPort(pin);
	const uint32_t mask = GpioMask(pin);
	pio->PIO_IDR = mask;									// ensure the interrupt is disabled before we start changing the tables
	const unsigned int pos = LowestSetBitNumber(mask);		// only one bit should be set

	// Set callback function and parameter
	if (pio == PIOA)
	{
		callbacksPioA[pos].func = callback;
		callbacksPioA[pos].param = param;
	}
	else if (pio == PIOB)
	{
		callbacksPioB[pos].func = callback;
		callbacksPioB[pos].param = param;
	}
	else if (pio == PIOC)
	{
		callbacksPioC[pos].func = callback;
		callbacksPioC[pos].param = param;
	}
#ifdef ID_PIOD
	else if (pio == PIOD)
	{
		callbacksPioD[pos].func = callback;
		callbacksPioD[pos].param = param;
	}
#endif
#ifdef ID_PIOE
	else if (pio == PIOE)
	{
		callbacksPioE[pos].func = callback;
		callbacksPioE[pos].param = param;
	}
#endif

	// Configure the interrupt mode
	if (mode == InterruptMode::change)
	{
		// Disable additional interrupt mode (detects both rising and falling edges)
		pio->PIO_AIMDR = mask;
	}
	else
	{
		// Enable additional interrupt mode
		pio->PIO_AIMER = mask;

		// Select mode of operation
		switch(mode)
		{
		case InterruptMode::low:
			pio->PIO_LSR = mask;    // "Level" Select Register
			pio->PIO_FELLSR = mask; // "Falling Edge / Low Level" Select Register
			break;

		case InterruptMode::high:
			pio->PIO_LSR = mask;    // "Level" Select Register
			pio->PIO_REHLSR = mask; // "Rising Edge / High Level" Select Register
			break;

		case InterruptMode::falling:
			pio->PIO_ESR = mask;    // "Edge" Select Register
			pio->PIO_FELLSR = mask; // "Falling Edge / Low Level" Select Register
			break;

		case InterruptMode::rising:
			pio->PIO_ESR = mask;    // "Edge" Select Register
			pio->PIO_REHLSR = mask; // "Rising Edge / High Level" Select Register
			break;

		default:
			break;
		}
	}

	// Enable interrupt
	if (mode != InterruptMode::none)
	{
		pio->PIO_IFER = mask;		// enable glitch filter on this pin
		pio->PIO_IER = mask;		// enable interrupt on this pin
	}

	return true;
}

void detachInterrupt(Pin pin) noexcept
{
	const PinDescriptionBase * const pinDesc = AppGetPinDescription(pin);
	if (pinDesc != nullptr)
	{
		// Retrieve pin information
		Pio * const pio = GpioPort(pin);
		const uint32_t mask = GpioMask(pin);

		// Disable interrupt
		pio->PIO_IDR = mask;
	}
}

// Common PIO interrupt handler
void CommonPioHandler(Pio *pio, const InterruptCallback callbacks[])
{
	uint32_t isr = pio->PIO_ISR & pio->PIO_IMR;
	while (isr != 0)
	{
		const unsigned int pos = LowestSetBitNumber(isr);
		if (callbacks[pos].func != nullptr)
		{
			callbacks[pos].func(callbacks[pos].param);
		}
		isr &= ~(1u << pos);
	}
}

extern "C" void PIOA_Handler(void)
{
	CommonPioHandler(PIOA, callbacksPioA);
}

extern "C" void PIOB_Handler(void)
{
	CommonPioHandler(PIOB, callbacksPioB);
}

extern "C" void PIOC_Handler(void)
{
	CommonPioHandler(PIOC, callbacksPioC);
}

#ifdef ID_PIOD
extern "C" void PIOD_Handler(void)
{
	CommonPioHandler(PIOD, callbacksPioD);
}
#endif

#ifdef ID_PIOE
extern "C" void PIOE_Handler(void)
{
	CommonPioHandler(PIOE, callbacksPioE);
}
#endif

// End
