/*
 * PinInterrupts.cpp
 *
 *  Created on: 6 Jul 2019
 *      Author: David
 */

#include "Interrupts.h"

#if SAME5x
#include <hri_gclk_e54.h>
constexpr unsigned int ExintGclkNum = GclkNum120MHz;
#elif SAMC21
#include <hri_gclk_c21.h>
constexpr unsigned int ExintGclkNum = GclkNum48MHz;
#endif

struct InterruptCallback
{
	StandardCallbackFunction func;
	CallbackParameter param;

	InterruptCallback() noexcept : func(nullptr) { }
};

// On the SAME5x we have 16 external interrupts shared between multiple pins. Only one of those pins may be programmed to generate an interrupt.
// Therefore we will have a clash if we try to attach an interrupt to two pins that use the same EXINT.
// The pin table ensures that only one pin is flagged as able to use each EXINT.
static InterruptCallback exintCallbacks[16];

void InitialiseExints() noexcept
{
	hri_gclk_write_PCHCTRL_reg(GCLK, EIC_GCLK_ID, GCLK_PCHCTRL_GEN(ExintGclkNum) | GCLK_PCHCTRL_CHEN);
	hri_mclk_set_APBAMASK_EIC_bit(MCLK);

	if (!hri_eic_is_syncing(EIC, EIC_SYNCBUSY_SWRST)) {
		if (hri_eic_get_CTRLA_reg(EIC, EIC_CTRLA_ENABLE)) {
			hri_eic_clear_CTRLA_ENABLE_bit(EIC);
			hri_eic_wait_for_sync(EIC, EIC_SYNCBUSY_ENABLE);
		}
		hri_eic_write_CTRLA_reg(EIC, EIC_CTRLA_SWRST);
	}
	hri_eic_wait_for_sync(EIC, EIC_SYNCBUSY_SWRST);

	hri_eic_write_CTRLA_CKSEL_bit(EIC, 0);				// clocked by GCLK

	// Leave NMI disabled (hri_eic_write_NMICTRL_reg)
	// Leave event control disabled (hri_eic_write_EVCTRL_reg)

	hri_eic_write_ASYNCH_reg(EIC, 0);					// all channels synchronous (needed to have debouncing or filtering)

#if SAME5x
	hri_eic_write_DEBOUNCEN_reg(EIC, 0);				// debouncing disabled
#elif SAMC21
	// Only the SAMC21N has the debounce register, the SAMC21G that we use doesn't have it
#else
# error Undefined processor
#endif

#if 0
	hri_eic_write_DPRESCALER_reg(
	    EIC,
	    (EIC_DPRESCALER_PRESCALER0(CONF_EIC_DPRESCALER0)) | (CONF_EIC_STATES0 << EIC_DPRESCALER_STATES0_Pos)
	        | (EIC_DPRESCALER_PRESCALER1(CONF_EIC_DPRESCALER1)) | (CONF_EIC_STATES1 << EIC_DPRESCALER_STATES1_Pos)
	        | CONF_EIC_TICKON << EIC_DPRESCALER_TICKON_Pos | 0);
#endif

	hri_eic_write_CONFIG_reg(EIC, 0, 0);
	hri_eic_write_CONFIG_reg(EIC, 1, 0);

	hri_eic_set_CTRLA_ENABLE_bit(EIC);
}

// Attach an interrupt to the specified pin returning true if successful
bool attachInterrupt(Pin pin, StandardCallbackFunction callback, InterruptMode mode, CallbackParameter param) noexcept
{
	const PinDescriptionBase * const pinDesc = AppGetPinDescription(pin);
	if (pinDesc == nullptr)
	{
		return false;
	}

	const ExintNumber exint = pinDesc->exintNumber;
	if (exint >= 16)
	{
		return false;
	}

	// Configure the interrupt mode
	uint32_t modeWord;
	switch (mode)
	{
	case InterruptMode::low:		modeWord = EIC_CONFIG_SENSE0_LOW_Val  | EIC_CONFIG_FILTEN0; break;
	case InterruptMode::high:		modeWord = EIC_CONFIG_SENSE0_HIGH_Val | EIC_CONFIG_FILTEN0; break;
	case InterruptMode::falling:	modeWord = EIC_CONFIG_SENSE0_FALL_Val | EIC_CONFIG_FILTEN0; break;
	case InterruptMode::rising:		modeWord = EIC_CONFIG_SENSE0_RISE_Val | EIC_CONFIG_FILTEN0; break;
	case InterruptMode::change:		modeWord = EIC_CONFIG_SENSE0_BOTH_Val | EIC_CONFIG_FILTEN0; break;
	default:						modeWord = EIC_CONFIG_SENSE0_NONE_Val; break;
	}

	{
		AtomicCriticalSectionLocker lock;

		exintCallbacks[exint].func = callback;
		exintCallbacks[exint].param = param;

		// Switch the pin into EIC mode
		SetPinFunction(pin, GpioPinFunction::A);		// EIC is always on peripheral A

		const unsigned int shift = (exint & 7u) << 2u;
		const uint32_t mask = ~(0x0000000F << shift);

		EIC->CTRLA.reg &= ~EIC_CTRLA_ENABLE;
		hri_eic_wait_for_sync(EIC, EIC_SYNCBUSY_ENABLE);

		if (exint < 8)
		{
			EIC->CONFIG[0].reg = (EIC->CONFIG[0].reg & mask) | (modeWord << shift);
		}
		else
		{
			EIC->CONFIG[1].reg = (EIC->CONFIG[1].reg & mask) | (modeWord << shift);
		}

		EIC->CTRLA.reg |= EIC_CTRLA_ENABLE;
		hri_eic_wait_for_sync(EIC, EIC_SYNCBUSY_ENABLE);

		// Enable interrupt
		EIC->INTENSET.reg = 1ul << exint;
	}

#if SAME5x
	NVIC_EnableIRQ((IRQn)(EIC_0_IRQn + exint));
#elif SAMC21
	NVIC_EnableIRQ(EIC_IRQn);
#else
# error Undefined processor
#endif

	return true;
}

void detachInterrupt(Pin pin) noexcept
{
	const PinDescriptionBase * const pinDesc = AppGetPinDescription(pin);
	if (pinDesc != nullptr)
	{
		const ExintNumber exint = pinDesc->exintNumber;
		if (exint < 16)
		{
			const unsigned int shift = (exint & 7u) << 2u;
			const uint32_t mask = ~((uint32_t)0x0000000F << shift);

			EIC->CTRLA.reg &= ~EIC_CTRLA_ENABLE;
			hri_eic_wait_for_sync(EIC, EIC_SYNCBUSY_ENABLE);

			if (exint < 8)
			{
				EIC->CONFIG[0].reg &= mask;
			}
			else
			{
				EIC->CONFIG[1].reg &= mask;
			}

			EIC->CTRLA.reg |= EIC_CTRLA_ENABLE;
			hri_eic_wait_for_sync(EIC, EIC_SYNCBUSY_ENABLE);

			// Disable the interrupt
			EIC->INTENCLR.reg = 1ul << exint;
			EIC->INTFLAG.reg = 1ul << exint;

			// Switch the pin out of EIC mode
			ClearPinFunction(pin);

			exintCallbacks[exint].func = nullptr;
		}
	}
}

ExintNumber AttachEvent(Pin pin, InterruptMode mode, bool enableFilter) noexcept
{
	const PinDescriptionBase * const pinDesc = AppGetPinDescription(pin);
	if (pinDesc == nullptr)
	{
		return Nx;
	}

	const ExintNumber exint = pinDesc->exintNumber;
	if (exint >= 16)
	{
		return Nx;
	}

	// Configure the interrupt mode
	uint32_t modeWord;
	switch (mode)
	{
	case InterruptMode::low:		modeWord = EIC_CONFIG_SENSE0_LOW_Val; break;
	case InterruptMode::high:		modeWord = EIC_CONFIG_SENSE0_HIGH_Val; break;
	case InterruptMode::falling:	modeWord = EIC_CONFIG_SENSE0_FALL_Val; break;
	case InterruptMode::rising:		modeWord = EIC_CONFIG_SENSE0_RISE_Val; break;
	case InterruptMode::change:		modeWord = EIC_CONFIG_SENSE0_BOTH_Val; break;
	default:						modeWord = EIC_CONFIG_SENSE0_NONE_Val; break;
	}

	if (enableFilter)
	{
		modeWord |= EIC_CONFIG_FILTEN0;
	}

	{
		AtomicCriticalSectionLocker lock;

		// Ensure that the interrupt is disabled
		EIC->INTENCLR.reg = 1ul << exint;
		EIC->INTFLAG.reg = 1ul << exint;

		// Switch the pin into EIC mode
		SetPinFunction(pin, GpioPinFunction::A);		// EIC is always on peripheral A

		const unsigned int shift = (exint & 7u) << 2u;
		const uint32_t mask = ~(0x0000000F << shift);

		EIC->CTRLA.reg &= ~EIC_CTRLA_ENABLE;
		hri_eic_wait_for_sync(EIC, EIC_SYNCBUSY_ENABLE);

		if (exint < 8)
		{
			EIC->CONFIG[0].reg = (EIC->CONFIG[0].reg & mask) | (modeWord << shift);
		}
		else
		{
			EIC->CONFIG[1].reg = (EIC->CONFIG[1].reg & mask) | (modeWord << shift);
		}

		if (enableFilter)
		{
			EIC->ASYNCH.reg &= ~(1ul << exint);
		}
		else
		{
			EIC->ASYNCH.reg |= 1ul << exint;
		}
		EIC->EVCTRL.reg |= 1ul << exint;					// enable the event
		EIC->CTRLA.reg |= EIC_CTRLA_ENABLE;
		hri_eic_wait_for_sync(EIC, EIC_SYNCBUSY_ENABLE);
	}

	return exint;
}

void DetachEvent(Pin pin) noexcept
{
	const PinDescriptionBase * const pinDesc = AppGetPinDescription(pin);
	if (pinDesc != nullptr)
	{
		const ExintNumber exint = pinDesc->exintNumber;
		if (exint < 16)
		{
			const unsigned int shift = (exint & 7u) << 2u;
			const uint32_t mask = ~(0x0000000F << shift);

			EIC->CTRLA.reg &= ~EIC_CTRLA_ENABLE;
			hri_eic_wait_for_sync(EIC, EIC_SYNCBUSY_ENABLE);

			if (exint < 8)
			{
				EIC->CONFIG[0].reg &= mask;
			}
			else
			{
				EIC->CONFIG[1].reg &= mask;
			}

			EIC->CTRLA.reg |= EIC_CTRLA_ENABLE;
			hri_eic_wait_for_sync(EIC, EIC_SYNCBUSY_ENABLE);

			// Disable the interrupt
			EIC->INTENCLR.reg = 1ul << exint;
			EIC->INTFLAG.reg = 1ul << exint;

			// Switch the pin out of EIC mode
			ClearPinFunction(pin);
		}
	}
}


#if SAME5x

// Common EXINT handler
static inline void CommonExintHandler(size_t exintNumber) noexcept
{
	EIC->INTFLAG.reg = 1ul << exintNumber;				// clear the interrupt
	const InterruptCallback& cb = exintCallbacks[exintNumber];
	if (cb.func != nullptr)
	{
		cb.func(cb.param);
	}
}

extern "C" void EIC_0_Handler() noexcept
{
	CommonExintHandler(0);
}

extern "C" void EIC_1_Handler() noexcept
{
	CommonExintHandler(1);
}

extern "C" void EIC_2_Handler() noexcept
{
	CommonExintHandler(2);
}

extern "C" void EIC_3_Handler() noexcept
{
	CommonExintHandler(3);
}

extern "C" void EIC_4_Handler() noexcept
{
	CommonExintHandler(4);
}

extern "C" void EIC_5_Handler() noexcept
{
	CommonExintHandler(5);
}

extern "C" void EIC_6_Handler() noexcept
{
	CommonExintHandler(6);
}

extern "C" void EIC_7_Handler() noexcept
{
	CommonExintHandler(7);
}

extern "C" void EIC_8_Handler() noexcept
{
	CommonExintHandler(8);
}

extern "C" void EIC_9_Handler() noexcept
{
	CommonExintHandler(9);
}

extern "C" void EIC_10_Handler() noexcept
{
	CommonExintHandler(10);
}

extern "C" void EIC_11_Handler() noexcept
{
	CommonExintHandler(11);
}

extern "C" void EIC_12_Handler() noexcept
{
	CommonExintHandler(12);
}

extern "C" void EIC_13_Handler() noexcept
{
	CommonExintHandler(13);
}

extern "C" void EIC_14_Handler() noexcept
{
	CommonExintHandler(14);
}

extern "C" void EIC_15_Handler() noexcept
{
	CommonExintHandler(15);
}

#elif SAMC21

extern "C" void EIC_Handler() noexcept
{
	uint16_t intflag;
	while ((intflag = EIC->INTFLAG.reg) != 0)
	{
		uint16_t mask = 1;
		size_t exintNumber = 0;
		do
		{
			if ((intflag & mask) != 0)
			{
				EIC->INTFLAG.reg = mask;
				const InterruptCallback& cb = exintCallbacks[exintNumber];
				if (cb.func != nullptr)
				{
					cb.func(cb.param);
				}
				intflag &= ~mask;
			}
			++exintNumber;
			mask <<= 1;
		} while (intflag != 0);
	}
}

#else
# error Undefined processor
#endif

// End
