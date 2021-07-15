/**
 * \file
 *
 * \brief General Purpose Backup Registers (GPBR) driver for SAM.
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

#ifndef GPBR_H_INCLUDED
#define GPBR_H_INCLUDED

#include "compiler.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/** GPBR register number type */
typedef enum gpbr_num_type {
	GPBR0 = 0,
	GPBR1,
	GPBR2,
	GPBR3,
#if !SAM3U	
	GPBR4,
	GPBR5,
	GPBR6,
	GPBR7,
#if (SAM4C || SAM4CP || SAM4CM)
	GPBR8,
	GPBR9,
	GPBR10,
	GPBR11,
	GPBR12,
	GPBR13,
	GPBR14,
	GPBR15,
#endif
#if SAM4E
	GPBR8,
	GPBR9,
	GPBR10,
	GPBR11,
	GPBR12,
	GPBR13,
	GPBR14,
	GPBR15,
	GPBR16,
	GPRB17,
	GPBR18,
	GPBR19,
#endif
#endif
} gpbr_num_t;

uint32_t gpbr_read(gpbr_num_t ul_reg_num);
void gpbr_write(gpbr_num_t ul_reg_num, uint32_t ul_value);

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

#endif /* GPBR_H_INCLUDED */
