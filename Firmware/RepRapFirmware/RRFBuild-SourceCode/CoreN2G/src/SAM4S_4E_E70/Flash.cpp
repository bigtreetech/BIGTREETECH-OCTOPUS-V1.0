/**
 * \file
 *
 * \brief Embedded Flash service for SAM.
 *
 * Copyright (c) 2011-2016 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <Core.h>
#include <Flash.h>
#include <efc/efc.h>
#include <cstring>

/**
 * \defgroup sam_services_flash_efc_group Embedded Flash Service
 *
 * The Embedded Flash service provides functions for internal flash operations.
 *
 * @{
 */

/*! \name Flash erase page num in FARG[1:0]
  \note The erase page commands should be cautiouly used as EPA4/EPA32 will not
  take effect according to errata and EPA8/EPA16 must module 8/16 page addresses.*/
//! @{
typedef enum flash_farg_page_num {
	/* 4 of pages to be erased with EPA command*/
	IFLASH_ERASE_PAGES_4=0,
	/* 8 of pages to be erased with EPA command*/
	IFLASH_ERASE_PAGES_8,
	/* 16 of pages to be erased with EPA command*/
	IFLASH_ERASE_PAGES_16,
	/* 32 of pages to be erased with EPA command*/
	IFLASH_ERASE_PAGES_32,
	/* Parameter is not support */
	IFLASH_ERASE_PAGES_INVALID,
}flash_farg_page_num_t;
//! @}

/* User signature size */
# define FLASH_USER_SIG_SIZE   (512)

#if SAM4S
/* Internal Flash Controller 0. */
# define EFC     EFC0
#if (SAM4SD16 || SAM4SD32)
/* The max GPNVM number. */
# define GPNVM_NUM_MAX        3
#else
/* The max GPNVM number. */
# define GPNVM_NUM_MAX        2
#endif
/* Internal Flash 0 base address. */
# define IFLASH_ADDR     IFLASH0_ADDR
/* Internal flash page size. */
# define IFLASH_PAGE_SIZE     IFLASH0_PAGE_SIZE
/* Internal flash lock region size. */
# define IFLASH_LOCK_REGION_SIZE     IFLASH0_LOCK_REGION_SIZE
#elif (SAM3XA || SAM3U4)
/* Internal Flash Controller 0. */
# define EFC     EFC0
/* The max GPNVM number. */
# define GPNVM_NUM_MAX        3
/* Internal Flash 0 base address. */
# define IFLASH_ADDR     IFLASH0_ADDR
/* Internal flash page size. */
# define IFLASH_PAGE_SIZE     IFLASH0_PAGE_SIZE
/* Internal flash lock region size. */
# define IFLASH_LOCK_REGION_SIZE     IFLASH0_LOCK_REGION_SIZE
#elif (SAM3U)
/* There is no EFC1 for SAM3U except for SAM3U4 */
# undef EFC1
/* Internal Flash Controller 0. */
# define EFC     EFC0
/* The max GPNVM number. */
# define GPNVM_NUM_MAX        2
/* Internal Flash 0 base address. */
# define IFLASH_ADDR     IFLASH0_ADDR
/* Internal flash page size. */
# define IFLASH_PAGE_SIZE     IFLASH0_PAGE_SIZE
/* Internal flash lock region size. */
# define IFLASH_LOCK_REGION_SIZE     IFLASH0_LOCK_REGION_SIZE
#elif (SAM3S8 || SAM3SD8)
/* The max GPNVM number. */
# define GPNVM_NUM_MAX        3
/* Internal flash page size. */
# define IFLASH_PAGE_SIZE     IFLASH0_PAGE_SIZE
/* Internal flash lock region size. */
# define IFLASH_LOCK_REGION_SIZE     IFLASH0_LOCK_REGION_SIZE
#elif (SAM4C32 || SAM4CMP32 || SAM4CMS32)
/* The max GPNVM number SAM4C(M)32. */
# define GPNVM_NUM_MAX        3
#elif (SAMG)
/* The max GPNVM number SAMG. */
# define GPNVM_NUM_MAX        8
#elif (SAMV71 || SAMV70 || SAMS70 || SAME70)
/* The max GPNVM number SAMV/S/E. */
# define GPNVM_NUM_MAX        9
#else
/* The max GPNVM number. */
# define GPNVM_NUM_MAX        2
#endif

#if (SAM4C || SAM4CP || SAM4CM)
#if (SAM4C32 || SAM4CMP32 || SAM4CMS32)
# define EFC     EFC0
/* Internal Flash 0 base address. */
# define IFLASH0_ADDR    IFLASH0_CNC_ADDR
# define IFLASH1_ADDR    IFLASH1_CNC_ADDR
# define IFLASH_ADDR     IFLASH0_ADDR
/* Internal flash page size. */
# define IFLASH_PAGE_SIZE     IFLASH0_PAGE_SIZE
/* Internal flash lock region size. */
# define IFLASH_LOCK_REGION_SIZE     IFLASH0_LOCK_REGION_SIZE
#else
#define IFLASH_ADDR  IFLASH_CNC_ADDR
#endif
#endif

/**
 * \brief Translate the given flash address to page and offset values.
 * \note pus_page and pus_offset must not be null in order to store the
 * corresponding values.
 *
 * \param pp_efc Pointer to an EFC pointer.
 * \param ul_addr Address to translate.
 * \param pus_page The first page accessed.
 * \param pus_offset Byte offset in the first page.
 */
static void translate_address(Efc **pp_efc, uint32_t ul_addr, uint16_t *pus_page, uint16_t *pus_offset) noexcept
{
	Efc *p_efc;
	uint16_t us_page;
	uint16_t us_offset;

#if (SAM3XA || SAM3U4)
	if (ul_addr >= IFLASH1_ADDR) {
		p_efc = EFC1;
		us_page = (ul_addr - IFLASH1_ADDR) / IFLASH1_PAGE_SIZE;
		us_offset = (ul_addr - IFLASH1_ADDR) % IFLASH1_PAGE_SIZE;
	} else {
		p_efc = EFC0;
		us_page = (ul_addr - IFLASH0_ADDR) / IFLASH0_PAGE_SIZE;
		us_offset = (ul_addr - IFLASH0_ADDR) % IFLASH0_PAGE_SIZE;
	}
#elif (SAM4SD16 || SAM4SD32 || SAM4C32 || SAM4CMP32 || SAM4CMS32)
	uint32_t uc_gpnvm2;
	uc_gpnvm2 = flash_is_gpnvm_set(2);
	if (ul_addr >= IFLASH1_ADDR) {
		if(uc_gpnvm2 == FLASH_RC_YES) {
			p_efc = EFC0;
		} else {
			p_efc = EFC1;
		}
		us_page = (ul_addr - IFLASH1_ADDR) / IFLASH1_PAGE_SIZE;
		us_offset = (ul_addr - IFLASH1_ADDR) % IFLASH1_PAGE_SIZE;
	} else {
		if(uc_gpnvm2 == FLASH_RC_YES) {
			p_efc = EFC1;
		} else {
			p_efc = EFC0;
		}
		us_page = (ul_addr - IFLASH0_ADDR) / IFLASH0_PAGE_SIZE;
		us_offset = (ul_addr - IFLASH0_ADDR) % IFLASH0_PAGE_SIZE;
	}
#elif (SAM3S8 || SAM3SD8)
	p_efc = EFC;
	us_page = (ul_addr - IFLASH0_ADDR) / IFLASH0_PAGE_SIZE;
	us_offset = (ul_addr - IFLASH0_ADDR) % IFLASH0_PAGE_SIZE;
#else
	Assert(ul_addr >= IFLASH_ADDR);
	Assert(ul_addr <= (IFLASH_ADDR + IFLASH_SIZE));

	p_efc = EFC;
	us_page = (ul_addr - IFLASH_ADDR) / IFLASH_PAGE_SIZE;
	us_offset = (ul_addr - IFLASH_ADDR) % IFLASH_PAGE_SIZE;
#endif

	/* Store values */
	if (pp_efc) {
		*pp_efc = p_efc;
	}

	if (pus_page) {
		*pus_page = us_page;
	}

	if (pus_offset) {
		*pus_offset = us_offset;
	}
}

/**
 * \brief Compute the address of a flash by the given page and offset.
 *
 * \param p_efc Pointer to an EFC instance.
 * \param us_page Page number.
 * \param us_offset Byte offset inside page.
 * \param pul_addr Computed address (optional).
 */
static uint32_t compute_address(Efc *p_efc, uint16_t us_page) noexcept
{
/* Dual bank flash */
#ifdef EFC1
	/* Compute address */
#if (SAM4SD16 || SAM4SD32 || SAM4C32 || SAM4CMP32 || SAM4CMS32)
	const uint32_t uc_gpnvm2 = flash_is_gpnvm_set(2);
	if (p_efc == EFC0) {
		if(uc_gpnvm2 == FLASH_RC_YES) {
			return IFLASH1_ADDR + us_page * IFLASH_PAGE_SIZE;
		} else {
			return IFLASH0_ADDR + us_page * IFLASH_PAGE_SIZE;
		}
	} else {
		if(uc_gpnvm2 == FLASH_RC_YES) {
			return IFLASH0_ADDR + us_page * IFLASH_PAGE_SIZE;
		} else {
			return IFLASH1_ADDR + us_page * IFLASH_PAGE_SIZE;
		}
	}
#else
	return (p_efc == EFC0) ?
			IFLASH0_ADDR + us_page * IFLASH_PAGE_SIZE :
			IFLASH1_ADDR + us_page * IFLASH_PAGE_SIZE;
#endif
/* One bank flash */
#else
	/* avoid Cppcheck Warning */
	UNUSED(p_efc);
	/* Compute address */
	return IFLASH_ADDR + us_page * IFLASH_PAGE_SIZE;
#endif
}

/**
 * \brief Compute the lock range associated with the given address range.
 *
 * \param ul_start Start address of lock range.
 * \param ul_end End address of lock range.
 * \param pul_actual_start Actual start address of lock range.
 * \param pul_actual_end Actual end address of lock range.
 */
static void compute_lock_range(uint32_t ul_start, uint32_t ul_end, uint32_t *pul_actual_start, uint32_t *pul_actual_end) noexcept
{
	const uint32_t ul_actual_start = ul_start - (ul_start % IFLASH_LOCK_REGION_SIZE);
	const uint32_t ul_actual_end = ul_end - (ul_end % IFLASH_LOCK_REGION_SIZE) + IFLASH_LOCK_REGION_SIZE - 1;

	if (pul_actual_start)
	{
		*pul_actual_start = ul_actual_start;
	}

	if (pul_actual_end)
	{
		*pul_actual_end = ul_actual_end;
	}
}

/**
 * \brief Initialize the flash service.
 *
 * \return true if successful
 */
bool Flash::Init() noexcept
{
	return true;
}

/**
 * \brief Erase the flash sector.
 *
 * \note Erase sector command needs a page number parameter which belongs to the sector to be erased.
 *
 * \param start Flash sector start address.
 *
 * \return 0 if successful; otherwise returns an error code.
 */
bool Flash::EraseSector(uint32_t start) noexcept
{
	Efc *p_efc;
	uint16_t us_page;
	translate_address(&p_efc, start, &us_page, nullptr);

	return efc_perform_command(p_efc, EFC_FCMD_ES, us_page) == 0;
}

/**
 * \brief Write a data buffer on flash.
 *
 * \note This function works in polling mode, and thus only returns when the data has been effectively written.
 * \note For dual bank flash, this function doesn't support cross write from bank 0 to bank 1. In this case, flash_write must be called twice (i.e. for each bank).
 *
 * \param ul_address Write address.
 * \param p_buffer Data buffer.
 * \param ul_size Size of data buffer in bytes.
 * \param ul_erase_flag Flag to set if erase first.
 *
 * \return 0 if successful, otherwise returns an error code.
 */
bool Flash::Write(uint32_t start, uint32_t length, const uint32_t *data) noexcept
{
	// We only support writing whole pages, and the source buffer must be dword aligned
	if ((start % IFLASH_PAGE_SIZE) != 0 || (length % IFLASH_PAGE_SIZE) != 0)
	{
		return false;
	}

	Efc *p_efc;
	uint16_t us_page;
	translate_address(&p_efc, start, &us_page, nullptr);

	/* Write all pages */
	while (length != 0)
	{
		uint32_t ul_page_addr = compute_address(p_efc, us_page);
		memcpyu32(reinterpret_cast<uint32_t*>(ul_page_addr), data, IFLASH_PAGE_SIZE/4);

		if (efc_perform_command(p_efc, EFC_FCMD_WP, us_page) != 0)
		{
			return false;
		}

		/* Progression */
		data += IFLASH_PAGE_SIZE;
		length -= IFLASH_PAGE_SIZE;
		us_page++;
	}

	return true;
}

uint32_t Flash::GetLockRegionSize() noexcept
{
	return IFLASH_LOCK_REGION_SIZE;
}

/**
 * \brief Lock all the regions in the given address range. The actual lock
 * range is reported through two output parameters.
 *
 * \param start Start address of lock range.
 * \param length Length of lock range.
 *
 * \return true if successful
 */
bool Flash::Lock(uint32_t start, uint32_t length) noexcept
{
	uint32_t ul_actual_start, ul_actual_end;

	/* Compute actual lock range and store it */
	compute_lock_range(start, start + length, &ul_actual_start, &ul_actual_end);

	/* Compute page numbers */
	Efc *p_efc;
	uint16_t us_start_page, us_end_page;
	translate_address(&p_efc, ul_actual_start, &us_start_page, 0);
	translate_address(0, ul_actual_end, &us_end_page, 0);

	/* Lock all pages */
	const uint16_t us_num_pages_in_region = IFLASH_LOCK_REGION_SIZE / IFLASH_PAGE_SIZE;
	while (us_start_page < us_end_page)
	{
		if (efc_perform_command(p_efc, EFC_FCMD_SLB, us_start_page) != 0)
		{
			return false;
		}
		us_start_page += us_num_pages_in_region;
	}

	return true;
}

/**
 * \brief Unlock all the regions in the given address range. The actual unlock
 * range is reported through two output parameters.
 *
 * \param ul_start Start address of unlock range.
 * \param ul_end End address of unlock range.
 * \param pul_actual_start Start address of the actual unlock range (optional).
 * \param pul_actual_end End address of the actual unlock range (optional).
 *
 * \return 0 if successful, otherwise returns an error code.
 */
bool Flash::Unlock(uint32_t start, uint32_t length) noexcept
{
	uint32_t ul_actual_start, ul_actual_end;

	/* Compute actual unlock range and store it */
	compute_lock_range(start, start + length, &ul_actual_start, &ul_actual_end);

	/* Compute page numbers */
	Efc *p_efc;
	uint16_t us_start_page, us_end_page;
	translate_address(&p_efc, ul_actual_start, &us_start_page, 0);
	translate_address(0, ul_actual_end, &us_end_page, 0);

	/* Unlock all pages */
	const uint16_t us_num_pages_in_region = IFLASH_LOCK_REGION_SIZE / IFLASH_PAGE_SIZE;
	while (us_start_page < us_end_page)
	{
		if (efc_perform_command(p_efc, EFC_FCMD_CLB, us_start_page) != 0)
		{
			return false;
		}
		us_start_page += us_num_pages_in_region;
	}

	return true;
}

/**
 * \brief Read the flash unique ID.
 *
 * \param pul_data Pointer to a data buffer to store 128-bit unique ID.
 * \param ul_size Data buffer size in DWORD.
 *
 * \return 0 if successful; otherwise returns an error code.
 */
bool Flash::ReadUniqueId(uint32_t* pul_data) noexcept
{
	// dc42 bBug fix: must disable interrupts while executing the EFC read command
	const irqflags_t flags = IrqSave();
	const uint32_t rc = efc_perform_read_sequence(EFC, EFC_FCMD_STUI, EFC_FCMD_SPUI, pul_data, 4);
	IrqRestore(flags);
	return rc == 0;
}

/**
 * \brief Read the flash user signature.
 *
 * \param p_data Pointer to a data buffer to store 512 bytes of user signature.
 * \param ul_size Data buffer size in 32 bit words.
 *
 * \return 0 if successful; otherwise returns an error code.
 */
bool Flash::ReadUserSignature(uint32_t *p_data, uint32_t ul_size) noexcept
{
	if (ul_size > (FLASH_USER_SIG_SIZE / sizeof(uint32_t)))
	{
		/* Only 512 byte to store user signature */
		ul_size = FLASH_USER_SIG_SIZE / sizeof(uint32_t);
	}

	// dc42 bug fix: must disable interrupts while executing the EFC read command
	const irqflags_t flags = IrqSave();
	const uint32_t rc = efc_perform_read_sequence(EFC, EFC_FCMD_STUS, EFC_FCMD_SPUS, p_data, ul_size);
	IrqRestore(flags);
	return rc == 0;
}

/**
 * \brief Write the flash user signature.
 *
 * \param p_data Pointer to a 512-byte 32-bit aligned data buffer to store info for the user signature.
 * \param ul_size Data buffer size in 32 bit words.
 *
 * \return 0 if successful; otherwise returns an error code.
 */
bool Flash::WriteUserSignature(const uint32_t *p_buffer) noexcept
{
	/* Write page buffer.
	* Writing 8-bit and 16-bit data is not allowed and may lead to unpredictable data corruption.
	*/
	memcpyu32((uint32_t *)IFLASH_ADDR, p_buffer, IFLASH_PAGE_SIZE / sizeof(uint32_t));

	/* Send the write signature command */
	return efc_perform_command(EFC, EFC_FCMD_WUS, 0) == 0;
}

/**
 * \brief Erase the flash user signature.
 *
 * \return 0 if successful; otherwise returns an error code.
 */
bool Flash::EraseUserSignature() noexcept
{
	/* Perform the erase user signature command */
	return efc_perform_command(EFC, EFC_FCMD_EUS, 0) == 0;
}

// Read all nine GPNVM bits. Return 0xFFFFFFFF if failed, else the GPNVM bits in bits 0 to 8.
uint32_t Flash::ReadGpNvmBits() noexcept
{
	if (EFC_RC_OK != efc_perform_command(EFC, EFC_FCMD_GGPB, 0))
	{
		return 0xFFFFFFFF;
	}

	return efc_get_result(EFC) & ((1ul << 9) - 1ul);
}

/**
 * \brief Check if the given GPNVM bit is set or not.
 *
 * \param ul_gpnvm GPNVM bit index.
 *
 * \return -1 if command failed, 0 if not not set, 1 if bit set
 */
int Flash::IsGpNvmSet(uint32_t gpnvm) noexcept
{
	if (gpnvm >= GPNVM_NUM_MAX)
	{
		return -1;
	}

	if (efc_perform_command(EFC, EFC_FCMD_GGPB, 0) != EFC_RC_OK)
	{
		return -1;
	}

	const uint32_t ul_gpnvm_bits = efc_get_result(EFC);
	return (int)((ul_gpnvm_bits >> gpnvm) & 1u);
}

/**
 * \brief Clear the given GPNVM bit.
 *
 * \param ul_gpnvm GPNVM bit index.
 *
 * \return true if successful
 */
bool Flash::ClearGpNvm(uint32_t gpnvm) noexcept
{
	if (gpnvm >= GPNVM_NUM_MAX)
	{
		return false;
	}

	if (IsGpNvmSet(gpnvm) == 0)
	{
		return true;
	}

	return efc_perform_command(EFC, EFC_FCMD_CGPB, gpnvm) == EFC_RC_OK;
}

// End
