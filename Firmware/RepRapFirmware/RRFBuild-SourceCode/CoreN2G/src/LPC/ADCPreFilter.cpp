/*
* ADCPreFilter.cpp
*
*  Created on: 15 Jan 2020
*      Author: sdavi
*/
 
#include "ADCPreFilter.h"
#include "CoreImp.h"
#include "DMA.h"

/*static*/ volatile uint32_t ADCPreFilter::adcSamplesArray[NumADCChannels*ADCPreFilter::numberADCSamples];

constexpr uint32_t adcDMAControlConfig = GPDMA_DMACCxControl_TransferSize(8)               //Transfer the 8 channels
                                        | GPDMA_DMACCxControl_SBSize(GPDMA_BSIZE_8)        //Source burst size set to 8
                                        | GPDMA_DMACCxControl_DBSize(GPDMA_BSIZE_8)        //Destination burst size set to 8
                                        | GPDMA_DMACCxControl_SWidth(GPDMA_WIDTH_WORD)     //Source Tranfser width
                                        | GPDMA_DMACCxControl_DWidth(GPDMA_WIDTH_WORD)     //Destination Transfer width
                                        | GPDMA_DMACCxControl_SI                           //Source increment after each transfer
                                        | GPDMA_DMACCxControl_DI;                          //Destination increment after each transfer

#define INIT_DMA_DESCRIPTOR(DSTROW, LLI) { \
    (uint32_t)&LPC_ADC->DR[0], \
    (uint32_t)&ADCPreFilter::adcSamplesArray[DSTROW*NumADCChannels], \
    (uint32_t)LLI, \
    adcDMAControlConfig }


//Build a circular linked list of descriptors
extern const DMA_TransferDescriptor_t sampleRow1;
const DMA_TransferDescriptor_t sampleRow8 = INIT_DMA_DESCRIPTOR(7, &sampleRow1);
const DMA_TransferDescriptor_t sampleRow7 = INIT_DMA_DESCRIPTOR(6, &sampleRow8);
const DMA_TransferDescriptor_t sampleRow6 = INIT_DMA_DESCRIPTOR(5, &sampleRow7);
const DMA_TransferDescriptor_t sampleRow5 = INIT_DMA_DESCRIPTOR(4, &sampleRow6);
const DMA_TransferDescriptor_t sampleRow4 = INIT_DMA_DESCRIPTOR(3, &sampleRow5);
const DMA_TransferDescriptor_t sampleRow3 = INIT_DMA_DESCRIPTOR(2, &sampleRow4);
const DMA_TransferDescriptor_t sampleRow2 = INIT_DMA_DESCRIPTOR(1, &sampleRow3);
const DMA_TransferDescriptor_t sampleRow1 = INIT_DMA_DESCRIPTOR(0, &sampleRow2);



bool ADCPreFilter::Init() noexcept
{
    //create the array
    //Format will be:
    //       CH0 CH1 CH2 CH3 CH4 CH5 CH6 CH7
    //       CH0 CH1 CH2 CH3 CH4 CH5 CH6 CH7
    //        ...
    
    //DMA will fill in each row of samples
    
    NVIC_DisableIRQ(ADC_IRQn); //ensure ADC interrupts are disabled
    
    InitialiseDMA(); //Init GPDMA
    adcDmaChannel = DMAGetChannelNumber(DMA_TIMER_MAT1_0);
    
    adcPreFilterInitialised = true;

    PrepareAdcDma();

    return true;
}


//from LPCOpen gpdma_17xx_40xx.c
static inline uint8_t configDMAMux(uint32_t gpdma_peripheral_connection_number) noexcept
{
    if (gpdma_peripheral_connection_number > 15)
    {
        LPC_SYSCTL->DMAREQSEL |= (1 << (gpdma_peripheral_connection_number - 16));
        return gpdma_peripheral_connection_number - 8;
    }
    else
    {
        if (gpdma_peripheral_connection_number > 7)
        {
            LPC_SYSCTL->DMAREQSEL &= ~(1 << (gpdma_peripheral_connection_number - 8));
        }
        return gpdma_peripheral_connection_number;
    }
}

uint8_t ADCPreFilter::HighestSetBit(uint8_t val) noexcept
{
    if(val == 0) return 0;                          //__builtin_clz is undefined if called with 0
    const uint16_t numBits = (sizeof(int)<<3)-1;    // __builtin_clz returns an int
    int res = __builtin_clz (val);                  //gets the number of leading 0's starting from MSB
    return (uint8_t) 1U << (numBits-res);
}

void ADCPreFilter::UpdateChannels(uint8_t channels) noexcept
{
    LPC_ADC->INTEN = HighestSetBit(channels);   //enable interrupt after highest enabled channel has been scanned
                                                //note: the interrupt signal is still used in DMA mode to trigger the DMA transfer
}


void ADCPreFilter::PrepareAdcDma() noexcept
{
    //Setup DMA Channel
    GPDMA_CH_T *pDMAch = (GPDMA_CH_T *) &(LPC_GPDMA->CH[adcDmaChannel]);
    pDMAch->CONFIG = GPDMA_DMACCxConfig_H;                                                          //halt the DMA channel - Clears DMA FIFO
    
    LPC_GPDMA->INTTCCLEAR = (((1UL << (adcDmaChannel)) & 0xFF));                                    //clear terminal count interrupt
    LPC_GPDMA->INTERRCLR = (((1UL << (adcDmaChannel)) & 0xFF));                                     //clear the error interrupt request

    // Enable DMA channels
    LPC_GPDMA->CONFIG = GPDMA_DMACConfig_E;
    while (!(LPC_GPDMA->CONFIG & GPDMA_DMACConfig_E)) {}

    pDMAch->SRCADDR  = sampleRow1.src;
    pDMAch->DESTADDR = sampleRow1.dst;
    pDMAch->CONTROL  = sampleRow1.ctrl;
    pDMAch->LLI      = sampleRow1.lli;
    
    const uint16_t srcPeripheral = configDMAMux(GPDMA_CONN_ADC);                                    //select ADC as src
    LPC_GPDMA->SYNC |= (1 << (srcPeripheral & 0xFFFF));

    pDMAch->CONFIG = GPDMA_DMACCxConfig_E
                        | GPDMA_DMACCxConfig_SrcPeripheral(srcPeripheral)
                        | GPDMA_DMACCxConfig_TransferType(GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA)   //Peripheral to Memory
                        | GPDMA_DMACCxConfig_IE                                                    //Interrupt Error Mask
                        | GPDMA_DMACCxConfig_ITC;                                                  //Terminal count interrupt mask

}

// End
