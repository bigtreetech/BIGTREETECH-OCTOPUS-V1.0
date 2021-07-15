/**
 *
 * \file
 *
 * \brief CMCC software driver for SAM.
 *
 * This file defines a useful set of functions for the CMCC on SAM devices.
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

#include "cmcc.h"

/**
 * \brief Initializes a CMCC configuration structure to defaults.
 *
 *  Initializes a given CMCC configuration structure to a set of
 *  known default values. This function should be called on all new
 *  instances of these configuration structures before being modified by the
 *  user application.
 *
 *  The default configuration is as follows:
 *  - the monitor counter is activated.
 *  - Data hit counter mode.
 *
 *  \param cfg    Configuration structure to initialize to default values.
 */
void cmcc_get_config_defaults(struct cmcc_config *const cfg)
{
	/* Sanity check arguments */
	Assert(cfg);

	/* Default configuration values */
	cfg->cmcc_monitor_enable = true;
	cfg->cmcc_mcfg_mode = CMCC_DHIT_COUNT_MODE;
#if SAMG55
	cfg->cmcc_cfg_cache_size = CMCC_PROG_CSIZE_1KB;
#endif
}

/**
 * \brief Initialize the CMCC module.
 *
 * \param p_cmcc Pointer to an CMCC instance.
 * \param cfg Pointer to CMCC configuration.
 *
 * \retval true if the initialization was successful.
 * \retval false if initialization failed.
 */
bool cmcc_init(Cmcc *const p_cmcc, struct cmcc_config *const cfg)
{
	/* Sanity check arguments */
	Assert(cfg);

	/* Initialize the Cache Controller Monitor if it is enabled */
	if (true == cfg->cmcc_monitor_enable) {
		cmcc_set_config(p_cmcc, cfg);
		cmcc_enable_monitor(p_cmcc);
	}

	return true;
}

/**
 * \brief Enable Cache Controller.
 *
 * \param p_cmcc Pointer to an CMCC instance.
 *
 */
void cmcc_enable(Cmcc *const p_cmcc)
{
	if (CMCC_SR_CSTS != cmcc_get_status(p_cmcc)) {
		p_cmcc->CMCC_CTRL |= CMCC_CTRL_CEN;
	}
}

/**
 * \brief Cache Controller Invalidate by Line Operation.
 *
 * \param p_cmcc Pointer to an CMCC instance.
 *
 */
void cmcc_invalidate_line(Cmcc *const p_cmcc, uint32_t cmcc_way,
		uint32_t cmcc_index)
{
	cmcc_disable(p_cmcc);
	while (cmcc_get_status(p_cmcc) & CMCC_SR_CSTS) {
	}
	p_cmcc->CMCC_MAINT1 = (cmcc_way << CMCC_MAINT1_WAY_Pos) |
			(cmcc_index << CMCC_MAINT1_INDEX_Pos);
	cmcc_enable(p_cmcc);
}
