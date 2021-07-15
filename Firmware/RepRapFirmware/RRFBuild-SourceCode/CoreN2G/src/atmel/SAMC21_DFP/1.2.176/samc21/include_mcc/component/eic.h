/**
 * \brief Component description for EIC
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

/* file generated from device description version 2018-11-30T04:40:03Z */
#ifndef _SAMC21_EIC_COMPONENT_H_
#define _SAMC21_EIC_COMPONENT_H_

/* ************************************************************************** */
/*   SOFTWARE API DEFINITION FOR EIC                                          */
/* ************************************************************************** */

/* -------- EIC_CTRLA : (EIC Offset: 0x00) (R/W 8) Control -------- */
#define EIC_CTRLA_RESETVALUE                  _U_(0x00)                                            /**<  (EIC_CTRLA) Control  Reset Value */

#define EIC_CTRLA_SWRST_Pos                   _U_(0)                                               /**< (EIC_CTRLA) Software Reset Position */
#define EIC_CTRLA_SWRST_Msk                   (_U_(0x1) << EIC_CTRLA_SWRST_Pos)                    /**< (EIC_CTRLA) Software Reset Mask */
#define EIC_CTRLA_SWRST(value)                (EIC_CTRLA_SWRST_Msk & ((value) << EIC_CTRLA_SWRST_Pos))
#define EIC_CTRLA_ENABLE_Pos                  _U_(1)                                               /**< (EIC_CTRLA) Enable Position */
#define EIC_CTRLA_ENABLE_Msk                  (_U_(0x1) << EIC_CTRLA_ENABLE_Pos)                   /**< (EIC_CTRLA) Enable Mask */
#define EIC_CTRLA_ENABLE(value)               (EIC_CTRLA_ENABLE_Msk & ((value) << EIC_CTRLA_ENABLE_Pos))
#define EIC_CTRLA_CKSEL_Pos                   _U_(4)                                               /**< (EIC_CTRLA) Clock Selection Position */
#define EIC_CTRLA_CKSEL_Msk                   (_U_(0x1) << EIC_CTRLA_CKSEL_Pos)                    /**< (EIC_CTRLA) Clock Selection Mask */
#define EIC_CTRLA_CKSEL(value)                (EIC_CTRLA_CKSEL_Msk & ((value) << EIC_CTRLA_CKSEL_Pos))
#define   EIC_CTRLA_CKSEL_CLK_GCLK_Val        _U_(0x0)                                             /**< (EIC_CTRLA) Clocked by GCLK  */
#define   EIC_CTRLA_CKSEL_CLK_ULP32K_Val      _U_(0x1)                                             /**< (EIC_CTRLA) Clocked by ULP32K  */
#define EIC_CTRLA_CKSEL_CLK_GCLK              (EIC_CTRLA_CKSEL_CLK_GCLK_Val << EIC_CTRLA_CKSEL_Pos) /**< (EIC_CTRLA) Clocked by GCLK Position  */
#define EIC_CTRLA_CKSEL_CLK_ULP32K            (EIC_CTRLA_CKSEL_CLK_ULP32K_Val << EIC_CTRLA_CKSEL_Pos) /**< (EIC_CTRLA) Clocked by ULP32K Position  */
#define EIC_CTRLA_Msk                         _U_(0x13)                                            /**< (EIC_CTRLA) Register Mask  */


/* -------- EIC_NMICTRL : (EIC Offset: 0x01) (R/W 8) NMI Control -------- */
#define EIC_NMICTRL_RESETVALUE                _U_(0x00)                                            /**<  (EIC_NMICTRL) NMI Control  Reset Value */

#define EIC_NMICTRL_NMISENSE_Pos              _U_(0)                                               /**< (EIC_NMICTRL) NMI Input Sense Configuration Position */
#define EIC_NMICTRL_NMISENSE_Msk              (_U_(0x7) << EIC_NMICTRL_NMISENSE_Pos)               /**< (EIC_NMICTRL) NMI Input Sense Configuration Mask */
#define EIC_NMICTRL_NMISENSE(value)           (EIC_NMICTRL_NMISENSE_Msk & ((value) << EIC_NMICTRL_NMISENSE_Pos))
#define   EIC_NMICTRL_NMISENSE_NONE_Val       _U_(0x0)                                             /**< (EIC_NMICTRL) No detection  */
#define   EIC_NMICTRL_NMISENSE_RISE_Val       _U_(0x1)                                             /**< (EIC_NMICTRL) Rising-edge detection  */
#define   EIC_NMICTRL_NMISENSE_FALL_Val       _U_(0x2)                                             /**< (EIC_NMICTRL) Falling-edge detection  */
#define   EIC_NMICTRL_NMISENSE_BOTH_Val       _U_(0x3)                                             /**< (EIC_NMICTRL) Both-edges detection  */
#define   EIC_NMICTRL_NMISENSE_HIGH_Val       _U_(0x4)                                             /**< (EIC_NMICTRL) High-level detection  */
#define   EIC_NMICTRL_NMISENSE_LOW_Val        _U_(0x5)                                             /**< (EIC_NMICTRL) Low-level detection  */
#define EIC_NMICTRL_NMISENSE_NONE             (EIC_NMICTRL_NMISENSE_NONE_Val << EIC_NMICTRL_NMISENSE_Pos) /**< (EIC_NMICTRL) No detection Position  */
#define EIC_NMICTRL_NMISENSE_RISE             (EIC_NMICTRL_NMISENSE_RISE_Val << EIC_NMICTRL_NMISENSE_Pos) /**< (EIC_NMICTRL) Rising-edge detection Position  */
#define EIC_NMICTRL_NMISENSE_FALL             (EIC_NMICTRL_NMISENSE_FALL_Val << EIC_NMICTRL_NMISENSE_Pos) /**< (EIC_NMICTRL) Falling-edge detection Position  */
#define EIC_NMICTRL_NMISENSE_BOTH             (EIC_NMICTRL_NMISENSE_BOTH_Val << EIC_NMICTRL_NMISENSE_Pos) /**< (EIC_NMICTRL) Both-edges detection Position  */
#define EIC_NMICTRL_NMISENSE_HIGH             (EIC_NMICTRL_NMISENSE_HIGH_Val << EIC_NMICTRL_NMISENSE_Pos) /**< (EIC_NMICTRL) High-level detection Position  */
#define EIC_NMICTRL_NMISENSE_LOW              (EIC_NMICTRL_NMISENSE_LOW_Val << EIC_NMICTRL_NMISENSE_Pos) /**< (EIC_NMICTRL) Low-level detection Position  */
#define EIC_NMICTRL_NMIFILTEN_Pos             _U_(3)                                               /**< (EIC_NMICTRL) NMI Filter Enable Position */
#define EIC_NMICTRL_NMIFILTEN_Msk             (_U_(0x1) << EIC_NMICTRL_NMIFILTEN_Pos)              /**< (EIC_NMICTRL) NMI Filter Enable Mask */
#define EIC_NMICTRL_NMIFILTEN(value)          (EIC_NMICTRL_NMIFILTEN_Msk & ((value) << EIC_NMICTRL_NMIFILTEN_Pos))
#define EIC_NMICTRL_NMIASYNCH_Pos             _U_(4)                                               /**< (EIC_NMICTRL) NMI Asynchronous edge Detection Enable Position */
#define EIC_NMICTRL_NMIASYNCH_Msk             (_U_(0x1) << EIC_NMICTRL_NMIASYNCH_Pos)              /**< (EIC_NMICTRL) NMI Asynchronous edge Detection Enable Mask */
#define EIC_NMICTRL_NMIASYNCH(value)          (EIC_NMICTRL_NMIASYNCH_Msk & ((value) << EIC_NMICTRL_NMIASYNCH_Pos))
#define   EIC_NMICTRL_NMIASYNCH_SYNC_Val      _U_(0x0)                                             /**< (EIC_NMICTRL) Edge detection is clock synchronously operated  */
#define   EIC_NMICTRL_NMIASYNCH_ASYNC_Val     _U_(0x1)                                             /**< (EIC_NMICTRL) Edge detection is clock asynchronously operated  */
#define EIC_NMICTRL_NMIASYNCH_SYNC            (EIC_NMICTRL_NMIASYNCH_SYNC_Val << EIC_NMICTRL_NMIASYNCH_Pos) /**< (EIC_NMICTRL) Edge detection is clock synchronously operated Position  */
#define EIC_NMICTRL_NMIASYNCH_ASYNC           (EIC_NMICTRL_NMIASYNCH_ASYNC_Val << EIC_NMICTRL_NMIASYNCH_Pos) /**< (EIC_NMICTRL) Edge detection is clock asynchronously operated Position  */
#define EIC_NMICTRL_Msk                       _U_(0x1F)                                            /**< (EIC_NMICTRL) Register Mask  */


/* -------- EIC_NMIFLAG : (EIC Offset: 0x02) (R/W 16) NMI Interrupt Flag -------- */
#define EIC_NMIFLAG_RESETVALUE                _U_(0x00)                                            /**<  (EIC_NMIFLAG) NMI Interrupt Flag  Reset Value */

#define EIC_NMIFLAG_NMI_Pos                   _U_(0)                                               /**< (EIC_NMIFLAG) NMI Interrupt Flag Position */
#define EIC_NMIFLAG_NMI_Msk                   (_U_(0x1) << EIC_NMIFLAG_NMI_Pos)                    /**< (EIC_NMIFLAG) NMI Interrupt Flag Mask */
#define EIC_NMIFLAG_NMI(value)                (EIC_NMIFLAG_NMI_Msk & ((value) << EIC_NMIFLAG_NMI_Pos))
#define EIC_NMIFLAG_Msk                       _U_(0x0001)                                          /**< (EIC_NMIFLAG) Register Mask  */


/* -------- EIC_SYNCBUSY : (EIC Offset: 0x04) ( R/ 32) Syncbusy register -------- */
#define EIC_SYNCBUSY_RESETVALUE               _U_(0x00)                                            /**<  (EIC_SYNCBUSY) Syncbusy register  Reset Value */

#define EIC_SYNCBUSY_SWRST_Pos                _U_(0)                                               /**< (EIC_SYNCBUSY) Software reset synchronisation Position */
#define EIC_SYNCBUSY_SWRST_Msk                (_U_(0x1) << EIC_SYNCBUSY_SWRST_Pos)                 /**< (EIC_SYNCBUSY) Software reset synchronisation Mask */
#define EIC_SYNCBUSY_SWRST(value)             (EIC_SYNCBUSY_SWRST_Msk & ((value) << EIC_SYNCBUSY_SWRST_Pos))
#define EIC_SYNCBUSY_ENABLE_Pos               _U_(1)                                               /**< (EIC_SYNCBUSY) Enable synchronisation Position */
#define EIC_SYNCBUSY_ENABLE_Msk               (_U_(0x1) << EIC_SYNCBUSY_ENABLE_Pos)                /**< (EIC_SYNCBUSY) Enable synchronisation Mask */
#define EIC_SYNCBUSY_ENABLE(value)            (EIC_SYNCBUSY_ENABLE_Msk & ((value) << EIC_SYNCBUSY_ENABLE_Pos))
#define EIC_SYNCBUSY_Msk                      _U_(0x00000003)                                      /**< (EIC_SYNCBUSY) Register Mask  */


/* -------- EIC_EVCTRL : (EIC Offset: 0x08) (R/W 32) Event Control -------- */
#define EIC_EVCTRL_RESETVALUE                 _U_(0x00)                                            /**<  (EIC_EVCTRL) Event Control  Reset Value */

#define EIC_EVCTRL_EXTINTEO_Pos               _U_(0)                                               /**< (EIC_EVCTRL) External Interrupt Event Output Enable Position */
#define EIC_EVCTRL_EXTINTEO_Msk               (_U_(0xFFFF) << EIC_EVCTRL_EXTINTEO_Pos)             /**< (EIC_EVCTRL) External Interrupt Event Output Enable Mask */
#define EIC_EVCTRL_EXTINTEO(value)            (EIC_EVCTRL_EXTINTEO_Msk & ((value) << EIC_EVCTRL_EXTINTEO_Pos))
#define EIC_EVCTRL_Msk                        _U_(0x0000FFFF)                                      /**< (EIC_EVCTRL) Register Mask  */


/* -------- EIC_INTENCLR : (EIC Offset: 0x0C) (R/W 32) Interrupt Enable Clear -------- */
#define EIC_INTENCLR_RESETVALUE               _U_(0x00)                                            /**<  (EIC_INTENCLR) Interrupt Enable Clear  Reset Value */

#define EIC_INTENCLR_EXTINT_Pos               _U_(0)                                               /**< (EIC_INTENCLR) External Interrupt Disable Position */
#define EIC_INTENCLR_EXTINT_Msk               (_U_(0xFFFF) << EIC_INTENCLR_EXTINT_Pos)             /**< (EIC_INTENCLR) External Interrupt Disable Mask */
#define EIC_INTENCLR_EXTINT(value)            (EIC_INTENCLR_EXTINT_Msk & ((value) << EIC_INTENCLR_EXTINT_Pos))
#define EIC_INTENCLR_Msk                      _U_(0x0000FFFF)                                      /**< (EIC_INTENCLR) Register Mask  */


/* -------- EIC_INTENSET : (EIC Offset: 0x10) (R/W 32) Interrupt Enable Set -------- */
#define EIC_INTENSET_RESETVALUE               _U_(0x00)                                            /**<  (EIC_INTENSET) Interrupt Enable Set  Reset Value */

#define EIC_INTENSET_EXTINT_Pos               _U_(0)                                               /**< (EIC_INTENSET) External Interrupt Enable Position */
#define EIC_INTENSET_EXTINT_Msk               (_U_(0xFFFF) << EIC_INTENSET_EXTINT_Pos)             /**< (EIC_INTENSET) External Interrupt Enable Mask */
#define EIC_INTENSET_EXTINT(value)            (EIC_INTENSET_EXTINT_Msk & ((value) << EIC_INTENSET_EXTINT_Pos))
#define EIC_INTENSET_Msk                      _U_(0x0000FFFF)                                      /**< (EIC_INTENSET) Register Mask  */


/* -------- EIC_INTFLAG : (EIC Offset: 0x14) (R/W 32) Interrupt Flag Status and Clear -------- */
#define EIC_INTFLAG_RESETVALUE                _U_(0x00)                                            /**<  (EIC_INTFLAG) Interrupt Flag Status and Clear  Reset Value */

#define EIC_INTFLAG_EXTINT_Pos                _U_(0)                                               /**< (EIC_INTFLAG) External Interrupt Flag Position */
#define EIC_INTFLAG_EXTINT_Msk                (_U_(0xFFFF) << EIC_INTFLAG_EXTINT_Pos)              /**< (EIC_INTFLAG) External Interrupt Flag Mask */
#define EIC_INTFLAG_EXTINT(value)             (EIC_INTFLAG_EXTINT_Msk & ((value) << EIC_INTFLAG_EXTINT_Pos))
#define EIC_INTFLAG_Msk                       _U_(0x0000FFFF)                                      /**< (EIC_INTFLAG) Register Mask  */


/* -------- EIC_ASYNCH : (EIC Offset: 0x18) (R/W 32) EIC Asynchronous edge Detection Enable -------- */
#define EIC_ASYNCH_RESETVALUE                 _U_(0x00)                                            /**<  (EIC_ASYNCH) EIC Asynchronous edge Detection Enable  Reset Value */

#define EIC_ASYNCH_ASYNCH_Pos                 _U_(0)                                               /**< (EIC_ASYNCH) EIC Asynchronous edge Detection Enable Position */
#define EIC_ASYNCH_ASYNCH_Msk                 (_U_(0xFFFF) << EIC_ASYNCH_ASYNCH_Pos)               /**< (EIC_ASYNCH) EIC Asynchronous edge Detection Enable Mask */
#define EIC_ASYNCH_ASYNCH(value)              (EIC_ASYNCH_ASYNCH_Msk & ((value) << EIC_ASYNCH_ASYNCH_Pos))
#define   EIC_ASYNCH_ASYNCH_SYNC_Val          _U_(0x0)                                             /**< (EIC_ASYNCH) Edge detection is clock synchronously operated  */
#define   EIC_ASYNCH_ASYNCH_ASYNC_Val         _U_(0x1)                                             /**< (EIC_ASYNCH) Edge detection is clock asynchronously operated  */
#define EIC_ASYNCH_ASYNCH_SYNC                (EIC_ASYNCH_ASYNCH_SYNC_Val << EIC_ASYNCH_ASYNCH_Pos) /**< (EIC_ASYNCH) Edge detection is clock synchronously operated Position  */
#define EIC_ASYNCH_ASYNCH_ASYNC               (EIC_ASYNCH_ASYNCH_ASYNC_Val << EIC_ASYNCH_ASYNCH_Pos) /**< (EIC_ASYNCH) Edge detection is clock asynchronously operated Position  */
#define EIC_ASYNCH_Msk                        _U_(0x0000FFFF)                                      /**< (EIC_ASYNCH) Register Mask  */


/* -------- EIC_CONFIG : (EIC Offset: 0x1C) (R/W 32) Configuration n -------- */
#define EIC_CONFIG_RESETVALUE                 _U_(0x00)                                            /**<  (EIC_CONFIG) Configuration n  Reset Value */

#define EIC_CONFIG_SENSE0_Pos                 _U_(0)                                               /**< (EIC_CONFIG) Input Sense Configuration 0 Position */
#define EIC_CONFIG_SENSE0_Msk                 (_U_(0x7) << EIC_CONFIG_SENSE0_Pos)                  /**< (EIC_CONFIG) Input Sense Configuration 0 Mask */
#define EIC_CONFIG_SENSE0(value)              (EIC_CONFIG_SENSE0_Msk & ((value) << EIC_CONFIG_SENSE0_Pos))
#define   EIC_CONFIG_SENSE0_NONE_Val          _U_(0x0)                                             /**< (EIC_CONFIG) No detection  */
#define   EIC_CONFIG_SENSE0_RISE_Val          _U_(0x1)                                             /**< (EIC_CONFIG) Rising edge detection  */
#define   EIC_CONFIG_SENSE0_FALL_Val          _U_(0x2)                                             /**< (EIC_CONFIG) Falling edge detection  */
#define   EIC_CONFIG_SENSE0_BOTH_Val          _U_(0x3)                                             /**< (EIC_CONFIG) Both edges detection  */
#define   EIC_CONFIG_SENSE0_HIGH_Val          _U_(0x4)                                             /**< (EIC_CONFIG) High level detection  */
#define   EIC_CONFIG_SENSE0_LOW_Val           _U_(0x5)                                             /**< (EIC_CONFIG) Low level detection  */
#define EIC_CONFIG_SENSE0_NONE                (EIC_CONFIG_SENSE0_NONE_Val << EIC_CONFIG_SENSE0_Pos) /**< (EIC_CONFIG) No detection Position  */
#define EIC_CONFIG_SENSE0_RISE                (EIC_CONFIG_SENSE0_RISE_Val << EIC_CONFIG_SENSE0_Pos) /**< (EIC_CONFIG) Rising edge detection Position  */
#define EIC_CONFIG_SENSE0_FALL                (EIC_CONFIG_SENSE0_FALL_Val << EIC_CONFIG_SENSE0_Pos) /**< (EIC_CONFIG) Falling edge detection Position  */
#define EIC_CONFIG_SENSE0_BOTH                (EIC_CONFIG_SENSE0_BOTH_Val << EIC_CONFIG_SENSE0_Pos) /**< (EIC_CONFIG) Both edges detection Position  */
#define EIC_CONFIG_SENSE0_HIGH                (EIC_CONFIG_SENSE0_HIGH_Val << EIC_CONFIG_SENSE0_Pos) /**< (EIC_CONFIG) High level detection Position  */
#define EIC_CONFIG_SENSE0_LOW                 (EIC_CONFIG_SENSE0_LOW_Val << EIC_CONFIG_SENSE0_Pos) /**< (EIC_CONFIG) Low level detection Position  */
#define EIC_CONFIG_FILTEN0_Pos                _U_(3)                                               /**< (EIC_CONFIG) Filter Enable 0 Position */
#define EIC_CONFIG_FILTEN0_Msk                (_U_(0x1) << EIC_CONFIG_FILTEN0_Pos)                 /**< (EIC_CONFIG) Filter Enable 0 Mask */
#define EIC_CONFIG_FILTEN0(value)             (EIC_CONFIG_FILTEN0_Msk & ((value) << EIC_CONFIG_FILTEN0_Pos))
#define EIC_CONFIG_SENSE1_Pos                 _U_(4)                                               /**< (EIC_CONFIG) Input Sense Configuration 1 Position */
#define EIC_CONFIG_SENSE1_Msk                 (_U_(0x7) << EIC_CONFIG_SENSE1_Pos)                  /**< (EIC_CONFIG) Input Sense Configuration 1 Mask */
#define EIC_CONFIG_SENSE1(value)              (EIC_CONFIG_SENSE1_Msk & ((value) << EIC_CONFIG_SENSE1_Pos))
#define   EIC_CONFIG_SENSE1_NONE_Val          _U_(0x0)                                             /**< (EIC_CONFIG) No detection  */
#define   EIC_CONFIG_SENSE1_RISE_Val          _U_(0x1)                                             /**< (EIC_CONFIG) Rising edge detection  */
#define   EIC_CONFIG_SENSE1_FALL_Val          _U_(0x2)                                             /**< (EIC_CONFIG) Falling edge detection  */
#define   EIC_CONFIG_SENSE1_BOTH_Val          _U_(0x3)                                             /**< (EIC_CONFIG) Both edges detection  */
#define   EIC_CONFIG_SENSE1_HIGH_Val          _U_(0x4)                                             /**< (EIC_CONFIG) High level detection  */
#define   EIC_CONFIG_SENSE1_LOW_Val           _U_(0x5)                                             /**< (EIC_CONFIG) Low level detection  */
#define EIC_CONFIG_SENSE1_NONE                (EIC_CONFIG_SENSE1_NONE_Val << EIC_CONFIG_SENSE1_Pos) /**< (EIC_CONFIG) No detection Position  */
#define EIC_CONFIG_SENSE1_RISE                (EIC_CONFIG_SENSE1_RISE_Val << EIC_CONFIG_SENSE1_Pos) /**< (EIC_CONFIG) Rising edge detection Position  */
#define EIC_CONFIG_SENSE1_FALL                (EIC_CONFIG_SENSE1_FALL_Val << EIC_CONFIG_SENSE1_Pos) /**< (EIC_CONFIG) Falling edge detection Position  */
#define EIC_CONFIG_SENSE1_BOTH                (EIC_CONFIG_SENSE1_BOTH_Val << EIC_CONFIG_SENSE1_Pos) /**< (EIC_CONFIG) Both edges detection Position  */
#define EIC_CONFIG_SENSE1_HIGH                (EIC_CONFIG_SENSE1_HIGH_Val << EIC_CONFIG_SENSE1_Pos) /**< (EIC_CONFIG) High level detection Position  */
#define EIC_CONFIG_SENSE1_LOW                 (EIC_CONFIG_SENSE1_LOW_Val << EIC_CONFIG_SENSE1_Pos) /**< (EIC_CONFIG) Low level detection Position  */
#define EIC_CONFIG_FILTEN1_Pos                _U_(7)                                               /**< (EIC_CONFIG) Filter Enable 1 Position */
#define EIC_CONFIG_FILTEN1_Msk                (_U_(0x1) << EIC_CONFIG_FILTEN1_Pos)                 /**< (EIC_CONFIG) Filter Enable 1 Mask */
#define EIC_CONFIG_FILTEN1(value)             (EIC_CONFIG_FILTEN1_Msk & ((value) << EIC_CONFIG_FILTEN1_Pos))
#define EIC_CONFIG_SENSE2_Pos                 _U_(8)                                               /**< (EIC_CONFIG) Input Sense Configuration 2 Position */
#define EIC_CONFIG_SENSE2_Msk                 (_U_(0x7) << EIC_CONFIG_SENSE2_Pos)                  /**< (EIC_CONFIG) Input Sense Configuration 2 Mask */
#define EIC_CONFIG_SENSE2(value)              (EIC_CONFIG_SENSE2_Msk & ((value) << EIC_CONFIG_SENSE2_Pos))
#define   EIC_CONFIG_SENSE2_NONE_Val          _U_(0x0)                                             /**< (EIC_CONFIG) No detection  */
#define   EIC_CONFIG_SENSE2_RISE_Val          _U_(0x1)                                             /**< (EIC_CONFIG) Rising edge detection  */
#define   EIC_CONFIG_SENSE2_FALL_Val          _U_(0x2)                                             /**< (EIC_CONFIG) Falling edge detection  */
#define   EIC_CONFIG_SENSE2_BOTH_Val          _U_(0x3)                                             /**< (EIC_CONFIG) Both edges detection  */
#define   EIC_CONFIG_SENSE2_HIGH_Val          _U_(0x4)                                             /**< (EIC_CONFIG) High level detection  */
#define   EIC_CONFIG_SENSE2_LOW_Val           _U_(0x5)                                             /**< (EIC_CONFIG) Low level detection  */
#define EIC_CONFIG_SENSE2_NONE                (EIC_CONFIG_SENSE2_NONE_Val << EIC_CONFIG_SENSE2_Pos) /**< (EIC_CONFIG) No detection Position  */
#define EIC_CONFIG_SENSE2_RISE                (EIC_CONFIG_SENSE2_RISE_Val << EIC_CONFIG_SENSE2_Pos) /**< (EIC_CONFIG) Rising edge detection Position  */
#define EIC_CONFIG_SENSE2_FALL                (EIC_CONFIG_SENSE2_FALL_Val << EIC_CONFIG_SENSE2_Pos) /**< (EIC_CONFIG) Falling edge detection Position  */
#define EIC_CONFIG_SENSE2_BOTH                (EIC_CONFIG_SENSE2_BOTH_Val << EIC_CONFIG_SENSE2_Pos) /**< (EIC_CONFIG) Both edges detection Position  */
#define EIC_CONFIG_SENSE2_HIGH                (EIC_CONFIG_SENSE2_HIGH_Val << EIC_CONFIG_SENSE2_Pos) /**< (EIC_CONFIG) High level detection Position  */
#define EIC_CONFIG_SENSE2_LOW                 (EIC_CONFIG_SENSE2_LOW_Val << EIC_CONFIG_SENSE2_Pos) /**< (EIC_CONFIG) Low level detection Position  */
#define EIC_CONFIG_FILTEN2_Pos                _U_(11)                                              /**< (EIC_CONFIG) Filter Enable 2 Position */
#define EIC_CONFIG_FILTEN2_Msk                (_U_(0x1) << EIC_CONFIG_FILTEN2_Pos)                 /**< (EIC_CONFIG) Filter Enable 2 Mask */
#define EIC_CONFIG_FILTEN2(value)             (EIC_CONFIG_FILTEN2_Msk & ((value) << EIC_CONFIG_FILTEN2_Pos))
#define EIC_CONFIG_SENSE3_Pos                 _U_(12)                                              /**< (EIC_CONFIG) Input Sense Configuration 3 Position */
#define EIC_CONFIG_SENSE3_Msk                 (_U_(0x7) << EIC_CONFIG_SENSE3_Pos)                  /**< (EIC_CONFIG) Input Sense Configuration 3 Mask */
#define EIC_CONFIG_SENSE3(value)              (EIC_CONFIG_SENSE3_Msk & ((value) << EIC_CONFIG_SENSE3_Pos))
#define   EIC_CONFIG_SENSE3_NONE_Val          _U_(0x0)                                             /**< (EIC_CONFIG) No detection  */
#define   EIC_CONFIG_SENSE3_RISE_Val          _U_(0x1)                                             /**< (EIC_CONFIG) Rising edge detection  */
#define   EIC_CONFIG_SENSE3_FALL_Val          _U_(0x2)                                             /**< (EIC_CONFIG) Falling edge detection  */
#define   EIC_CONFIG_SENSE3_BOTH_Val          _U_(0x3)                                             /**< (EIC_CONFIG) Both edges detection  */
#define   EIC_CONFIG_SENSE3_HIGH_Val          _U_(0x4)                                             /**< (EIC_CONFIG) High level detection  */
#define   EIC_CONFIG_SENSE3_LOW_Val           _U_(0x5)                                             /**< (EIC_CONFIG) Low level detection  */
#define EIC_CONFIG_SENSE3_NONE                (EIC_CONFIG_SENSE3_NONE_Val << EIC_CONFIG_SENSE3_Pos) /**< (EIC_CONFIG) No detection Position  */
#define EIC_CONFIG_SENSE3_RISE                (EIC_CONFIG_SENSE3_RISE_Val << EIC_CONFIG_SENSE3_Pos) /**< (EIC_CONFIG) Rising edge detection Position  */
#define EIC_CONFIG_SENSE3_FALL                (EIC_CONFIG_SENSE3_FALL_Val << EIC_CONFIG_SENSE3_Pos) /**< (EIC_CONFIG) Falling edge detection Position  */
#define EIC_CONFIG_SENSE3_BOTH                (EIC_CONFIG_SENSE3_BOTH_Val << EIC_CONFIG_SENSE3_Pos) /**< (EIC_CONFIG) Both edges detection Position  */
#define EIC_CONFIG_SENSE3_HIGH                (EIC_CONFIG_SENSE3_HIGH_Val << EIC_CONFIG_SENSE3_Pos) /**< (EIC_CONFIG) High level detection Position  */
#define EIC_CONFIG_SENSE3_LOW                 (EIC_CONFIG_SENSE3_LOW_Val << EIC_CONFIG_SENSE3_Pos) /**< (EIC_CONFIG) Low level detection Position  */
#define EIC_CONFIG_FILTEN3_Pos                _U_(15)                                              /**< (EIC_CONFIG) Filter Enable 3 Position */
#define EIC_CONFIG_FILTEN3_Msk                (_U_(0x1) << EIC_CONFIG_FILTEN3_Pos)                 /**< (EIC_CONFIG) Filter Enable 3 Mask */
#define EIC_CONFIG_FILTEN3(value)             (EIC_CONFIG_FILTEN3_Msk & ((value) << EIC_CONFIG_FILTEN3_Pos))
#define EIC_CONFIG_SENSE4_Pos                 _U_(16)                                              /**< (EIC_CONFIG) Input Sense Configuration 4 Position */
#define EIC_CONFIG_SENSE4_Msk                 (_U_(0x7) << EIC_CONFIG_SENSE4_Pos)                  /**< (EIC_CONFIG) Input Sense Configuration 4 Mask */
#define EIC_CONFIG_SENSE4(value)              (EIC_CONFIG_SENSE4_Msk & ((value) << EIC_CONFIG_SENSE4_Pos))
#define   EIC_CONFIG_SENSE4_NONE_Val          _U_(0x0)                                             /**< (EIC_CONFIG) No detection  */
#define   EIC_CONFIG_SENSE4_RISE_Val          _U_(0x1)                                             /**< (EIC_CONFIG) Rising edge detection  */
#define   EIC_CONFIG_SENSE4_FALL_Val          _U_(0x2)                                             /**< (EIC_CONFIG) Falling edge detection  */
#define   EIC_CONFIG_SENSE4_BOTH_Val          _U_(0x3)                                             /**< (EIC_CONFIG) Both edges detection  */
#define   EIC_CONFIG_SENSE4_HIGH_Val          _U_(0x4)                                             /**< (EIC_CONFIG) High level detection  */
#define   EIC_CONFIG_SENSE4_LOW_Val           _U_(0x5)                                             /**< (EIC_CONFIG) Low level detection  */
#define EIC_CONFIG_SENSE4_NONE                (EIC_CONFIG_SENSE4_NONE_Val << EIC_CONFIG_SENSE4_Pos) /**< (EIC_CONFIG) No detection Position  */
#define EIC_CONFIG_SENSE4_RISE                (EIC_CONFIG_SENSE4_RISE_Val << EIC_CONFIG_SENSE4_Pos) /**< (EIC_CONFIG) Rising edge detection Position  */
#define EIC_CONFIG_SENSE4_FALL                (EIC_CONFIG_SENSE4_FALL_Val << EIC_CONFIG_SENSE4_Pos) /**< (EIC_CONFIG) Falling edge detection Position  */
#define EIC_CONFIG_SENSE4_BOTH                (EIC_CONFIG_SENSE4_BOTH_Val << EIC_CONFIG_SENSE4_Pos) /**< (EIC_CONFIG) Both edges detection Position  */
#define EIC_CONFIG_SENSE4_HIGH                (EIC_CONFIG_SENSE4_HIGH_Val << EIC_CONFIG_SENSE4_Pos) /**< (EIC_CONFIG) High level detection Position  */
#define EIC_CONFIG_SENSE4_LOW                 (EIC_CONFIG_SENSE4_LOW_Val << EIC_CONFIG_SENSE4_Pos) /**< (EIC_CONFIG) Low level detection Position  */
#define EIC_CONFIG_FILTEN4_Pos                _U_(19)                                              /**< (EIC_CONFIG) Filter Enable 4 Position */
#define EIC_CONFIG_FILTEN4_Msk                (_U_(0x1) << EIC_CONFIG_FILTEN4_Pos)                 /**< (EIC_CONFIG) Filter Enable 4 Mask */
#define EIC_CONFIG_FILTEN4(value)             (EIC_CONFIG_FILTEN4_Msk & ((value) << EIC_CONFIG_FILTEN4_Pos))
#define EIC_CONFIG_SENSE5_Pos                 _U_(20)                                              /**< (EIC_CONFIG) Input Sense Configuration 5 Position */
#define EIC_CONFIG_SENSE5_Msk                 (_U_(0x7) << EIC_CONFIG_SENSE5_Pos)                  /**< (EIC_CONFIG) Input Sense Configuration 5 Mask */
#define EIC_CONFIG_SENSE5(value)              (EIC_CONFIG_SENSE5_Msk & ((value) << EIC_CONFIG_SENSE5_Pos))
#define   EIC_CONFIG_SENSE5_NONE_Val          _U_(0x0)                                             /**< (EIC_CONFIG) No detection  */
#define   EIC_CONFIG_SENSE5_RISE_Val          _U_(0x1)                                             /**< (EIC_CONFIG) Rising edge detection  */
#define   EIC_CONFIG_SENSE5_FALL_Val          _U_(0x2)                                             /**< (EIC_CONFIG) Falling edge detection  */
#define   EIC_CONFIG_SENSE5_BOTH_Val          _U_(0x3)                                             /**< (EIC_CONFIG) Both edges detection  */
#define   EIC_CONFIG_SENSE5_HIGH_Val          _U_(0x4)                                             /**< (EIC_CONFIG) High level detection  */
#define   EIC_CONFIG_SENSE5_LOW_Val           _U_(0x5)                                             /**< (EIC_CONFIG) Low level detection  */
#define EIC_CONFIG_SENSE5_NONE                (EIC_CONFIG_SENSE5_NONE_Val << EIC_CONFIG_SENSE5_Pos) /**< (EIC_CONFIG) No detection Position  */
#define EIC_CONFIG_SENSE5_RISE                (EIC_CONFIG_SENSE5_RISE_Val << EIC_CONFIG_SENSE5_Pos) /**< (EIC_CONFIG) Rising edge detection Position  */
#define EIC_CONFIG_SENSE5_FALL                (EIC_CONFIG_SENSE5_FALL_Val << EIC_CONFIG_SENSE5_Pos) /**< (EIC_CONFIG) Falling edge detection Position  */
#define EIC_CONFIG_SENSE5_BOTH                (EIC_CONFIG_SENSE5_BOTH_Val << EIC_CONFIG_SENSE5_Pos) /**< (EIC_CONFIG) Both edges detection Position  */
#define EIC_CONFIG_SENSE5_HIGH                (EIC_CONFIG_SENSE5_HIGH_Val << EIC_CONFIG_SENSE5_Pos) /**< (EIC_CONFIG) High level detection Position  */
#define EIC_CONFIG_SENSE5_LOW                 (EIC_CONFIG_SENSE5_LOW_Val << EIC_CONFIG_SENSE5_Pos) /**< (EIC_CONFIG) Low level detection Position  */
#define EIC_CONFIG_FILTEN5_Pos                _U_(23)                                              /**< (EIC_CONFIG) Filter Enable 5 Position */
#define EIC_CONFIG_FILTEN5_Msk                (_U_(0x1) << EIC_CONFIG_FILTEN5_Pos)                 /**< (EIC_CONFIG) Filter Enable 5 Mask */
#define EIC_CONFIG_FILTEN5(value)             (EIC_CONFIG_FILTEN5_Msk & ((value) << EIC_CONFIG_FILTEN5_Pos))
#define EIC_CONFIG_SENSE6_Pos                 _U_(24)                                              /**< (EIC_CONFIG) Input Sense Configuration 6 Position */
#define EIC_CONFIG_SENSE6_Msk                 (_U_(0x7) << EIC_CONFIG_SENSE6_Pos)                  /**< (EIC_CONFIG) Input Sense Configuration 6 Mask */
#define EIC_CONFIG_SENSE6(value)              (EIC_CONFIG_SENSE6_Msk & ((value) << EIC_CONFIG_SENSE6_Pos))
#define   EIC_CONFIG_SENSE6_NONE_Val          _U_(0x0)                                             /**< (EIC_CONFIG) No detection  */
#define   EIC_CONFIG_SENSE6_RISE_Val          _U_(0x1)                                             /**< (EIC_CONFIG) Rising edge detection  */
#define   EIC_CONFIG_SENSE6_FALL_Val          _U_(0x2)                                             /**< (EIC_CONFIG) Falling edge detection  */
#define   EIC_CONFIG_SENSE6_BOTH_Val          _U_(0x3)                                             /**< (EIC_CONFIG) Both edges detection  */
#define   EIC_CONFIG_SENSE6_HIGH_Val          _U_(0x4)                                             /**< (EIC_CONFIG) High level detection  */
#define   EIC_CONFIG_SENSE6_LOW_Val           _U_(0x5)                                             /**< (EIC_CONFIG) Low level detection  */
#define EIC_CONFIG_SENSE6_NONE                (EIC_CONFIG_SENSE6_NONE_Val << EIC_CONFIG_SENSE6_Pos) /**< (EIC_CONFIG) No detection Position  */
#define EIC_CONFIG_SENSE6_RISE                (EIC_CONFIG_SENSE6_RISE_Val << EIC_CONFIG_SENSE6_Pos) /**< (EIC_CONFIG) Rising edge detection Position  */
#define EIC_CONFIG_SENSE6_FALL                (EIC_CONFIG_SENSE6_FALL_Val << EIC_CONFIG_SENSE6_Pos) /**< (EIC_CONFIG) Falling edge detection Position  */
#define EIC_CONFIG_SENSE6_BOTH                (EIC_CONFIG_SENSE6_BOTH_Val << EIC_CONFIG_SENSE6_Pos) /**< (EIC_CONFIG) Both edges detection Position  */
#define EIC_CONFIG_SENSE6_HIGH                (EIC_CONFIG_SENSE6_HIGH_Val << EIC_CONFIG_SENSE6_Pos) /**< (EIC_CONFIG) High level detection Position  */
#define EIC_CONFIG_SENSE6_LOW                 (EIC_CONFIG_SENSE6_LOW_Val << EIC_CONFIG_SENSE6_Pos) /**< (EIC_CONFIG) Low level detection Position  */
#define EIC_CONFIG_FILTEN6_Pos                _U_(27)                                              /**< (EIC_CONFIG) Filter Enable 6 Position */
#define EIC_CONFIG_FILTEN6_Msk                (_U_(0x1) << EIC_CONFIG_FILTEN6_Pos)                 /**< (EIC_CONFIG) Filter Enable 6 Mask */
#define EIC_CONFIG_FILTEN6(value)             (EIC_CONFIG_FILTEN6_Msk & ((value) << EIC_CONFIG_FILTEN6_Pos))
#define EIC_CONFIG_SENSE7_Pos                 _U_(28)                                              /**< (EIC_CONFIG) Input Sense Configuration 7 Position */
#define EIC_CONFIG_SENSE7_Msk                 (_U_(0x7) << EIC_CONFIG_SENSE7_Pos)                  /**< (EIC_CONFIG) Input Sense Configuration 7 Mask */
#define EIC_CONFIG_SENSE7(value)              (EIC_CONFIG_SENSE7_Msk & ((value) << EIC_CONFIG_SENSE7_Pos))
#define   EIC_CONFIG_SENSE7_NONE_Val          _U_(0x0)                                             /**< (EIC_CONFIG) No detection  */
#define   EIC_CONFIG_SENSE7_RISE_Val          _U_(0x1)                                             /**< (EIC_CONFIG) Rising edge detection  */
#define   EIC_CONFIG_SENSE7_FALL_Val          _U_(0x2)                                             /**< (EIC_CONFIG) Falling edge detection  */
#define   EIC_CONFIG_SENSE7_BOTH_Val          _U_(0x3)                                             /**< (EIC_CONFIG) Both edges detection  */
#define   EIC_CONFIG_SENSE7_HIGH_Val          _U_(0x4)                                             /**< (EIC_CONFIG) High level detection  */
#define   EIC_CONFIG_SENSE7_LOW_Val           _U_(0x5)                                             /**< (EIC_CONFIG) Low level detection  */
#define EIC_CONFIG_SENSE7_NONE                (EIC_CONFIG_SENSE7_NONE_Val << EIC_CONFIG_SENSE7_Pos) /**< (EIC_CONFIG) No detection Position  */
#define EIC_CONFIG_SENSE7_RISE                (EIC_CONFIG_SENSE7_RISE_Val << EIC_CONFIG_SENSE7_Pos) /**< (EIC_CONFIG) Rising edge detection Position  */
#define EIC_CONFIG_SENSE7_FALL                (EIC_CONFIG_SENSE7_FALL_Val << EIC_CONFIG_SENSE7_Pos) /**< (EIC_CONFIG) Falling edge detection Position  */
#define EIC_CONFIG_SENSE7_BOTH                (EIC_CONFIG_SENSE7_BOTH_Val << EIC_CONFIG_SENSE7_Pos) /**< (EIC_CONFIG) Both edges detection Position  */
#define EIC_CONFIG_SENSE7_HIGH                (EIC_CONFIG_SENSE7_HIGH_Val << EIC_CONFIG_SENSE7_Pos) /**< (EIC_CONFIG) High level detection Position  */
#define EIC_CONFIG_SENSE7_LOW                 (EIC_CONFIG_SENSE7_LOW_Val << EIC_CONFIG_SENSE7_Pos) /**< (EIC_CONFIG) Low level detection Position  */
#define EIC_CONFIG_FILTEN7_Pos                _U_(31)                                              /**< (EIC_CONFIG) Filter Enable 7 Position */
#define EIC_CONFIG_FILTEN7_Msk                (_U_(0x1) << EIC_CONFIG_FILTEN7_Pos)                 /**< (EIC_CONFIG) Filter Enable 7 Mask */
#define EIC_CONFIG_FILTEN7(value)             (EIC_CONFIG_FILTEN7_Msk & ((value) << EIC_CONFIG_FILTEN7_Pos))
#define EIC_CONFIG_Msk                        _U_(0xFFFFFFFF)                                      /**< (EIC_CONFIG) Register Mask  */


/** \brief EIC register offsets definitions */
#define EIC_CTRLA_REG_OFST             (0x00)              /**< (EIC_CTRLA) Control Offset */
#define EIC_NMICTRL_REG_OFST           (0x01)              /**< (EIC_NMICTRL) NMI Control Offset */
#define EIC_NMIFLAG_REG_OFST           (0x02)              /**< (EIC_NMIFLAG) NMI Interrupt Flag Offset */
#define EIC_SYNCBUSY_REG_OFST          (0x04)              /**< (EIC_SYNCBUSY) Syncbusy register Offset */
#define EIC_EVCTRL_REG_OFST            (0x08)              /**< (EIC_EVCTRL) Event Control Offset */
#define EIC_INTENCLR_REG_OFST          (0x0C)              /**< (EIC_INTENCLR) Interrupt Enable Clear Offset */
#define EIC_INTENSET_REG_OFST          (0x10)              /**< (EIC_INTENSET) Interrupt Enable Set Offset */
#define EIC_INTFLAG_REG_OFST           (0x14)              /**< (EIC_INTFLAG) Interrupt Flag Status and Clear Offset */
#define EIC_ASYNCH_REG_OFST            (0x18)              /**< (EIC_ASYNCH) EIC Asynchronous edge Detection Enable Offset */
#define EIC_CONFIG_REG_OFST            (0x1C)              /**< (EIC_CONFIG) Configuration n Offset */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief EIC register API structure */
typedef struct
{  /* External Interrupt Controller */
  __IO  uint8_t                        EIC_CTRLA;          /**< Offset: 0x00 (R/W  8) Control */
  __IO  uint8_t                        EIC_NMICTRL;        /**< Offset: 0x01 (R/W  8) NMI Control */
  __IO  uint16_t                       EIC_NMIFLAG;        /**< Offset: 0x02 (R/W  16) NMI Interrupt Flag */
  __I   uint32_t                       EIC_SYNCBUSY;       /**< Offset: 0x04 (R/   32) Syncbusy register */
  __IO  uint32_t                       EIC_EVCTRL;         /**< Offset: 0x08 (R/W  32) Event Control */
  __IO  uint32_t                       EIC_INTENCLR;       /**< Offset: 0x0C (R/W  32) Interrupt Enable Clear */
  __IO  uint32_t                       EIC_INTENSET;       /**< Offset: 0x10 (R/W  32) Interrupt Enable Set */
  __IO  uint32_t                       EIC_INTFLAG;        /**< Offset: 0x14 (R/W  32) Interrupt Flag Status and Clear */
  __IO  uint32_t                       EIC_ASYNCH;         /**< Offset: 0x18 (R/W  32) EIC Asynchronous edge Detection Enable */
  __IO  uint32_t                       EIC_CONFIG[2];      /**< Offset: 0x1C (R/W  32) Configuration n */
} eic_registers_t;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* _SAMC21_EIC_COMPONENT_H_ */
