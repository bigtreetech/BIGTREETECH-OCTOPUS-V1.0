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

#ifndef CMCC_H_INCLUDED
#define CMCC_H_INCLUDED

/**
 * \defgroup group_sam_drivers_cmcc CMCC - Cortex M Cache Controller module
 *
 * The Cortex M Cache Controller (CMCC) is a 4-way set associative unified
 * cache controller.
 * It integrates a controller, a tag directory, data memory, metadata memory
 * and a configuration interface.
 *
 * @{
 */

#include "compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

#if SAMG55
/** Cache Controller Programmable Cache Size */
enum cmcc_cache_size {
	CMCC_PROG_CSIZE_1KB = 0 << 4,
	CMCC_PROG_CSIZE_2KB = 1 << 4,
	CMCC_PROG_CSIZE_4KB = 2 << 4,
	CMCC_PROG_CSIZE_8KB = 3 << 4,
	CMCC_PROG_CSIZE_16KB = 4 << 4,
};
#endif

/** Cache Controller Monitor Counter Mode */
enum cmcc_monitor_mode {
	CMCC_CYCLE_COUNT_MODE = 0,
	CMCC_IHIT_COUNT_MODE,
	CMCC_DHIT_COUNT_MODE,
};

/** CMCC Configuration structure. */
struct cmcc_config {
	/* false = cache controller monitor disable, true = cache controller
	 *monitor enable */
	bool cmcc_monitor_enable;
	/* Cache Controller Monitor Counter Mode */
	enum cmcc_monitor_mode cmcc_mcfg_mode;
#if SAMG55
	/* Cache Controller Programmable Cache Size */
	enum cmcc_cache_size cmcc_cfg_cache_size;
#endif
};

void cmcc_get_config_defaults(struct cmcc_config *const cfg);

bool cmcc_init(Cmcc *const p_cmcc, struct cmcc_config *const cfg);

void cmcc_enable(Cmcc *const p_cmcc);

void cmcc_invalidate_line(Cmcc *const p_cmcc, uint32_t cmcc_way,
		uint32_t cmcc_index);

/**
 * \brief Configure the CMCC.
 *
 * \param p_cmcc Pointer to an CMCC instance.
 * \param cfg Pointer to CMCC configuration.
 */
static inline void cmcc_set_config(Cmcc *const p_cmcc,
		struct cmcc_config *const cfg)
{
	p_cmcc->CMCC_MCFG = cfg->cmcc_mcfg_mode;
#if SAMG55	
	p_cmcc->CMCC_CFG |= cfg->cmcc_cfg_cache_size;
#endif
}

#if SAM4E || SAMG55
/**
 * \brief Enable Clock gating.
 *
 * \param p_cmcc Pointer to an CMCC instance.
 *
 */
static inline void cmcc_enable_clock_gating(Cmcc *const p_cmcc)
{
	p_cmcc->CMCC_CFG &= ~CMCC_CFG_GCLKDIS;
}

/**
 * \brief Disable Clock gating.
 *
 * \param p_cmcc Pointer to an CMCC instance.
 *
 */
static inline void cmcc_disable_clock_gating(Cmcc *const p_cmcc)
{
	p_cmcc->CMCC_CFG |= CMCC_CFG_GCLKDIS;
}
#endif

#if SAMG55
/**
 * \brief Enable Instruction Caching.
 *
 * \param p_cmcc Pointer to an CMCC instance.
 *
 */
static inline void cmcc_enable_instruction_caching(Cmcc *const p_cmcc)
{
	p_cmcc->CMCC_CFG &= ~CMCC_CFG_ICDIS;
}

/**
 * \brief Disable Instruction Caching.
 *
 * \param p_cmcc Pointer to an CMCC instance.
 *
 */
static inline void cmcc_disable_instruction_caching(Cmcc *const p_cmcc)
{
	p_cmcc->CMCC_CFG |= CMCC_CFG_ICDIS;
}

/**
 * \brief Enable Data Caching.
 *
 * \param p_cmcc Pointer to an CMCC instance.
 *
 */
static inline void cmcc_enable_data_caching(Cmcc *const p_cmcc)
{
	p_cmcc->CMCC_CFG &= ~CMCC_CFG_DCDIS;
}

/**
 * \brief Disable Data Caching.
 *
 * \param p_cmcc Pointer to an CMCC instance.
 *
 */
static inline void cmcc_disable_data_caching(Cmcc *const p_cmcc)
{
	p_cmcc->CMCC_CFG |= CMCC_CFG_DCDIS;
}
#endif

/**
 * \brief Enable Cache Controller monitor.
 *
 * \param p_cmcc Pointer to an CMCC instance.
 *
 */
static inline void cmcc_enable_monitor(Cmcc *const p_cmcc)
{
	p_cmcc->CMCC_MEN |= CMCC_MEN_MENABLE;
}

/**
 * \brief Disable Cache Controller monitor.
 *
 * \param p_cmcc Pointer to an CMCC instance.
 *
 */
static inline void cmcc_disable_monitor(Cmcc *const p_cmcc)
{
	p_cmcc->CMCC_MEN &= ~CMCC_MEN_MENABLE;
}

/**
 * \brief Reset event counter register.
 *
 * \param p_cmcc Pointer to an CMCC instance.
 *
 */
static inline void cmcc_reset_monitor(Cmcc *const p_cmcc)
{
	p_cmcc->CMCC_MCTRL = CMCC_MCTRL_SWRST;
}

/**
 * \brief Get the Cache Controller status.
 *
 * \param p_cmcc Pointer to an CMCC instance.
 *
 * \return the content of the status register.
 *
 */
static inline uint32_t cmcc_get_status(Cmcc *const p_cmcc)
{
	return p_cmcc->CMCC_SR;
}

/**
 * \brief Get the Cache Controller monitor status.
 *
 * \param p_cmcc Pointer to an CMCC instance.
 *
 * \return the content of the status register.
 *
 */
static inline uint32_t cmcc_get_monitor_cnt(Cmcc *const p_cmcc)
{
	return p_cmcc->CMCC_MSR;
}

/**
 * \brief Disable Cache Controller.
 *
 * \param p_cmcc Pointer to an CMCC instance.
 *
 */
static inline void cmcc_disable(Cmcc *const p_cmcc)
{
	p_cmcc->CMCC_CTRL = 0;
}

/**
 * \brief Cache Controller Invalidate All.
 *
 * \param p_cmcc Pointer to an CMCC instance.
 *
 */
static inline void cmcc_invalidate_all(Cmcc *const p_cmcc)
{
	p_cmcc->CMCC_MAINT0 = CMCC_MAINT0_INVALL;
}

/** @} */

#ifdef __cplusplus
}
#endif

/**
 * \page sam_cmcc_quick_start Quick Start Guide for the CMCC driver
 *
 * This is the quick start guide for the \ref group_sam_drivers_cmcc, with
 * step-by-step instructions on how to configure and use the driver for
 * a specific use case.The code examples can be copied into e.g the main
 * application loop or any other function that will need to control the
 * CMCC module.
 *
 * \section cmcc_qs_use_cases Use cases
 * - \ref cmcc_basic
 *
 * \section cmcc_basic CMCC basic usage
 *
 * This use case will demonstrate how to initialize the CMCC module.
 *
 *
 * \section cmcc_basic_setup Setup steps
 *
 * \subsection cmcc_basic_setup_code  Code
 *
 * Add this to the main loop or a setup function:
 * \code
	struct cmcc_config   g_cmcc_cfg;
	cmcc_get_config_defaults(&g_cmcc_cfg);
	cmcc_init(CMCC, &g_cmcc_cfg);
	cmcc_enable(CMCC);
\endcode
 *
 * \subsection cmcc_basic_setup_workflow Workflow
 *
 * -# Enable the CMCC module
 * \code 
	cmcc_enable(CMCC); 
\endcode
 *
 * -# Initialize the CMCC to Data hit counter mode
 * \code
	g_cmcc_cfg->cmcc_mcfg_mode = CMCC_DHIT_COUNT_MODE;
	cmcc_set_config(CMCC,&g_cmcc_cfg);
	cmcc_enable_monitor(CMCC);
\endcode
 *
 * \section cmcc_basic_usage Usage steps
 *
 * \subsection cmcc_basic_usage_code Code
 *
 * We can then get the count of Cache Monitor Event by
 * \code
	cmcc_get_monitor_cnt(CMCC);
\endcode
 */

#endif  /* CMCC_H_INCLUDED */
