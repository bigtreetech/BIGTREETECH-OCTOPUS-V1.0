/*
 SDClass for use by RepRapFirmware
 
 Author: GA
 
*/
#ifndef SDCARDSDIO_H
#define SDCARDSDIO_H


#include "SDCard.h"
#include "HardwareSDIO.h"

class SDCardSDIO : public SDCard {
public:
    SDCardSDIO() noexcept;
    ~SDCardSDIO() noexcept {};

    void unmount() noexcept;
    void set_max_frequency(uint32_t maxFrequency) noexcept;  

    //DiskIO
    uint8_t disk_initialize() noexcept;
    uint8_t disk_status() noexcept;
    DRESULT disk_read (uint8_t *buff, uint32_t sector, uint32_t count) noexcept;
    DRESULT disk_write (const uint8_t *buff, uint32_t sector, uint32_t count) noexcept;
    DRESULT disk_ioctl (uint8_t cmd, void *buff) noexcept;

protected:
    HardwareSDIO *sdio;
    uint8_t status;
};

#endif
