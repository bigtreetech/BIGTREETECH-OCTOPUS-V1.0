/**
 * \file
 *
 * \brief TRNG driver for SAM.
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

/**
 * \defgroup group_sam_drivers_trng TRNG - True Random Number Generator
 *
 * Driver for the TRNG (True Random Number Generator). This driver provides access
 * to the main features of the TRNG controller.
 *
 * \{
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "trng.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \brief Enable TRNG.
 *
 * \param p_trng  Pointer to a TRNG instance.
 *
 */
void trng_enable(Trng *p_trng)
{
	p_trng->TRNG_CR = TRNG_CR_ENABLE | TRNG_CR_KEY_PASSWD;
}

/**
 * \brief Disable TRNG.
 *
 * \param p_trng  Pointer to a TRNG instance.
 *
 */
void trng_disable(Trng *p_trng)
{
	p_trng->TRNG_CR = TRNG_CR_KEY_PASSWD;
}

/**
 * \brief Enable TRNG interrupt.
 *
 * \param p_trng  Pointer to a TRNG instance.
 *
 */
void trng_enable_interrupt(Trng *p_trng)
{
	p_trng->TRNG_IER = TRNG_IER_DATRDY;
}

/**
 * \brief Disable TRNG interrupt.
 *
 * \param p_trng  Pointer to a TRNG instance.
 *
 */
void trng_disable_interrupt(Trng *p_trng)
{
	p_trng->TRNG_IDR = TRNG_IER_DATRDY;
}

/**
 * \brief Get TRNG interrupt mask.
 *
 * \param p_trng  Pointer to a TRNG instance.
 *
 * \retval The interrupt mask value.
 */
uint32_t trng_get_interrupt_mask(Trng *p_trng)
{
	return p_trng->TRNG_IMR;
}

/**
 * \brief Get TRNG interrupt status.
 *
 * \param p_trng  Pointer to a TRNG instance.
 *
 * \retval The interrupt status value.
 */
uint32_t trng_get_interrupt_status(Trng *p_trng)
{
	return p_trng->TRNG_ISR;
}

/**
 * \brief Read TRNG output data.
 *
 * \param p_trng  Pointer to a TRNG instance.
 *
 * \retval The output data value.
 */
uint32_t trng_read_output_data(Trng *p_trng)
{
	return p_trng->TRNG_ODATA;
}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \}
 */
