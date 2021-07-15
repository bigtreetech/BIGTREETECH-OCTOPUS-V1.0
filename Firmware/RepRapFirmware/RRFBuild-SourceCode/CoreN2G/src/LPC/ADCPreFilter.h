/*
 * ADCPreFilter.h
 *
 *  Created on: 15 Jan 2020
 *      Author: sdavi
 */

#ifndef ADCPREFILTER_H_
#define ADCPREFILTER_H_

#include "CoreImp.h"
#include "Median.h"

class ADCPreFilter
{

public:
    ADCPreFilter() noexcept : adcPreFilterInitialised(false) { };
    
    bool Init() noexcept;
    Status Read(uint8_t channel, uint16_t *val) noexcept;
    void UpdateChannels(uint8_t channels) noexcept;

    static constexpr uint8_t numberADCSamples = 8;
    static volatile uint32_t adcSamplesArray[NumADCChannels*numberADCSamples];

    
private:
    void PrepareAdcDma() noexcept;
    uint8_t HighestSetBit(uint8_t val) noexcept;

    uint8_t adcDmaChannel;
    bool adcPreFilterInitialised;
    
    uint16_t median_buffer[NumADCChannels];
};



inline Status ADCPreFilter::Read(uint8_t channel, uint16_t *val) noexcept
{
    uint32_t error = 0;
    if(adcPreFilterInitialised == false)
    {
        return ERROR;
    }
    
    for(uint8_t i=0; i<numberADCSamples; i++)
    {
        if (!ADC_DR_DONE(adcSamplesArray[i*NumADCChannels + channel]))
            error++;
        median_buffer[i] = ((adcSamplesArray[i*NumADCChannels + channel] >> 4) & 0xFFF);
    }

    *val = median_buffer[quick_median(median_buffer, numberADCSamples)];
    return (error ? ERROR : SUCCESS);
}




#endif /* ADCPREFILTER_H_ */
