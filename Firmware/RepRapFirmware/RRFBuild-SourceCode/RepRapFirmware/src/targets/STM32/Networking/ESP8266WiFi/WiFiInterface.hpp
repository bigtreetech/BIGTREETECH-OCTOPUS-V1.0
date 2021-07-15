//Author: sdavi/gloomyandy
#include "Hardware/SharedSpi/SpiMode.h"
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
    dmaActive = false;
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
    spiDevice->flushRx();
    dmaActive = true;
    spiDevice->startTransfer((const uint8_t *)bufferOut, (uint8_t *)bufferIn, dsize, ESP_SPI_HANDLER);
}

void WiFiInterface::SpiInterrupt() noexcept
{
    if (transferPending)
    {
        digitalWrite(SamTfrReadyPin, 0);

        transferPending = false;
        TaskBase::GiveFromISR(espWaitingTask);
    }
}

static void SpiCSInterrupt(CallbackParameter) noexcept
{
    // Called when CS goes high. If the DMA trasnfer has not yet completed
    // we force it to end early.
    if (transferPending && digitalRead(SamCsPin) != 0)
        wifiInterface->SpiInterrupt();    
}


// Set up the SPI system
void WiFiInterface::SetupSpi() noexcept
{
    attachInterrupt(SamCsPin, SpiCSInterrupt, InterruptMode::rising, nullptr);
    spiDevice = (HardwareSPI *) SPI::getSSPDevice(WiFiSpiChannel);
    spiDevice->configureDevice(SPI_MODE_SLAVE, 8, (uint8_t)SPI_MODE_1, 100000000, false);
}
    
