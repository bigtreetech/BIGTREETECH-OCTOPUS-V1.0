//Author: sdavi

#include "chip.h" //LPC Open
#include "DMA.h"
#include "HardwareSPI.h"

//ESP connected to SSP0
static HardwareSPI *spiDevice;
static volatile bool dmaActive;

static inline void DisableSpi() noexcept
{
    if (spiDevice != nullptr)
        spiDevice->disable();
}

static inline void spi_dma_disable() noexcept
{
    if (spiDevice != nullptr)
        spiDevice->stopTransfer();
}

static bool spi_dma_check_rx_complete() noexcept
{
    if (!transferPending)
    {
        // If CS goes high before the DMA transfer completes we need to abort
        // the transfer.
        if (dmaActive)
            spiDevice->stopTransfer();
        dmaActive = false;
        return true;
    }
    return false;
}


// SPI completion handler
void ESP_SPI_HANDLER(HardwareSPI *spiDevice) noexcept
{
    dmaActive = false;
	wifiInterface->SpiInterrupt();
}

void WiFiInterface::spi_slave_dma_setup(uint32_t dataOutSize, uint32_t dataInSize) noexcept
{
    //Find the largest transfer size
    const uint32_t dsize = MAX(dataOutSize + sizeof(MessageHeaderSamToEsp), dataInSize + sizeof(MessageHeaderEspToSam));
    // clear any previous transaction
    dmaActive = true;
    spiDevice->flushRx();
    spiDevice->startTransfer((const uint8_t *)bufferOut, (uint8_t *)bufferIn, dsize, ESP_SPI_HANDLER);
}

void WiFiInterface::SpiInterrupt() noexcept
{
    if (transferPending)
    {
        digitalWrite(SamTfrReadyPin, LOW);

        transferPending = false;
        TaskBase::GiveFromISR(espWaitingTask);
    }
}

static void SpiCSInterrupt(CallbackParameter) noexcept
{
    // Called when CS goes high. If the DMA trasnfer has not yet completed
    // we force it to end early.
    if (transferPending && digitalRead(SPI0_SSEL) != 0)
        wifiInterface->SpiInterrupt();    
}


// Set up the SPI system
void WiFiInterface::SetupSpi() noexcept
{
    attachInterrupt(SPI0_SSEL, SpiCSInterrupt, InterruptMode::rising, nullptr);

    spiDevice = &HardwareSPI::SSP0;
    //In Slave mode, the SSP clock rate provided by the master must not exceed 1/12 of the
    //SSP peripheral clock (which is set to PCLK/1 above), therefore to cater for LPC1768
    //(100MHz) max Master SCK is limited to 8.33MHz
    spiDevice->configureDevice(SSP_MODE_SLAVE, SSP_BITS_8, SSP_CLOCK_MODE1, SystemCoreClock/2, true);
}
    
