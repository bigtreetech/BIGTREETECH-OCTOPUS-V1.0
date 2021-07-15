/*
 * Cache.cpp
 *
 *  Created on: 22 Nov 2019
 *      Author: David
 */

#include "Cache.h"

#ifdef RTOS
# include <RTOSIface/RTOSIface.h>
#endif

#if SAM4E || SAME70 || SAME5x

#if SAME70
# include <core_cm7.h>

#define USE_MPU		1

extern uint32_t _nocache_ram_start;
extern uint32_t _nocache_ram_end;

# if USE_MPU
#  include <mpu_armv7.h>

// Macro ARM_MPU_RASR_EX is incorrectly defined in CMSIS 5.4.0, see https://github.com/ARM-software/CMSIS_5/releases. Redefine it here.

#  undef ARM_MPU_RASR_EX

/**
* MPU Region Attribute and Size Register Value
*
* \param DisableExec       Instruction access disable bit, 1= disable instruction fetches.
* \param AccessPermission  Data access permissions, allows you to configure read/write access for User and Privileged mode.
* \param AccessAttributes  Memory access attribution, see \ref ARM_MPU_ACCESS_.
* \param SubRegionDisable  Sub-region disable field.
* \param Size              Region size of the region to be configured, for example 4K, 8K.
*/
#  define ARM_MPU_RASR_EX(DisableExec, AccessPermission, AccessAttributes, SubRegionDisable, Size)    \
  ((((DisableExec)      << MPU_RASR_XN_Pos)   & MPU_RASR_XN_Msk)                                  | \
   (((AccessPermission) << MPU_RASR_AP_Pos)   & MPU_RASR_AP_Msk)                                  | \
   (((AccessAttributes) & (MPU_RASR_TEX_Msk | MPU_RASR_S_Msk | MPU_RASR_C_Msk | MPU_RASR_B_Msk))) | \
   (((SubRegionDisable) << MPU_RASR_SRD_Pos)  & MPU_RASR_SRD_Msk)                                 | \
   (((Size)             << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)                                | \
   (((MPU_RASR_ENABLE_Msk))))

# endif

#else

// SAM4E and SAME5x use fairly similar cache controllers

const unsigned int CacheWays = 4;
const uint32_t CacheLineSize = 16;							// each cache line is 16 bytes long on both SAME5x and SAM4E
const unsigned int CacheLineShift = 4; 						// how many bits we shift an address right to get the cache line number
static_assert(CacheLineSize == 1u << CacheLineShift);

# if SAME5x
const uint32_t CacheLinesPerWay = 64;
static_assert(CacheWays * CacheLinesPerWay * CacheLineSize == 4096);	// cache size is 4K
# elif SAM4E
const uint32_t CacheLinesPerWay = 32;
static_assert(CacheWays * CacheLinesPerWay * CacheLineSize == 2048);	// cache size is 2K
# endif

// Check whether the cache is enabled
static inline bool is_cache_enabled() noexcept
{
#if SAME5x
	return CMCC->SR.bit.CSTS;
#elif SAM4E
	return (CMCC->CMCC_SR & CMCC_SR_CSTS) != 0;
#endif
}

// Disable the cache
static inline void cache_disable() noexcept
{
	while (is_cache_enabled())
	{
#if SAME5x
		CMCC->CTRL.reg = 0;
#elif SAM4E
		CMCC->CMCC_CTRL = 0;
#endif
		__ISB();
#if !(SAME5x && CACHE_INSTRUCTIONS_ONLY)
		__DSB();
#endif
	}
}

// Enable the cache. If this is called other than from an invalidate operation, the cache must be invalidated first.
static inline void cache_enable() noexcept
{
#if SAME5x
# if CACHE_INSTRUCTIONS_ONLY
	CMCC->CFG.bit.DCDIS = 1;
# endif
	CMCC->CTRL.reg = CMCC_CTRL_CEN;
#elif SAM4E
	CMCC->CMCC_CTRL = CMCC_CTRL_CEN;
#endif
	__ISB();
#if !(SAME5x && CACHE_INSTRUCTIONS_ONLY)
	__DSB();
#endif
}

// Invalidate the whole cache. Cache must be disabled first.
static inline void cache_invalidate_all() noexcept
{
#if SAME5x
	CMCC->MAINT0.reg = CMCC_MAINT0_INVALL;
#elif SAM4E
	CMCC->CMCC_MAINT0 = CMCC_MAINT0_INVALL;
#endif
	__ISB();
#if !(SAME5x && CACHE_INSTRUCTIONS_ONLY)
	__DSB();
#endif
}

#if !(SAME5x && CACHE_INSTRUCTIONS_ONLY)

// Invalidate a region
// Due to the time this can take, above a certain size it is quicker to invalidate the whole cache.
// DMA receive buffer sizes we use commonly:
//	TMC2660 driver: 4
//	TMC2209 driver: 20
//	ADC on SAME5x: 32
//	SBC header: 16
//	SBC reply: 4
//	SBC data: up to 8Kb
//	WiFi header: 12
//	WiFi data: up to 2Kb
//	GMAC Tx or Rx descriptor on SAME5x: 8
//	GMAC data: up to about 1500
//	CAN buffers on SAME5x: 72 (8-byte aligned, so always fits in 5 cache lines)
// All of the short buffers fit within 5 cache lines
constexpr uint32_t MaxSelectiveInvalidateCacheLines = 6;

static inline void cache_invalidate_region(const volatile void *start, size_t length) noexcept
{
	if (length != 0 && is_cache_enabled())										// the following won't work if the length is zero
	{
		// In non-RTOS builds, just invalidate the whole cache always
#ifdef RTOS
		const uint32_t startAddr = reinterpret_cast<uint32_t>(start);			// convert start address to integer
		length += startAddr & (CacheLineSize - 1);								// round up size to start of the first cache line
		uint32_t numLines = (length + (CacheLineSize - 1)) >> CacheLineShift;	// get the number of cache lines to be invalidated
		if (numLines > MaxSelectiveInvalidateCacheLines)						// if more than a small part the cache needs to be invalidated, invalidate the whole cache
#endif
		{
			const irqflags_t flags = IrqSave();
			cache_disable();
			cache_invalidate_all();
			cache_enable();
			IrqRestore(flags);
		}
#ifdef RTOS
		else
		{
			// Unfortunately we have to disable the cache to invalidate cache lines.
			// We must do no data writes while the cache is disabled, or we might subsequently read stale data. Therefore interrupts must be disabled.
			uint32_t startLine = startAddr >> CacheLineShift;					// this will have extraneous bits set, but CMCC_MAINT1_INDEX will mask those off
			while (numLines != 0)
			{
				// Invalidate this cache line in all 4 ways
				const irqflags_t flags = IrqSave();
				cache_disable();
# if SAME5x
				CMCC->MAINT1.reg = CMCC_MAINT1_WAY(0) | CMCC_MAINT1_INDEX(startLine);
				CMCC->MAINT1.reg = CMCC_MAINT1_WAY(1) | CMCC_MAINT1_INDEX(startLine);
				CMCC->MAINT1.reg = CMCC_MAINT1_WAY(2) | CMCC_MAINT1_INDEX(startLine);
				CMCC->MAINT1.reg = CMCC_MAINT1_WAY(3) | CMCC_MAINT1_INDEX(startLine);
# elif SAM4E
				CMCC->CMCC_MAINT1 = CMCC_MAINT1_WAY_WAY0 | CMCC_MAINT1_INDEX(startLine);
				CMCC->CMCC_MAINT1 = CMCC_MAINT1_WAY_WAY1 | CMCC_MAINT1_INDEX(startLine);
				CMCC->CMCC_MAINT1 = CMCC_MAINT1_WAY_WAY2 | CMCC_MAINT1_INDEX(startLine);
				CMCC->CMCC_MAINT1 = CMCC_MAINT1_WAY_WAY3 | CMCC_MAINT1_INDEX(startLine);
# endif
				cache_enable();
				IrqRestore(flags);

				++startLine;
				--numLines;
			}
		}
#endif
	}
}

#endif

#endif

void Cache::Init() noexcept
{

#if SAME70 && USE_MPU

# if 0
// For debugging
#  define CACHE_MODE	ARM_MPU_CACHEP_WT_NWA
# else
// Normal operation
#  define CACHE_MODE	ARM_MPU_CACHEP_WB_WRA
# endif

	// Set up the MPU so that we can have a non-cacheable RAM region, and so that we can trap accesses to non-existent memory
	// Where regions overlap, the region with the highest region number takes priority
	constexpr ARM_MPU_Region_t regionTable[] =
	{
		// Flash memory: read-only, execute allowed, cacheable
		{
			ARM_MPU_RBAR(0, IFLASH_ADDR),
			ARM_MPU_RASR_EX(0u, ARM_MPU_AP_RO, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_WB_WRA, ARM_MPU_CACHEP_WB_WRA, 0u), 0u, ARM_MPU_REGION_SIZE_1MB)
		},
		// First 512b of the flash memory is also the flash write page buffer, which we need to write to when writing the user page
		{
			ARM_MPU_RBAR(1, IFLASH_ADDR),
			ARM_MPU_RASR_EX(0u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_WT_NWA, ARM_MPU_CACHEP_WT_NWA, 0u), 0u, ARM_MPU_REGION_SIZE_512B)
		},
		// First 256kb RAM, read-write, cacheable, execute disabled (parts of this are overridden later)
		{
			ARM_MPU_RBAR(2, IRAM_ADDR),
			ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(CACHE_MODE, CACHE_MODE, 0u), 0u, ARM_MPU_REGION_SIZE_256KB)
		},
		// First 64kb RAM, read-write, shared, execute disabled
		{
			ARM_MPU_RBAR(3, IRAM_ADDR),
			ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_NOCACHE, ARM_MPU_CACHEP_NOCACHE, 1u), 0u, ARM_MPU_REGION_SIZE_64KB)
		},
		// Next 32kb RAM, read-write, shared, execute disabled
		{
			ARM_MPU_RBAR(4, IRAM_ADDR + 0x00010000),
			ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_NOCACHE, ARM_MPU_CACHEP_NOCACHE, 1u), 0u, ARM_MPU_REGION_SIZE_32KB)
		},
		// RAMFUNC memory. Read-only (the code has already been written to it), execution allowed. The initialised data memory follows, so it must be RW.
		// 256 bytes is enough at present (check the linker memory map if adding more RAMFUNCs).
		{
			ARM_MPU_RBAR(5, IRAM_ADDR + 0x00018000),
			ARM_MPU_RASR_EX(0u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(CACHE_MODE, CACHE_MODE, 0u), 0u, ARM_MPU_REGION_SIZE_256B)
		},
		// Final 128kb RAM, read-write, cacheable, execute disabled
		{
			ARM_MPU_RBAR(6, IRAM_ADDR + 0x00040000),
			ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(CACHE_MODE, CACHE_MODE, 0u), 0u, ARM_MPU_REGION_SIZE_128KB)
		},
		// Peripherals
		{
			ARM_MPU_RBAR(7, 0x40000000),
			ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_DEVICE(1u), 0u, ARM_MPU_REGION_SIZE_16MB)
		},
		// USBHS
		{
			ARM_MPU_RBAR(8, 0xA0100000),
			ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_DEVICE(1u), 0u, ARM_MPU_REGION_SIZE_1MB)
		},
		// ROM
		{
			ARM_MPU_RBAR(9, IROM_ADDR),
			ARM_MPU_RASR_EX(0u, ARM_MPU_AP_RO, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_WT_NWA, ARM_MPU_CACHEP_WT_NWA, 0u), 0u, ARM_MPU_REGION_SIZE_4MB)
		},
		// ARM Private Peripheral Bus
		{
			ARM_MPU_RBAR(10, 0xE0000000),
			ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_ORDERED, 0u, ARM_MPU_REGION_SIZE_1MB)
		}
	};

	static_assert(ARRAY_SIZE(regionTable) <= 16);		// SAME70 supports 16 regions

	// Ensure MPU is disabled
	ARM_MPU_Disable();

	// Clear all regions
	const uint32_t numRegions = (MPU->TYPE & MPU_TYPE_DREGION_Msk) >> MPU_TYPE_DREGION_Pos;
	for (unsigned int region = 0; region < numRegions; ++region)
	{
		ARM_MPU_ClrRegion(region);
	}

	// Load regions from our table
	ARM_MPU_Load(regionTable, ARRAY_SIZE(regionTable));

	// Enable the MPU, disabling the default map but allowing exception handlers to use it
	ARM_MPU_Enable(0x01);
#elif SAME5x
	CMCC->MCFG.reg = CMCC_MCFG_MODE_DHIT_COUNT;		// data hit mode
	CMCC->MEN.bit.MENABLE = 1;
#elif SAM4E
	CMCC->CMCC_MCFG = 1;							// instruction hit mode
	CMCC->CMCC_MEN |= CMCC_MEN_MENABLE;
#endif
}

void Cache::Enable() noexcept
{
#if SAME70
	if ((SCB->CCR & SCB_CCR_IC_Msk) == 0)			// if instruction cache is not enabled
	{
		SCB_EnableICache();
	}

	if ((SCB->CCR & SCB_CCR_DC_Msk) == 0)			// if data cache is not enabled
	{
		SCB_EnableDCache();
	}
#else
	const irqflags_t flags = IrqSave();
	if (!is_cache_enabled())
	{
		cache_invalidate_all();
		cache_enable();
	}
	IrqRestore(flags);
#endif
}

// Disable the cache, returning true if it was enabled
bool Cache::Disable() noexcept
{
#if SAME70
	if ((SCB->CCR & SCB_CCR_IC_Msk) != 0)			// if instruction cache is enabled
	{
		SCB_DisableICache();
	}

	const bool wasEnabled = (SCB->CCR & SCB_CCR_DC_Msk) != 0;
	if (wasEnabled)									// if data cache is enabled
	{
		// Warning: this code is fragile! There must be no memory writes while flushing the data cache, hence we must disable interrupts.
		const irqflags_t flags = IrqSave();
		SCB_DisableDCache();						// this cleans it as well as disabling it
		IrqRestore(flags);
	}
#else
	const bool wasEnabled = is_cache_enabled();
	cache_disable();
#endif
	return wasEnabled;
}

#if SAME70

extern "C" [[noreturn]] void vAssertCalled(uint32_t line, const char *file) noexcept;

void Cache::Flush(const volatile void *start, size_t length) noexcept
{
	if ((SCB->CCR & SCB_CCR_DC_Msk) != 0)			// if data cache is enabled
	{
		// The DMA buffer should be entirely inside the non-cached RAM area
		if ((const char *)start < (const char *)&_nocache_ram_start || (const char *)start + length >= (const char *)&_nocache_ram_end)
		{
			vAssertCalled(__LINE__, __FILE__);
		}
	}
}

#endif

#if !(SAME5x && CACHE_INSTRUCTIONS_ONLY)
void Cache::Invalidate(const volatile void *start, size_t length) noexcept
{
# if SAME70
	if ((SCB->CCR & SCB_CCR_DC_Msk) != 0)			// if data cache is enabled
	{
		// The DMA buffer should be entirely inside the non-cached RAM area
		if ((const char *)start < (const char *)&_nocache_ram_start || (const char *)start + length >= (const char *)&_nocache_ram_end)
		{
			vAssertCalled(__LINE__, __FILE__);
		}
	}
# else
	cache_invalidate_region(start, length);
# endif
}

#endif

#if SAM4E || SAME5x

uint32_t Cache::GetHitCount() noexcept
{
#if SAM4E
	return CMCC->CMCC_MSR;
#elif SAME5x
	return CMCC->MSR.reg;
#endif
}

#endif

#endif	// SAM4E || SAME70 || SAME5x

// Entry points that can be called from ASF C code
void CacheFlushBeforeDMAReceive(const volatile void *start, size_t length) noexcept { Cache::FlushBeforeDMAReceive(start, length); }
void CacheInvalidateAfterDMAReceive(const volatile void *start, size_t length) noexcept { Cache::InvalidateAfterDMAReceive(start, length); }
void CacheFlushBeforeDMASend(const volatile void *start, size_t length) noexcept { Cache::FlushBeforeDMASend(start, length); }

// End
