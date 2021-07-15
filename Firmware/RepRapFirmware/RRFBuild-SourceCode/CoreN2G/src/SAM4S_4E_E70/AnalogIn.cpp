/*
 * AnalogInput.cpp
 *
 *  Created on: 2 Apr 2016
 *      Author: David
 */

/*
 * A note on the ADCs in the SAME70
 * The ADCs on the SAME70 suffer from noise as mentioned in the errata for the chip.
 * The ADCs support hardware averaging, so we use that to reduce the noise. However, out tests show that hardware averaging above x16 gives the wrong results
 * if a sequence of channels is converted, except for the last channel converted.
 * Duet 3 uses AFEC1 for thermistor, Vref and Vssa monitoring and for the IO_8_IN pin analog functionality. The voltage monitoring, MCU temperature and all other IO_x_IN pins use AFEC1.
 * So we program the AFECs as follows:
 * - AFEC0 is programmed in x16 averaging mode with all active channels converted in sequence.
 *   The maximum number of clock cycles needed is 12 channels * 16 samples * 23 clock/cycle = 4416. So a 10MHz clock is more than enough to convert the sequence within 1ms.
 * - AFEC1 is programmed in x256 averaging mode and is only asked to convert 1 input per tick.
 *   The maximum number of clock cycles needed is 256 samples * 23 clocks/cycle = 5888. So again a 10MHz clock is sufficient.
 * When averaging mode is used, the current data register is not always the last converted result for the corresponding channel. So we need to save all the values
 * before starting another conversion. Call the AnalogInFinaliseConversion function to do this.
 * In order to make AdcBits a constant, we shift the 16-bit results from ADC1 right 2 bits before returning them.
 */
#include <CoreIO.h>
#include <AnalogIn.h>

#if SAM3XA || SAM4S
# include "adc/adc.h"
#elif SAM4E || SAME70
# include <afec/afec.h>
#else
# error Analog input module not written for this processor
#endif

#include <pmc/pmc.h>

#if SAM3XA || SAM4S
constexpr unsigned int NumChannels = 16;
#elif SAM4E
constexpr unsigned int NumChannels = 31;
constexpr uint32_t AfecLowChannelMask = 0x0000FFFF;
constexpr uint32_t AfecHighChannelMask = 0x7FFF0000;
#elif SAME70
constexpr unsigned int NumChannels = 28;				// but channels 12-15 don't exist
constexpr uint32_t AfecLowChannelMask = 0x00000FFF;
constexpr uint32_t AfecHighChannelMask = 0x0FFF0000;
#endif

static uint32_t activeChannels = 0;

#if SAME70
static volatile uint16_t results[NumChannels] = { 0 };
#endif

#if SAM3XA || SAM4S
static inline adc_channel_num_t GetAdcChannel(AnalogChannelNumber channel)
{
	return static_cast<adc_channel_num_t>((unsigned int)channel);
}
#endif

#if SAM4E || SAME70
static inline Afec *GetAfec(AnalogChannelNumber channel)
{
	return (GetDeviceNumber(channel) == 1) ? AFEC1 : AFEC0;
}

static inline afec_channel_num GetAfecChannel(AnalogChannelNumber channel)
{
	return static_cast<afec_channel_num>((unsigned int)channel & 15);
}
#endif

namespace LegacyAnalogIn
{
	// Module initialisation
	void AnalogInInit()
	{
#if SAM3XA || SAM4S
		pmc_enable_periph_clk(ID_ADC);
		adc_init(ADC, SystemCoreClock, 2000000, ADC_STARTUP_TIME_12);	// 2MHz clock
		adc_configure_timing(ADC, 3, ADC_SETTLING_TIME_3, 1);			// Add transfer time
		adc_configure_trigger(ADC, ADC_TRIG_SW, 0);						// Disable hardware trigger
		adc_disable_interrupt(ADC, 0xFFFFFFFF);							// Disable all ADC interrupts
		adc_disable_all_channel(ADC);
#elif SAM4E || SAME70
		afec_enable(AFEC0);
		afec_enable(AFEC1);
		afec_config cfg;

# if SAME70
		// afec_get_config_defaults returns the wrong values for the SAME70
		cfg.resolution = AFEC_14_BITS;					// the SAME70 ADC is noisy, so use x16 hardware averaging on ADC0, 14-bit result
		cfg.mck = SystemPeripheralClock();
		cfg.afec_clock = 10000000UL;					// datasheet says typical AFEC clock is 20MHz, minimum 4, maximum 40. App note 44093 says don't use 40MHz, use 10 or 20.
														// 20MHz with x64 averaging allows us to sample up to 13 channels per clock tick
		cfg.startup_time = AFEC_STARTUP_TIME_4;
		cfg.tracktim = 0;								// datasheet says don't modify this field
		cfg.transfer = 2;								// as recommended on the 2018 datasheet
		cfg.anach = true;
		cfg.useq = false;
		cfg.tag = true;
		cfg.stm = true;
		cfg.ibctl = 0b10;
# else
		afec_get_config_defaults(&cfg);
# endif

		while (afec_init(AFEC0, &cfg) != STATUS_OK)
		{
			(void)afec_get_latest_value(AFEC0);
		}

# if SAME70
		cfg.resolution = AFEC_16_BITS;					// the SAME70 ADC is noisy, so use x256 hardware averaging on ADC1, 16-bit result
# endif

		while (afec_init(AFEC1, &cfg) != STATUS_OK)
		{
			(void)afec_get_latest_value(AFEC1);
		}

		afec_disable_interrupt(AFEC0, AFEC_INTERRUPT_ALL);
		afec_disable_interrupt(AFEC1, AFEC_INTERRUPT_ALL);
		afec_set_trigger(AFEC0, AFEC_TRIG_SW);
		afec_set_trigger(AFEC1, AFEC_TRIG_SW);
#endif
	}

	// Enable or disable a channel. Use AnalogCheckReady to make sure the ADC is ready before calling this.
	void AnalogInEnableChannel(AnalogChannelNumber channel, bool enable)
	{
		if ((uint8_t)channel >= 0 && (unsigned int)channel < NumChannels)
		{
#if SAM3XA || SAM4S
			const adc_channel_num_t chan = GetAdcChannel(channel);
#else
			Afec * const afec = GetAfec(channel);
			const afec_channel_num chan = GetAfecChannel(channel);
#endif
			if (enable)
			{
				activeChannels |= (1u << (uint8_t)channel);
#if SAM3XA || SAM4S
				adc_enable_channel(ADC, chan);
# if SAM4S
				adc_set_calibmode(ADC);								// auto calibrate at start of next sequence
# endif
				if (channel == GetTemperatureAdcChannel())
				{
					adc_enable_ts(ADC);
				}
#elif SAM4E || SAME70
				afec_ch_config cfg;
				afec_ch_get_config_defaults(&cfg);
# if SAME70
				cfg.gain = AFEC_GAINVALUE_0;						// SAME70 defaults to gain 2
# endif
				afec_ch_set_config(afec, chan, &cfg);
# if SAM4E
				afec_channel_set_analog_offset(afec, chan, 2048);	// 2048 means zero offset compensation
# elif SAME70
				afec_channel_set_analog_offset(afec, chan, 512);	// 512 means zero offset compensation
				if (channel == GetTemperatureAdcChannel())
				{
					afec_temp_sensor_config afec_temp_sensor_cfg;
					afec_temp_sensor_get_config_defaults(&afec_temp_sensor_cfg);
					afec_temp_sensor_set_config(afec, &afec_temp_sensor_cfg);
				}
# endif
				afec_channel_enable(afec, chan);
# if SAM4E
				afec_start_calibration(afec);						// do automatic calibration
# endif
#endif
			}
			else
			{
				activeChannels &= ~(1u << (uint8_t)channel);
#if SAM3XA || SAM4S
				adc_disable_channel(ADC, chan);
				if (channel == GetTemperatureAdcChannel())
				{
					adc_disable_ts(ADC);
				}
#elif SAM4E || SAME70
				afec_channel_disable(afec, chan);
#endif
			}
		}
	}

	// Read the most recent 12-bit result from a channel
	uint16_t AnalogInReadChannel(AnalogChannelNumber channel)
	{
		if ((uint8_t)channel >= 0 && (unsigned int)channel < NumChannels)
		{
#if SAM3XA || SAM4S
			return *(ADC->ADC_CDR + GetAdcChannel(channel));
#elif SAM4E
			Afec * const afec = GetAfec(channel);
			const irqflags_t flags = IrqSave();
			afec->AFEC_CSELR = GetAfecChannel(channel);
			const uint16_t rslt = afec->AFEC_CDR;
			IrqRestore(flags);
			return rslt;
#elif SAME70
			return (GetDeviceNumber(channel) == 1) ? results[(uint8_t)channel] >> 2 : results[(uint8_t)channel];		// normalise to 14-bit result
#endif
		}
		return 0;
	}

#if 0	// not currently used

	static AnalogCallback_t callbackFn = nullptr;

	// Set up a callback for when all conversions have been completed. Returns the previous callback pointer.
	AnalogCallback_t AnalogInSetCallback(AnalogCallback_t fn)
	{
		AnalogCallback_t oldFn = fn;
		callbackFn = fn;
		if (fn == nullptr)
		{
			//TODO disable conversions complete interrupt
		}
		else
		{
			//TODO enable conversions complete interrupt
		}
		return oldFn;
	}
#endif
#if SAM4E || SAME70

	static void StartConversion(Afec *afec)
	{
		// Clear out any existing conversion complete bits in the status register
		for (uint32_t chan = 0;
# if SAM4E
			chan < 16;
# elif SAME70
			chan < 12;
# endif
				++chan)
		{
			afec->AFEC_CSELR = chan;
			(void) afec->AFEC_CDR;
		}
# if SAME70
		(void)afec->AFEC_OVER;
# endif
		afec_start_software_conversion(afec);
	}

#endif

	// Start converting the enabled channels
	void AnalogInStartConversion(uint32_t channels)
	{
#if SAM3XA || SAM4S
		// Clear out any existing conversion complete bits in the status register
		for (uint32_t chan = 0; chan < 16; ++chan)
		{
			(void)(*(ADC->ADC_CDR + chan));
		}
		ADC->ADC_CR = ADC_CR_START;
#elif SAM4E || SAME70
		channels &= activeChannels;
		if ((channels & AfecLowChannelMask) != 0)
		{
			AFEC0->AFEC_CHDR = ~channels & AfecLowChannelMask;
			AFEC0->AFEC_CHER = channels & AfecLowChannelMask;
			StartConversion(AFEC0);
		}
		if ((channels & AfecHighChannelMask) != 0)
		{
			AFEC1->AFEC_CHDR = (~channels & AfecHighChannelMask) >> 16;
			AFEC1->AFEC_CHER = (channels & AfecHighChannelMask) >> 16;
			StartConversion(AFEC1);
		}
#endif
	}

#if SAME70

	static void SaveResults(Afec *afec, volatile uint16_t * resultArea)
	{
		uint32_t channelsCompleted = afec->AFEC_CHSR & afec->AFEC_ISR & ~afec->AFEC_OVER & 0x00000FFF;
		uint32_t channel = 0;
		while (channelsCompleted != 0)
		{
			if (channelsCompleted & 1u)
			{
				const irqflags_t flags = IrqSave();
				afec->AFEC_CSELR = channel;
				resultArea[channel] = afec->AFEC_CDR;
				IrqRestore(flags);
			}
			channelsCompleted >>= 1;
			++channel;
		}
	}


	// Finalise a conversion
	void AnalogInFinaliseConversion()
	{
		// We use the SAME70 ADCs in averaging mode in order to reduce noise. This means that the result registers don;t always hold the result of the most recent conversion.
		// So when the conversion has finished, we save all the results.
		SaveResults(AFEC0, results);
		SaveResults(AFEC1, results + 16);
	}

#endif

	// Check whether all conversions have been completed since the last call to AnalogStartConversion
	bool AnalogInCheckReady(uint32_t channels)
	{
#if SAM3XA || SAM4S
		const uint32_t mask = channels & activeChannels;
		return (adc_get_status(ADC) & mask) == mask;
#elif SAM4E || SAME70
		channels &= activeChannels;
		const uint32_t afec0Mask = channels & AfecLowChannelMask;
		const uint32_t afec1Mask = (channels & AfecHighChannelMask) >> 16;
		return (afec_get_interrupt_status(AFEC0) & afec0Mask) == afec0Mask
			&& (afec_get_interrupt_status(AFEC1) & afec1Mask) == afec1Mask;
#endif
	}

	// Convert an Arduino Due analog pin number to the corresponding ADC channel number
	AnalogChannelNumber PinToAdcChannel(uint32_t pin)
	{
#if SAM3XA
		// Arduino Due uses separate analog pin numbers
		if (pin < A0)
		{
			pin += A0;
		}
#endif
		const PinDescriptionBase * const pinDesc = AppGetPinDescription(pin);
		return (pinDesc != nullptr) ? pinDesc->adc : AdcInput::none;
	}

	// Get the temperature measurement channel
	AnalogChannelNumber GetTemperatureAdcChannel()
	{
#if SAM4E || SAME70
		return static_cast<AnalogChannelNumber>(AFEC_TEMPERATURE_SENSOR);		// AFEC0 channel 15 on SAM4E and channel 11 on SAME70
#elif SAM3XA || SAM4S
		return static_cast<AnalogChannelNumber>(ADC_TEMPERATURE_SENSOR);
#endif
	}
}

// End
