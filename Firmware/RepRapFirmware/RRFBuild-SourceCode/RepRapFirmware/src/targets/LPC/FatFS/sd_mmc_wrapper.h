#ifndef SD_MMC_WRAPPER_H
#define SD_MMC_WRAPPER_H

#include "Core.h"
#include "SPI.h"

//#define _DRIVES 2 // Support 2 cards (one on each SSP slot)
constexpr size_t _DRIVES = 1;


typedef uint8_t sd_mmc_err_t; //!< Type of return error code

#define SD_MMC_OK               0    //! No error
#define SD_MMC_INIT_ONGOING     1    //! Card not initialized
#define SD_MMC_ERR_NO_CARD      2    //! No SD/MMC card inserted
#define SD_MMC_ERR_UNUSABLE     3    //! Unusable card
#define SD_MMC_ERR_SLOT         4    //! Slot unknown
#define SD_MMC_ERR_COMM         5    //! General communication error
#define SD_MMC_ERR_PARAM        6    //! Illegal input parameter
#define SD_MMC_ERR_WP           7    //! Card write protected
#define SD_MMC_CD_DEBOUNCING    8     //! Waiting for card to settle after CD


typedef uint8_t card_type_t; //!< Type of card type
#define CARD_TYPE_UNKNOWN   (0)      //!< Unknown type card
#define CARD_TYPE_SD        (1 << 0) //!< SD card
#define CARD_TYPE_MMC       (1 << 1) //!< MMC card
#define CARD_TYPE_SDIO      (1 << 2) //!< SDIO card
#define CARD_TYPE_HC        (1 << 3) //!< High capacity card
#define CARD_TYPE_SD_COMBO  (CARD_TYPE_SD | CARD_TYPE_SDIO)


void sd_mmc_init(/*const Pin cdPins[],*/ const Pin wpPins[], const Pin spiCsPins[]);
sd_mmc_err_t sd_mmc_check(uint8_t slot);
uint32_t sd_mmc_get_capacity(uint8_t slot);
card_type_t sd_mmc_get_type(uint8_t slot);
void sd_mmc_unmount(uint8_t slot);
uint32_t sd_mmc_get_interface_speed(uint8_t slot);


void sd_mmc_reinit_slot(uint8_t slot, Pin csPin, uint32_t spiFrequency);
void sd_mmc_setSSPChannel(uint8_t slot, SSPChannel channel);


#endif
