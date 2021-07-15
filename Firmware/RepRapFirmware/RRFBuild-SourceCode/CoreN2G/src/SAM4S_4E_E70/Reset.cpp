/*
  Copyright (c) 2012 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "CoreIO.h"
#include "Reset.h"

#include "wdt/wdt.h"
#include "rstc/rstc.h"
#include "Flash.h"

#ifdef __cplusplus
extern "C" {
#endif

// Switch into boot mode and reset
[[noreturn]] void EraseAndReset()
{
	IrqDisable();

#if SAM4S
# define IFLASH_ADDR				IFLASH0_ADDR
# define IFLASH_PAGE_SIZE			IFLASH0_PAGE_SIZE
# define IFLASH_NB_OF_PAGES			(IFLASH0_SIZE / IFLASH_PAGE_SIZE)
#endif

#if SAM3XA
# define IFLASH_ADDR				IFLASH0_ADDR
# define IFLASH_PAGE_SIZE			IFLASH0_PAGE_SIZE
# define IFLASH_NB_OF_PAGES			((IFLASH1_ADDR + IFLASH1_SIZE - IFLASH_ADDR) / IFLASH_PAGE_SIZE)
#endif

    for(size_t i = 0; i <= IFLASH_NB_OF_PAGES; i++)
    {
    	wdt_restart(WDT);
        size_t pageStartAddr = IFLASH_ADDR + i * IFLASH_PAGE_SIZE;
        Flash::Unlock(pageStartAddr, pageStartAddr + IFLASH_PAGE_SIZE - 1);
    }

    Flash::ClearGpNvm(1);			// tell the system to boot from ROM next time
	rstc_start_software_reset(RSTC);
	for(;;) {}
}

#ifdef __cplusplus
}
#endif
