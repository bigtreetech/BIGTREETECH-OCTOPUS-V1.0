/*
 SDClass for use by RepRapFirmware
 
 Author: sdavi
 
*/
#ifndef SDCARD_H
#define SDCARD_H


#include "gpio.h"
#include "Core.h"
#include "SharedSpiClient.h"

#include "diskio.h" //fatfs




/* MMC card type flags (MMC_GET_TYPE) */
#define CT_MMC        0x01        /* MMC ver 3 */
#define CT_SD1        0x02        /* SD ver 1 */
#define CT_SD2        0x04        /* SD ver 2 */
#define CT_SDC        (CT_SD1|CT_SD2)    /* SD */
#define CT_BLOCK      0x08        /* Block addressing */



typedef uint8_t CARD_TYPE;

class SDCard {
public:


    SDCard(SSPChannel SSPSlot, Pin cs);
    ~SDCard() {};
    void ReInit(Pin cs, uint32_t frequency);
    void SetSSPChannel(SSPChannel channel);

    CARD_TYPE card_type(void);
    
    void unmount();
    uint32_t interface_speed() { return frequency; };
    uint32_t disk_sectors() { return sdcardSectors; };
    uint32_t disk_blocksize() { return sdcardBlockSize; };
    uint32_t disk_highSpeedMode() {return isHighSpeed; };
    
    
    
    //DiskIO
    uint8_t disk_initialize();
    uint8_t disk_status();
    DRESULT disk_read (uint8_t *buff, uint32_t sector, uint32_t count);
    DRESULT disk_write (const uint8_t *buff, uint32_t sector, uint32_t count);
    DRESULT disk_ioctl (uint8_t cmd, void *buff);

protected:

    inline uint8_t xchg_spi (uint8_t dat);
    inline void rcvr_spi_multi(uint8_t *buff, uint32_t btr);
    inline void xmit_spi_multi (const uint8_t *buff, uint32_t btx);
    int wait_ready (uint32_t wt);
    void deselect (void);
    int select (void);
    int rcvr_datablock (uint8_t *buff, uint32_t btr);
    int xmit_datablock (const uint8_t *buff, uint8_t token);
    uint8_t send_cmd (uint8_t cmd, uint32_t arg);

    bool enableHighSpeedMode();
    
    //variables
    SharedSpiClient *spi;
    CARD_TYPE cardtype;
    uint32_t maxFrequency; //max frequency the user has specified
    uint32_t frequency;
    uint8_t status;
    
    
    uint32_t sdcardSectors;
    uint32_t sdcardBlockSize;
    
    bool isHighSpeed;
};

#endif
