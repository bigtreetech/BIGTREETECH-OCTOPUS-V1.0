/*
 * Flash.h
 *
 *  Created on: 8 Aug 2019
 *      Author: David
 */

#ifndef SRC_FLASH_H_
#define SRC_FLASH_H_

#include <CoreIO.h>

namespace Flash
{
	bool Init() noexcept;
	bool Unlock(uint32_t start, uint32_t length) noexcept;
	bool Lock(uint32_t start, uint32_t length) noexcept;
	bool Write(uint32_t start, uint32_t length, const uint32_t *data) noexcept;
#if SAM4S || SAM4E || SAME70
	bool EraseSector(uint32_t) noexcept;
#else
	bool Erase(uint32_t start, uint32_t length) noexcept;
#endif

#if SAMC21
	bool RwwErase(uint32_t start, uint32_t length) noexcept;
	bool RwwWrite(uint32_t start, uint32_t length, const uint8_t *data) noexcept;
#elif SAM4S || SAM4E || SAME70
	bool ReadUserSignature(uint32_t *p_data, uint32_t ul_size) noexcept;
	bool WriteUserSignature(const uint32_t *p_buffer) noexcept;
	bool EraseUserSignature() noexcept;
	bool ReadUniqueId(uint32_t* pul_data) noexcept;
	int IsGpNvmSet(uint32_t gpnvm) noexcept;
	uint32_t ReadGpNvmBits() noexcept;
	bool ClearGpNvm(uint32_t gpnvm) noexcept;
#endif

	uint32_t GetPageSize() noexcept;
	uint32_t GetLockRegionSize() noexcept;
	uint32_t GetEraseRegionSize() noexcept;
	uint32_t GetFlashSize() noexcept;
}

extern "C" uint32_t GetFlashSize_C() noexcept;

#endif /* SRC_FLASH_H_ */
