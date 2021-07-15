#ifndef SOFTWARESPI_H
#define SOFTWARESPI_H

#include "CoreImp.h"
#include "variant.h"
#include "SPI.h"

class SoftwareSPI: public SPI
{
public:
    SoftwareSPI();
    spi_status_t transceivePacket(const uint8_t *tx_data, uint8_t *rx_data, size_t len) noexcept;
    void configureDevice(uint32_t bits, uint32_t clockMode, uint32_t bitRate) noexcept; // Master mode
    void initPins(Pin clk, Pin miso, Pin mosi, Pin cs = NoPin, DMA_Stream_TypeDef* rxStream = nullptr, uint32_t rxChan = 0, IRQn_Type rxIrq = DMA1_Stream0_IRQn,
                            DMA_Stream_TypeDef* txStream = nullptr, uint32_t txChan = 0, IRQn_Type txIrq = DMA1_Stream0_IRQn) noexcept;
    bool waitForTxEmpty() noexcept;
    
    static SoftwareSPI SWSSP0;
    static SoftwareSPI SWSSP1;
    static SoftwareSPI SWSSP2;

private:
    
    uint8_t mode01TransferByte(uint8_t byte_out) noexcept;
    uint8_t mode23TransferByte(uint8_t byte_out) noexcept;
    
    bool needInit;
    Pin sck;
    Pin mosi;
    Pin miso;
    uint32_t mode;
    uint32_t delay;
};




#endif
