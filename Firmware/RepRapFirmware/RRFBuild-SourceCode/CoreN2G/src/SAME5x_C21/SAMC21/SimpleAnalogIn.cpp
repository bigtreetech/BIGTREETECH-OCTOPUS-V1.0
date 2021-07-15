/*
 * SimpleAnalogIn.cpp
 *
 *  Created on: 12 Jun 2020
 *      Author: David
 */

#include "AnalogIn.h"

#if SAMC21 && !defined(RTOS)

# include <hri_adc_c21.h>
# define ADC_INPUTCTRL_MUXNEG_GND   (0x18 << ADC_INPUTCTRL_MUXNEG_Pos)			// this definition is missing from file adc.h for the SAMC21

void AnalogIn::Init(Adc * device)
{
	// Enable ADC clock
	if (device == ADC0)
	{
		hri_mclk_set_APBCMASK_ADC0_bit(MCLK);
		hri_gclk_write_PCHCTRL_reg(GCLK, ADC0_GCLK_ID, GCLK_PCHCTRL_GEN_GCLK0_Val | (1 << GCLK_PCHCTRL_CHEN_Pos));
	}
	else
	{
		hri_mclk_set_APBCMASK_ADC1_bit(MCLK);
		hri_gclk_write_PCHCTRL_reg(GCLK, ADC1_GCLK_ID, GCLK_PCHCTRL_GEN_GCLK0_Val | (1 << GCLK_PCHCTRL_CHEN_Pos));
	}

	if (!hri_adc_is_syncing(device, ADC_SYNCBUSY_SWRST))
	{
		if (hri_adc_get_CTRLA_reg(device, ADC_CTRLA_ENABLE))
		{
			hri_adc_clear_CTRLA_ENABLE_bit(device);
			hri_adc_wait_for_sync(device, ADC_SYNCBUSY_ENABLE);
		}
		hri_adc_write_CTRLA_reg(device, ADC_CTRLA_SWRST);
	}
	hri_adc_wait_for_sync(device, ADC_SYNCBUSY_SWRST);

	hri_adc_write_CTRLB_reg(device, ADC_CTRLB_PRESCALER_DIV4);					// Max ADC clock is 16MHz. GCLK0 is 48MHz, divided by 4 is 12MHz
	hri_adc_write_CTRLC_reg(device, ADC_CTRLC_RESSEL_16BIT | ADC_CTRLC_R2R);	// 16 bit result, rail-to-rail
	hri_adc_write_REFCTRL_reg(device,  ADC_REFCTRL_REFSEL_INTVCC2);
	hri_adc_write_EVCTRL_reg(device, ADC_EVCTRL_RESRDYEO);
	hri_adc_write_INPUTCTRL_reg(device, ADC_INPUTCTRL_MUXNEG_GND);
	hri_adc_write_AVGCTRL_reg(device, ADC_AVGCTRL_SAMPLENUM_64);				// average 64 measurements
	hri_adc_write_SAMPCTRL_reg(device, ADC_SAMPCTRL_OFFCOMP);					// enable comparator offset compensation, sampling time is fixed at 4 ADC clocks
	hri_adc_write_WINLT_reg(device, 0);
	hri_adc_write_WINUT_reg(device, 0xFFFF);
	hri_adc_write_GAINCORR_reg(device, 1u << 11);
	hri_adc_write_OFFSETCORR_reg(device, 0);
	hri_adc_write_DBGCTRL_reg(device, 0);

	// Load CALIB with NVM data calibration results
	do
	{
		uint32_t biasComp, biasRefbuf;
		if (device == ADC0)
		{
			biasComp = (*reinterpret_cast<const uint32_t*>(ADC0_FUSES_BIASCOMP_ADDR) & ADC0_FUSES_BIASCOMP_Msk) >> ADC0_FUSES_BIASCOMP_Pos;
			biasRefbuf = (*reinterpret_cast<const uint32_t*>(ADC0_FUSES_BIASREFBUF_ADDR) & ADC0_FUSES_BIASREFBUF_Msk) >> ADC0_FUSES_BIASREFBUF_Pos;
		}
		else if (device == ADC1)
		{
			biasComp = (*reinterpret_cast<const uint32_t*>(ADC1_FUSES_BIASCOMP_ADDR) & ADC1_FUSES_BIASCOMP_Msk) >> ADC1_FUSES_BIASCOMP_Pos;
			biasRefbuf = (*reinterpret_cast<const uint32_t*>(ADC1_FUSES_BIASREFBUF_ADDR) & ADC1_FUSES_BIASREFBUF_Msk) >> ADC1_FUSES_BIASREFBUF_Pos;
		}
		else
		{
			break;
		}
		hri_adc_write_CALIB_reg(device, ADC_CALIB_BIASCOMP(biasComp) | ADC_CALIB_BIASREFBUF(biasRefbuf));
	} while (false);

	hri_adc_set_CTRLA_ENABLE_bit(device);
	hri_adc_wait_for_sync(device, ADC_SYNCBUSY_ENABLE);
}

uint16_t AnalogIn::ReadChannel(Adc * device, uint8_t channel)
{
	device->SEQCTRL.reg = 0;								// disable sequence
	device->INPUTCTRL.bit.MUXPOS = channel;
	device->INTFLAG.reg = ADC_INTFLAG_RESRDY;				// clear RESRDY bit
	device->SWTRIG.reg = ADC_SWTRIG_START;
	while (!device->INTFLAG.bit.RESRDY) { }
	return device->RESULT.reg;
}

void AnalogIn::Disable(Adc * device)
{
	hri_adc_clear_CTRLA_ENABLE_bit(device);
	hri_adc_wait_for_sync(device, ADC_SYNCBUSY_ENABLE);
}

#endif
