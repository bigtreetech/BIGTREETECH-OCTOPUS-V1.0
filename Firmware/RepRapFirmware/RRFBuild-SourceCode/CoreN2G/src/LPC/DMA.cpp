//Author: sdavi

#include "DMA.h"

extern "C" void debugPrintf(const char* fmt, ...) __attribute__ ((format (printf, 1, 2)));

static constexpr uint8_t NumberDMAChannels = 8;
static DMACallbackFunction dma_callbacks[NumberDMAChannels] = {nullptr};
static uint8_t dma_channels[NumberDMAChannels];

void InitialiseDMA()
{

    static bool gpdmaInit = false;
    if(gpdmaInit == false)
    {
        /* Initialize GPDMA controller */
        Chip_GPDMA_Init(LPC_GPDMA);

        //Timer1 MR3 Match Channel
        dma_channels[DMA_TIMER_MAT3_0] = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, GPDMA_CONN_MAT3_0);
        
        //SSP0 DMA Channels
        dma_channels[DMA_SSP0_RX] = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, GPDMA_CONN_SSP0_Rx);
        dma_channels[DMA_SSP0_TX] = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, GPDMA_CONN_SSP0_Tx);
        
        //SSP1 DMA Channels
        dma_channels[DMA_SSP1_RX] = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, GPDMA_CONN_SSP1_Rx);
        dma_channels[DMA_SSP1_TX] = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, GPDMA_CONN_SSP1_Tx);

        //Timer1 MR0 Match Channel
        dma_channels[DMA_TIMER_MAT1_0] = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, GPDMA_CONN_MAT1_0);

        gpdmaInit = true;
        
        NVIC_EnableIRQ(DMA_IRQn);
    }

}

//Get the DMA channel number that was assigned to DMA channels we configured.
uint8_t DMAGetChannelNumber(DMA_Channel_t dma_channel)
{
    return dma_channels[dma_channel];
}


// Attach DMA Handler for channel. Can be nullptr for no call handler, a function to call
// or the special value DMA_USE_DEVICE_INTERRUPT which will generate a new interrupt for
// the base device. This allows different interrupt levels to be used for
// the general DMA device and for the completion interrupt of the actual hardware device.
void AttachDMAChannelInterruptHandler(DMACallbackFunction callback, DMA_Channel_t channel)
{
    dma_callbacks[channel] = callback;
}

static void inline checkAndCallHandler(uint32_t chan, IRQn_Type intHandler)
{
    // Did this chan generate an event?
    if (Chip_GPDMA_Interrupt(LPC_GPDMA, dma_channels[chan]) == SUCCESS) //also clears the interrupt
    {
        if (dma_callbacks[chan] == DMA_USE_DEVICE_INTERRUPT)
            NVIC_SetPendingIRQ(intHandler);
        else if (dma_callbacks[chan] != nullptr)
            dma_callbacks[chan]();
    }
}

//DMA Interrupt Handler
extern "C"  void DMA_IRQHandler(void)
{
    //SSP0 Channels
    checkAndCallHandler(DMA_SSP0_RX, SSP0_IRQn);
    checkAndCallHandler(DMA_SSP0_TX, SSP0_IRQn);
    
    //SSP1 Channels
    checkAndCallHandler(DMA_SSP1_RX, SSP1_IRQn);
    checkAndCallHandler(DMA_SSP1_TX, SSP1_IRQn);

    //Timer1 MR0 Match channel
    checkAndCallHandler(DMA_TIMER_MAT1_0, TIMER1_IRQn);

    //Timer3 MR0 Match channel
    checkAndCallHandler(DMA_TIMER_MAT3_0, TIMER3_IRQn);
}


void SspDmaRxTransfer(DMA_Channel_t ssp_dma_channel, const void *buf, uint32_t transferLength, DMA_TransferWidth_t transferWidth)
{
    // Setup DMA Receive: SSP --> inBuffer (Peripheral to Memory)
    const uint8_t channelNumber = dma_channels[ssp_dma_channel];
    uint8_t srcPeripheral;
    uint32_t srcAddress;
    
    if(ssp_dma_channel == DMA_SSP0_RX)
    {
        srcPeripheral = GPDMA_CONN_SSP0_Rx;
        srcAddress = (uint32_t)&LPC_SSP0->DR;
    }
    else if(ssp_dma_channel == DMA_SSP1_RX)
    {
        srcPeripheral = GPDMA_CONN_SSP1_Rx;
        srcAddress = (uint32_t)&LPC_SSP1->DR;
    }
    else
    {
        //invalid channel number
        return;
    }
    
    
    
    GPDMA_CH_T *pDMAchRx = (GPDMA_CH_T *) &(LPC_GPDMA->CH[channelNumber]);

    pDMAchRx->CONFIG = GPDMA_DMACCxConfig_H;                        //halt the DMA channel - Clears DMA FIFO
    
    LPC_GPDMA->INTTCCLEAR = (((1UL << (channelNumber)) & 0xFF));    //clear terminal count interrupt requests for Rx and Tx Channels
    LPC_GPDMA->INTERRCLR = (((1UL << (channelNumber)) & 0xFF));     //clear the error interrupt request

    
    // Enable DMA channels
    LPC_GPDMA->CONFIG = GPDMA_DMACConfig_E;
    while (!(LPC_GPDMA->CONFIG & GPDMA_DMACConfig_E)) {}

    pDMAchRx->SRCADDR  = srcAddress;                //Source Address (SSP DataRegister)
    pDMAchRx->DESTADDR = (uint32_t)buf;             //Destination Address (buffer in memory)
    pDMAchRx->LLI      = 0;                         //linked list item register

    pDMAchRx->CONTROL  = (transferLength & 0xFFF)
                            | GPDMA_DMACCxControl_SBSize(GPDMA_BSIZE_1)     //Source burst size set to 1
                            | GPDMA_DMACCxControl_DBSize(GPDMA_BSIZE_1)     //Destination burst size set to 1
                            | GPDMA_DMACCxControl_SWidth(transferWidth)  //Source Tranfser width set to 1 byte
                            | GPDMA_DMACCxControl_DWidth(transferWidth)  //Destination Transfer width set to 1 byte
                            | GPDMA_DMACCxControl_DI                        //Destination increment after each transfer
                            | GPDMA_DMACCxControl_I;                        //Terminal count interrupt enable

    
    pDMAchRx->CONFIG =  GPDMA_DMACCxConfig_E                                                        //Enable
                        | GPDMA_DMACCxConfig_SrcPeripheral(srcPeripheral)                           //Peripheral destination is SSP0 RX
                        | GPDMA_DMACCxConfig_TransferType(GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA)    //Peripheral to Memory
                        | GPDMA_DMACCxConfig_IE                                                     //Interrupt Error Mask
                        | GPDMA_DMACCxConfig_ITC;                                                   //Terminal count interrupt mask

    
}

void SspDmaTxTransfer(DMA_Channel_t ssp_dma_channel, const void *buf, uint32_t transferLength, DMA_TransferWidth_t transferWidth)
{
    // Setup DMA transfer: outBuffer --> SSP (Memory to Peripheral Transfer)
    const uint8_t channelNumber = dma_channels[ssp_dma_channel];
    uint8_t dstPeripheral;
    uint32_t dstAddress;
    
    if(ssp_dma_channel == DMA_SSP0_TX)
    {
        dstPeripheral = GPDMA_CONN_SSP0_Tx;
        dstAddress = (uint32_t)&LPC_SSP0->DR;
    }
    else if(ssp_dma_channel == DMA_SSP1_TX)
    {
        dstPeripheral = GPDMA_CONN_SSP1_Tx;
        dstAddress = (uint32_t)&LPC_SSP1->DR;
    }
    else
    {
        //invalid channel number
        return;
    }

    
    
    GPDMA_CH_T *pDMAchTx = (GPDMA_CH_T *) &(LPC_GPDMA->CH[channelNumber]);

    pDMAchTx->CONFIG = GPDMA_DMACCxConfig_H;                        //halt the DMA channel - Also clears the DMA FIFO
    
    LPC_GPDMA->INTTCCLEAR = (((1UL << (channelNumber)) & 0xFF));   //clear terminal count interrupt requests for Rx and Tx Channels
    LPC_GPDMA->INTERRCLR = (((1UL << (channelNumber)) & 0xFF));    //clear the error interrupt request

    
    // Enable DMA channels
    LPC_GPDMA->CONFIG = GPDMA_DMACConfig_E;
    while (!(LPC_GPDMA->CONFIG & GPDMA_DMACConfig_E)) {}
    
    pDMAchTx->SRCADDR  = (uint32_t)buf;             //Source Address (buffer in memory)
    pDMAchTx->DESTADDR = dstAddress;                //Destination Address (SSP0 DataRegister)
    pDMAchTx->LLI      = 0;                         //linked list item register
    pDMAchTx->CONTROL  = (transferLength & 0xFFF)
                            | GPDMA_DMACCxControl_SBSize(GPDMA_BSIZE_1)     //Source burst size set to 1
                            | GPDMA_DMACCxControl_DBSize(GPDMA_BSIZE_1)     //Destination burst size set to 1
                            | GPDMA_DMACCxControl_SWidth(transferWidth)  //Source Tranfser width set to 1 byte
                            | GPDMA_DMACCxControl_DWidth(transferWidth)  //Destination Transfer width set to 1 byte
                            | GPDMA_DMACCxControl_SI                        //Source increment after each transfer
                            | GPDMA_DMACCxControl_I;                        //Terminal count interrupt enable

    //Enable Channel
    pDMAchTx->CONFIG = GPDMA_DMACCxConfig_E                                                             //Enable
                            | GPDMA_DMACCxConfig_DestPeripheral(dstPeripheral)                          //Peripheral destination is SSP0 TX
                            | GPDMA_DMACCxConfig_TransferType(GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA)    //Memory to Peripheral
                            | GPDMA_DMACCxConfig_IE                                                     //Interrupt Error Mask
                            | GPDMA_DMACCxConfig_ITC;                                                   //Terminal count interrupt mask

    
}






//No Increment Versions (do not increment the memory buffer after each data transfer)

void SspDmaRxTransferNI(DMA_Channel_t ssp_dma_channel, const void *buf, uint32_t transferLength, DMA_TransferWidth_t transferWidth)
{
    // Setup DMA Receive: SSP --> inBuffer (Peripheral to Memory)
    const uint8_t channelNumber = dma_channels[ssp_dma_channel];
    uint8_t srcPeripheral;
    uint32_t srcAddress;
    
    if(ssp_dma_channel == DMA_SSP0_RX)
    {
        srcPeripheral = GPDMA_CONN_SSP0_Rx;
        srcAddress = (uint32_t)&LPC_SSP0->DR;
    }
    else if(ssp_dma_channel == DMA_SSP1_RX)
    {
        srcPeripheral = GPDMA_CONN_SSP1_Rx;
        srcAddress = (uint32_t)&LPC_SSP1->DR;
    }
    else
    {
        //invalid channel number
        return;
    }
    
    
    
    GPDMA_CH_T *pDMAchRx = (GPDMA_CH_T *) &(LPC_GPDMA->CH[channelNumber]);

    pDMAchRx->CONFIG = GPDMA_DMACCxConfig_H;                        //halt the DMA channel - Clears DMA FIFO
    
    LPC_GPDMA->INTTCCLEAR = (((1UL << (channelNumber)) & 0xFF));    //clear terminal count interrupt requests for Rx and Tx Channels
    LPC_GPDMA->INTERRCLR = (((1UL << (channelNumber)) & 0xFF));     //clear the error interrupt request

    
    // Enable DMA channels
    LPC_GPDMA->CONFIG = GPDMA_DMACConfig_E;
    while (!(LPC_GPDMA->CONFIG & GPDMA_DMACConfig_E)) {}

    pDMAchRx->SRCADDR  = srcAddress;                //Source Address (SSP DataRegister)
    pDMAchRx->DESTADDR = (uint32_t)buf;             //Destination Address (buffer in memory)
    pDMAchRx->LLI      = 0;                         //linked list item register

    pDMAchRx->CONTROL  = (transferLength & 0xFFF)
                            | GPDMA_DMACCxControl_SBSize(GPDMA_BSIZE_1)     //Source burst size set to 1
                            | GPDMA_DMACCxControl_DBSize(GPDMA_BSIZE_1)     //Destination burst size set to 1
                            | GPDMA_DMACCxControl_SWidth(transferWidth)  //Source Tranfser width set to 1 byte
                            | GPDMA_DMACCxControl_DWidth(transferWidth)  //Destination Transfer width set to 1 byte
                            | GPDMA_DMACCxControl_I;                        //Terminal count interrupt enable

    
    pDMAchRx->CONFIG =  GPDMA_DMACCxConfig_E                                                        //Enable
                        | GPDMA_DMACCxConfig_SrcPeripheral(srcPeripheral)                           //Peripheral destination is SSP0 RX
                        | GPDMA_DMACCxConfig_TransferType(GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA)    //Peripheral to Memory
                        | GPDMA_DMACCxConfig_IE                                                     //Interrupt Error Mask
                        | GPDMA_DMACCxConfig_ITC;                                                   //Terminal count interrupt mask

    
}

void SspDmaTxTransferNI(DMA_Channel_t ssp_dma_channel, const void *buf, uint32_t transferLength, DMA_TransferWidth_t transferWidth)
{
    // Setup DMA transfer: outBuffer --> SSP (Memory to Peripheral Transfer)
    const uint8_t channelNumber = dma_channels[ssp_dma_channel];
    uint8_t dstPeripheral;
    uint32_t dstAddress;
    
    if(ssp_dma_channel == DMA_SSP0_TX)
    {
        dstPeripheral = GPDMA_CONN_SSP0_Tx;
        dstAddress = (uint32_t)&LPC_SSP0->DR;
    }
    else if(ssp_dma_channel == DMA_SSP1_TX)
    {
        dstPeripheral = GPDMA_CONN_SSP1_Tx;
        dstAddress = (uint32_t)&LPC_SSP1->DR;
    }
    else
    {
        //invalid channel number
        return;
    }

    
    
    GPDMA_CH_T *pDMAchTx = (GPDMA_CH_T *) &(LPC_GPDMA->CH[channelNumber]);

    pDMAchTx->CONFIG = GPDMA_DMACCxConfig_H;                        //halt the DMA channel - Also clears the DMA FIFO
    
    LPC_GPDMA->INTTCCLEAR = (((1UL << (channelNumber)) & 0xFF));   //clear terminal count interrupt requests for Rx and Tx Channels
    LPC_GPDMA->INTERRCLR = (((1UL << (channelNumber)) & 0xFF));    //clear the error interrupt request

    
    // Enable DMA channels
    LPC_GPDMA->CONFIG = GPDMA_DMACConfig_E;
    while (!(LPC_GPDMA->CONFIG & GPDMA_DMACConfig_E)) {}
    
    pDMAchTx->SRCADDR  = (uint32_t)buf;             //Source Address (buffer in memory)
    pDMAchTx->DESTADDR = dstAddress;                //Destination Address (SSP0 DataRegister)
    pDMAchTx->LLI      = 0;                         //linked list item register
    pDMAchTx->CONTROL  = (transferLength & 0xFFF)
                            | GPDMA_DMACCxControl_SBSize(GPDMA_BSIZE_1)     //Source burst size set to 1
                            | GPDMA_DMACCxControl_DBSize(GPDMA_BSIZE_1)     //Destination burst size set to 1
                            | GPDMA_DMACCxControl_SWidth(transferWidth)  //Source Tranfser width set to 1 byte
                            | GPDMA_DMACCxControl_DWidth(transferWidth)  //Destination Transfer width set to 1 byte
                            | GPDMA_DMACCxControl_I;                        //Terminal count interrupt enable

    //Enable Channel
    pDMAchTx->CONFIG = GPDMA_DMACCxConfig_E                                                             //Enable
                            | GPDMA_DMACCxConfig_DestPeripheral(dstPeripheral)                          //Peripheral destination is SSP0 TX
                            | GPDMA_DMACCxConfig_TransferType(GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA)    //Memory to Peripheral
                            | GPDMA_DMACCxConfig_IE                                                     //Interrupt Error Mask
                            | GPDMA_DMACCxConfig_ITC;                                                   //Terminal count interrupt mask

    
}
