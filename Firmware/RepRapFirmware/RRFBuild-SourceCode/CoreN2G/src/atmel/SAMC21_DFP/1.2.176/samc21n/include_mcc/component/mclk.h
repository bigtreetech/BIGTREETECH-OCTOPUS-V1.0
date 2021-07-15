/**
 * \brief Component description for MCLK
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
 *
 * Subject to your compliance with these terms, you may use Microchip software and any derivatives
 * exclusively with Microchip products. It is your responsibility to comply with third party license
 * terms applicable to your use of third party software (including open source software) that may
 * accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
 * APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF
 * MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT
 * EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

/* file generated from device description version 2018-11-30T04:44:36Z */
#ifndef _SAMC21_MCLK_COMPONENT_H_
#define _SAMC21_MCLK_COMPONENT_H_

/* ************************************************************************** */
/*   SOFTWARE API DEFINITION FOR MCLK                                         */
/* ************************************************************************** */

/* -------- MCLK_INTENCLR : (MCLK Offset: 0x01) (R/W 8) Interrupt Enable Clear -------- */
#define MCLK_INTENCLR_RESETVALUE              _U_(0x00)                                            /**<  (MCLK_INTENCLR) Interrupt Enable Clear  Reset Value */

#define MCLK_INTENCLR_CKRDY_Pos               _U_(0)                                               /**< (MCLK_INTENCLR) Clock Ready Interrupt Enable Position */
#define MCLK_INTENCLR_CKRDY_Msk               (_U_(0x1) << MCLK_INTENCLR_CKRDY_Pos)                /**< (MCLK_INTENCLR) Clock Ready Interrupt Enable Mask */
#define MCLK_INTENCLR_CKRDY(value)            (MCLK_INTENCLR_CKRDY_Msk & ((value) << MCLK_INTENCLR_CKRDY_Pos))
#define MCLK_INTENCLR_Msk                     _U_(0x01)                                            /**< (MCLK_INTENCLR) Register Mask  */


/* -------- MCLK_INTENSET : (MCLK Offset: 0x02) (R/W 8) Interrupt Enable Set -------- */
#define MCLK_INTENSET_RESETVALUE              _U_(0x00)                                            /**<  (MCLK_INTENSET) Interrupt Enable Set  Reset Value */

#define MCLK_INTENSET_CKRDY_Pos               _U_(0)                                               /**< (MCLK_INTENSET) Clock Ready Interrupt Enable Position */
#define MCLK_INTENSET_CKRDY_Msk               (_U_(0x1) << MCLK_INTENSET_CKRDY_Pos)                /**< (MCLK_INTENSET) Clock Ready Interrupt Enable Mask */
#define MCLK_INTENSET_CKRDY(value)            (MCLK_INTENSET_CKRDY_Msk & ((value) << MCLK_INTENSET_CKRDY_Pos))
#define MCLK_INTENSET_Msk                     _U_(0x01)                                            /**< (MCLK_INTENSET) Register Mask  */


/* -------- MCLK_INTFLAG : (MCLK Offset: 0x03) (R/W 8) Interrupt Flag Status and Clear -------- */
#define MCLK_INTFLAG_RESETVALUE               _U_(0x01)                                            /**<  (MCLK_INTFLAG) Interrupt Flag Status and Clear  Reset Value */

#define MCLK_INTFLAG_CKRDY_Pos                _U_(0)                                               /**< (MCLK_INTFLAG) Clock Ready Position */
#define MCLK_INTFLAG_CKRDY_Msk                (_U_(0x1) << MCLK_INTFLAG_CKRDY_Pos)                 /**< (MCLK_INTFLAG) Clock Ready Mask */
#define MCLK_INTFLAG_CKRDY(value)             (MCLK_INTFLAG_CKRDY_Msk & ((value) << MCLK_INTFLAG_CKRDY_Pos))
#define MCLK_INTFLAG_Msk                      _U_(0x01)                                            /**< (MCLK_INTFLAG) Register Mask  */


/* -------- MCLK_CPUDIV : (MCLK Offset: 0x04) (R/W 8) CPU Clock Division -------- */
#define MCLK_CPUDIV_RESETVALUE                _U_(0x01)                                            /**<  (MCLK_CPUDIV) CPU Clock Division  Reset Value */

#define MCLK_CPUDIV_CPUDIV_Pos                _U_(0)                                               /**< (MCLK_CPUDIV) CPU Clock Division Factor Position */
#define MCLK_CPUDIV_CPUDIV_Msk                (_U_(0xFF) << MCLK_CPUDIV_CPUDIV_Pos)                /**< (MCLK_CPUDIV) CPU Clock Division Factor Mask */
#define MCLK_CPUDIV_CPUDIV(value)             (MCLK_CPUDIV_CPUDIV_Msk & ((value) << MCLK_CPUDIV_CPUDIV_Pos))
#define   MCLK_CPUDIV_CPUDIV_DIV1_Val         _U_(0x1)                                             /**< (MCLK_CPUDIV) Divide by 1  */
#define   MCLK_CPUDIV_CPUDIV_DIV2_Val         _U_(0x2)                                             /**< (MCLK_CPUDIV) Divide by 2  */
#define   MCLK_CPUDIV_CPUDIV_DIV4_Val         _U_(0x4)                                             /**< (MCLK_CPUDIV) Divide by 4  */
#define   MCLK_CPUDIV_CPUDIV_DIV8_Val         _U_(0x8)                                             /**< (MCLK_CPUDIV) Divide by 8  */
#define   MCLK_CPUDIV_CPUDIV_DIV16_Val        _U_(0x10)                                            /**< (MCLK_CPUDIV) Divide by 16  */
#define   MCLK_CPUDIV_CPUDIV_DIV32_Val        _U_(0x20)                                            /**< (MCLK_CPUDIV) Divide by 32  */
#define   MCLK_CPUDIV_CPUDIV_DIV64_Val        _U_(0x40)                                            /**< (MCLK_CPUDIV) Divide by 64  */
#define   MCLK_CPUDIV_CPUDIV_DIV128_Val       _U_(0x80)                                            /**< (MCLK_CPUDIV) Divide by 128  */
#define MCLK_CPUDIV_CPUDIV_DIV1               (MCLK_CPUDIV_CPUDIV_DIV1_Val << MCLK_CPUDIV_CPUDIV_Pos) /**< (MCLK_CPUDIV) Divide by 1 Position  */
#define MCLK_CPUDIV_CPUDIV_DIV2               (MCLK_CPUDIV_CPUDIV_DIV2_Val << MCLK_CPUDIV_CPUDIV_Pos) /**< (MCLK_CPUDIV) Divide by 2 Position  */
#define MCLK_CPUDIV_CPUDIV_DIV4               (MCLK_CPUDIV_CPUDIV_DIV4_Val << MCLK_CPUDIV_CPUDIV_Pos) /**< (MCLK_CPUDIV) Divide by 4 Position  */
#define MCLK_CPUDIV_CPUDIV_DIV8               (MCLK_CPUDIV_CPUDIV_DIV8_Val << MCLK_CPUDIV_CPUDIV_Pos) /**< (MCLK_CPUDIV) Divide by 8 Position  */
#define MCLK_CPUDIV_CPUDIV_DIV16              (MCLK_CPUDIV_CPUDIV_DIV16_Val << MCLK_CPUDIV_CPUDIV_Pos) /**< (MCLK_CPUDIV) Divide by 16 Position  */
#define MCLK_CPUDIV_CPUDIV_DIV32              (MCLK_CPUDIV_CPUDIV_DIV32_Val << MCLK_CPUDIV_CPUDIV_Pos) /**< (MCLK_CPUDIV) Divide by 32 Position  */
#define MCLK_CPUDIV_CPUDIV_DIV64              (MCLK_CPUDIV_CPUDIV_DIV64_Val << MCLK_CPUDIV_CPUDIV_Pos) /**< (MCLK_CPUDIV) Divide by 64 Position  */
#define MCLK_CPUDIV_CPUDIV_DIV128             (MCLK_CPUDIV_CPUDIV_DIV128_Val << MCLK_CPUDIV_CPUDIV_Pos) /**< (MCLK_CPUDIV) Divide by 128 Position  */
#define MCLK_CPUDIV_Msk                       _U_(0xFF)                                            /**< (MCLK_CPUDIV) Register Mask  */


/* -------- MCLK_AHBMASK : (MCLK Offset: 0x10) (R/W 32) AHB Mask -------- */
#define MCLK_AHBMASK_RESETVALUE               _U_(0x3CFF)                                          /**<  (MCLK_AHBMASK) AHB Mask  Reset Value */

#define MCLK_AHBMASK_HPB0_Pos                 _U_(0)                                               /**< (MCLK_AHBMASK) HPB0 AHB Clock Mask Position */
#define MCLK_AHBMASK_HPB0_Msk                 (_U_(0x1) << MCLK_AHBMASK_HPB0_Pos)                  /**< (MCLK_AHBMASK) HPB0 AHB Clock Mask Mask */
#define MCLK_AHBMASK_HPB0(value)              (MCLK_AHBMASK_HPB0_Msk & ((value) << MCLK_AHBMASK_HPB0_Pos))
#define MCLK_AHBMASK_HPB1_Pos                 _U_(1)                                               /**< (MCLK_AHBMASK) HPB1 AHB Clock Mask Position */
#define MCLK_AHBMASK_HPB1_Msk                 (_U_(0x1) << MCLK_AHBMASK_HPB1_Pos)                  /**< (MCLK_AHBMASK) HPB1 AHB Clock Mask Mask */
#define MCLK_AHBMASK_HPB1(value)              (MCLK_AHBMASK_HPB1_Msk & ((value) << MCLK_AHBMASK_HPB1_Pos))
#define MCLK_AHBMASK_HPB2_Pos                 _U_(2)                                               /**< (MCLK_AHBMASK) HPB2 AHB Clock Mask Position */
#define MCLK_AHBMASK_HPB2_Msk                 (_U_(0x1) << MCLK_AHBMASK_HPB2_Pos)                  /**< (MCLK_AHBMASK) HPB2 AHB Clock Mask Mask */
#define MCLK_AHBMASK_HPB2(value)              (MCLK_AHBMASK_HPB2_Msk & ((value) << MCLK_AHBMASK_HPB2_Pos))
#define MCLK_AHBMASK_DSU_Pos                  _U_(3)                                               /**< (MCLK_AHBMASK) DSU AHB Clock Mask Position */
#define MCLK_AHBMASK_DSU_Msk                  (_U_(0x1) << MCLK_AHBMASK_DSU_Pos)                   /**< (MCLK_AHBMASK) DSU AHB Clock Mask Mask */
#define MCLK_AHBMASK_DSU(value)               (MCLK_AHBMASK_DSU_Msk & ((value) << MCLK_AHBMASK_DSU_Pos))
#define MCLK_AHBMASK_HMATRIXHS_Pos            _U_(4)                                               /**< (MCLK_AHBMASK) HMATRIXHS AHB Clock Mask Position */
#define MCLK_AHBMASK_HMATRIXHS_Msk            (_U_(0x1) << MCLK_AHBMASK_HMATRIXHS_Pos)             /**< (MCLK_AHBMASK) HMATRIXHS AHB Clock Mask Mask */
#define MCLK_AHBMASK_HMATRIXHS(value)         (MCLK_AHBMASK_HMATRIXHS_Msk & ((value) << MCLK_AHBMASK_HMATRIXHS_Pos))
#define MCLK_AHBMASK_NVMCTRL_Pos              _U_(5)                                               /**< (MCLK_AHBMASK) NVMCTRL AHB Clock Mask Position */
#define MCLK_AHBMASK_NVMCTRL_Msk              (_U_(0x1) << MCLK_AHBMASK_NVMCTRL_Pos)               /**< (MCLK_AHBMASK) NVMCTRL AHB Clock Mask Mask */
#define MCLK_AHBMASK_NVMCTRL(value)           (MCLK_AHBMASK_NVMCTRL_Msk & ((value) << MCLK_AHBMASK_NVMCTRL_Pos))
#define MCLK_AHBMASK_HSRAM_Pos                _U_(6)                                               /**< (MCLK_AHBMASK) HSRAM AHB Clock Mask Position */
#define MCLK_AHBMASK_HSRAM_Msk                (_U_(0x1) << MCLK_AHBMASK_HSRAM_Pos)                 /**< (MCLK_AHBMASK) HSRAM AHB Clock Mask Mask */
#define MCLK_AHBMASK_HSRAM(value)             (MCLK_AHBMASK_HSRAM_Msk & ((value) << MCLK_AHBMASK_HSRAM_Pos))
#define MCLK_AHBMASK_DMAC_Pos                 _U_(7)                                               /**< (MCLK_AHBMASK) DMAC AHB Clock Mask Position */
#define MCLK_AHBMASK_DMAC_Msk                 (_U_(0x1) << MCLK_AHBMASK_DMAC_Pos)                  /**< (MCLK_AHBMASK) DMAC AHB Clock Mask Mask */
#define MCLK_AHBMASK_DMAC(value)              (MCLK_AHBMASK_DMAC_Msk & ((value) << MCLK_AHBMASK_DMAC_Pos))
#define MCLK_AHBMASK_CAN0_Pos                 _U_(8)                                               /**< (MCLK_AHBMASK) CAN0 AHB Clock Mask Position */
#define MCLK_AHBMASK_CAN0_Msk                 (_U_(0x1) << MCLK_AHBMASK_CAN0_Pos)                  /**< (MCLK_AHBMASK) CAN0 AHB Clock Mask Mask */
#define MCLK_AHBMASK_CAN0(value)              (MCLK_AHBMASK_CAN0_Msk & ((value) << MCLK_AHBMASK_CAN0_Pos))
#define MCLK_AHBMASK_CAN1_Pos                 _U_(9)                                               /**< (MCLK_AHBMASK) CAN1 AHB Clock Mask Position */
#define MCLK_AHBMASK_CAN1_Msk                 (_U_(0x1) << MCLK_AHBMASK_CAN1_Pos)                  /**< (MCLK_AHBMASK) CAN1 AHB Clock Mask Mask */
#define MCLK_AHBMASK_CAN1(value)              (MCLK_AHBMASK_CAN1_Msk & ((value) << MCLK_AHBMASK_CAN1_Pos))
#define MCLK_AHBMASK_PAC_Pos                  _U_(10)                                              /**< (MCLK_AHBMASK) PAC AHB Clock Mask Position */
#define MCLK_AHBMASK_PAC_Msk                  (_U_(0x1) << MCLK_AHBMASK_PAC_Pos)                   /**< (MCLK_AHBMASK) PAC AHB Clock Mask Mask */
#define MCLK_AHBMASK_PAC(value)               (MCLK_AHBMASK_PAC_Msk & ((value) << MCLK_AHBMASK_PAC_Pos))
#define MCLK_AHBMASK_NVMCTRL_PICACHU_Pos      _U_(11)                                              /**< (MCLK_AHBMASK) NVMCTRL_PICACHU AHB Clock Mask Position */
#define MCLK_AHBMASK_NVMCTRL_PICACHU_Msk      (_U_(0x1) << MCLK_AHBMASK_NVMCTRL_PICACHU_Pos)       /**< (MCLK_AHBMASK) NVMCTRL_PICACHU AHB Clock Mask Mask */
#define MCLK_AHBMASK_NVMCTRL_PICACHU(value)   (MCLK_AHBMASK_NVMCTRL_PICACHU_Msk & ((value) << MCLK_AHBMASK_NVMCTRL_PICACHU_Pos))
#define MCLK_AHBMASK_DIVAS_Pos                _U_(12)                                              /**< (MCLK_AHBMASK) DIVAS AHB Clock Mask Position */
#define MCLK_AHBMASK_DIVAS_Msk                (_U_(0x1) << MCLK_AHBMASK_DIVAS_Pos)                 /**< (MCLK_AHBMASK) DIVAS AHB Clock Mask Mask */
#define MCLK_AHBMASK_DIVAS(value)             (MCLK_AHBMASK_DIVAS_Msk & ((value) << MCLK_AHBMASK_DIVAS_Pos))
#define MCLK_AHBMASK_HPB3_Pos                 _U_(13)                                              /**< (MCLK_AHBMASK) HPB3 AHB Clock Mask Position */
#define MCLK_AHBMASK_HPB3_Msk                 (_U_(0x1) << MCLK_AHBMASK_HPB3_Pos)                  /**< (MCLK_AHBMASK) HPB3 AHB Clock Mask Mask */
#define MCLK_AHBMASK_HPB3(value)              (MCLK_AHBMASK_HPB3_Msk & ((value) << MCLK_AHBMASK_HPB3_Pos))
#define MCLK_AHBMASK_Msk                      _U_(0x00003FFF)                                      /**< (MCLK_AHBMASK) Register Mask  */

#define MCLK_AHBMASK_CAN_Pos                  _U_(8)                                               /**< (MCLK_AHBMASK Position) CANx AHB Clock Mask */
#define MCLK_AHBMASK_CAN_Msk                  (_U_(0x3) << MCLK_AHBMASK_CAN_Pos)                   /**< (MCLK_AHBMASK Mask) CAN */
#define MCLK_AHBMASK_CAN(value)               (MCLK_AHBMASK_CAN_Msk & ((value) << MCLK_AHBMASK_CAN_Pos)) 

/* -------- MCLK_APBAMASK : (MCLK Offset: 0x14) (R/W 32) APBA Mask -------- */
#define MCLK_APBAMASK_RESETVALUE              _U_(0xFFF)                                           /**<  (MCLK_APBAMASK) APBA Mask  Reset Value */

#define MCLK_APBAMASK_PAC_Pos                 _U_(0)                                               /**< (MCLK_APBAMASK) PAC APB Clock Enable Position */
#define MCLK_APBAMASK_PAC_Msk                 (_U_(0x1) << MCLK_APBAMASK_PAC_Pos)                  /**< (MCLK_APBAMASK) PAC APB Clock Enable Mask */
#define MCLK_APBAMASK_PAC(value)              (MCLK_APBAMASK_PAC_Msk & ((value) << MCLK_APBAMASK_PAC_Pos))
#define MCLK_APBAMASK_PM_Pos                  _U_(1)                                               /**< (MCLK_APBAMASK) PM APB Clock Enable Position */
#define MCLK_APBAMASK_PM_Msk                  (_U_(0x1) << MCLK_APBAMASK_PM_Pos)                   /**< (MCLK_APBAMASK) PM APB Clock Enable Mask */
#define MCLK_APBAMASK_PM(value)               (MCLK_APBAMASK_PM_Msk & ((value) << MCLK_APBAMASK_PM_Pos))
#define MCLK_APBAMASK_MCLK_Pos                _U_(2)                                               /**< (MCLK_APBAMASK) MCLK APB Clock Enable Position */
#define MCLK_APBAMASK_MCLK_Msk                (_U_(0x1) << MCLK_APBAMASK_MCLK_Pos)                 /**< (MCLK_APBAMASK) MCLK APB Clock Enable Mask */
#define MCLK_APBAMASK_MCLK(value)             (MCLK_APBAMASK_MCLK_Msk & ((value) << MCLK_APBAMASK_MCLK_Pos))
#define MCLK_APBAMASK_RSTC_Pos                _U_(3)                                               /**< (MCLK_APBAMASK) RSTC APB Clock Enable Position */
#define MCLK_APBAMASK_RSTC_Msk                (_U_(0x1) << MCLK_APBAMASK_RSTC_Pos)                 /**< (MCLK_APBAMASK) RSTC APB Clock Enable Mask */
#define MCLK_APBAMASK_RSTC(value)             (MCLK_APBAMASK_RSTC_Msk & ((value) << MCLK_APBAMASK_RSTC_Pos))
#define MCLK_APBAMASK_OSCCTRL_Pos             _U_(4)                                               /**< (MCLK_APBAMASK) OSCCTRL APB Clock Enable Position */
#define MCLK_APBAMASK_OSCCTRL_Msk             (_U_(0x1) << MCLK_APBAMASK_OSCCTRL_Pos)              /**< (MCLK_APBAMASK) OSCCTRL APB Clock Enable Mask */
#define MCLK_APBAMASK_OSCCTRL(value)          (MCLK_APBAMASK_OSCCTRL_Msk & ((value) << MCLK_APBAMASK_OSCCTRL_Pos))
#define MCLK_APBAMASK_OSC32KCTRL_Pos          _U_(5)                                               /**< (MCLK_APBAMASK) OSC32KCTRL APB Clock Enable Position */
#define MCLK_APBAMASK_OSC32KCTRL_Msk          (_U_(0x1) << MCLK_APBAMASK_OSC32KCTRL_Pos)           /**< (MCLK_APBAMASK) OSC32KCTRL APB Clock Enable Mask */
#define MCLK_APBAMASK_OSC32KCTRL(value)       (MCLK_APBAMASK_OSC32KCTRL_Msk & ((value) << MCLK_APBAMASK_OSC32KCTRL_Pos))
#define MCLK_APBAMASK_SUPC_Pos                _U_(6)                                               /**< (MCLK_APBAMASK) SUPC APB Clock Enable Position */
#define MCLK_APBAMASK_SUPC_Msk                (_U_(0x1) << MCLK_APBAMASK_SUPC_Pos)                 /**< (MCLK_APBAMASK) SUPC APB Clock Enable Mask */
#define MCLK_APBAMASK_SUPC(value)             (MCLK_APBAMASK_SUPC_Msk & ((value) << MCLK_APBAMASK_SUPC_Pos))
#define MCLK_APBAMASK_GCLK_Pos                _U_(7)                                               /**< (MCLK_APBAMASK) GCLK APB Clock Enable Position */
#define MCLK_APBAMASK_GCLK_Msk                (_U_(0x1) << MCLK_APBAMASK_GCLK_Pos)                 /**< (MCLK_APBAMASK) GCLK APB Clock Enable Mask */
#define MCLK_APBAMASK_GCLK(value)             (MCLK_APBAMASK_GCLK_Msk & ((value) << MCLK_APBAMASK_GCLK_Pos))
#define MCLK_APBAMASK_WDT_Pos                 _U_(8)                                               /**< (MCLK_APBAMASK) WDT APB Clock Enable Position */
#define MCLK_APBAMASK_WDT_Msk                 (_U_(0x1) << MCLK_APBAMASK_WDT_Pos)                  /**< (MCLK_APBAMASK) WDT APB Clock Enable Mask */
#define MCLK_APBAMASK_WDT(value)              (MCLK_APBAMASK_WDT_Msk & ((value) << MCLK_APBAMASK_WDT_Pos))
#define MCLK_APBAMASK_RTC_Pos                 _U_(9)                                               /**< (MCLK_APBAMASK) RTC APB Clock Enable Position */
#define MCLK_APBAMASK_RTC_Msk                 (_U_(0x1) << MCLK_APBAMASK_RTC_Pos)                  /**< (MCLK_APBAMASK) RTC APB Clock Enable Mask */
#define MCLK_APBAMASK_RTC(value)              (MCLK_APBAMASK_RTC_Msk & ((value) << MCLK_APBAMASK_RTC_Pos))
#define MCLK_APBAMASK_EIC_Pos                 _U_(10)                                              /**< (MCLK_APBAMASK) EIC APB Clock Enable Position */
#define MCLK_APBAMASK_EIC_Msk                 (_U_(0x1) << MCLK_APBAMASK_EIC_Pos)                  /**< (MCLK_APBAMASK) EIC APB Clock Enable Mask */
#define MCLK_APBAMASK_EIC(value)              (MCLK_APBAMASK_EIC_Msk & ((value) << MCLK_APBAMASK_EIC_Pos))
#define MCLK_APBAMASK_FREQM_Pos               _U_(11)                                              /**< (MCLK_APBAMASK) FREQM APB Clock Enable Position */
#define MCLK_APBAMASK_FREQM_Msk               (_U_(0x1) << MCLK_APBAMASK_FREQM_Pos)                /**< (MCLK_APBAMASK) FREQM APB Clock Enable Mask */
#define MCLK_APBAMASK_FREQM(value)            (MCLK_APBAMASK_FREQM_Msk & ((value) << MCLK_APBAMASK_FREQM_Pos))
#define MCLK_APBAMASK_TSENS_Pos               _U_(12)                                              /**< (MCLK_APBAMASK) TSENS APB Clock Enable Position */
#define MCLK_APBAMASK_TSENS_Msk               (_U_(0x1) << MCLK_APBAMASK_TSENS_Pos)                /**< (MCLK_APBAMASK) TSENS APB Clock Enable Mask */
#define MCLK_APBAMASK_TSENS(value)            (MCLK_APBAMASK_TSENS_Msk & ((value) << MCLK_APBAMASK_TSENS_Pos))
#define MCLK_APBAMASK_Msk                     _U_(0x00001FFF)                                      /**< (MCLK_APBAMASK) Register Mask  */


/* -------- MCLK_APBBMASK : (MCLK Offset: 0x18) (R/W 32) APBB Mask -------- */
#define MCLK_APBBMASK_RESETVALUE              _U_(0x07)                                            /**<  (MCLK_APBBMASK) APBB Mask  Reset Value */

#define MCLK_APBBMASK_PORT_Pos                _U_(0)                                               /**< (MCLK_APBBMASK) PORT APB Clock Enable Position */
#define MCLK_APBBMASK_PORT_Msk                (_U_(0x1) << MCLK_APBBMASK_PORT_Pos)                 /**< (MCLK_APBBMASK) PORT APB Clock Enable Mask */
#define MCLK_APBBMASK_PORT(value)             (MCLK_APBBMASK_PORT_Msk & ((value) << MCLK_APBBMASK_PORT_Pos))
#define MCLK_APBBMASK_DSU_Pos                 _U_(1)                                               /**< (MCLK_APBBMASK) DSU APB Clock Enable Position */
#define MCLK_APBBMASK_DSU_Msk                 (_U_(0x1) << MCLK_APBBMASK_DSU_Pos)                  /**< (MCLK_APBBMASK) DSU APB Clock Enable Mask */
#define MCLK_APBBMASK_DSU(value)              (MCLK_APBBMASK_DSU_Msk & ((value) << MCLK_APBBMASK_DSU_Pos))
#define MCLK_APBBMASK_NVMCTRL_Pos             _U_(2)                                               /**< (MCLK_APBBMASK) NVMCTRL APB Clock Enable Position */
#define MCLK_APBBMASK_NVMCTRL_Msk             (_U_(0x1) << MCLK_APBBMASK_NVMCTRL_Pos)              /**< (MCLK_APBBMASK) NVMCTRL APB Clock Enable Mask */
#define MCLK_APBBMASK_NVMCTRL(value)          (MCLK_APBBMASK_NVMCTRL_Msk & ((value) << MCLK_APBBMASK_NVMCTRL_Pos))
#define MCLK_APBBMASK_HMATRIXHS_Pos           _U_(5)                                               /**< (MCLK_APBBMASK) HMATRIXHS APB Clock Enable Position */
#define MCLK_APBBMASK_HMATRIXHS_Msk           (_U_(0x1) << MCLK_APBBMASK_HMATRIXHS_Pos)            /**< (MCLK_APBBMASK) HMATRIXHS APB Clock Enable Mask */
#define MCLK_APBBMASK_HMATRIXHS(value)        (MCLK_APBBMASK_HMATRIXHS_Msk & ((value) << MCLK_APBBMASK_HMATRIXHS_Pos))
#define MCLK_APBBMASK_Msk                     _U_(0x00000027)                                      /**< (MCLK_APBBMASK) Register Mask  */


/* -------- MCLK_APBCMASK : (MCLK Offset: 0x1C) (R/W 32) APBC Mask -------- */
#define MCLK_APBCMASK_RESETVALUE              _U_(0x00)                                            /**<  (MCLK_APBCMASK) APBC Mask  Reset Value */

#define MCLK_APBCMASK_EVSYS_Pos               _U_(0)                                               /**< (MCLK_APBCMASK) EVSYS APB Clock Enable Position */
#define MCLK_APBCMASK_EVSYS_Msk               (_U_(0x1) << MCLK_APBCMASK_EVSYS_Pos)                /**< (MCLK_APBCMASK) EVSYS APB Clock Enable Mask */
#define MCLK_APBCMASK_EVSYS(value)            (MCLK_APBCMASK_EVSYS_Msk & ((value) << MCLK_APBCMASK_EVSYS_Pos))
#define MCLK_APBCMASK_SERCOM0_Pos             _U_(1)                                               /**< (MCLK_APBCMASK) SERCOM0 APB Clock Enable Position */
#define MCLK_APBCMASK_SERCOM0_Msk             (_U_(0x1) << MCLK_APBCMASK_SERCOM0_Pos)              /**< (MCLK_APBCMASK) SERCOM0 APB Clock Enable Mask */
#define MCLK_APBCMASK_SERCOM0(value)          (MCLK_APBCMASK_SERCOM0_Msk & ((value) << MCLK_APBCMASK_SERCOM0_Pos))
#define MCLK_APBCMASK_SERCOM1_Pos             _U_(2)                                               /**< (MCLK_APBCMASK) SERCOM1 APB Clock Enable Position */
#define MCLK_APBCMASK_SERCOM1_Msk             (_U_(0x1) << MCLK_APBCMASK_SERCOM1_Pos)              /**< (MCLK_APBCMASK) SERCOM1 APB Clock Enable Mask */
#define MCLK_APBCMASK_SERCOM1(value)          (MCLK_APBCMASK_SERCOM1_Msk & ((value) << MCLK_APBCMASK_SERCOM1_Pos))
#define MCLK_APBCMASK_SERCOM2_Pos             _U_(3)                                               /**< (MCLK_APBCMASK) SERCOM2 APB Clock Enable Position */
#define MCLK_APBCMASK_SERCOM2_Msk             (_U_(0x1) << MCLK_APBCMASK_SERCOM2_Pos)              /**< (MCLK_APBCMASK) SERCOM2 APB Clock Enable Mask */
#define MCLK_APBCMASK_SERCOM2(value)          (MCLK_APBCMASK_SERCOM2_Msk & ((value) << MCLK_APBCMASK_SERCOM2_Pos))
#define MCLK_APBCMASK_SERCOM3_Pos             _U_(4)                                               /**< (MCLK_APBCMASK) SERCOM3 APB Clock Enable Position */
#define MCLK_APBCMASK_SERCOM3_Msk             (_U_(0x1) << MCLK_APBCMASK_SERCOM3_Pos)              /**< (MCLK_APBCMASK) SERCOM3 APB Clock Enable Mask */
#define MCLK_APBCMASK_SERCOM3(value)          (MCLK_APBCMASK_SERCOM3_Msk & ((value) << MCLK_APBCMASK_SERCOM3_Pos))
#define MCLK_APBCMASK_SERCOM4_Pos             _U_(5)                                               /**< (MCLK_APBCMASK) SERCOM4 APB Clock Enable Position */
#define MCLK_APBCMASK_SERCOM4_Msk             (_U_(0x1) << MCLK_APBCMASK_SERCOM4_Pos)              /**< (MCLK_APBCMASK) SERCOM4 APB Clock Enable Mask */
#define MCLK_APBCMASK_SERCOM4(value)          (MCLK_APBCMASK_SERCOM4_Msk & ((value) << MCLK_APBCMASK_SERCOM4_Pos))
#define MCLK_APBCMASK_SERCOM5_Pos             _U_(6)                                               /**< (MCLK_APBCMASK) SERCOM5 APB Clock Enable Position */
#define MCLK_APBCMASK_SERCOM5_Msk             (_U_(0x1) << MCLK_APBCMASK_SERCOM5_Pos)              /**< (MCLK_APBCMASK) SERCOM5 APB Clock Enable Mask */
#define MCLK_APBCMASK_SERCOM5(value)          (MCLK_APBCMASK_SERCOM5_Msk & ((value) << MCLK_APBCMASK_SERCOM5_Pos))
#define MCLK_APBCMASK_TCC0_Pos                _U_(9)                                               /**< (MCLK_APBCMASK) TCC0 APB Clock Enable Position */
#define MCLK_APBCMASK_TCC0_Msk                (_U_(0x1) << MCLK_APBCMASK_TCC0_Pos)                 /**< (MCLK_APBCMASK) TCC0 APB Clock Enable Mask */
#define MCLK_APBCMASK_TCC0(value)             (MCLK_APBCMASK_TCC0_Msk & ((value) << MCLK_APBCMASK_TCC0_Pos))
#define MCLK_APBCMASK_TCC1_Pos                _U_(10)                                              /**< (MCLK_APBCMASK) TCC1 APB Clock Enable Position */
#define MCLK_APBCMASK_TCC1_Msk                (_U_(0x1) << MCLK_APBCMASK_TCC1_Pos)                 /**< (MCLK_APBCMASK) TCC1 APB Clock Enable Mask */
#define MCLK_APBCMASK_TCC1(value)             (MCLK_APBCMASK_TCC1_Msk & ((value) << MCLK_APBCMASK_TCC1_Pos))
#define MCLK_APBCMASK_TCC2_Pos                _U_(11)                                              /**< (MCLK_APBCMASK) TCC2 APB Clock Enable Position */
#define MCLK_APBCMASK_TCC2_Msk                (_U_(0x1) << MCLK_APBCMASK_TCC2_Pos)                 /**< (MCLK_APBCMASK) TCC2 APB Clock Enable Mask */
#define MCLK_APBCMASK_TCC2(value)             (MCLK_APBCMASK_TCC2_Msk & ((value) << MCLK_APBCMASK_TCC2_Pos))
#define MCLK_APBCMASK_TC0_Pos                 _U_(12)                                              /**< (MCLK_APBCMASK) TC0 APB Clock Enable Position */
#define MCLK_APBCMASK_TC0_Msk                 (_U_(0x1) << MCLK_APBCMASK_TC0_Pos)                  /**< (MCLK_APBCMASK) TC0 APB Clock Enable Mask */
#define MCLK_APBCMASK_TC0(value)              (MCLK_APBCMASK_TC0_Msk & ((value) << MCLK_APBCMASK_TC0_Pos))
#define MCLK_APBCMASK_TC1_Pos                 _U_(13)                                              /**< (MCLK_APBCMASK) TC1 APB Clock Enable Position */
#define MCLK_APBCMASK_TC1_Msk                 (_U_(0x1) << MCLK_APBCMASK_TC1_Pos)                  /**< (MCLK_APBCMASK) TC1 APB Clock Enable Mask */
#define MCLK_APBCMASK_TC1(value)              (MCLK_APBCMASK_TC1_Msk & ((value) << MCLK_APBCMASK_TC1_Pos))
#define MCLK_APBCMASK_TC2_Pos                 _U_(14)                                              /**< (MCLK_APBCMASK) TC2 APB Clock Enable Position */
#define MCLK_APBCMASK_TC2_Msk                 (_U_(0x1) << MCLK_APBCMASK_TC2_Pos)                  /**< (MCLK_APBCMASK) TC2 APB Clock Enable Mask */
#define MCLK_APBCMASK_TC2(value)              (MCLK_APBCMASK_TC2_Msk & ((value) << MCLK_APBCMASK_TC2_Pos))
#define MCLK_APBCMASK_TC3_Pos                 _U_(15)                                              /**< (MCLK_APBCMASK) TC3 APB Clock Enable Position */
#define MCLK_APBCMASK_TC3_Msk                 (_U_(0x1) << MCLK_APBCMASK_TC3_Pos)                  /**< (MCLK_APBCMASK) TC3 APB Clock Enable Mask */
#define MCLK_APBCMASK_TC3(value)              (MCLK_APBCMASK_TC3_Msk & ((value) << MCLK_APBCMASK_TC3_Pos))
#define MCLK_APBCMASK_TC4_Pos                 _U_(16)                                              /**< (MCLK_APBCMASK) TC4 APB Clock Enable Position */
#define MCLK_APBCMASK_TC4_Msk                 (_U_(0x1) << MCLK_APBCMASK_TC4_Pos)                  /**< (MCLK_APBCMASK) TC4 APB Clock Enable Mask */
#define MCLK_APBCMASK_TC4(value)              (MCLK_APBCMASK_TC4_Msk & ((value) << MCLK_APBCMASK_TC4_Pos))
#define MCLK_APBCMASK_ADC0_Pos                _U_(17)                                              /**< (MCLK_APBCMASK) ADC0 APB Clock Enable Position */
#define MCLK_APBCMASK_ADC0_Msk                (_U_(0x1) << MCLK_APBCMASK_ADC0_Pos)                 /**< (MCLK_APBCMASK) ADC0 APB Clock Enable Mask */
#define MCLK_APBCMASK_ADC0(value)             (MCLK_APBCMASK_ADC0_Msk & ((value) << MCLK_APBCMASK_ADC0_Pos))
#define MCLK_APBCMASK_ADC1_Pos                _U_(18)                                              /**< (MCLK_APBCMASK) ADC1 APB Clock Enable Position */
#define MCLK_APBCMASK_ADC1_Msk                (_U_(0x1) << MCLK_APBCMASK_ADC1_Pos)                 /**< (MCLK_APBCMASK) ADC1 APB Clock Enable Mask */
#define MCLK_APBCMASK_ADC1(value)             (MCLK_APBCMASK_ADC1_Msk & ((value) << MCLK_APBCMASK_ADC1_Pos))
#define MCLK_APBCMASK_SDADC_Pos               _U_(19)                                              /**< (MCLK_APBCMASK) SDADC APB Clock Enable Position */
#define MCLK_APBCMASK_SDADC_Msk               (_U_(0x1) << MCLK_APBCMASK_SDADC_Pos)                /**< (MCLK_APBCMASK) SDADC APB Clock Enable Mask */
#define MCLK_APBCMASK_SDADC(value)            (MCLK_APBCMASK_SDADC_Msk & ((value) << MCLK_APBCMASK_SDADC_Pos))
#define MCLK_APBCMASK_AC_Pos                  _U_(20)                                              /**< (MCLK_APBCMASK) AC APB Clock Enable Position */
#define MCLK_APBCMASK_AC_Msk                  (_U_(0x1) << MCLK_APBCMASK_AC_Pos)                   /**< (MCLK_APBCMASK) AC APB Clock Enable Mask */
#define MCLK_APBCMASK_AC(value)               (MCLK_APBCMASK_AC_Msk & ((value) << MCLK_APBCMASK_AC_Pos))
#define MCLK_APBCMASK_DAC_Pos                 _U_(21)                                              /**< (MCLK_APBCMASK) DAC APB Clock Enable Position */
#define MCLK_APBCMASK_DAC_Msk                 (_U_(0x1) << MCLK_APBCMASK_DAC_Pos)                  /**< (MCLK_APBCMASK) DAC APB Clock Enable Mask */
#define MCLK_APBCMASK_DAC(value)              (MCLK_APBCMASK_DAC_Msk & ((value) << MCLK_APBCMASK_DAC_Pos))
#define MCLK_APBCMASK_PTC_Pos                 _U_(22)                                              /**< (MCLK_APBCMASK) PTC APB Clock Enable Position */
#define MCLK_APBCMASK_PTC_Msk                 (_U_(0x1) << MCLK_APBCMASK_PTC_Pos)                  /**< (MCLK_APBCMASK) PTC APB Clock Enable Mask */
#define MCLK_APBCMASK_PTC(value)              (MCLK_APBCMASK_PTC_Msk & ((value) << MCLK_APBCMASK_PTC_Pos))
#define MCLK_APBCMASK_CCL_Pos                 _U_(23)                                              /**< (MCLK_APBCMASK) CCL APB Clock Enable Position */
#define MCLK_APBCMASK_CCL_Msk                 (_U_(0x1) << MCLK_APBCMASK_CCL_Pos)                  /**< (MCLK_APBCMASK) CCL APB Clock Enable Mask */
#define MCLK_APBCMASK_CCL(value)              (MCLK_APBCMASK_CCL_Msk & ((value) << MCLK_APBCMASK_CCL_Pos))
#define MCLK_APBCMASK_Msk                     _U_(0x00FFFE7F)                                      /**< (MCLK_APBCMASK) Register Mask  */

#define MCLK_APBCMASK_SERCOM_Pos              _U_(1)                                               /**< (MCLK_APBCMASK Position) SERCOMx APB Clock Enable */
#define MCLK_APBCMASK_SERCOM_Msk              (_U_(0x3F) << MCLK_APBCMASK_SERCOM_Pos)              /**< (MCLK_APBCMASK Mask) SERCOM */
#define MCLK_APBCMASK_SERCOM(value)           (MCLK_APBCMASK_SERCOM_Msk & ((value) << MCLK_APBCMASK_SERCOM_Pos)) 
#define MCLK_APBCMASK_TCC_Pos                 _U_(9)                                               /**< (MCLK_APBCMASK Position) TCCx APB Clock Enable */
#define MCLK_APBCMASK_TCC_Msk                 (_U_(0x7) << MCLK_APBCMASK_TCC_Pos)                  /**< (MCLK_APBCMASK Mask) TCC */
#define MCLK_APBCMASK_TCC(value)              (MCLK_APBCMASK_TCC_Msk & ((value) << MCLK_APBCMASK_TCC_Pos)) 
#define MCLK_APBCMASK_TC_Pos                  _U_(12)                                              /**< (MCLK_APBCMASK Position) TCx APB Clock Enable */
#define MCLK_APBCMASK_TC_Msk                  (_U_(0x1F) << MCLK_APBCMASK_TC_Pos)                  /**< (MCLK_APBCMASK Mask) TC */
#define MCLK_APBCMASK_TC(value)               (MCLK_APBCMASK_TC_Msk & ((value) << MCLK_APBCMASK_TC_Pos)) 
#define MCLK_APBCMASK_ADC_Pos                 _U_(17)                                              /**< (MCLK_APBCMASK Position) ADCx APB Clock Enable */
#define MCLK_APBCMASK_ADC_Msk                 (_U_(0x3) << MCLK_APBCMASK_ADC_Pos)                  /**< (MCLK_APBCMASK Mask) ADC */
#define MCLK_APBCMASK_ADC(value)              (MCLK_APBCMASK_ADC_Msk & ((value) << MCLK_APBCMASK_ADC_Pos)) 

/* -------- MCLK_APBDMASK : (MCLK Offset: 0x20) (R/W 32) APBD Mask -------- */
#define MCLK_APBDMASK_RESETVALUE              _U_(0x00)                                            /**<  (MCLK_APBDMASK) APBD Mask  Reset Value */

#define MCLK_APBDMASK_SERCOM6_Pos             _U_(0)                                               /**< (MCLK_APBDMASK) SERCOM6 APB Clock Enable Position */
#define MCLK_APBDMASK_SERCOM6_Msk             (_U_(0x1) << MCLK_APBDMASK_SERCOM6_Pos)              /**< (MCLK_APBDMASK) SERCOM6 APB Clock Enable Mask */
#define MCLK_APBDMASK_SERCOM6(value)          (MCLK_APBDMASK_SERCOM6_Msk & ((value) << MCLK_APBDMASK_SERCOM6_Pos))
#define MCLK_APBDMASK_SERCOM7_Pos             _U_(1)                                               /**< (MCLK_APBDMASK) SERCOM7 APB Clock Enable Position */
#define MCLK_APBDMASK_SERCOM7_Msk             (_U_(0x1) << MCLK_APBDMASK_SERCOM7_Pos)              /**< (MCLK_APBDMASK) SERCOM7 APB Clock Enable Mask */
#define MCLK_APBDMASK_SERCOM7(value)          (MCLK_APBDMASK_SERCOM7_Msk & ((value) << MCLK_APBDMASK_SERCOM7_Pos))
#define MCLK_APBDMASK_TC5_Pos                 _U_(2)                                               /**< (MCLK_APBDMASK) TC5 APB Clock Enable Position */
#define MCLK_APBDMASK_TC5_Msk                 (_U_(0x1) << MCLK_APBDMASK_TC5_Pos)                  /**< (MCLK_APBDMASK) TC5 APB Clock Enable Mask */
#define MCLK_APBDMASK_TC5(value)              (MCLK_APBDMASK_TC5_Msk & ((value) << MCLK_APBDMASK_TC5_Pos))
#define MCLK_APBDMASK_TC6_Pos                 _U_(3)                                               /**< (MCLK_APBDMASK) TC6 APB Clock Enable Position */
#define MCLK_APBDMASK_TC6_Msk                 (_U_(0x1) << MCLK_APBDMASK_TC6_Pos)                  /**< (MCLK_APBDMASK) TC6 APB Clock Enable Mask */
#define MCLK_APBDMASK_TC6(value)              (MCLK_APBDMASK_TC6_Msk & ((value) << MCLK_APBDMASK_TC6_Pos))
#define MCLK_APBDMASK_TC7_Pos                 _U_(4)                                               /**< (MCLK_APBDMASK) TC7 APB Clock Enable Position */
#define MCLK_APBDMASK_TC7_Msk                 (_U_(0x1) << MCLK_APBDMASK_TC7_Pos)                  /**< (MCLK_APBDMASK) TC7 APB Clock Enable Mask */
#define MCLK_APBDMASK_TC7(value)              (MCLK_APBDMASK_TC7_Msk & ((value) << MCLK_APBDMASK_TC7_Pos))
#define MCLK_APBDMASK_Msk                     _U_(0x0000001F)                                      /**< (MCLK_APBDMASK) Register Mask  */

#define MCLK_APBDMASK_SERCOM_Pos              _U_(0)                                               /**< (MCLK_APBDMASK Position) SERCOM6 APB Clock Enable */
#define MCLK_APBDMASK_SERCOM_Msk              (_U_(0x3) << MCLK_APBDMASK_SERCOM_Pos)               /**< (MCLK_APBDMASK Mask) SERCOM */
#define MCLK_APBDMASK_SERCOM(value)           (MCLK_APBDMASK_SERCOM_Msk & ((value) << MCLK_APBDMASK_SERCOM_Pos)) 
#define MCLK_APBDMASK_TC_Pos                  _U_(2)                                               /**< (MCLK_APBDMASK Position) TC7 APB Clock Enable */
#define MCLK_APBDMASK_TC_Msk                  (_U_(0x7) << MCLK_APBDMASK_TC_Pos)                   /**< (MCLK_APBDMASK Mask) TC */
#define MCLK_APBDMASK_TC(value)               (MCLK_APBDMASK_TC_Msk & ((value) << MCLK_APBDMASK_TC_Pos)) 

/** \brief MCLK register offsets definitions */
#define MCLK_INTENCLR_REG_OFST         (0x01)              /**< (MCLK_INTENCLR) Interrupt Enable Clear Offset */
#define MCLK_INTENSET_REG_OFST         (0x02)              /**< (MCLK_INTENSET) Interrupt Enable Set Offset */
#define MCLK_INTFLAG_REG_OFST          (0x03)              /**< (MCLK_INTFLAG) Interrupt Flag Status and Clear Offset */
#define MCLK_CPUDIV_REG_OFST           (0x04)              /**< (MCLK_CPUDIV) CPU Clock Division Offset */
#define MCLK_AHBMASK_REG_OFST          (0x10)              /**< (MCLK_AHBMASK) AHB Mask Offset */
#define MCLK_APBAMASK_REG_OFST         (0x14)              /**< (MCLK_APBAMASK) APBA Mask Offset */
#define MCLK_APBBMASK_REG_OFST         (0x18)              /**< (MCLK_APBBMASK) APBB Mask Offset */
#define MCLK_APBCMASK_REG_OFST         (0x1C)              /**< (MCLK_APBCMASK) APBC Mask Offset */
#define MCLK_APBDMASK_REG_OFST         (0x20)              /**< (MCLK_APBDMASK) APBD Mask Offset */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief MCLK register API structure */
typedef struct
{  /* Main Clock */
  __I   uint8_t                        Reserved1[0x01];
  __IO  uint8_t                        MCLK_INTENCLR;      /**< Offset: 0x01 (R/W  8) Interrupt Enable Clear */
  __IO  uint8_t                        MCLK_INTENSET;      /**< Offset: 0x02 (R/W  8) Interrupt Enable Set */
  __IO  uint8_t                        MCLK_INTFLAG;       /**< Offset: 0x03 (R/W  8) Interrupt Flag Status and Clear */
  __IO  uint8_t                        MCLK_CPUDIV;        /**< Offset: 0x04 (R/W  8) CPU Clock Division */
  __I   uint8_t                        Reserved2[0x0B];
  __IO  uint32_t                       MCLK_AHBMASK;       /**< Offset: 0x10 (R/W  32) AHB Mask */
  __IO  uint32_t                       MCLK_APBAMASK;      /**< Offset: 0x14 (R/W  32) APBA Mask */
  __IO  uint32_t                       MCLK_APBBMASK;      /**< Offset: 0x18 (R/W  32) APBB Mask */
  __IO  uint32_t                       MCLK_APBCMASK;      /**< Offset: 0x1C (R/W  32) APBC Mask */
  __IO  uint32_t                       MCLK_APBDMASK;      /**< Offset: 0x20 (R/W  32) APBD Mask */
} mclk_registers_t;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* _SAMC21_MCLK_COMPONENT_H_ */
