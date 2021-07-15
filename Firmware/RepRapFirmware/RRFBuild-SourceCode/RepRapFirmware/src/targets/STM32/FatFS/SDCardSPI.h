/*
 SDClass for use by RepRapFirmware
 
 Author: GA
 
*/
#ifndef SDCARDSPI_H
#define SDCARDSPI_H


#include "SDCard.h"
#include "SharedSpiClient.h"
class SDCardSPI : public SDCard {
public:
    SDCardSPI(SSPChannel SSPSlot, Pin cs) noexcept;
    ~SDCardSPI() noexcept {};

    void unmount() noexcept;
    virtual void set_max_frequency(uint32_t maxFrequency) noexcept;  

    //DiskIO
    uint8_t disk_initialize() noexcept;
    uint8_t disk_status() noexcept;
    DRESULT disk_read (uint8_t *buff, uint32_t sector, uint32_t count) noexcept;
    DRESULT disk_write (const uint8_t *buff, uint32_t sector, uint32_t count) noexcept;
    DRESULT disk_ioctl (uint8_t cmd, void *buff) noexcept;

protected:
    inline uint8_t xchg_spi (uint8_t dat) noexcept;
    inline void rcvr_spi_multi(uint8_t *buff, uint32_t btr) noexcept;
    inline void xmit_spi_multi (const uint8_t *buff, uint32_t btx) noexcept;
    int wait_ready (uint32_t wt) noexcept;
    void deselect (void) noexcept;
    int select (void) noexcept;
    int rcvr_datablock (uint8_t *buff, uint32_t btr) noexcept;
    int xmit_datablock (const uint8_t *buff, uint8_t token) noexcept;
    uint8_t send_cmd (uint8_t cmd, uint32_t arg) noexcept;

    bool enableHighSpeedMode() noexcept;
    
    //variables
    SharedSpiClient *spi;
    uint32_t maxFrequency;
    uint8_t status;
    // We need cmd buffers that are not on the stack so that
    // they can be accessed via DMA
    uint8_t tx;
    uint8_t rx;
    uint8_t cmdData[64];
};

#endif
