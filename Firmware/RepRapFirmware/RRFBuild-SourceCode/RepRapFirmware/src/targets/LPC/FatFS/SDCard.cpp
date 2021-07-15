/*------------------------------------------------------------------------*/
/* LPCXpresso176x: MMCv3/SDv1/SDv2 (SPI mode) control module              */
/*------------------------------------------------------------------------*/
/*
 /  Copyright (C) 2015, ChaN, all right reserved.
 /
 / * This software is a free software and there is NO WARRANTY.
 / * No restriction on use. You can use, modify and redistribute it for
 /   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
 / * Redistributions of source code must retain the above copyright notice.
 /
 /-------------------------------------------------------------------------*/


// Sdavi: Modified for RRF
// GA: Modified to use SharedSpiClient and moved from core

#include <stdio.h>
#include <stdlib.h>

#include "SDCard.h"
#include "SpiMode.h"
#include "SharedSpiDevice.h"
#include "SharedSpiClient.h"

//#define SD_DEBUG


constexpr uint32_t SCLK_SD25 =  50000000;   /* SCLK frequency under High Speed operation [Hz] */
constexpr uint32_t SCLK_SD12 =  25000000;   /* SCLK frequency under normal operation  [Hz] */
constexpr uint32_t SCLK_INIT =  400000;     /* SCLK frequency under initialization [Hz] */

/* MMC/SD command */
#define CMD0     (0)         /* GO_IDLE_STATE */
#define CMD1     (1)         /* SEND_OP_COND (MMC) */
#define ACMD41   (0x80+41)   /* SEND_OP_COND (SDC) */
#define CMD6     (6)         /* Switch Function Command*/
#define CMD8     (8)         /* SEND_IF_COND */
#define CMD9     (9)         /* SEND_CSD */
#define CMD10    (10)        /* SEND_CID */
#define CMD12    (12)        /* STOP_TRANSMISSION */
#define ACMD13   (0x80+13)   /* SD_STATUS (SDC) */
#define CMD16    (16)        /* SET_BLOCKLEN */
#define CMD17    (17)        /* READ_SINGLE_BLOCK */
#define CMD18    (18)        /* READ_MULTIPLE_BLOCK */
#define CMD23    (23)        /* SET_BLOCK_COUNT (MMC) */
#define ACMD23   (0x80+23)   /* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24    (24)        /* WRITE_BLOCK */
#define CMD25    (25)        /* WRITE_MULTIPLE_BLOCK */
#define CMD32    (32)        /* ERASE_ER_BLK_START */
#define CMD33    (33)        /* ERASE_ER_BLK_END */
#define CMD38    (38)        /* ERASE */
#define CMD48    (48)        /* READ_EXTR_SINGLE */
#define CMD49    (49)        /* WRITE_EXTR_SINGLE */
#define CMD55    (55)        /* APP_CMD */
#define CMD58    (58)        /* READ_OCR */




#define SD_COMMAND_TIMEOUT 5000

SDCard::SDCard(SSPChannel SSPSlot, Pin cs) {
    
    maxFrequency = SCLK_SD12; //default max frequency to run at
    frequency = SCLK_SD12;
    isHighSpeed = false;
    sdcardSectors = 0;
    sdcardBlockSize = 512;
    if (SSPSlot != SSPNONE)
    {
        spi = new SharedSpiClient(SharedSpiDevice::GetSharedSpiDevice(SSPSlot), SCLK_INIT, SPI_MODE_0, cs, false);
    }
    else
        spi = nullptr;
    status = STA_NOINIT;
}

//call before ReInit
void SDCard::SetSSPChannel(SSPChannel channel)
{
    if (channel != SSPNONE)
    {
        spi = new SharedSpiClient(SharedSpiDevice::GetSharedSpiDevice(channel), SCLK_INIT, SPI_MODE_0, NoPin, false);
    }
}


void SDCard::ReInit(Pin cs, uint32_t freq)
{
    maxFrequency = freq; //Maximum frequency set by the user

    if(!(status & STA_NOINIT))
    {
        //card already initialised
        if(isHighSpeed)
        {
            frequency = SCLK_SD25;
        }
        else
        {
            frequency = SCLK_SD12;
        }
    }
    if(frequency > maxFrequency) frequency = maxFrequency; //dont set higher than the max speed user set in config.

    if (spi != nullptr)
    {
        spi->SetClockFrequency(frequency);
        spi->SetCsPin(cs);
    }
}

void SDCard::unmount()
{
    status = STA_NOINIT;
    isHighSpeed = false;
    frequency = SCLK_INIT;
}

/*-----------------------------------------------------------------------*/
/* Send/Receive data to the MMC  (Platform dependent)                    */
/*-----------------------------------------------------------------------*/

/* Exchange a byte */
inline uint8_t SDCard::xchg_spi (uint8_t dat)
{
    uint8_t rx;
    spi->TransceivePacket(&dat, &rx, 1);
    return rx;
}


/* Receive multiple byte */
/* buff - Pointer to data buffer */
/* btr - Number of bytes to receive (16, 64 or 512) */
inline void SDCard::rcvr_spi_multi(uint8_t *buff, uint32_t btr)
{
    spi->TransceivePacket(nullptr, buff, btr);
}

/* Send multiple byte */
/* buff - ointer to the data */
/* Number of bytes to send (multiple of 16) */
inline void SDCard::xmit_spi_multi (const uint8_t *buff, uint32_t btx)
{
    spi->TransceivePacket(buff, nullptr, btx);
}



/*-----------------------------------------------------------------------*/
/* Wait for card ready                                                   */
/*-----------------------------------------------------------------------*/

/* wt - Timeout [ms] */
int SDCard::wait_ready (uint32_t wt) /* 1:Ready, 0:Timeout */
{
    uint8_t d;
    
    uint32_t now = millis();
    
    do {
        d = xchg_spi(0xFF);
        
        /* This loop takes a time. Insert rot_rdq() here for multitask envilonment. */
        
    } while (d != 0xFF && (millis() - now) < wt);    /* Wait for card goes ready or timeout */
    
    return (d == 0xFF) ? 1 : 0;
}

int selected = 0;
/*-----------------------------------------------------------------------*/
/* Deselect card and release SPI                                         */
/*-----------------------------------------------------------------------*/

void SDCard::deselect (void)
{
#ifdef SD_DEBUG
    if (!selected)
    {
        debugPrintf("deselect when not selected\n");
        return;
    }
#endif
    spi->Deselect();
    //xchg_spi(0xFF);    /* Dummy clock (force DO hi-z for multiple slave SPI) */
    selected = 0;
}



/*-----------------------------------------------------------------------*/
/* Select card and wait for ready                                        */
/*-----------------------------------------------------------------------*/

int SDCard::select (void)    /* 1:OK, 0:Timeout */
{
#ifdef SD_DEBUG
    if (selected)
    {
        debugPrintf("Selected when selected\n");
        return 0;
    }
#endif
    if (!spi->Select(500)) return 0;
    selected = 1;
    xchg_spi(0xFF);    /* Dummy clock (force DO enabled) */
    
    if (wait_ready(500)) return 1;    /* Leading busy check: Wait for card ready */
#ifdef SD_DEBUG
    debugPrintf("select timeout\n");
#endif
    spi->Deselect();        /* Timeout */
    return 0;
}


/*-----------------------------------------------------------------------*/
/* Receive a data packet from the MMC                                    */
/*-----------------------------------------------------------------------*/
/* buff - Data buffer */
/* btr - Data block length (byte) */
int SDCard::rcvr_datablock (uint8_t *buff, uint32_t btr)/* 1:OK, 0:Error */
{
    uint8_t token;
    
    uint32_t now = millis();
    do {                            /* Wait for DataStart token in timeout of 200ms */
        token = xchg_spi(0xFF);
        
        /* This loop will take a time. Insert rot_rdq() here for multitask envilonment. */
        
    } while ((token == 0xFF) && (millis() - now) < 200 );
    if(token != 0xFE) return 0;        /* Function fails if invalid DataStart token or timeout */
    rcvr_spi_multi(buff, btr);        /* Store trailing data to the buffer */
    xchg_spi(0xFF); xchg_spi(0xFF);    /* Discard CRC */
    
    return 1;                        /* Function succeeded */
}



/*-----------------------------------------------------------------------*/
/* Send a data packet to the MMC                                         */
/*-----------------------------------------------------------------------*/

/* buff - Pointer to 512 byte data to be sent */
/* Token */

int SDCard::xmit_datablock (const uint8_t *buff, uint8_t token) /* 1:OK, 0:Failed */
{
    if (!wait_ready(500)) return 0;        /* Leading busy check: Wait for card ready to accept data block */
    
    xchg_spi(token);                    /* Send token */
    if (token == 0xFD) return 1;        /* Do not send data if token is StopTran */
    
    xmit_spi_multi(buff, 512);            /* Data */
    xchg_spi(0xFF); xchg_spi(0xFF);        /* Dummy CRC */
    
    uint8_t resp = xchg_spi(0xFF);                /* Receive data resp */
    
    return (resp & 0x1F) == 0x05 ? 1 : 0;    /* Data was accepted or not */
    
    /* Busy check is done at next transmission */
}


/*-----------------------------------------------------------------------*/
/* Send a command packet to the MMC                                      */
/*-----------------------------------------------------------------------*/
/* cmd - Command index */
/* arg - Argument */
uint8_t SDCard::send_cmd (uint8_t cmd, uint32_t arg)/* Return value: R1 resp (bit7==1:Failed to send) */
{
    uint8_t n, res;
   
    if (cmd & 0x80) {    /* Send a CMD55 prior to ACMD<n> */
        cmd &= 0x7F;
        res = send_cmd(CMD55, 0);
        if (res > 1) return res;
    }
    
    /* Select the card and wait for ready except to stop multiple block read */
    if (cmd != CMD12) {
        xchg_spi(0xff);
    }
    
    /* Send command packet */
    xchg_spi(0x40 | cmd);                   /* Start + command index */
    xchg_spi((uint8_t)(arg >> 24));         /* Argument[31..24] */
    xchg_spi((uint8_t)(arg >> 16));         /* Argument[23..16] */
    xchg_spi((uint8_t)(arg >> 8));          /* Argument[15..8] */
    xchg_spi((uint8_t)arg);                 /* Argument[7..0] */
    n = 0x01;                               /* Dummy CRC + Stop */
    if (cmd == CMD0) n = 0x95;              /* Valid CRC for CMD0(0) */
    if (cmd == CMD8) n = 0x87;              /* Valid CRC for CMD8(0x1AA) */
    xchg_spi(n);
    
    /* Receive command resp */
    if (cmd == CMD12) xchg_spi(0xFF);       /* Discard following one byte when CMD12 */
    n = 10;                                 /* Wait for response (10 bytes max) */
    do
        res = xchg_spi(0xFF);
    while ((res & 0x80) && --n);
    return res;                            /* Return received response */
}

/*-----------------------------------------------------------------------*/
/* Initialize disk drive                                                 */
/*-----------------------------------------------------------------------*/

uint8_t SDCard::disk_initialize ()
{
    uint8_t n, cmd, ty, ocr[4];

    // Do we have a device to talk to?
    if (spi == nullptr) return 1;    
    if (status & STA_NODISK) return status;    /* Is a card existing in the soket? */
    
    
    //Change frequency to slow clock for initialisation
    spi->SetClockFrequency(SCLK_INIT);
    select();
    for (n = 10; n; n--) xchg_spi(0xFF);    /* Send 80 dummy clocks */
    ty = 0;
    if (send_cmd(CMD0, 0) == 1) {            /* Put the card SPI state */
       
        uint32_t now = millis();
        const uint32_t timeout = 1000;                        /* Initialization timeout = 1 sec */
        
        if (send_cmd(CMD8, 0x1AA) == 1) {    /* Is the card SDv2? */
            for (n = 0; n < 4; n++) ocr[n] = xchg_spi(0xFF);    /* Get 32 bit return value of R7 resp */
            if (ocr[2] == 0x01 && ocr[3] == 0xAA) {                /* Does the card support 2.7-3.6V? */
                while ((millis() - now) < timeout && send_cmd(ACMD41, 1UL << 30)) ;    /* Wait for end of initialization with ACMD41(HCS) */
                if ((millis() - now) < timeout && send_cmd(CMD58, 0) == 0) {        /* Check CCS bit in the OCR */
                    for (n = 0; n < 4; n++) ocr[n] = xchg_spi(0xFF);
                    ty = (ocr[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2;    /* Check if the card is SDv2 */
                }
            }
        } else {    /* Not an SDv2 card */
            if (send_cmd(ACMD41, 0) <= 1)     {    /* SDv1 or MMCv3? */
                ty = CT_SD1; cmd = ACMD41;    /* SDv1 (ACMD41(0)) */
            } else {
                ty = CT_MMC; cmd = CMD1;    /* MMCv3 (CMD1(0)) */
            }
            now = millis();
            while ((millis() - now) < timeout && send_cmd(cmd, 0)) ;        /* Wait for the card leaves idle state */
            if ((millis() - now) > timeout || send_cmd(CMD16, 512) != 0){    /* Set block length: 512 */
                ty = 0;
            }
        }
        //set card Blockmode to 512
        if(send_cmd(CMD16, 512) != 0) {
            //failed to set block mode
            debugPrintf("Failed to set blockmode\n");
        }
        
    }
    cardtype = ty;    /* Card type */
    deselect();
    if (ty) {        /* OK */

        //sdavi: now find the max freq to run card at.
        frequency = SCLK_SD12; // 12.5MB/s interface - clock speed up to 25MHz (default)
        if(cardtype & CT_SD2)
        {
            isHighSpeed = false;
            
            //Try and put the Card in HighSpeed Mode
            select();
            if (send_cmd(CMD6, 0x80FFFFF1) == 0)
            {
                // 512 bits of status (64 bytes)
                uint8_t buf[64];
                if(rcvr_datablock(buf, 64))
                {
                    //bits of interest are 376:379
                    isHighSpeed = ((buf[16] & 0x0F) == 1);
                    
                    if(isHighSpeed)
                    {
                        frequency = SCLK_SD25; // 25MB/s card interface - clock speed up to 50MHz
                        xchg_spi(0xFF);// send 8 dummy cycles before switching speed
#ifdef SD_DEBUG
                        debugPrintf("SDCard supports High Speed Mode\n");
#endif
                    }
                    
                }
            }
            deselect();
        }
        if(frequency > maxFrequency) frequency = maxFrequency; //dont set higher than the max speed user set in config.

        spi->SetClockFrequency(frequency);

        status = 0;// clear the status flags (currently not using NoDisk or Protect)
        
        //get the Sector Count for the card
        uint32_t sec = 0;
        if(disk_ioctl(GET_SECTOR_COUNT, &sec) == RES_OK) sdcardSectors = sec;
        
#ifdef SD_DEBUG
        debugPrintf("SD1:%d, SDv2:%d, SDv2HC:%d\n", ((cardtype & CT_SD1)>0),((cardtype & CT_SD2)>0), (( (cardtype & CT_SD2) && (cardtype & CT_BLOCK) )>0));
        debugPrintf("Sectors: %" PRIu32 ", BlockSize: %" PRIu32 "\n", sdcardSectors, sdcardBlockSize);
#endif
        
    } else {        /* Failed */
#ifdef SD_DEBUG
        debugPrintf("Failed to initialise SD card\n");
#endif

        status = STA_NOINIT;
        return 1;
    }
    return 0; //Success
}



/*-----------------------------------------------------------------------*/
/* Get disk status                                                       */
/*-----------------------------------------------------------------------*/

///* Physical drive number (0) */
uint8_t SDCard::disk_status ()
{
    return status;
}


CARD_TYPE SDCard::card_type()
{
    return cardtype;
}




/*-----------------------------------------------------------------------*/
/* Read sector(s)                                                        */
/*-----------------------------------------------------------------------*/
/* buff - Pointer to the data buffer to store read data */
/* sector - Start sector number (LBA) */
/* count - Number of sectors to read (1..128) */

DRESULT SDCard::disk_read (uint8_t *buff, uint32_t sector, uint32_t count)
{
    uint8_t cmd;
    if (!count) return RES_PARERR;        /* Check parameter */
    if (status & STA_NOINIT) return RES_NOTRDY;    /* Check if drive is ready */
    if (!(cardtype & CT_BLOCK)) sector *= 512;    /* LBA ot BA conversion (byte addressing cards) */
    select(); 
    cmd = count > 1 ? CMD18 : CMD17;            /*  READ_MULTIPLE_BLOCK : READ_SINGLE_BLOCK */
    if (send_cmd(cmd, sector) == 0) {
        do {
            if (!rcvr_datablock(buff, 512)) break;
            buff += 512;
        } while (--count);
        if (cmd == CMD18) send_cmd(CMD12, 0);    /* STOP_TRANSMISSION */
    }
    deselect();
    return count ? RES_ERROR : RES_OK;    /* Return result */
}



/*-----------------------------------------------------------------------*/
/* Write sector(s)                                                       */
/*-----------------------------------------------------------------------*/
/* Pointer to the data to write */
/* Start sector number (LBA) */
/* Number of sectors to write (1..128) */

DRESULT SDCard::disk_write (const uint8_t *buff, uint32_t sector, uint32_t count)
{
    if (!count){
#ifdef SD_DEBUG
        debugPrintf("[SDCard:disk_write] Err: count is incorrect count=%" PRIu32 "", count);
#endif
        return RES_PARERR;        /* Check parameter */
    }
    if (status & STA_NOINIT) return RES_NOTRDY;    /* Check drive status */
    if (status & STA_PROTECT) return RES_WRPRT;    /* Check write protect */
    
    if (!(cardtype & CT_BLOCK)) sector *= 512;    /* LBA ==> BA conversion (byte addressing cards) */
    select();
    if (count == 1) {    /* Single sector write */
        if ((send_cmd(CMD24, sector) == 0)    /* WRITE_BLOCK */
            && xmit_datablock(buff, 0xFE)) {
            count = 0;
        } else {
#ifdef SD_DEBUG
            debugPrintf("[SDCard:disk_write] SingleSectorWrite Failed. Sector:%" PRIu32 "\n", sector);
#endif
        }
    }
    else {                /* Multiple sector write */
        if (cardtype & CT_SDC) send_cmd(ACMD23, count);    /* Predefine number of sectors */
        if (send_cmd(CMD25, sector) == 0) {    /* WRITE_MULTIPLE_BLOCK */
            do {
                if (!xmit_datablock(buff, 0xFC)) break;
                buff += 512;
            } while (--count);
            if (!xmit_datablock(0, 0xFD)) count = 1;    /* STOP_TRAN token */
        }
    }
    deselect();

    return count ? RES_ERROR : RES_OK;    /* Return result */
}



/*-----------------------------------------------------------------------*/
/* Miscellaneous drive controls other than data read/write               */
/*-----------------------------------------------------------------------*/
/* Control command code */
/* Pointer to the control data */


DRESULT SDCard::disk_ioctl (uint8_t cmd, void *buff)
{
    DRESULT res;
    uint8_t n, csd[16];
    uint32_t csize;
    if (status & STA_NOINIT) return RES_NOTRDY;    /* Check if drive is ready */
    
    res = RES_ERROR;
    if (select()) res = RES_OK;
    
    switch (cmd) {
        case CTRL_SYNC:            /* Wait for end of internal write process of the drive */
            //if (select()) res = RES_OK;
            break;
            
        case GET_SECTOR_COUNT:    /* Get drive capacity in unit of sector (DWORD) */
            if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {
                if ((csd[0] >> 6) == 1) {    /* SDC ver 2.00 */
                    csize = csd[9] + ((uint16_t)csd[8] << 8) + ((uint32_t)(csd[7] & 63) << 16) + 1;
                    *(uint32_t*)buff = csize << 10;
                } else {                    /* SDC ver 1.XX or MMC ver 3 */
                    n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
                    csize = (csd[8] >> 6) + ((uint16_t)csd[7] << 2) + ((uint16_t)(csd[6] & 3) << 10) + 1;
                    *(uint32_t*)buff = csize << (n - 9);
                }
                res = RES_OK;
            }
            break;
            
        case GET_BLOCK_SIZE:    /* Get erase block size in unit of sector (DWORD) */
            if (cardtype & CT_SD2) {    /* SDC ver 2.00 */
                if (send_cmd(ACMD13, 0) == 0) {    /* Read SD status */
                    xchg_spi(0xFF);
                    if (rcvr_datablock(csd, 16)) {                /* Read partial block */
                        for (n = 64 - 16; n; n--) xchg_spi(0xFF);    /* Purge trailing data */
                        *(uint32_t*)buff = 16UL << (csd[10] >> 4);
                        res = RES_OK;
                    }
                }
            } else {                    /* SDC ver 1.XX or MMC */
                if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {    /* Read CSD */
                    if (cardtype & CT_SD1) {    /* SDC ver 1.XX */
                        *(uint32_t*)buff = (((csd[10] & 63) << 1) + ((uint16_t)(csd[11] & 128) >> 7) + 1) << ((csd[13] >> 6) - 1);
                    } else {                    /* MMC */
                        *(uint32_t*)buff = ((uint16_t)((csd[10] & 124) >> 2) + 1) * (((csd[11] & 3) << 3) + ((csd[11] & 224) >> 5) + 1);
                    }
                    res = RES_OK;
                }
            }
            break;

        default:
#ifdef SD_DEBUG
            debugPrintf("[SDCard:disk_ioctl] Unhandled command: %d", cmd);
#endif
            res = RES_PARERR;
    }
    
    deselect();
    return res;
}


