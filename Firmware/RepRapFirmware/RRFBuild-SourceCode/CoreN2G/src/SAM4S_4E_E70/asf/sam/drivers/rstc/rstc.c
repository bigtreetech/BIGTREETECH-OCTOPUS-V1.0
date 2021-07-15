/**
 * \file
 *
 * \brief SAM Reset Controller (RSTC) driver.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
 
#include "rstc.h"

/// @cond
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

#define RSTC_KEY  0xA5000000

/**
 * \brief Set the external reset length.
 *
 * \param[in,out] p_rstc Module hardware register base address pointer
 * \param[in] ul_length The length of external reset
 */
void rstc_set_external_reset(
		Rstc *p_rstc,
		const uint32_t ul_length)
{
	/* Validate the parameters. */
	Assert(p_rstc);
	
	uint32_t mode = p_rstc->RSTC_MR;

	mode &= ~(RSTC_MR_ERSTL_Msk | RSTC_MR_KEY_Msk);
	mode |= (RSTC_MR_ERSTL(ul_length) | RSTC_KEY);

	p_rstc->RSTC_MR = mode;
}

/**
 * \brief Enable User Reset.
 *
 * \param[in,out] p_rstc Module hardware register base address pointer
 */
void rstc_enable_user_reset(
		Rstc *p_rstc)
{
	/* Validate the parameters. */
	Assert(p_rstc);
	
	uint32_t mode = p_rstc->RSTC_MR;

	mode &= ~RSTC_MR_KEY_Msk;
	mode |= (RSTC_MR_URSTEN | RSTC_KEY);

	p_rstc->RSTC_MR = mode;
}

/**
 * \brief Disable User Reset.
 *
 * \param[in,out] p_rstc Module hardware register base address pointer
 */
void rstc_disable_user_reset(
		Rstc *p_rstc)
{
	/* Validate the parameters. */
	Assert(p_rstc);
	
	uint32_t mode = p_rstc->RSTC_MR;

	mode &= ~(RSTC_MR_URSTEN | RSTC_MR_KEY_Msk);
	mode |= RSTC_KEY;

	p_rstc->RSTC_MR = mode;
}

/**
 * \brief Enable the User Reset interrupt.
 *
 * \param[in,out] p_rstc Module hardware register base address pointer
 */
void rstc_enable_user_reset_interrupt(
		Rstc *p_rstc)
{
	/* Validate the parameters. */
	Assert(p_rstc);
	
	uint32_t mode = p_rstc->RSTC_MR;

	mode &= ~RSTC_MR_KEY_Msk;
	mode |= (RSTC_MR_URSTIEN | RSTC_KEY);

	p_rstc->RSTC_MR = mode;
}

/**
 * \brief Disable the User Reset interrupt.
 *
 * \param[in,out] p_rstc Module hardware register base address pointer
 */
void rstc_disable_user_reset_interrupt(
		Rstc *p_rstc)
{
	/* Validate the parameters. */
	Assert(p_rstc);
	
	uint32_t mode = p_rstc->RSTC_MR;

	mode &= ~(RSTC_MR_URSTIEN | RSTC_MR_KEY_Msk);
	mode |= RSTC_KEY;

	p_rstc->RSTC_MR = mode;
}

/**
 * \brief Perform a Software Reset.
 *
 * \param[out] p_rstc Module hardware register base address pointer
 */
void rstc_start_software_reset(
		Rstc *p_rstc)
{
#if (SAMV71 || SAMV70 || SAMS70 || SAME70)
	p_rstc->RSTC_CR = RSTC_KEY | RSTC_CR_PROCRST;
#else
	p_rstc->RSTC_CR = RSTC_KEY | RSTC_CR_PROCRST | RSTC_CR_PERRST;
#endif
}

/**
 * \brief Asserts the NRST pin for external resets.
 *
 * \param[out] p_rstc Module hardware register base address pointer
 */
void rstc_reset_extern(
		Rstc *p_rstc)
{
	p_rstc->RSTC_CR = RSTC_KEY | RSTC_CR_EXTRST;
}

/**
 * \brief Get the RSTC status.
 *
 * \param[in] p_rstc Module hardware register base address pointer
 *
 * \return RSTC status.
 */
uint32_t rstc_get_status(
		Rstc *p_rstc)
{
	return p_rstc->RSTC_SR;
}

/**
 * \brief Get the reset cause.
 *
 * \param[in] p_rstc Module hardware register base address pointer
 *
 * \return The last reset cause.
 */
uint32_t rstc_get_reset_cause(
		Rstc *p_rstc)
{
	return (p_rstc->RSTC_SR & RSTC_SR_RSTTYP_Msk);
}

/// @cond
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
