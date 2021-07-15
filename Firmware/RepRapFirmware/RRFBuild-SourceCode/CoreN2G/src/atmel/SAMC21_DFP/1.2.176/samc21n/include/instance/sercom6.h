/**
 * \file
 *
 * \brief Instance description for SERCOM6
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

#ifndef _SAMC21_SERCOM6_INSTANCE_
#define _SAMC21_SERCOM6_INSTANCE_

/* ========== Register definition for SERCOM6 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_SERCOM6_I2CM_CTRLA     (0x43000000) /**< \brief (SERCOM6) I2CM Control A */
#define REG_SERCOM6_I2CM_CTRLB     (0x43000004) /**< \brief (SERCOM6) I2CM Control B */
#define REG_SERCOM6_I2CM_BAUD      (0x4300000C) /**< \brief (SERCOM6) I2CM Baud Rate */
#define REG_SERCOM6_I2CM_INTENCLR  (0x43000014) /**< \brief (SERCOM6) I2CM Interrupt Enable Clear */
#define REG_SERCOM6_I2CM_INTENSET  (0x43000016) /**< \brief (SERCOM6) I2CM Interrupt Enable Set */
#define REG_SERCOM6_I2CM_INTFLAG   (0x43000018) /**< \brief (SERCOM6) I2CM Interrupt Flag Status and Clear */
#define REG_SERCOM6_I2CM_STATUS    (0x4300001A) /**< \brief (SERCOM6) I2CM Status */
#define REG_SERCOM6_I2CM_SYNCBUSY  (0x4300001C) /**< \brief (SERCOM6) I2CM Synchronization Busy */
#define REG_SERCOM6_I2CM_ADDR      (0x43000024) /**< \brief (SERCOM6) I2CM Address */
#define REG_SERCOM6_I2CM_DATA      (0x43000028) /**< \brief (SERCOM6) I2CM Data */
#define REG_SERCOM6_I2CM_DBGCTRL   (0x43000030) /**< \brief (SERCOM6) I2CM Debug Control */
#define REG_SERCOM6_I2CS_CTRLA     (0x43000000) /**< \brief (SERCOM6) I2CS Control A */
#define REG_SERCOM6_I2CS_CTRLB     (0x43000004) /**< \brief (SERCOM6) I2CS Control B */
#define REG_SERCOM6_I2CS_INTENCLR  (0x43000014) /**< \brief (SERCOM6) I2CS Interrupt Enable Clear */
#define REG_SERCOM6_I2CS_INTENSET  (0x43000016) /**< \brief (SERCOM6) I2CS Interrupt Enable Set */
#define REG_SERCOM6_I2CS_INTFLAG   (0x43000018) /**< \brief (SERCOM6) I2CS Interrupt Flag Status and Clear */
#define REG_SERCOM6_I2CS_STATUS    (0x4300001A) /**< \brief (SERCOM6) I2CS Status */
#define REG_SERCOM6_I2CS_SYNCBUSY  (0x4300001C) /**< \brief (SERCOM6) I2CS Synchronization Busy */
#define REG_SERCOM6_I2CS_ADDR      (0x43000024) /**< \brief (SERCOM6) I2CS Address */
#define REG_SERCOM6_I2CS_DATA      (0x43000028) /**< \brief (SERCOM6) I2CS Data */
#define REG_SERCOM6_SPI_CTRLA      (0x43000000) /**< \brief (SERCOM6) SPI Control A */
#define REG_SERCOM6_SPI_CTRLB      (0x43000004) /**< \brief (SERCOM6) SPI Control B */
#define REG_SERCOM6_SPI_BAUD       (0x4300000C) /**< \brief (SERCOM6) SPI Baud Rate */
#define REG_SERCOM6_SPI_INTENCLR   (0x43000014) /**< \brief (SERCOM6) SPI Interrupt Enable Clear */
#define REG_SERCOM6_SPI_INTENSET   (0x43000016) /**< \brief (SERCOM6) SPI Interrupt Enable Set */
#define REG_SERCOM6_SPI_INTFLAG    (0x43000018) /**< \brief (SERCOM6) SPI Interrupt Flag Status and Clear */
#define REG_SERCOM6_SPI_STATUS     (0x4300001A) /**< \brief (SERCOM6) SPI Status */
#define REG_SERCOM6_SPI_SYNCBUSY   (0x4300001C) /**< \brief (SERCOM6) SPI Synchronization Busy */
#define REG_SERCOM6_SPI_ADDR       (0x43000024) /**< \brief (SERCOM6) SPI Address */
#define REG_SERCOM6_SPI_DATA       (0x43000028) /**< \brief (SERCOM6) SPI Data */
#define REG_SERCOM6_SPI_DBGCTRL    (0x43000030) /**< \brief (SERCOM6) SPI Debug Control */
#define REG_SERCOM6_USART_CTRLA    (0x43000000) /**< \brief (SERCOM6) USART Control A */
#define REG_SERCOM6_USART_CTRLB    (0x43000004) /**< \brief (SERCOM6) USART Control B */
#define REG_SERCOM6_USART_CTRLC    (0x43000008) /**< \brief (SERCOM6) USART Control C */
#define REG_SERCOM6_USART_BAUD     (0x4300000C) /**< \brief (SERCOM6) USART Baud Rate */
#define REG_SERCOM6_USART_RXPL     (0x4300000E) /**< \brief (SERCOM6) USART Receive Pulse Length */
#define REG_SERCOM6_USART_INTENCLR (0x43000014) /**< \brief (SERCOM6) USART Interrupt Enable Clear */
#define REG_SERCOM6_USART_INTENSET (0x43000016) /**< \brief (SERCOM6) USART Interrupt Enable Set */
#define REG_SERCOM6_USART_INTFLAG  (0x43000018) /**< \brief (SERCOM6) USART Interrupt Flag Status and Clear */
#define REG_SERCOM6_USART_STATUS   (0x4300001A) /**< \brief (SERCOM6) USART Status */
#define REG_SERCOM6_USART_SYNCBUSY (0x4300001C) /**< \brief (SERCOM6) USART Synchronization Busy */
#define REG_SERCOM6_USART_DATA     (0x43000028) /**< \brief (SERCOM6) USART Data */
#define REG_SERCOM6_USART_DBGCTRL  (0x43000030) /**< \brief (SERCOM6) USART Debug Control */
#else
#define REG_SERCOM6_I2CM_CTRLA     (*(RwReg  *)0x43000000UL) /**< \brief (SERCOM6) I2CM Control A */
#define REG_SERCOM6_I2CM_CTRLB     (*(RwReg  *)0x43000004UL) /**< \brief (SERCOM6) I2CM Control B */
#define REG_SERCOM6_I2CM_BAUD      (*(RwReg  *)0x4300000CUL) /**< \brief (SERCOM6) I2CM Baud Rate */
#define REG_SERCOM6_I2CM_INTENCLR  (*(RwReg8 *)0x43000014UL) /**< \brief (SERCOM6) I2CM Interrupt Enable Clear */
#define REG_SERCOM6_I2CM_INTENSET  (*(RwReg8 *)0x43000016UL) /**< \brief (SERCOM6) I2CM Interrupt Enable Set */
#define REG_SERCOM6_I2CM_INTFLAG   (*(RwReg8 *)0x43000018UL) /**< \brief (SERCOM6) I2CM Interrupt Flag Status and Clear */
#define REG_SERCOM6_I2CM_STATUS    (*(RwReg16*)0x4300001AUL) /**< \brief (SERCOM6) I2CM Status */
#define REG_SERCOM6_I2CM_SYNCBUSY  (*(RoReg  *)0x4300001CUL) /**< \brief (SERCOM6) I2CM Synchronization Busy */
#define REG_SERCOM6_I2CM_ADDR      (*(RwReg  *)0x43000024UL) /**< \brief (SERCOM6) I2CM Address */
#define REG_SERCOM6_I2CM_DATA      (*(RwReg8 *)0x43000028UL) /**< \brief (SERCOM6) I2CM Data */
#define REG_SERCOM6_I2CM_DBGCTRL   (*(RwReg8 *)0x43000030UL) /**< \brief (SERCOM6) I2CM Debug Control */
#define REG_SERCOM6_I2CS_CTRLA     (*(RwReg  *)0x43000000UL) /**< \brief (SERCOM6) I2CS Control A */
#define REG_SERCOM6_I2CS_CTRLB     (*(RwReg  *)0x43000004UL) /**< \brief (SERCOM6) I2CS Control B */
#define REG_SERCOM6_I2CS_INTENCLR  (*(RwReg8 *)0x43000014UL) /**< \brief (SERCOM6) I2CS Interrupt Enable Clear */
#define REG_SERCOM6_I2CS_INTENSET  (*(RwReg8 *)0x43000016UL) /**< \brief (SERCOM6) I2CS Interrupt Enable Set */
#define REG_SERCOM6_I2CS_INTFLAG   (*(RwReg8 *)0x43000018UL) /**< \brief (SERCOM6) I2CS Interrupt Flag Status and Clear */
#define REG_SERCOM6_I2CS_STATUS    (*(RwReg16*)0x4300001AUL) /**< \brief (SERCOM6) I2CS Status */
#define REG_SERCOM6_I2CS_SYNCBUSY  (*(RoReg  *)0x4300001CUL) /**< \brief (SERCOM6) I2CS Synchronization Busy */
#define REG_SERCOM6_I2CS_ADDR      (*(RwReg  *)0x43000024UL) /**< \brief (SERCOM6) I2CS Address */
#define REG_SERCOM6_I2CS_DATA      (*(RwReg8 *)0x43000028UL) /**< \brief (SERCOM6) I2CS Data */
#define REG_SERCOM6_SPI_CTRLA      (*(RwReg  *)0x43000000UL) /**< \brief (SERCOM6) SPI Control A */
#define REG_SERCOM6_SPI_CTRLB      (*(RwReg  *)0x43000004UL) /**< \brief (SERCOM6) SPI Control B */
#define REG_SERCOM6_SPI_BAUD       (*(RwReg8 *)0x4300000CUL) /**< \brief (SERCOM6) SPI Baud Rate */
#define REG_SERCOM6_SPI_INTENCLR   (*(RwReg8 *)0x43000014UL) /**< \brief (SERCOM6) SPI Interrupt Enable Clear */
#define REG_SERCOM6_SPI_INTENSET   (*(RwReg8 *)0x43000016UL) /**< \brief (SERCOM6) SPI Interrupt Enable Set */
#define REG_SERCOM6_SPI_INTFLAG    (*(RwReg8 *)0x43000018UL) /**< \brief (SERCOM6) SPI Interrupt Flag Status and Clear */
#define REG_SERCOM6_SPI_STATUS     (*(RwReg16*)0x4300001AUL) /**< \brief (SERCOM6) SPI Status */
#define REG_SERCOM6_SPI_SYNCBUSY   (*(RoReg  *)0x4300001CUL) /**< \brief (SERCOM6) SPI Synchronization Busy */
#define REG_SERCOM6_SPI_ADDR       (*(RwReg  *)0x43000024UL) /**< \brief (SERCOM6) SPI Address */
#define REG_SERCOM6_SPI_DATA       (*(RwReg  *)0x43000028UL) /**< \brief (SERCOM6) SPI Data */
#define REG_SERCOM6_SPI_DBGCTRL    (*(RwReg8 *)0x43000030UL) /**< \brief (SERCOM6) SPI Debug Control */
#define REG_SERCOM6_USART_CTRLA    (*(RwReg  *)0x43000000UL) /**< \brief (SERCOM6) USART Control A */
#define REG_SERCOM6_USART_CTRLB    (*(RwReg  *)0x43000004UL) /**< \brief (SERCOM6) USART Control B */
#define REG_SERCOM6_USART_CTRLC    (*(RwReg  *)0x43000008UL) /**< \brief (SERCOM6) USART Control C */
#define REG_SERCOM6_USART_BAUD     (*(RwReg16*)0x4300000CUL) /**< \brief (SERCOM6) USART Baud Rate */
#define REG_SERCOM6_USART_RXPL     (*(RwReg8 *)0x4300000EUL) /**< \brief (SERCOM6) USART Receive Pulse Length */
#define REG_SERCOM6_USART_INTENCLR (*(RwReg8 *)0x43000014UL) /**< \brief (SERCOM6) USART Interrupt Enable Clear */
#define REG_SERCOM6_USART_INTENSET (*(RwReg8 *)0x43000016UL) /**< \brief (SERCOM6) USART Interrupt Enable Set */
#define REG_SERCOM6_USART_INTFLAG  (*(RwReg8 *)0x43000018UL) /**< \brief (SERCOM6) USART Interrupt Flag Status and Clear */
#define REG_SERCOM6_USART_STATUS   (*(RwReg16*)0x4300001AUL) /**< \brief (SERCOM6) USART Status */
#define REG_SERCOM6_USART_SYNCBUSY (*(RoReg  *)0x4300001CUL) /**< \brief (SERCOM6) USART Synchronization Busy */
#define REG_SERCOM6_USART_DATA     (*(RwReg16*)0x43000028UL) /**< \brief (SERCOM6) USART Data */
#define REG_SERCOM6_USART_DBGCTRL  (*(RwReg8 *)0x43000030UL) /**< \brief (SERCOM6) USART Debug Control */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for SERCOM6 peripheral ========== */
#define SERCOM6_DMAC_ID_RX          49       // Index of DMA RX trigger
#define SERCOM6_DMAC_ID_TX          50       // Index of DMA TX trigger
#define SERCOM6_GCLK_ID_CORE        41      
#define SERCOM6_GCLK_ID_SLOW        18      
#define SERCOM6_INT_MSB             6       
#define SERCOM6_PMSB                3       

#endif /* _SAMC21_SERCOM6_INSTANCE_ */
