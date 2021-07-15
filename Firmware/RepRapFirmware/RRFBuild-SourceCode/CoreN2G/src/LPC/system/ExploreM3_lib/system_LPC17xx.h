/**************************************************************************//**
 * @file     system_LPC17xx.h
 * @brief    CMSIS Cortex-M3 Device Peripheral Access Layer Header File
 *           for the NXP LPC17xx Device Series
 * @version  V1.02
 * @date     08. September 2009
 *
 * @note
 * Copyright (C) 2009 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M 
 * processor based microcontrollers.  This file can be freely distributed 
 * within development tools that are supporting such ARM based processors. 
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/


#ifndef __SYSTEM_LPC17xx_H
#define __SYSTEM_LPC17xx_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

extern const uint32_t OscRateIn;
extern const uint32_t RTCOscRateIn;
typedef void (*p_msDelay_func_t)(uint32_t); //required for LPCOpen


    
    
extern uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock)  */


/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit (void) noexcept;

/**
 * Update SystemCoreClock variable
 *
 * @param  none
 * @return none
 *
 * @brief  Updates the SystemCoreClock with current core Clock 
 *         retrieved from cpu registers.
 */
extern void SystemCoreClockUpdate (void) noexcept;

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_LPC17xx_H */
