/* -----------------------------------------------------------------------------
 * Copyright (c) 2014 ARM Ltd.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software. Permission is granted to anyone to use this
 * software for any purpose, including commercial applications, and to alter
 * it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 *
 * $Date:        16. December 2014
 * $Revision:    V1.00
 *
 * Project:      Flash Programming Functions for ATSAMC
 * --------------------------------------------------------------------------- */

/* History:
 *  Version 1.00
 *    Initial release
 */

#include "..\FlashOS.H"                          /* FlashOS Structures */

typedef volatile unsigned long    vu32;
typedef volatile unsigned short   vu16;
typedef volatile unsigned char    vu8;
typedef          unsigned long     u32;
typedef          unsigned char     u8;

/* System Control Interface register */
typedef struct {
  vu32 WRCTRL;           /* offset: 0x000 (R/W 32) Write Control Register */
} PAC_TypeDef;


/* Flash Registers register */
typedef struct {
  vu16 CTRLA;           /* offset: 0x000 (R/W 16) NVM Control Register A */
  vu8  RESERVED1[2];
  vu32 CTRLB;           /* offset: 0x004 (R/W 32) NVM Control Register B */
  vu32 PARAM;           /* offset: 0x008 (R/W 32) Parameter Register */
  vu8  INTENCLR;        /* offset: 0x00C (R/W  8) Interrupt Enable Clear Register */
  vu8  RESERVED2[3];
  vu8  INTENSET;        /* offset: 0x010 (R/W  8) Interrupt Enable Set Register */
  vu8  RESERVED3[3];
  vu8  INTFLAG;         /* offset: 0x014 (R/W  8) Interrupt Flag Status and Clear Register */
  vu8  RESERVED4[3];
  vu16 STATUS;          /* offset: 0x018 (R/W 16) Status Register */
  vu8  RESERVED5[2];
  vu32 ADDR;            /* offset: 0x01C (R/W 32) Address Register */
  vu16 LOCK;            /* offset: 0x020 (R/W 16) Lock Register */
} NVMCTRL_TypeDef;

/* NVMCTRL Control Register A definitions */
#define NVMCTRL_CTRLA_CMDEX_KEY    (0xA5UL   <<  8)    /* Command Execution Key */

/* NVMCTRL Control Register A command definitions */
#define NVMCTRL_CTRLA_CMD_ER       (0x02UL   <<  0)    /* Erase Row */
#define NVMCTRL_CTRLA_CMD_WP       (0x04UL   <<  0)    /* Write Page */
#define NVMCTRL_CTRLA_CMD_EAR      (0x05UL   <<  0)    /* Erase Auxiliary Row */
#define NVMCTRL_CTRLA_CMD_WAP      (0x06UL   <<  0)    /* Write Auxiliary Page */
#define NVMCTRL_CTRLA_CMD_WL       (0x0FUL   <<  0)    /* Write lockbits */
#define NVMCTRL_CTRLA_CMD_RWWEEER  (0x1AUL   <<  0)    /* RWWEE Erase Row */
#define NVMCTRL_CTRLA_CMD_RWWEEWP  (0x1CUL   <<  0)    /* RWWEE Write Page */
#define NVMCTRL_CTRLA_CMD_LR       (0x40UL   <<  0)    /* Lock Region */
#define NVMCTRL_CTRLA_CMD_UR       (0x41UL   <<  0)    /* Unlock Region */
#define NVMCTRL_CTRLA_CMD_SPRM     (0x42UL   <<  0)    /* Set power reduction mode */
#define NVMCTRL_CTRLA_CMD_CPRM     (0x43UL   <<  0)    /* Clear power reduction mode */
#define NVMCTRL_CTRLA_CMD_PBC      (0x44UL   <<  0)    /* Page Buffer Clear */
#define NVMCTRL_CTRLA_CMD_SSB      (0x45UL   <<  0)    /* Set Security Bit */
#define NVMCTRL_CTRLA_CMD_INVALL   (0x46UL   <<  0)    /* Invalidate all cache lines */

/* NVMCTRL NVM Parameter Register definitions */
#define NVMCTRL_PARAM_NVMP          (0xFFFFUL <<  0)   /* NVM Pages */
#define NVMCTRL_PARAM_PSZ           (0x07UL   << 16)   /* Page Size */

/* NVMCTRL Interrupt Flag Register definitions */
#define NVMCTRL_INTFLAG_READY       (0x01UL   <<  0)   /* NVM READY */
#define NVMCTRL_INTFLAG_ERROR       (0x01UL   <<  1)   /* Error */

/* NVMCTRL Status Register definitions */
#define NVMCTRL_STATUS_PRM          (0x01UL   <<  0)   /* Power Reduction Mode */
#define NVMCTRL_STATUS_LOAD         (0x01UL   <<  1)   /* NVM Page Buffer Active Loading */
#define NVMCTRL_STATUS_PROGE        (0x01UL   <<  2)   /* Programming Error Status */
#define NVMCTRL_STATUS_LOCKE        (0x01UL   <<  3)   /* Lock Error Status */
#define NVMCTRL_STATUS_NVME         (0x01UL   <<  4)   /* NVM Error */
#define NVMCTRL_STATUS_SB           (0x01UL   <<  8)   /* Security Bit Status */


/* Peripheral Memory Map */
/* ---- SAMC21 -------------------------------------------------------------------*/
#if defined ATSAMC_256 || defined ATSAMC_128 || defined ATSAMC_64 || defined ATSAMC_32
  #define PAC_BASE             0x40000000
  #define NVMCTRL_BASE         0x41004000        /* SAML21                     */
#endif

#if defined ATSAMC_256
  #define FLASH_SIZE           0x40000
#endif

#if defined ATSAMC_128
  #define FLASH_SIZE           0x20000
#endif

#if defined ATSAMC_64
  #define FLASH_SIZE           0x10000
#endif

#if defined ATSAMC_32
  #define FLASH_SIZE           0x08000
#endif


#define PAC            ((      PAC_TypeDef *)   PAC_BASE)
#define NVMCTRL        ((  NVMCTRL_TypeDef *)   NVMCTRL_BASE)

#define FLASH_PAGE_SIZE         64                          /* Page size is 64 Byte for all devices */
#define FLASH_REGION_SIZE      (FLASH_SIZE / 16)            /* Flash consists of 16 regions */
#define FLASH_ROW_SIZE         (FLASH_PAGE_SIZE * 4)        /* row = 4 pages */

unsigned long base_adr;        /* Base Address  */


/*
 *  Initialize Flash Programming Functions
 *    Parameter:      adr:  Device Base Address
 *                    clk:  Clock Frequency (Hz)
 *                    fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */

int Init (unsigned long adr, unsigned long clk, unsigned long fnc) {

  /* disable Watchdog */
/*
   --> add code to disable WDT
 */

  /* enable 8 MHz internal Oscillator */
/*
  PAC->WRCTRL = (      );             // disable SYSCTRL Write Protection
   --> add code to use OSC8M as core clock
 */


  /* configure Flash access */
  PAC->WRCTRL = (( 1ul << 16) |       /* disable NVMCTRL Write Protection */
                 (34ul <<  0) );
  NVMCTRL->CTRLB = (( 1ul << 18) |    /* cache disabled */
                    ( 1ul <<  7) |    /* manual write */
                    (15ul <<  1)  );  /* read wait states */

  /* store Flash Start address */
  base_adr = adr;

  return (0);
}


/*
 *  De-Initialize Flash Programming Functions
 *    Parameter:      fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */

int UnInit (unsigned long fnc) {

  return (0);
}


/*
 *  Erase Sector in Flash Memory
 *    Parameter:      adr:  Sector Address
 *    Return Value:   0 - OK,  1 - Failed
 */
#ifdef FLASH_MEM
int EraseSector (unsigned long adr) {
  u32           region_adr;
  u32           row_adr;

  /* instead of a sector we delete all rows in a region
     region is the smallest part which is write protected */

  region_adr = (adr & (FLASH_SIZE - 1)) & ~(FLASH_REGION_SIZE - 1);

  /* unlock region containing given page command */
  NVMCTRL->ADDR  = region_adr >> 1;
  NVMCTRL->CTRLA = NVMCTRL_CTRLA_CMDEX_KEY | NVMCTRL_CTRLA_CMD_UR;
  while (!(NVMCTRL->INTFLAG & NVMCTRL_INTFLAG_READY));

  /* erase all rows in the given region */
  for (row_adr = region_adr;  row_adr < (region_adr + FLASH_REGION_SIZE); row_adr += FLASH_ROW_SIZE) {
    /* Erase row command */
    NVMCTRL->ADDR  = row_adr >> 1;
    NVMCTRL->CTRLA = NVMCTRL_CTRLA_CMDEX_KEY | NVMCTRL_CTRLA_CMD_ER;
    while (!(NVMCTRL->INTFLAG & NVMCTRL_INTFLAG_READY));

    /* check for errors */
    if (NVMCTRL->INTFLAG & NVMCTRL_INTFLAG_ERROR)
      return (1);
  }

  return (0);
}
#endif

#ifdef FLASH_EEPROM
int EraseSector (unsigned long adr) {
  u32           row_adr;

  /* we delete one row */

  row_adr = adr;

  /* Erase row command */
  NVMCTRL->ADDR  = row_adr >> 1;
  NVMCTRL->CTRLA = NVMCTRL_CTRLA_CMDEX_KEY | NVMCTRL_CTRLA_CMD_RWWEEER;
  while (!(NVMCTRL->INTFLAG & NVMCTRL_INTFLAG_READY));

  /* check for errors */
  if (NVMCTRL->INTFLAG & NVMCTRL_INTFLAG_ERROR)
    return (1);

  return (0);
}
#endif

/*
 *  Program Page in Flash Memory
 *    Parameter:      adr:  Page Start Address
 *                    sz:   Page Size
 *                    buf:  Page Data
 *    Return Value:   0 - OK,  1 - Failed
 */
#ifdef FLASH_MEM
/* currently we rwite up to 4 pages at a time
   see page size in FlashDev.c                 */
int ProgramPage (unsigned long adr, unsigned long sz, unsigned char *buf) {
  u32          *Flash;
  u32           page_sz;
  u32           page_adr;

  /* adjust size to words */
  sz = (sz + 3) & ~3;

  /* set the initial page address */
  page_adr = adr;

  /* Clear page buffer; it is also cleared automatically  after page write */
  NVMCTRL->CTRLA = NVMCTRL_CTRLA_CMDEX_KEY | NVMCTRL_CTRLA_CMD_PBC;
  while (!(NVMCTRL->INTFLAG & NVMCTRL_INTFLAG_READY));

  while (sz) {
    /* set write pointer to Flash address */
    Flash = (unsigned long *)page_adr;

    /* set the page size we want to write */
    page_sz = (sz > FLASH_PAGE_SIZE) ? FLASH_PAGE_SIZE : sz;

    /* copy data to page buffer */
    while (page_sz) {
      *Flash++ = *((unsigned long *)buf);
      sz      -= 4;
      buf     += 4;
      page_sz -= 4;
    }

    /* increase page address */
    page_adr = page_adr + FLASH_PAGE_SIZE;

    /* start programming command */
    NVMCTRL->CTRLA = NVMCTRL_CTRLA_CMDEX_KEY | NVMCTRL_CTRLA_CMD_WP;
    while (!(NVMCTRL->INTFLAG & NVMCTRL_INTFLAG_READY));

    /* check for errors */
    if (NVMCTRL->INTFLAG & NVMCTRL_INTFLAG_ERROR)
      return (1);
  }

  return (0);
}
#endif

#ifdef FLASH_EEPROM
int ProgramPage (unsigned long adr, unsigned long sz, unsigned char *buf) {
  u32          *Flash;

  /* Clear Page Buffer */
  NVMCTRL->CTRLA = NVMCTRL_CTRLA_CMDEX_KEY | NVMCTRL_CTRLA_CMD_PBC;
  while (!(NVMCTRL->INTFLAG & NVMCTRL_INTFLAG_READY));

  /* set write pointer to Flash address */
  Flash = (unsigned long *)adr;

  /* copy data to write buffer (boundry are words) */
  for (sz = (sz + 3) & ~3; sz; sz -= 4, buf += 4) {
    *Flash++ = *((unsigned long *)buf);
  }

  /* start programming command */
  NVMCTRL->CTRLA = NVMCTRL_CTRLA_CMDEX_KEY | NVMCTRL_CTRLA_CMD_RWWEEWP;
  while (!(NVMCTRL->INTFLAG & NVMCTRL_INTFLAG_READY));

  /* check for errors */
  if (NVMCTRL->INTFLAG & NVMCTRL_INTFLAG_ERROR)
    return (1);

  return (0);
}
#endif
