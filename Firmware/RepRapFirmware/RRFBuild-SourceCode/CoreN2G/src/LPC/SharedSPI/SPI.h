#ifndef SPI_H
#define SPI_H

#include "CoreImp.h"
enum SSPChannel : uint8_t
{
    //Hardware SPI
    SSP0 = 0,
    SSP1,
    
    //Software SPI
    SWSPI0,

    // Not defined
    SSPNONE = 0xff
};

constexpr uint16_t SPITimeoutMillis = 250;
typedef enum
{
    SPI_ERROR = -1,
    SPI_OK = 0,
    SPI_ERROR_TIMEOUT = 1,
    SPI_ERROR_ARGUMENT,
    SPI_ERROR_OVERRUN,
    SPI_ERROR_MODE_FAULT,
    SPI_ERROR_OVERRUN_AND_MODE_FAULT
} spi_status_t;

class SPI
{
public:
    virtual void configureDevice(uint32_t bits, uint32_t clockMode, uint32_t bitRate) noexcept;
    virtual spi_status_t transceivePacket(const uint8_t *tx_data, uint8_t *rx_data, size_t len) noexcept;    
    virtual bool waitForTxEmpty() noexcept;
    virtual void initPins(Pin sck, Pin miso, Pin mosi, Pin cs = NoPin) noexcept;
    static SPI *getSSPDevice(SSPChannel channel) noexcept;
};

#endif
