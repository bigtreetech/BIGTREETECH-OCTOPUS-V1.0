/**
 * \file
 *
 * \brief Instance description for SERCOM7
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

#ifndef _SAMC21_SERCOM7_INSTANCE_
#define _SAMC21_SERCOM7_INSTANCE_

/* ========== Register definition for SERCOM7 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_SERCOM7_I2CM_CTRLA     (0x43000400) /**< \brief (SERCOM7) I2CM Control A */
#define REG_SERCOM7_I2CM_CTRLB     (0x43000404) /**< \brief (SERCOM7) I2CM Control B */
#define REG_SERCOM7_I2CM_BAUD      (0x4300040C) /**< \brief (SERCOM7) I2CM Baud Rate */
#define REG_SERCOM7_I2CM_INTENCLR  (0x43000414) /**< \brief (SERCOM7) I2CM Interrupt Enable Clear */
#define REG_SERCOM7_I2CM_INTENSET  (0x43000416) /**< \brief (SERCOM7) I2CM Interrupt Enable Set */
#define REG_SERCOM7_I2CM_INTFLAG   (0x43000418) /**< \brief (SERCOM7) I2CM Interrupt Flag Status and Clear */
#define REG_SERCOM7_I2CM_STATUS    (0x4300041A) /**< \brief (SERCOM7) I2CM Status */
#define REG_SERCOM7_I2CM_SYNCBUSY  (0x4300041C) /**< \brief (SERCOM7) I2CM Synchronization Busy */
#define REG_SERCOM7_I2CM_ADDR      (0x43000424) /**< \brief (SERCOM7) I2CM Address */
#define REG_SERCOM7_I2CM_DATA      (0x43000428) /**< \brief (SERCOM7) I2CM Data */
#define REG_SERCOM7_I2CM_DBGCTRL   (0x43000430) /**< \brief (SERCOM7) I2CM Debug Control */
#define REG_SERCOM7_I2CS_CTRLA     (0x43000400) /**< \brief (SERCOM7) I2CS Control A */
#define REG_SERCOM7_I2CS_CTRLB     (0x43000404) /**< \brief (SERCOM7) I2CS Control B */
#define REG_SERCOM7_I2CS_INTENCLR  (0x43000414) /**< \brief (SERCOM7) I2CS Interrupt Enable Clear */
#define REG_SERCOM7_I2CS_INTENSET  (0x43000416) /**< \brief (SERCOM7) I2CS Interrupt Enable Set */
#define REG_SERCOM7_I2CS_INTFLAG   (0x43000418) /**< \brief (SERCOM7) I2CS Interrupt Flag Status and Clear */
#define REG_SERCOM7_I2CS_STATUS    (0x4300041A) /**< \brief (SERCOM7) I2CS Status */
#define REG_SERCOM7_I2CS_SYNCBUSY  (0x4300041C) /**< \brief (SERCOM7) I2CS Synchronization Busy */
#define REG_SERCOM7_I2CS_ADDR      (0x43000424) /**< \brief (SERCOM7) I2CS Address */
#define REG_SERCOM7_I2CS_DATA      (0x43000428) /**< \brief (SERCOM7) I2CS Data */
#define REG_SERCOM7_SPI_CTRLA      (0x43000400) /**< \brief (SERCOM7) SPI Control A */
#define REG_SERCOM7_SPI_CTRLB      (0x43000404) /**< \brief (SERCOM7) SPI Control B */
#define REG_SERCOM7_SPI_BAUD       (0x4300040C) /**< \brief (SERCOM7) SPI Baud Rate */
#define REG_SERCOM7_SPI_INTENCLR   (0x43000414) /**< \brief (SERCOM7) SPI Interrupt Enable Clear */
#define REG_SERCOM7_SPI_INTENSET   (0x43000416) /**< \brief (SERCOM7) SPI Interrupt Enable Set */
#define REG_SERCOM7_SPI_INTFLAG    (0x43000418) /**< \brief (SERCOM7) SPI Interrupt Flag Status and Clear */
#define REG_SERCOM7_SPI_STATUS     (0x4300041A) /**< \brief (SERCOM7) SPI Status */
#define REG_SERCOM7_SPI_SYNCBUSY   (0x4300041C) /**< \brief (SERCOM7) SPI Synchronization Busy */
#define REG_SERCOM7_SPI_ADDR       (0x43000424) /**< \brief (SERCOM7) SPI Address */
#define REG_SERCOM7_SPI_DATA       (0x43000428) /**< \brief (SERCOM7) SPI Data */
#define REG_SERCOM7_SPI_DBGCTRL    (0x43000430) /**< \brief (SERCOM7) SPI Debug Control */
#define REG_SERCOM7_USART_CTRLA    (0x43000400) /**< \brief (SERCOM7) USART Control A */
#define REG_SERCOM7_USART_CTRLB    (0x43000404) /**< \brief (SERCOM7) USART Control B */
#define REG_SERCOM7_USART_CTRLC    (0x43000408) /**< \brief (SERCOM7) USART Control C */
#define REG_SERCOM7_USART_BAUD     (0x4300040C) /**< \brief (SERCOM7) USART Baud Rate */
#define REG_SERCOM7_USART_RXPL     (0x4300040E) /**< \brief (SERCOM7) USART Receive Pulse Length */
#define REG_SERCOM7_USART_INTENCLR (0x43000414) /**< \brief (SERCOM7) USART Interrupt Enable Clear */
#define REG_SERCOM7_USART_INTENSET (0x43000416) /**< \brief (SERCOM7) USART Interrupt Enable Set */
#define REG_SERCOM7_USART_INTFLAG  (0x43000418) /**< \brief (SERCOM7) USART Interrupt Flag Status and Clear */
#define REG_SERCOM7_USART_STATUS   (0x4300041A) /**< \brief (SERCOM7) USART Status */
#define REG_SERCOM7_USART_SYNCBUSY (0x4300041C) /**< \brief (SERCOM7) USART Synchronization Busy */
#define REG_SERCOM7_USART_DATA     (0x43000428) /**< \brief (SERCOM7) USART Data */
#define REG_SERCOM7_USART_DBGCTRL  (0x43000430) /**< \brief (SERCOM7) USART Debug Control */
#else
#define REG_SERCOM7_I2CM_CTRLA     (*(RwReg  *)0x43000400UL) /**< \brief (SERCOM7) I2CM Control A */
#define REG_SERCOM7_I2CM_CTRLB     (*(RwReg  *)0x43000404UL) /**< \brief (SERCOM7) I2CM Control B */
#define REG_SERCOM7_I2CM_BAUD      (*(RwReg  *)0x4300040CUL) /**< \brief (SERCOM7) I2CM Baud Rate */
#define REG_SERCOM7_I2CM_INTENCLR  (*(RwReg8 *)0x43000414UL) /**< \brief (SERCOM7) I2CM Interrupt Enable Clear */
#define REG_SERCOM7_I2CM_INTENSET  (*(RwReg8 *)0x43000416UL) /**< \brief (SERCOM7) I2CM Interrupt Enable Set */
#define REG_SERCOM7_I2CM_INTFLAG   (*(RwReg8 *)0x43000418UL) /**< \brief (SERCOM7) I2CM Interrupt Flag Status and Clear */
#define REG_SERCOM7_I2CM_STATUS    (*(RwReg16*)0x4300041AUL) /**< \brief (SERCOM7) I2CM Status */
#define REG_SERCOM7_I2CM_SYNCBUSY  (*(RoReg  *)0x4300041CUL) /**< \brief (SERCOM7) I2CM Synchronization Busy */
#define REG_SERCOM7_I2CM_ADDR      (*(RwReg  *)0x43000424UL) /**< \brief (SERCOM7) I2CM Address */
#define REG_SERCOM7_I2CM_DATA      (*(RwReg8 *)0x43000428UL) /**< \brief (SERCOM7) I2CM Data */
#define REG_SERCOM7_I2CM_DBGCTRL   (*(RwReg8 *)0x43000430UL) /**< \brief (SERCOM7) I2CM Debug Control */
#define REG_SERCOM7_I2CS_CTRLA     (*(RwReg  *)0x43000400UL) /**< \brief (SERCOM7) I2CS Control A */
#define REG_SERCOM7_I2CS_CTRLB     (*(RwReg  *)0x43000404UL) /**< \brief (SERCOM7) I2CS Control B */
#define REG_SERCOM7_I2CS_INTENCLR  (*(RwReg8 *)0x43000414UL) /**< \brief (SERCOM7) I2CS Interrupt Enable Clear */
#define REG_SERCOM7_I2CS_INTENSET  (*(RwReg8 *)0x43000416UL) /**< \brief (SERCOM7) I2CS Interrupt Enable Set */
#define REG_SERCOM7_I2CS_INTFLAG   (*(RwReg8 *)0x43000418UL) /**< \brief (SERCOM7) I2CS Interrupt Flag Status and Clear */
#define REG_SERCOM7_I2CS_STATUS    (*(RwReg16*)0x4300041AUL) /**< \brief (SERCOM7) I2CS Status */
#define REG_SERCOM7_I2CS_SYNCBUSY  (*(RoReg  *)0x4300041CUL) /**< \brief (SERCOM7) I2CS Synchronization Busy */
#define REG_SERCOM7_I2CS_ADDR      (*(RwReg  *)0x43000424UL) /**< \brief (SERCOM7) I2CS Address */
#define REG_SERCOM7_I2CS_DATA      (*(RwReg8 *)0x43000428UL) /**< \brief (SERCOM7) I2CS Data */
#define REG_SERCOM7_SPI_CTRLA      (*(RwReg  *)0x43000400UL) /**< \brief (SERCOM7) SPI Control A */
#define REG_SERCOM7_SPI_CTRLB      (*(RwReg  *)0x43000404UL) /**< \brief (SERCOM7) SPI Control B */
#define REG_SERCOM7_SPI_BAUD       (*(RwReg8 *)0x4300040CUL) /**< \brief (SERCOM7) SPI Baud Rate */
#define REG_SERCOM7_SPI_INTENCLR   (*(RwReg8 *)0x43000414UL) /**< \brief (SERCOM7) SPI Interrupt Enable Clear */
#define REG_SERCOM7_SPI_INTENSET   (*(RwReg8 *)0x43000416UL) /**< \brief (SERCOM7) SPI Interrupt Enable Set */
#define REG_SERCOM7_SPI_INTFLAG    (*(RwReg8 *)0x43000418UL) /**< \brief (SERCOM7) SPI Interrupt Flag Status and Clear */
#define REG_SERCOM7_SPI_STATUS     (*(RwReg16*)0x4300041AUL) /**< \brief (SERCOM7) SPI Status */
#define REG_SERCOM7_SPI_SYNCBUSY   (*(RoReg  *)0x4300041CUL) /**< \brief (SERCOM7) SPI Synchronization Busy */
#define REG_SERCOM7_SPI_ADDR       (*(RwReg  *)0x43000424UL) /**< \brief (SERCOM7) SPI Address */
#define REG_SERCOM7_SPI_DATA       (*(RwReg  *)0x43000428UL) /**< \brief (SERCOM7) SPI Data */
#define REG_SERCOM7_SPI_DBGCTRL    (*(RwReg8 *)0x43000430UL) /**< \brief (SERCOM7) SPI Debug Control */
#define REG_SERCOM7_USART_CTRLA    (*(RwReg  *)0x43000400UL) /**< \brief (SERCOM7) USART Control A */
#define REG_SERCOM7_USART_CTRLB    (*(RwReg  *)0x43000404UL) /**< \brief (SERCOM7) USART Control B */
#define REG_SERCOM7_USART_CTRLC    (*(RwReg  *)0x43000408UL) /**< \brief (SERCOM7) USART Control C */
#define REG_SERCOM7_USART_BAUD     (*(RwReg16*)0x4300040CUL) /**< \brief (SERCOM7) USART Baud Rate */
#define REG_SERCOM7_USART_RXPL     (*(RwReg8 *)0x4300040EUL) /**< \brief (SERCOM7) USART Receive Pulse Length */
#define REG_SERCOM7_USART_INTENCLR (*(RwReg8 *)0x43000414UL) /**< \brief (SERCOM7) USART Interrupt Enable Clear */
#define REG_SERCOM7_USART_INTENSET (*(RwReg8 *)0x43000416UL) /**< \brief (SERCOM7) USART Interrupt Enable Set */
#define REG_SERCOM7_USART_INTFLAG  (*(RwReg8 *)0x43000418UL) /**< \brief (SERCOM7) USART Interrupt Flag Status and Clear */
#define REG_SERCOM7_USART_STATUS   (*(RwReg16*)0x4300041AUL) /**< \brief (SERCOM7) USART Status */
#define REG_SERCOM7_USART_SYNCBUSY (*(RoReg  *)0x4300041CUL) /**< \brief (SERCOM7) USART Synchronization Busy */
#define REG_SERCOM7_USART_DATA     (*(RwReg16*)0x43000428UL) /**< \brief (SERCOM7) USART Data */
#define REG_SERCOM7_USART_DBGCTRL  (*(RwReg8 *)0x43000430UL) /**< \brief (SERCOM7) USART Debug Control */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for SERCOM7 peripheral ========== */
#define SERCOM7_DMAC_ID_RX          51       // Index of DMA RX trigger
#define SERCOM7_DMAC_ID_TX          52       // Index of DMA TX trigger
#define SERCOM7_GCLK_ID_CORE        42      
#define SERCOM7_GCLK_ID_SLOW        18      
#define SERCOM7_INT_MSB             6       
#define SERCOM7_PMSB                3       

#endif /* _SAMC21_SERCOM7_INSTANCE_ */
