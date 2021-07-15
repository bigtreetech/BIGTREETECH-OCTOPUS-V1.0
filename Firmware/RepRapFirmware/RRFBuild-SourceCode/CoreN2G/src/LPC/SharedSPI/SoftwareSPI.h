#ifndef SOFTWARESPI_H
#define SOFTWARESPI_H

#include "Core.h"
#include "variant.h"
#include "SPI.h"

class SoftwareSPI: public SPI
{
public:
    SoftwareSPI();
    spi_status_t transceivePacket(const uint8_t *tx_data, uint8_t *rx_data, size_t len) noexcept;
    void configureDevice(uint32_t bits, uint32_t clockMode, uint32_t bitRate) noexcept; // Master mode
    void initPins(Pin sck, Pin miso, Pin mosi, Pin cs = NoPin) noexcept;
    bool waitForTxEmpty() noexcept;
    
    static SoftwareSPI SWSSP0;

private:
    
    uint8_t transfer_byte(uint8_t byte_out) noexcept;
    
    bool needInit;
    Pin sck;
    Pin mosi;
    Pin miso;
};




#endif
