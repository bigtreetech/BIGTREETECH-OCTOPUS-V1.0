/**
 * \file
 *
 * \brief Instance description for TC6
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

#ifndef _SAMC21_TC6_INSTANCE_
#define _SAMC21_TC6_INSTANCE_

/* ========== Register definition for TC6 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_TC6_CTRLA              (0x43000C00) /**< \brief (TC6) Control A */
#define REG_TC6_CTRLBCLR           (0x43000C04) /**< \brief (TC6) Control B Clear */
#define REG_TC6_CTRLBSET           (0x43000C05) /**< \brief (TC6) Control B Set */
#define REG_TC6_EVCTRL             (0x43000C06) /**< \brief (TC6) Event Control */
#define REG_TC6_INTENCLR           (0x43000C08) /**< \brief (TC6) Interrupt Enable Clear */
#define REG_TC6_INTENSET           (0x43000C09) /**< \brief (TC6) Interrupt Enable Set */
#define REG_TC6_INTFLAG            (0x43000C0A) /**< \brief (TC6) Interrupt Flag Status and Clear */
#define REG_TC6_STATUS             (0x43000C0B) /**< \brief (TC6) Status */
#define REG_TC6_WAVE               (0x43000C0C) /**< \brief (TC6) Waveform Generation Control */
#define REG_TC6_DRVCTRL            (0x43000C0D) /**< \brief (TC6) Control C */
#define REG_TC6_DBGCTRL            (0x43000C0F) /**< \brief (TC6) Debug Control */
#define REG_TC6_SYNCBUSY           (0x43000C10) /**< \brief (TC6) Synchronization Status */
#define REG_TC6_COUNT16_COUNT      (0x43000C14) /**< \brief (TC6) COUNT16 Count */
#define REG_TC6_COUNT16_CC0        (0x43000C1C) /**< \brief (TC6) COUNT16 Compare and Capture 0 */
#define REG_TC6_COUNT16_CC1        (0x43000C1E) /**< \brief (TC6) COUNT16 Compare and Capture 1 */
#define REG_TC6_COUNT16_CCBUF0     (0x43000C30) /**< \brief (TC6) COUNT16 Compare and Capture Buffer 0 */
#define REG_TC6_COUNT16_CCBUF1     (0x43000C32) /**< \brief (TC6) COUNT16 Compare and Capture Buffer 1 */
#define REG_TC6_COUNT32_COUNT      (0x43000C14) /**< \brief (TC6) COUNT32 Count */
#define REG_TC6_COUNT32_CC0        (0x43000C1C) /**< \brief (TC6) COUNT32 Compare and Capture 0 */
#define REG_TC6_COUNT32_CC1        (0x43000C20) /**< \brief (TC6) COUNT32 Compare and Capture 1 */
#define REG_TC6_COUNT32_CCBUF0     (0x43000C30) /**< \brief (TC6) COUNT32 Compare and Capture Buffer 0 */
#define REG_TC6_COUNT32_CCBUF1     (0x43000C34) /**< \brief (TC6) COUNT32 Compare and Capture Buffer 1 */
#define REG_TC6_COUNT8_COUNT       (0x43000C14) /**< \brief (TC6) COUNT8 Count */
#define REG_TC6_COUNT8_PER         (0x43000C1B) /**< \brief (TC6) COUNT8 Period */
#define REG_TC6_COUNT8_CC0         (0x43000C1C) /**< \brief (TC6) COUNT8 Compare and Capture 0 */
#define REG_TC6_COUNT8_CC1         (0x43000C1D) /**< \brief (TC6) COUNT8 Compare and Capture 1 */
#define REG_TC6_COUNT8_PERBUF      (0x43000C2F) /**< \brief (TC6) COUNT8 Period Buffer */
#define REG_TC6_COUNT8_CCBUF0      (0x43000C30) /**< \brief (TC6) COUNT8 Compare and Capture Buffer 0 */
#define REG_TC6_COUNT8_CCBUF1      (0x43000C31) /**< \brief (TC6) COUNT8 Compare and Capture Buffer 1 */
#else
#define REG_TC6_CTRLA              (*(RwReg  *)0x43000C00UL) /**< \brief (TC6) Control A */
#define REG_TC6_CTRLBCLR           (*(RwReg8 *)0x43000C04UL) /**< \brief (TC6) Control B Clear */
#define REG_TC6_CTRLBSET           (*(RwReg8 *)0x43000C05UL) /**< \brief (TC6) Control B Set */
#define REG_TC6_EVCTRL             (*(RwReg16*)0x43000C06UL) /**< \brief (TC6) Event Control */
#define REG_TC6_INTENCLR           (*(RwReg8 *)0x43000C08UL) /**< \brief (TC6) Interrupt Enable Clear */
#define REG_TC6_INTENSET           (*(RwReg8 *)0x43000C09UL) /**< \brief (TC6) Interrupt Enable Set */
#define REG_TC6_INTFLAG            (*(RwReg8 *)0x43000C0AUL) /**< \brief (TC6) Interrupt Flag Status and Clear */
#define REG_TC6_STATUS             (*(RwReg8 *)0x43000C0BUL) /**< \brief (TC6) Status */
#define REG_TC6_WAVE               (*(RwReg8 *)0x43000C0CUL) /**< \brief (TC6) Waveform Generation Control */
#define REG_TC6_DRVCTRL            (*(RwReg8 *)0x43000C0DUL) /**< \brief (TC6) Control C */
#define REG_TC6_DBGCTRL            (*(RwReg8 *)0x43000C0FUL) /**< \brief (TC6) Debug Control */
#define REG_TC6_SYNCBUSY           (*(RoReg  *)0x43000C10UL) /**< \brief (TC6) Synchronization Status */
#define REG_TC6_COUNT16_COUNT      (*(RwReg16*)0x43000C14UL) /**< \brief (TC6) COUNT16 Count */
#define REG_TC6_COUNT16_CC0        (*(RwReg16*)0x43000C1CUL) /**< \brief (TC6) COUNT16 Compare and Capture 0 */
#define REG_TC6_COUNT16_CC1        (*(RwReg16*)0x43000C1EUL) /**< \brief (TC6) COUNT16 Compare and Capture 1 */
#define REG_TC6_COUNT16_CCBUF0     (*(RwReg16*)0x43000C30UL) /**< \brief (TC6) COUNT16 Compare and Capture Buffer 0 */
#define REG_TC6_COUNT16_CCBUF1     (*(RwReg16*)0x43000C32UL) /**< \brief (TC6) COUNT16 Compare and Capture Buffer 1 */
#define REG_TC6_COUNT32_COUNT      (*(RwReg  *)0x43000C14UL) /**< \brief (TC6) COUNT32 Count */
#define REG_TC6_COUNT32_CC0        (*(RwReg  *)0x43000C1CUL) /**< \brief (TC6) COUNT32 Compare and Capture 0 */
#define REG_TC6_COUNT32_CC1        (*(RwReg  *)0x43000C20UL) /**< \brief (TC6) COUNT32 Compare and Capture 1 */
#define REG_TC6_COUNT32_CCBUF0     (*(RwReg  *)0x43000C30UL) /**< \brief (TC6) COUNT32 Compare and Capture Buffer 0 */
#define REG_TC6_COUNT32_CCBUF1     (*(RwReg  *)0x43000C34UL) /**< \brief (TC6) COUNT32 Compare and Capture Buffer 1 */
#define REG_TC6_COUNT8_COUNT       (*(RwReg8 *)0x43000C14UL) /**< \brief (TC6) COUNT8 Count */
#define REG_TC6_COUNT8_PER         (*(RwReg8 *)0x43000C1BUL) /**< \brief (TC6) COUNT8 Period */
#define REG_TC6_COUNT8_CC0         (*(RwReg8 *)0x43000C1CUL) /**< \brief (TC6) COUNT8 Compare and Capture 0 */
#define REG_TC6_COUNT8_CC1         (*(RwReg8 *)0x43000C1DUL) /**< \brief (TC6) COUNT8 Compare and Capture 1 */
#define REG_TC6_COUNT8_PERBUF      (*(RwReg8 *)0x43000C2FUL) /**< \brief (TC6) COUNT8 Period Buffer */
#define REG_TC6_COUNT8_CCBUF0      (*(RwReg8 *)0x43000C30UL) /**< \brief (TC6) COUNT8 Compare and Capture Buffer 0 */
#define REG_TC6_COUNT8_CCBUF1      (*(RwReg8 *)0x43000C31UL) /**< \brief (TC6) COUNT8 Compare and Capture Buffer 1 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for TC6 peripheral ========== */
#define TC6_CC_NUM                  2       
#define TC6_DMAC_ID_MC_0            57
#define TC6_DMAC_ID_MC_1            58
#define TC6_DMAC_ID_MC_LSB          57
#define TC6_DMAC_ID_MC_MSB          58
#define TC6_DMAC_ID_MC_SIZE         2
#define TC6_DMAC_ID_OVF             56       // Indexes of DMA Overflow trigger
#define TC6_EXT                     0        // Coding of implemented extended features (keep 0 value)
#define TC6_GCLK_ID                 44       // Index of Generic Clock
#define TC6_MASTER_SLAVE_MODE       0        // TC type 0 : NA, 1 : Master, 2 : Slave
#define TC6_OW_NUM                  2        // Number of Output Waveforms

#endif /* _SAMC21_TC6_INSTANCE_ */
