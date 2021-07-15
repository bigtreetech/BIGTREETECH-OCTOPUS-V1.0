/**
 * \file
 *
 * \brief Reinforced Safety Watchdog Timer (RSWDT) driver for SAM.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

#include "rswdt.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \defgroup sam_drivers_rswdt_group Reinforced Safety Watchdog Timer (RSWDT)
 *
 * Driver for the RSWDT (Reinforced Safety Watchdog Timer). This driver provides access to the main
 * features of the RSWDT controller.
 * The Reinforced Safety Watchdog Timer can be used to prevent system lock-up if the software
 * becomes trapped in a deadlock. It features a 12-bit down counter that allows
 * a watchdog period of up to 16 seconds (slow clock at 32.768 kHz). It can
 * generate a general reset or a processor reset only. In addition, it can be
 * stopped while the processor is in debug mode or idle mode.
 *
 * @{
 */

#define RSWDT_KEY_PASSWORD  0xC4000000
#define RSWDT_SLCK_DIV      128
#define RSWDT_MAX_VALUE     4095

/**
 * \brief Get counter value or permitted range value of reinforced safety watchdog timer from the
 * desired timeout period (in us).
 *
 * \note The value returned by this function can be used by rswdt_init() if it is
 * not RSWDT_INVALID_ARGUMENT.
 *
 * \param ul_us The desired timeout period (in us).
 * \param ul_sclk The slow clock on board (in Hz).
 *
 * \return If the desired period is beyond the reinforced safety watchdog period, this function
 * returns RSWDT_INVALID_ARGUMENT. Otherwise it returns valid value.
 */
uint32_t rswdt_get_timeout_value(uint32_t ul_us, uint32_t ul_sclk)
{
	uint32_t max, min;

	min = RSWDT_SLCK_DIV * 1000000 / ul_sclk;
	max = min * RSWDT_MAX_VALUE;

	if ((ul_us < min) || (ul_us > max)) {
		return RSWDT_INVALID_ARGUMENT;
	}

	return RSWDT_MR_WDV(ul_us / min);
}

/**
 * \brief Initialize reinforced safety watchdog timer with the given mode.
 *
 * \param p_rswdt Pointer to a RSWDT instance.
 * \param ul_mode Bitmask of reinforced safety watchdog timer mode.
 * \param us_counter The value loaded in the 12-bit Reinforced Safety Watchdog Counter.
 * \param us_delta The permitted range for reloading the Reinforced Safety Watchdog Timer.
 */
void rswdt_init(Rswdt *p_rswdt, uint32_t ul_mode, uint16_t us_counter,
		uint16_t us_delta)
{
#if (SAMV71 || SAMV70 || SAME70 || SAMS70)
	p_rswdt->RSWDT_MR = ul_mode |
			RSWDT_MR_WDV(us_counter);
#else
	p_rswdt->RSWDT_MR = ul_mode |
			RSWDT_MR_WDV(us_counter) | RSWDT_MR_WDD(us_delta);
#endif
}

/**
 * \brief Disable the reinforced safety watchdog timer.
 */
void rswdt_disable(Rswdt *p_rswdt)
{
	p_rswdt->RSWDT_MR = RSWDT_MR_WDDIS;
}

/**
 * \brief Restart the reinforced safety watchdog timer.
 */
void rswdt_restart(Rswdt *p_rswdt)
{
	if (p_rswdt == RSWDT) {
		p_rswdt->RSWDT_CR = RSWDT_KEY_PASSWORD | RSWDT_CR_WDRSTT;
	}
}

/**
 * \brief Check the reinforced safety watchdog timer status.
 *
 * \return Bitmask of reinforced safety watchdog timer status.
 */
uint32_t rswdt_get_status(Rswdt *p_rswdt)
{
	return p_rswdt->RSWDT_SR;
}

/**
 * \brief Get the timeout period of the Reinforced Safety WatchDog Timer in microseconds.
 *
 * \param p_rswdt Pointer to a RSWDT instance.
 * \param ul_sclk The slow clock frequency (in Hz).
 *
 * \return The timeout period in microseconds.
 */
uint32_t rswdt_get_us_timeout_period(Rswdt *p_rswdt, uint32_t ul_sclk)
{
	return RSWDT_MR_WDV(p_rswdt->RSWDT_MR) * RSWDT_SLCK_DIV / ul_sclk * 1000000;
}

//@}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
