/**
 * \file
 *
 * \brief Instance description for TC5
 *
 * Copyright (c) 2018 Microchip Technology Inc.
 *
 * \asf_license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the Licence at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \asf_license_stop
 *
 */

#ifndef _SAMC21_TC5_INSTANCE_
#define _SAMC21_TC5_INSTANCE_

/* ========== Register definition for TC5 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_TC5_CTRLA              (0x43000800) /**< \brief (TC5) Control A */
#define REG_TC5_CTRLBCLR           (0x43000804) /**< \brief (TC5) Control B Clear */
#define REG_TC5_CTRLBSET           (0x43000805) /**< \brief (TC5) Control B Set */
#define REG_TC5_EVCTRL             (0x43000806) /**< \brief (TC5) Event Control */
#define REG_TC5_INTENCLR           (0x43000808) /**< \brief (TC5) Interrupt Enable Clear */
#define REG_TC5_INTENSET           (0x43000809) /**< \brief (TC5) Interrupt Enable Set */
#define REG_TC5_INTFLAG            (0x4300080A) /**< \brief (TC5) Interrupt Flag Status and Clear */
#define REG_TC5_STATUS             (0x4300080B) /**< \brief (TC5) Status */
#define REG_TC5_WAVE               (0x4300080C) /**< \brief (TC5) Waveform Generation Control */
#define REG_TC5_DRVCTRL            (0x4300080D) /**< \brief (TC5) Control C */
#define REG_TC5_DBGCTRL            (0x4300080F) /**< \brief (TC5) Debug Control */
#define REG_TC5_SYNCBUSY           (0x43000810) /**< \brief (TC5) Synchronization Status */
#define REG_TC5_COUNT16_COUNT      (0x43000814) /**< \brief (TC5) COUNT16 Count */
#define REG_TC5_COUNT16_CC0        (0x4300081C) /**< \brief (TC5) COUNT16 Compare and Capture 0 */
#define REG_TC5_COUNT16_CC1        (0x4300081E) /**< \brief (TC5) COUNT16 Compare and Capture 1 */
#define REG_TC5_COUNT16_CCBUF0     (0x43000830) /**< \brief (TC5) COUNT16 Compare and Capture Buffer 0 */
#define REG_TC5_COUNT16_CCBUF1     (0x43000832) /**< \brief (TC5) COUNT16 Compare and Capture Buffer 1 */
#define REG_TC5_COUNT32_COUNT      (0x43000814) /**< \brief (TC5) COUNT32 Count */
#define REG_TC5_COUNT32_CC0        (0x4300081C) /**< \brief (TC5) COUNT32 Compare and Capture 0 */
#define REG_TC5_COUNT32_CC1        (0x43000820) /**< \brief (TC5) COUNT32 Compare and Capture 1 */
#define REG_TC5_COUNT32_CCBUF0     (0x43000830) /**< \brief (TC5) COUNT32 Compare and Capture Buffer 0 */
#define REG_TC5_COUNT32_CCBUF1     (0x43000834) /**< \brief (TC5) COUNT32 Compare and Capture Buffer 1 */
#define REG_TC5_COUNT8_COUNT       (0x43000814) /**< \brief (TC5) COUNT8 Count */
#define REG_TC5_COUNT8_PER         (0x4300081B) /**< \brief (TC5) COUNT8 Period */
#define REG_TC5_COUNT8_CC0         (0x4300081C) /**< \brief (TC5) COUNT8 Compare and Capture 0 */
#define REG_TC5_COUNT8_CC1         (0x4300081D) /**< \brief (TC5) COUNT8 Compare and Capture 1 */
#define REG_TC5_COUNT8_PERBUF      (0x4300082F) /**< \brief (TC5) COUNT8 Period Buffer */
#define REG_TC5_COUNT8_CCBUF0      (0x43000830) /**< \brief (TC5) COUNT8 Compare and Capture Buffer 0 */
#define REG_TC5_COUNT8_CCBUF1      (0x43000831) /**< \brief (TC5) COUNT8 Compare and Capture Buffer 1 */
#else
#define REG_TC5_CTRLA              (*(RwReg  *)0x43000800UL) /**< \brief (TC5) Control A */
#define REG_TC5_CTRLBCLR           (*(RwReg8 *)0x43000804UL) /**< \brief (TC5) Control B Clear */
#define REG_TC5_CTRLBSET           (*(RwReg8 *)0x43000805UL) /**< \brief (TC5) Control B Set */
#define REG_TC5_EVCTRL             (*(RwReg16*)0x43000806UL) /**< \brief (TC5) Event Control */
#define REG_TC5_INTENCLR           (*(RwReg8 *)0x43000808UL) /**< \brief (TC5) Interrupt Enable Clear */
#define REG_TC5_INTENSET           (*(RwReg8 *)0x43000809UL) /**< \brief (TC5) Interrupt Enable Set */
#define REG_TC5_INTFLAG            (*(RwReg8 *)0x4300080AUL) /**< \brief (TC5) Interrupt Flag Status and Clear */
#define REG_TC5_STATUS             (*(RwReg8 *)0x4300080BUL) /**< \brief (TC5) Status */
#define REG_TC5_WAVE               (*(RwReg8 *)0x4300080CUL) /**< \brief (TC5) Waveform Generation Control */
#define REG_TC5_DRVCTRL            (*(RwReg8 *)0x4300080DUL) /**< \brief (TC5) Control C */
#define REG_TC5_DBGCTRL            (*(RwReg8 *)0x4300080FUL) /**< \brief (TC5) Debug Control */
#define REG_TC5_SYNCBUSY           (*(RoReg  *)0x43000810UL) /**< \brief (TC5) Synchronization Status */
#define REG_TC5_COUNT16_COUNT      (*(RwReg16*)0x43000814UL) /**< \brief (TC5) COUNT16 Count */
#define REG_TC5_COUNT16_CC0        (*(RwReg16*)0x4300081CUL) /**< \brief (TC5) COUNT16 Compare and Capture 0 */
#define REG_TC5_COUNT16_CC1        (*(RwReg16*)0x4300081EUL) /**< \brief (TC5) COUNT16 Compare and Capture 1 */
#define REG_TC5_COUNT16_CCBUF0     (*(RwReg16*)0x43000830UL) /**< \brief (TC5) COUNT16 Compare and Capture Buffer 0 */
#define REG_TC5_COUNT16_CCBUF1     (*(RwReg16*)0x43000832UL) /**< \brief (TC5) COUNT16 Compare and Capture Buffer 1 */
#define REG_TC5_COUNT32_COUNT      (*(RwReg  *)0x43000814UL) /**< \brief (TC5) COUNT32 Count */
#define REG_TC5_COUNT32_CC0        (*(RwReg  *)0x4300081CUL) /**< \brief (TC5) COUNT32 Compare and Capture 0 */
#define REG_TC5_COUNT32_CC1        (*(RwReg  *)0x43000820UL) /**< \brief (TC5) COUNT32 Compare and Capture 1 */
#define REG_TC5_COUNT32_CCBUF0     (*(RwReg  *)0x43000830UL) /**< \brief (TC5) COUNT32 Compare and Capture Buffer 0 */
#define REG_TC5_COUNT32_CCBUF1     (*(RwReg  *)0x43000834UL) /**< \brief (TC5) COUNT32 Compare and Capture Buffer 1 */
#define REG_TC5_COUNT8_COUNT       (*(RwReg8 *)0x43000814UL) /**< \brief (TC5) COUNT8 Count */
#define REG_TC5_COUNT8_PER         (*(RwReg8 *)0x4300081BUL) /**< \brief (TC5) COUNT8 Period */
#define REG_TC5_COUNT8_CC0         (*(RwReg8 *)0x4300081CUL) /**< \brief (TC5) COUNT8 Compare and Capture 0 */
#define REG_TC5_COUNT8_CC1         (*(RwReg8 *)0x4300081DUL) /**< \brief (TC5) COUNT8 Compare and Capture 1 */
#define REG_TC5_COUNT8_PERBUF      (*(RwReg8 *)0x4300082FUL) /**< \brief (TC5) COUNT8 Period Buffer */
#define REG_TC5_COUNT8_CCBUF0      (*(RwReg8 *)0x43000830UL) /**< \brief (TC5) COUNT8 Compare and Capture Buffer 0 */
#define REG_TC5_COUNT8_CCBUF1      (*(RwReg8 *)0x43000831UL) /**< \brief (TC5) COUNT8 Compare and Capture Buffer 1 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for TC5 peripheral ========== */
#define TC5_CC_NUM                  2       
#define TC5_DMAC_ID_MC_0            54
#define TC5_DMAC_ID_MC_1            55
#define TC5_DMAC_ID_MC_LSB          54
#define TC5_DMAC_ID_MC_MSB          55
#define TC5_DMAC_ID_MC_SIZE         2
#define TC5_DMAC_ID_OVF             53       // Indexes of DMA Overflow trigger
#define TC5_EXT                     0        // Coding of implemented extended features (keep 0 value)
#define TC5_GCLK_ID                 43       // Index of Generic Clock
#define TC5_MASTER_SLAVE_MODE       0        // TC type 0 : NA, 1 : Master, 2 : Slave
#define TC5_OW_NUM                  2        // Number of Output Waveforms

#endif /* _SAMC21_TC5_INSTANCE_ */
