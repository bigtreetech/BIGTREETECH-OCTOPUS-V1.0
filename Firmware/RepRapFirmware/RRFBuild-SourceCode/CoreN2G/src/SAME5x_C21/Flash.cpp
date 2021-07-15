/*
 * Flash.cpp
 *
 *  Created on: 8 Aug 2019
 *      Author: David
 */

#include "Flash.h"

#include <hal/include/hal_flash.h>

#if SAMC21
constexpr uint32_t NVMCTRL_REGIONS_NUM = 16;						// from hpl_nvmctrl.c
#elif SAME5x
constexpr uint32_t NVMCTRL_REGIONS_NUM = 32;						// from hpl_nvmctrl.c
#endif

namespace Flash
{
	static flash_descriptor flash;
}

bool Flash::Init() noexcept
{
	hri_mclk_set_AHBMASK_NVMCTRL_bit(MCLK);
	return flash_init(&flash, NVMCTRL) == 0;
}

bool Flash::Unlock(uint32_t start, uint32_t length) noexcept
{
	// The flash_unlock command only works if the number of pages passed is exactly 1 lock region. So we need to loop calling it.
	const uint32_t pagesPerRegion = GetFlashSize() / (NVMCTRL_REGIONS_NUM * NVMCTRL_PAGE_SIZE);
	for (uint32_t lengthDone = 0; lengthDone < length; )
	{
		if (flash_unlock(&flash, start, pagesPerRegion) != (int32_t)pagesPerRegion)
		{
			return false;
		}
		start += pagesPerRegion * NVMCTRL_PAGE_SIZE;
		lengthDone += pagesPerRegion * NVMCTRL_PAGE_SIZE;
	}
	return true;
}

// We used to disable interrupts while erasing, however that causes the IAP to fail, probably because delays in handling tick interrupts affect the watchdog
// Programs that call this may need to disable interrupts themselves
bool Flash::Erase(uint32_t start, uint32_t length) noexcept
{
	return flash_erase(&flash, start, length/NVMCTRL_PAGE_SIZE) == 0;
}

bool Flash::Lock(uint32_t start, uint32_t length) noexcept
{
	// The flash_lock command only works if the number of pages passed is exactly 1 lock region. So we need to loop calling it.
	const uint32_t pagesPerRegion = GetFlashSize() / (NVMCTRL_REGIONS_NUM * NVMCTRL_PAGE_SIZE);
	for (uint32_t lengthDone = 0; lengthDone < length; )
	{
		if (flash_lock(&flash, start, pagesPerRegion) != (int32_t)pagesPerRegion)
		{
			return false;
		}
		start += pagesPerRegion * NVMCTRL_PAGE_SIZE;
		lengthDone += pagesPerRegion * NVMCTRL_PAGE_SIZE;
	}
	return true;
}

// We used to disable interrupts while erasing, but that isn't necessary when writing from the IAP in RAM
// Programs that call this may need to disable interrupts themselves
// The memory being written must already have been erased
bool Flash::Write(uint32_t start, uint32_t length, const uint32_t *data) noexcept
{
	return flash_append(&flash, start, (const uint8_t*)data, length) == 0;
}

uint32_t Flash::GetPageSize() noexcept
{
	return NVMCTRL_PAGE_SIZE;
}

uint32_t Flash::GetLockRegionSize() noexcept
{
	return GetFlashSize()/NVMCTRL_REGIONS_NUM;
}

uint32_t Flash::GetEraseRegionSize() noexcept
{
#if SAMC21
	return NVMCTRL_ROW_PAGES * NVMCTRL_PAGE_SIZE;
#elif SAME5x
	return NVMCTRL_BLOCK_SIZE;		// 8Kb on SAMD5x.SAME5x, see SAMD5x/E5x datasheet section 25.6.2
#else
# error Unsupported processor
#endif
}

uint32_t Flash::GetFlashSize() noexcept
{
#if SAMC21
	// We only support the SAMC21 members with 256Kb flash and 32Kb RAM
	return 256 * 1024;
#endif

#if SAME5x
	const uint32_t deviceId = DSU->DID.reg;
	const uint32_t family = deviceId >> 16;
	const uint32_t member = deviceId & 0x000000FF;

	switch (family)
	{
	case 0x6006:	// SAMD51
	case 0x6183:	// SAME53
	case 0x6184:	// SAME54
		if (member <= 8)
		{
			const uint32_t sizeTable[] = { 1024, 512, 1024, 512, 1024, 512, 256, 512, 256 };
			return sizeTable[member] * 1024;
		}
		break;

	case 0x6181:	// SAME51
		if (member <= 6)
		{
			const uint32_t sizeTable[] = { 1024, 512, 512, 256, 1024, 512, 256 };
			return sizeTable[member] * 1024;
		}
		break;

	default:
		break;
	}

	// Unknown device
	while (true) { }
#endif
}

extern "C" uint32_t GetFlashSize_C() noexcept
{
	return Flash::GetFlashSize();
}

#if SAMC21

bool Flash::RwwErase(uint32_t start, uint32_t length) noexcept
{
	return hpl_RwwErase(start, length);
}

bool Flash::RwwWrite(uint32_t start, uint32_t length, const uint8_t *data) noexcept
{
	return hpl_RwwWrite(start, length, data);
}

#endif

// End
