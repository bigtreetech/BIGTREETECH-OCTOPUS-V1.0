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
#include "RepRapFirmware.h"
#include "SDCardSDIO.h"

//#define SD_DEBUG


constexpr uint32_t SCLK_SD25 =  50000000;   /* SCLK frequency under High Speed operation [Hz] */
constexpr uint32_t SCLK_SD12 =  25000000;   /* SCLK frequency under normal operation  [Hz] */
constexpr uint32_t SCLK_INIT =  400000;     /* SCLK frequency under initialization [Hz] */


#define SD_COMMAND_TIMEOUT 5000

SDCardSDIO::SDCardSDIO() noexcept {
    frequency = SCLK_SD12;
    isHighSpeed = false;
    sdcardSectors = 0;
    sdcardBlockSize = 512;
    status = STA_NOINIT;
    sdio = &HardwareSDIO::SDIO1;
}

void SDCardSDIO::set_max_frequency(uint32_t maxFreq) noexcept
{

}

void SDCardSDIO::unmount() noexcept
{
    status = STA_NOINIT;
    isHighSpeed = false;
    frequency = SCLK_INIT;
}


/*-----------------------------------------------------------------------*/
/* Initialize disk drive                                                 */
/*-----------------------------------------------------------------------*/

uint8_t SDCardSDIO::disk_initialize () noexcept
{
    status = STA_NOINIT;
    if (sdio->Init() == MSD_OK)
    {
        if (sdio->GetCardState() == SD_TRANSFER_OK)
        {
            HAL_SD_CardInfoTypeDef cardInfo;
            sdio->GetCardInfo(&cardInfo);
#ifdef SD_DEBUG
            debugPrintf("Card type %x ver %d class %x sectors %d\n", (unsigned int)cardInfo.CardType, (int)cardInfo.CardVersion, (unsigned int)cardInfo.Class, (int)cardInfo.LogBlockNbr);
#endif
            // Stndard SDIO freq is 24MHz with a 4 bit wide transfer
            frequency = 24000000*4;
            cardtype = (cardInfo.CardType == CARD_SDHC_SDXC ? CT_SD2|CT_BLOCK : (cardInfo.CardType == CARD_SDSC ? CT_SD2 : CT_SD1));
            sdcardBlockSize = cardInfo.LogBlockSize;
            sdcardSectors = cardInfo.LogBlockNbr;
            status &= ~STA_NOINIT;
        }
    }

    return status;
}



/*-----------------------------------------------------------------------*/
/* Get disk status                                                       */
/*-----------------------------------------------------------------------*/

///* Physical drive number (0) */
uint8_t SDCardSDIO::disk_status () noexcept
{
    return status;
}


/*-----------------------------------------------------------------------*/
/* Read sector(s)                                                        */
/*-----------------------------------------------------------------------*/
/* buff - Pointer to the data buffer to store read data */
/* sector - Start sector number (LBA) */
/* count - Number of sectors to read (1..128) */

DRESULT SDCardSDIO::disk_read (uint8_t *buff, uint32_t sector, uint32_t count) noexcept
{
    if (!count) return RES_PARERR;        /* Check parameter */
    if (status & STA_NOINIT) return RES_NOTRDY;    /* Check if drive is ready */
    //debugPrintf("Read sector %d length %d\n", sector, count);
    //if (!(cardtype & CT_BLOCK)) sector *= 512;    /* LBA ot BA conversion (byte addressing cards) */
    if (sdio->ReadBlocks((uint32_t *) buff, sector, count, SD_COMMAND_TIMEOUT) == MSD_OK)
        return RES_OK;
    else
    {
        debugPrintf("Error reading sector %d length %d\n", (int)sector, (int)count);
        return RES_ERROR;
    }
}



/*-----------------------------------------------------------------------*/
/* Write sector(s)                                                       */
/*-----------------------------------------------------------------------*/
/* Pointer to the data to write */
/* Start sector number (LBA) */
/* Number of sectors to write (1..128) */

DRESULT SDCardSDIO::disk_write (const uint8_t *buff, uint32_t sector, uint32_t count) noexcept
{
    if (!count){
#ifdef SD_DEBUG
        debugPrintf("[SDCard:disk_write] Err: count is incorrect count=%" PRIu32 "", count);
#endif
        return RES_PARERR;        /* Check parameter */
    }
    if (status & STA_NOINIT) return RES_NOTRDY;    /* Check drive status */
    if (status & STA_PROTECT) return RES_WRPRT;    /* Check write protect */
    
    //if (!(cardtype & CT_BLOCK)) sector *= 512;    /* LBA ==> BA conversion (byte addressing cards) */
    //debugPrintf("write sector %d length %d\n", sector, count);
    if (sdio->WriteBlocks((uint32_t *)buff, sector, count, SD_COMMAND_TIMEOUT) == MSD_OK)
        return RES_OK;
    else
    {
        debugPrintf("Write error sector %d length %d\n", (int)sector, (int)count);
        return RES_ERROR;
    }
}



/*-----------------------------------------------------------------------*/
/* Miscellaneous drive controls other than data read/write               */
/*-----------------------------------------------------------------------*/
/* Control command code */
/* Pointer to the control data */


DRESULT SDCardSDIO::disk_ioctl (uint8_t cmd, void *buff) noexcept
{
    HAL_SD_CardInfoTypeDef cardInfo;
    if (status & STA_NOINIT) return RES_NOTRDY;    /* Check if drive is ready */
    
    DRESULT res = RES_ERROR;
    switch (cmd) {
        case CTRL_SYNC:            /* Wait for end of internal write process of the drive */
            res = RES_OK;
            break;
            
        case GET_SECTOR_COUNT :
            sdio->GetCardInfo(&cardInfo);
            *(uint32_t*)buff = cardInfo.LogBlockNbr;
            res = RES_OK;
            break;

        case GET_SECTOR_SIZE :
            sdio->GetCardInfo(&cardInfo);
            *(uint16_t*)buff = cardInfo.LogBlockSize;
            res = RES_OK;
            break;

        /* Get erase block size in unit of sector (DWORD) */
        case GET_BLOCK_SIZE :
            sdio->GetCardInfo(&cardInfo);
            *(uint32_t*)buff = cardInfo.LogBlockSize / SD_DEFAULT_BLOCK_SIZE;
            res = RES_OK;
            break;
        default:
#ifdef SD_DEBUG
            debugPrintf("[SDCard:disk_ioctl] Unhandled command: %d", cmd);
#endif
            res = RES_PARERR;
    }
    
    return res;
}


