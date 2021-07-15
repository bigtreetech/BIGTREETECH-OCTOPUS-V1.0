/**
 * \file
 *
 * \brief Instance description for TC7
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

#ifndef _SAMC21_TC7_INSTANCE_
#define _SAMC21_TC7_INSTANCE_

/* ========== Register definition for TC7 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_TC7_CTRLA              (0x43001000) /**< \brief (TC7) Control A */
#define REG_TC7_CTRLBCLR           (0x43001004) /**< \brief (TC7) Control B Clear */
#define REG_TC7_CTRLBSET           (0x43001005) /**< \brief (TC7) Control B Set */
#define REG_TC7_EVCTRL             (0x43001006) /**< \brief (TC7) Event Control */
#define REG_TC7_INTENCLR           (0x43001008) /**< \brief (TC7) Interrupt Enable Clear */
#define REG_TC7_INTENSET           (0x43001009) /**< \brief (TC7) Interrupt Enable Set */
#define REG_TC7_INTFLAG            (0x4300100A) /**< \brief (TC7) Interrupt Flag Status and Clear */
#define REG_TC7_STATUS             (0x4300100B) /**< \brief (TC7) Status */
#define REG_TC7_WAVE               (0x4300100C) /**< \brief (TC7) Waveform Generation Control */
#define REG_TC7_DRVCTRL            (0x4300100D) /**< \brief (TC7) Control C */
#define REG_TC7_DBGCTRL            (0x4300100F) /**< \brief (TC7) Debug Control */
#define REG_TC7_SYNCBUSY           (0x43001010) /**< \brief (TC7) Synchronization Status */
#define REG_TC7_COUNT16_COUNT      (0x43001014) /**< \brief (TC7) COUNT16 Count */
#define REG_TC7_COUNT16_CC0        (0x4300101C) /**< \brief (TC7) COUNT16 Compare and Capture 0 */
#define REG_TC7_COUNT16_CC1        (0x4300101E) /**< \brief (TC7) COUNT16 Compare and Capture 1 */
#define REG_TC7_COUNT16_CCBUF0     (0x43001030) /**< \brief (TC7) COUNT16 Compare and Capture Buffer 0 */
#define REG_TC7_COUNT16_CCBUF1     (0x43001032) /**< \brief (TC7) COUNT16 Compare and Capture Buffer 1 */
#define REG_TC7_COUNT32_COUNT      (0x43001014) /**< \brief (TC7) COUNT32 Count */
#define REG_TC7_COUNT32_CC0        (0x4300101C) /**< \brief (TC7) COUNT32 Compare and Capture 0 */
#define REG_TC7_COUNT32_CC1        (0x43001020) /**< \brief (TC7) COUNT32 Compare and Capture 1 */
#define REG_TC7_COUNT32_CCBUF0     (0x43001030) /**< \brief (TC7) COUNT32 Compare and Capture Buffer 0 */
#define REG_TC7_COUNT32_CCBUF1     (0x43001034) /**< \brief (TC7) COUNT32 Compare and Capture Buffer 1 */
#define REG_TC7_COUNT8_COUNT       (0x43001014) /**< \brief (TC7) COUNT8 Count */
#define REG_TC7_COUNT8_PER         (0x4300101B) /**< \brief (TC7) COUNT8 Period */
#define REG_TC7_COUNT8_CC0         (0x4300101C) /**< \brief (TC7) COUNT8 Compare and Capture 0 */
#define REG_TC7_COUNT8_CC1         (0x4300101D) /**< \brief (TC7) COUNT8 Compare and Capture 1 */
#define REG_TC7_COUNT8_PERBUF      (0x4300102F) /**< \brief (TC7) COUNT8 Period Buffer */
#define REG_TC7_COUNT8_CCBUF0      (0x43001030) /**< \brief (TC7) COUNT8 Compare and Capture Buffer 0 */
#define REG_TC7_COUNT8_CCBUF1      (0x43001031) /**< \brief (TC7) COUNT8 Compare and Capture Buffer 1 */
#else
#define REG_TC7_CTRLA              (*(RwReg  *)0x43001000UL) /**< \brief (TC7) Control A */
#define REG_TC7_CTRLBCLR           (*(RwReg8 *)0x43001004UL) /**< \brief (TC7) Control B Clear */
#define REG_TC7_CTRLBSET           (*(RwReg8 *)0x43001005UL) /**< \brief (TC7) Control B Set */
#define REG_TC7_EVCTRL             (*(RwReg16*)0x43001006UL) /**< \brief (TC7) Event Control */
#define REG_TC7_INTENCLR           (*(RwReg8 *)0x43001008UL) /**< \brief (TC7) Interrupt Enable Clear */
#define REG_TC7_INTENSET           (*(RwReg8 *)0x43001009UL) /**< \brief (TC7) Interrupt Enable Set */
#define REG_TC7_INTFLAG            (*(RwReg8 *)0x4300100AUL) /**< \brief (TC7) Interrupt Flag Status and Clear */
#define REG_TC7_STATUS             (*(RwReg8 *)0x4300100BUL) /**< \brief (TC7) Status */
#define REG_TC7_WAVE               (*(RwReg8 *)0x4300100CUL) /**< \brief (TC7) Waveform Generation Control */
#define REG_TC7_DRVCTRL            (*(RwReg8 *)0x4300100DUL) /**< \brief (TC7) Control C */
#define REG_TC7_DBGCTRL            (*(RwReg8 *)0x4300100FUL) /**< \brief (TC7) Debug Control */
#define REG_TC7_SYNCBUSY           (*(RoReg  *)0x43001010UL) /**< \brief (TC7) Synchronization Status */
#define REG_TC7_COUNT16_COUNT      (*(RwReg16*)0x43001014UL) /**< \brief (TC7) COUNT16 Count */
#define REG_TC7_COUNT16_CC0        (*(RwReg16*)0x4300101CUL) /**< \brief (TC7) COUNT16 Compare and Capture 0 */
#define REG_TC7_COUNT16_CC1        (*(RwReg16*)0x4300101EUL) /**< \brief (TC7) COUNT16 Compare and Capture 1 */
#define REG_TC7_COUNT16_CCBUF0     (*(RwReg16*)0x43001030UL) /**< \brief (TC7) COUNT16 Compare and Capture Buffer 0 */
#define REG_TC7_COUNT16_CCBUF1     (*(RwReg16*)0x43001032UL) /**< \brief (TC7) COUNT16 Compare and Capture Buffer 1 */
#define REG_TC7_COUNT32_COUNT      (*(RwReg  *)0x43001014UL) /**< \brief (TC7) COUNT32 Count */
#define REG_TC7_COUNT32_CC0        (*(RwReg  *)0x4300101CUL) /**< \brief (TC7) COUNT32 Compare and Capture 0 */
#define REG_TC7_COUNT32_CC1        (*(RwReg  *)0x43001020UL) /**< \brief (TC7) COUNT32 Compare and Capture 1 */
#define REG_TC7_COUNT32_CCBUF0     (*(RwReg  *)0x43001030UL) /**< \brief (TC7) COUNT32 Compare and Capture Buffer 0 */
#define REG_TC7_COUNT32_CCBUF1     (*(RwReg  *)0x43001034UL) /**< \brief (TC7) COUNT32 Compare and Capture Buffer 1 */
#define REG_TC7_COUNT8_COUNT       (*(RwReg8 *)0x43001014UL) /**< \brief (TC7) COUNT8 Count */
#define REG_TC7_COUNT8_PER         (*(RwReg8 *)0x4300101BUL) /**< \brief (TC7) COUNT8 Period */
#define REG_TC7_COUNT8_CC0         (*(RwReg8 *)0x4300101CUL) /**< \brief (TC7) COUNT8 Compare and Capture 0 */
#define REG_TC7_COUNT8_CC1         (*(RwReg8 *)0x4300101DUL) /**< \brief (TC7) COUNT8 Compare and Capture 1 */
#define REG_TC7_COUNT8_PERBUF      (*(RwReg8 *)0x4300102FUL) /**< \brief (TC7) COUNT8 Period Buffer */
#define REG_TC7_COUNT8_CCBUF0      (*(RwReg8 *)0x43001030UL) /**< \brief (TC7) COUNT8 Compare and Capture Buffer 0 */
#define REG_TC7_COUNT8_CCBUF1      (*(RwReg8 *)0x43001031UL) /**< \brief (TC7) COUNT8 Compare and Capture Buffer 1 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for TC7 peripheral ========== */
#define TC7_CC_NUM                  2       
#define TC7_DMAC_ID_MC_0            60
#define TC7_DMAC_ID_MC_1            61
#define TC7_DMAC_ID_MC_LSB          60
#define TC7_DMAC_ID_MC_MSB          61
#define TC7_DMAC_ID_MC_SIZE         2
#define TC7_DMAC_ID_OVF             59       // Indexes of DMA Overflow trigger
#define TC7_EXT                     0        // Coding of implemented extended features (keep 0 value)
#define TC7_GCLK_ID                 45       // Index of Generic Clock
#define TC7_MASTER_SLAVE_MODE       0        // TC type 0 : NA, 1 : Master, 2 : Slave
#define TC7_OW_NUM                  2        // Number of Output Waveforms

#endif /* _SAMC21_TC7_INSTANCE_ */
