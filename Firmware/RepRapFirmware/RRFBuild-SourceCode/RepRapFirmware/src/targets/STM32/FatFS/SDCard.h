/*
 SDClass for use by RepRapFirmware
 
 Author: GA
 
*/
#ifndef SDCARD_H
#define SDCARD_H


#include "Core.h"
#include "diskio.h" //fatfs


#define SD_DEFAULT_BLOCK_SIZE 512

/* MMC card type flags (MMC_GET_TYPE) */
#define CT_MMC        0x01        /* MMC ver 3 */
#define CT_SD1        0x02        /* SD ver 1 */
#define CT_SD2        0x04        /* SD ver 2 */
#define CT_SDC        (CT_SD1|CT_SD2)    /* SD */
#define CT_BLOCK      0x08        /* Block addressing */



typedef uint8_t CARD_TYPE;

class SDCard {
public:
    virtual ~SDCard() noexcept = default;
    CARD_TYPE card_type(void) noexcept {return cardtype;};
    uint32_t interface_speed() noexcept  { return frequency; };
    uint32_t disk_sectors() noexcept { return sdcardSectors; };
    uint32_t disk_blocksize() noexcept { return sdcardBlockSize; };
    
    virtual void unmount() noexcept = 0;
    virtual void set_max_frequency(uint32_t maxFrequency) noexcept = 0;  
    //DiskIO
    virtual uint8_t disk_initialize() noexcept = 0;
    virtual uint8_t disk_status() noexcept = 0;
    virtual DRESULT disk_read (uint8_t *buff, uint32_t sector, uint32_t count) noexcept = 0;
    virtual DRESULT disk_write (const uint8_t *buff, uint32_t sector, uint32_t count) noexcept = 0;
    virtual DRESULT disk_ioctl (uint8_t cmd, void *buff) noexcept = 0;

protected:
    CARD_TYPE cardtype;
    uint32_t frequency;    
    uint32_t sdcardSectors;
    uint32_t sdcardBlockSize;    
    bool isHighSpeed;
};

#endif
