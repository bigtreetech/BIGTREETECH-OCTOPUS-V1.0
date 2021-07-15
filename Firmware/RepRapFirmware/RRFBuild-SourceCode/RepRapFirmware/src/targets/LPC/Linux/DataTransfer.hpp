//Author: sdavi

//SBC connected to SSP0
#include "chip.h" //LPC Open
#include "DMA.h"
#include "HardwareSPI.h"

static HardwareSPI *spiDevice;

volatile bool dataReceived = false, transferReadyHigh = false;
volatile unsigned int spiTxUnderruns = 0, spiRxOverruns = 0;
void InitSpi() noexcept;

// interrupt handler
void SpiInterrupt(HardwareSPI *spi) noexcept
{
    dataReceived = true;
    TaskBase::GiveFromISR(linuxTaskHandle);
}



void setup_spi(void *inBuffer, const void *outBuffer, size_t bytesToTransfer)
{
    spiDevice->disable();
    spiDevice->startTransfer((const uint8_t *)outBuffer, (uint8_t *)inBuffer, bytesToTransfer, SpiInterrupt);
   
    // Begin transfer
    transferReadyHigh = !transferReadyHigh;
    digitalWrite(SbcTfrReadyPin, transferReadyHigh);
}

void disable_spi()
{
    spiDevice->disable();
}
    
// Set up the SPI system
void InitSpi() noexcept
{
    spiDevice = &HardwareSPI::SSP0;
    //In Slave mode, the SSP clock rate provided by the master must not exceed 1/12 of the
    //SSP peripheral clock (which is set to PCLK/1 above), therefore to cater for LPC1768
    //(100MHz) max Master SCK is limited to 8.33MHz
    spiDevice->configureDevice(SSP_MODE_SLAVE, SSP_BITS_8, SSP_CLOCK_MODE3, SystemCoreClock/2, true);
}
