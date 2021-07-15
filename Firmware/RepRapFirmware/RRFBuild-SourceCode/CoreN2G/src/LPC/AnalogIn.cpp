/*
 * AnalogInput.cpp
 *
 *  Created on: 2 Apr 2016
 *      Author: David
 
 * SD: Modified to run on LPC
 *   : - Uses the "Burst" mode of the LPC to continously sample each of the selected ADC channels once enabled
 *   : - Resolution is 12bit
 */


/*
 - From Errata sheet Rev. 10.4 — 17 March 2020

 Noise caused by I/O switching activity on pins close to the ADC input channels or caused by the board design/layout
 can couple into the ADC input channels. This causes the ADC conversion results to be corrupted up to 0xFFF.
 The issue occurs more frequently at -45 C and when toggling the I/O pins adjacent to the ADC input channels.

- SD some users were seeing large spikes in temp readings likey caused by this issue. The glitch only seems to
 occur for a sample or two and a prefilter was added to help eliminate the glitched samples.
 */


#include "AnalogIn.h"
#include "chip.h"
#include "ADCPreFilter.h"

uint32_t ADCNotReadyCnt = 0;
uint32_t ADCInitCnt = 0;
uint32_t ADCErrorThreshold = 10;

static ADC_CLOCK_SETUP_T ADCSetup;
const unsigned int numChannels = 8; //8 channels on LPC1768
static uint8_t activeChannels = 0;

static bool usingPreFilter = false;
const unsigned int numberSamples = 8;

static ADCPreFilter preFilter;

typedef struct
{
    gpioPins_et pinNumber;
    uint8_t PinFunSel;
} adcChannelConfig_st;

const adcChannelConfig_st AdcConfig[numChannels]=
{
    { P0_23, PINSEL_FUNC_1}, /* AD0[0] is on P0.23 second alternative function */
    { P0_24, PINSEL_FUNC_1}, /* AD0[1] is on P0.24 second alternative function */
    { P0_25, PINSEL_FUNC_1}, /* AD0[2] is on P0.25 second alternative function */
    { P0_26, PINSEL_FUNC_1}, /* AD0[3] is on P0.26 second alternative function */
    { P1_30, PINSEL_FUNC_3}, /* AD0[4] is on P1.30 third alternative function */
    { P1_31, PINSEL_FUNC_3}, /* AD0[5] is on P1.31 third alternative function */
    { P0_3,  PINSEL_FUNC_2}, /* AD0[6] is on P0.3  third alternative function */
    { P0_2,  PINSEL_FUNC_2}  /* AD0[7] is on P0.2  third alternative function */
};

void ConfigureADCPreFilter(bool enable) noexcept
{
    if(enable == true)
    {
        usingPreFilter = preFilter.Init();
    }
}


namespace LegacyAnalogIn
{
// Module initialisation
void AnalogInInit() noexcept
{
    if (ADCInitCnt++ > 0)
        Chip_ADC_DeInit(LPC_ADC);
    Chip_ADC_Init(LPC_ADC, &ADCSetup);                                  //Init ADC and setup the ADCSetup struct
    ADCSetup.burstMode = true;                                          //update the struct so SetSampleRate knows we will be using burst mode
    Chip_ADC_SetSampleRate(LPC_ADC, &ADCSetup, 1000);
    //Chip_ADC_SetBurstCmd(LPC_ADC, ENABLE);                              //enable burst mode
    
    LPC_ADC->INTEN = 0x00; //disable all interrupts
    LPC_ADC->CR  |= (activeChannels & 0x000000FF );
    Chip_ADC_SetBurstCmd(LPC_ADC, ENABLE);                              //enable burst mode
}


// Enable or disable a channel.
void AnalogInEnableChannel(AnalogChannelNumber channel, bool enable) noexcept
{
	if (channel != NO_ADC && (unsigned int)channel < numChannels)
	{
		if (enable == true)
		{
			activeChannels |= (0x01 << channel);
            //set the pin mode for ADC
            GPIO_PinFunction(AdcConfig[channel].pinNumber,AdcConfig[channel].PinFunSel);
            //set the channels to sample (bits 0-7 of CR)
            LPC_ADC->CR  |= (activeChannels & 0x000000FF );
		}
		else
		{
			activeChannels &= ~(1u << channel);
            LPC_ADC->CR  = (LPC_ADC->CR  & 0xFFFFFF00) | (activeChannels & 0x000000FF );
		}
        
        if(usingPreFilter == true)
        {
            preFilter.UpdateChannels(activeChannels);
        }
        
    }
}

// Read the most recent 12-bit result from a channel
__attribute__((optimize("-O3")))
uint16_t AnalogInReadChannel(AnalogChannelNumber channel) noexcept
{
    uint16_t val = 0;
    if(usingPreFilter == true)
    {
       if (preFilter.Read((uint8_t)channel, &val) == ERROR)
            ADCNotReadyCnt++;
    }
    else
    {
        if (Chip_ADC_ReadValue(LPC_ADC, (uint8_t)channel, &val) == ERROR)
            ADCNotReadyCnt++;
    }
    // If we are getting errors, try resetting
    if (ADCNotReadyCnt > ADCErrorThreshold)
    {
        // Increase threshold for next time
        ADCErrorThreshold *= 2;
        AnalogInInit();
    }
    return val;
}


// Start converting the enabled channels
void AnalogInStartConversion(uint32_t channels) noexcept
{
}


// Convert an  pin number to the corresponding ADC channel number
AnalogChannelNumber PinToAdcChannel(uint32_t pin) noexcept
{
    return g_APinDescription[pin].ulADCChannelNumber;
}

}
// End
