/**
 * \brief Component description for OSCCTRL
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
#ifndef _SAMC21_OSCCTRL_COMPONENT_H_
#define _SAMC21_OSCCTRL_COMPONENT_H_

/* ************************************************************************** */
/*   SOFTWARE API DEFINITION FOR OSCCTRL                                      */
/* ************************************************************************** */

/* -------- OSCCTRL_INTENCLR : (OSCCTRL Offset: 0x00) (R/W 32) Interrupt Enable Clear -------- */
#define OSCCTRL_INTENCLR_RESETVALUE           _U_(0x00)                                            /**<  (OSCCTRL_INTENCLR) Interrupt Enable Clear  Reset Value */

#define OSCCTRL_INTENCLR_XOSCRDY_Pos          _U_(0)                                               /**< (OSCCTRL_INTENCLR) XOSC Ready Interrupt Enable Position */
#define OSCCTRL_INTENCLR_XOSCRDY_Msk          (_U_(0x1) << OSCCTRL_INTENCLR_XOSCRDY_Pos)           /**< (OSCCTRL_INTENCLR) XOSC Ready Interrupt Enable Mask */
#define OSCCTRL_INTENCLR_XOSCRDY(value)       (OSCCTRL_INTENCLR_XOSCRDY_Msk & ((value) << OSCCTRL_INTENCLR_XOSCRDY_Pos))
#define OSCCTRL_INTENCLR_XOSCFAIL_Pos         _U_(1)                                               /**< (OSCCTRL_INTENCLR) XOSC Clock Failure Detector Interrupt Enable Position */
#define OSCCTRL_INTENCLR_XOSCFAIL_Msk         (_U_(0x1) << OSCCTRL_INTENCLR_XOSCFAIL_Pos)          /**< (OSCCTRL_INTENCLR) XOSC Clock Failure Detector Interrupt Enable Mask */
#define OSCCTRL_INTENCLR_XOSCFAIL(value)      (OSCCTRL_INTENCLR_XOSCFAIL_Msk & ((value) << OSCCTRL_INTENCLR_XOSCFAIL_Pos))
#define OSCCTRL_INTENCLR_OSC48MRDY_Pos        _U_(4)                                               /**< (OSCCTRL_INTENCLR) OSC48M Ready Interrupt Enable Position */
#define OSCCTRL_INTENCLR_OSC48MRDY_Msk        (_U_(0x1) << OSCCTRL_INTENCLR_OSC48MRDY_Pos)         /**< (OSCCTRL_INTENCLR) OSC48M Ready Interrupt Enable Mask */
#define OSCCTRL_INTENCLR_OSC48MRDY(value)     (OSCCTRL_INTENCLR_OSC48MRDY_Msk & ((value) << OSCCTRL_INTENCLR_OSC48MRDY_Pos))
#define OSCCTRL_INTENCLR_DPLLLCKR_Pos         _U_(8)                                               /**< (OSCCTRL_INTENCLR) DPLL Lock Rise Interrupt Enable Position */
#define OSCCTRL_INTENCLR_DPLLLCKR_Msk         (_U_(0x1) << OSCCTRL_INTENCLR_DPLLLCKR_Pos)          /**< (OSCCTRL_INTENCLR) DPLL Lock Rise Interrupt Enable Mask */
#define OSCCTRL_INTENCLR_DPLLLCKR(value)      (OSCCTRL_INTENCLR_DPLLLCKR_Msk & ((value) << OSCCTRL_INTENCLR_DPLLLCKR_Pos))
#define OSCCTRL_INTENCLR_DPLLLCKF_Pos         _U_(9)                                               /**< (OSCCTRL_INTENCLR) DPLL Lock Fall Interrupt Enable Position */
#define OSCCTRL_INTENCLR_DPLLLCKF_Msk         (_U_(0x1) << OSCCTRL_INTENCLR_DPLLLCKF_Pos)          /**< (OSCCTRL_INTENCLR) DPLL Lock Fall Interrupt Enable Mask */
#define OSCCTRL_INTENCLR_DPLLLCKF(value)      (OSCCTRL_INTENCLR_DPLLLCKF_Msk & ((value) << OSCCTRL_INTENCLR_DPLLLCKF_Pos))
#define OSCCTRL_INTENCLR_DPLLLTO_Pos          _U_(10)                                              /**< (OSCCTRL_INTENCLR) DPLL Time Out Interrupt Enable Position */
#define OSCCTRL_INTENCLR_DPLLLTO_Msk          (_U_(0x1) << OSCCTRL_INTENCLR_DPLLLTO_Pos)           /**< (OSCCTRL_INTENCLR) DPLL Time Out Interrupt Enable Mask */
#define OSCCTRL_INTENCLR_DPLLLTO(value)       (OSCCTRL_INTENCLR_DPLLLTO_Msk & ((value) << OSCCTRL_INTENCLR_DPLLLTO_Pos))
#define OSCCTRL_INTENCLR_DPLLLDRTO_Pos        _U_(11)                                              /**< (OSCCTRL_INTENCLR) DPLL Ratio Ready Interrupt Enable Position */
#define OSCCTRL_INTENCLR_DPLLLDRTO_Msk        (_U_(0x1) << OSCCTRL_INTENCLR_DPLLLDRTO_Pos)         /**< (OSCCTRL_INTENCLR) DPLL Ratio Ready Interrupt Enable Mask */
#define OSCCTRL_INTENCLR_DPLLLDRTO(value)     (OSCCTRL_INTENCLR_DPLLLDRTO_Msk & ((value) << OSCCTRL_INTENCLR_DPLLLDRTO_Pos))
#define OSCCTRL_INTENCLR_Msk                  _U_(0x00000F13)                                      /**< (OSCCTRL_INTENCLR) Register Mask  */


/* -------- OSCCTRL_INTENSET : (OSCCTRL Offset: 0x04) (R/W 32) Interrupt Enable Set -------- */
#define OSCCTRL_INTENSET_RESETVALUE           _U_(0x00)                                            /**<  (OSCCTRL_INTENSET) Interrupt Enable Set  Reset Value */

#define OSCCTRL_INTENSET_XOSCRDY_Pos          _U_(0)                                               /**< (OSCCTRL_INTENSET) XOSC Ready Interrupt Enable Position */
#define OSCCTRL_INTENSET_XOSCRDY_Msk          (_U_(0x1) << OSCCTRL_INTENSET_XOSCRDY_Pos)           /**< (OSCCTRL_INTENSET) XOSC Ready Interrupt Enable Mask */
#define OSCCTRL_INTENSET_XOSCRDY(value)       (OSCCTRL_INTENSET_XOSCRDY_Msk & ((value) << OSCCTRL_INTENSET_XOSCRDY_Pos))
#define OSCCTRL_INTENSET_XOSCFAIL_Pos         _U_(1)                                               /**< (OSCCTRL_INTENSET) XOSC Clock Failure Detector Interrupt Enable Position */
#define OSCCTRL_INTENSET_XOSCFAIL_Msk         (_U_(0x1) << OSCCTRL_INTENSET_XOSCFAIL_Pos)          /**< (OSCCTRL_INTENSET) XOSC Clock Failure Detector Interrupt Enable Mask */
#define OSCCTRL_INTENSET_XOSCFAIL(value)      (OSCCTRL_INTENSET_XOSCFAIL_Msk & ((value) << OSCCTRL_INTENSET_XOSCFAIL_Pos))
#define OSCCTRL_INTENSET_OSC48MRDY_Pos        _U_(4)                                               /**< (OSCCTRL_INTENSET) OSC48M Ready Interrupt Enable Position */
#define OSCCTRL_INTENSET_OSC48MRDY_Msk        (_U_(0x1) << OSCCTRL_INTENSET_OSC48MRDY_Pos)         /**< (OSCCTRL_INTENSET) OSC48M Ready Interrupt Enable Mask */
#define OSCCTRL_INTENSET_OSC48MRDY(value)     (OSCCTRL_INTENSET_OSC48MRDY_Msk & ((value) << OSCCTRL_INTENSET_OSC48MRDY_Pos))
#define OSCCTRL_INTENSET_DPLLLCKR_Pos         _U_(8)                                               /**< (OSCCTRL_INTENSET) DPLL Lock Rise Interrupt Enable Position */
#define OSCCTRL_INTENSET_DPLLLCKR_Msk         (_U_(0x1) << OSCCTRL_INTENSET_DPLLLCKR_Pos)          /**< (OSCCTRL_INTENSET) DPLL Lock Rise Interrupt Enable Mask */
#define OSCCTRL_INTENSET_DPLLLCKR(value)      (OSCCTRL_INTENSET_DPLLLCKR_Msk & ((value) << OSCCTRL_INTENSET_DPLLLCKR_Pos))
#define OSCCTRL_INTENSET_DPLLLCKF_Pos         _U_(9)                                               /**< (OSCCTRL_INTENSET) DPLL Lock Fall Interrupt Enable Position */
#define OSCCTRL_INTENSET_DPLLLCKF_Msk         (_U_(0x1) << OSCCTRL_INTENSET_DPLLLCKF_Pos)          /**< (OSCCTRL_INTENSET) DPLL Lock Fall Interrupt Enable Mask */
#define OSCCTRL_INTENSET_DPLLLCKF(value)      (OSCCTRL_INTENSET_DPLLLCKF_Msk & ((value) << OSCCTRL_INTENSET_DPLLLCKF_Pos))
#define OSCCTRL_INTENSET_DPLLLTO_Pos          _U_(10)                                              /**< (OSCCTRL_INTENSET) DPLL Time Out Interrupt Enable Position */
#define OSCCTRL_INTENSET_DPLLLTO_Msk          (_U_(0x1) << OSCCTRL_INTENSET_DPLLLTO_Pos)           /**< (OSCCTRL_INTENSET) DPLL Time Out Interrupt Enable Mask */
#define OSCCTRL_INTENSET_DPLLLTO(value)       (OSCCTRL_INTENSET_DPLLLTO_Msk & ((value) << OSCCTRL_INTENSET_DPLLLTO_Pos))
#define OSCCTRL_INTENSET_DPLLLDRTO_Pos        _U_(11)                                              /**< (OSCCTRL_INTENSET) DPLL Ratio Ready Interrupt Enable Position */
#define OSCCTRL_INTENSET_DPLLLDRTO_Msk        (_U_(0x1) << OSCCTRL_INTENSET_DPLLLDRTO_Pos)         /**< (OSCCTRL_INTENSET) DPLL Ratio Ready Interrupt Enable Mask */
#define OSCCTRL_INTENSET_DPLLLDRTO(value)     (OSCCTRL_INTENSET_DPLLLDRTO_Msk & ((value) << OSCCTRL_INTENSET_DPLLLDRTO_Pos))
#define OSCCTRL_INTENSET_Msk                  _U_(0x00000F13)                                      /**< (OSCCTRL_INTENSET) Register Mask  */


/* -------- OSCCTRL_INTFLAG : (OSCCTRL Offset: 0x08) (R/W 32) Interrupt Flag Status and Clear -------- */
#define OSCCTRL_INTFLAG_RESETVALUE            _U_(0x00)                                            /**<  (OSCCTRL_INTFLAG) Interrupt Flag Status and Clear  Reset Value */

#define OSCCTRL_INTFLAG_XOSCRDY_Pos           _U_(0)                                               /**< (OSCCTRL_INTFLAG) XOSC Ready Position */
#define OSCCTRL_INTFLAG_XOSCRDY_Msk           (_U_(0x1) << OSCCTRL_INTFLAG_XOSCRDY_Pos)            /**< (OSCCTRL_INTFLAG) XOSC Ready Mask */
#define OSCCTRL_INTFLAG_XOSCRDY(value)        (OSCCTRL_INTFLAG_XOSCRDY_Msk & ((value) << OSCCTRL_INTFLAG_XOSCRDY_Pos))
#define OSCCTRL_INTFLAG_XOSCFAIL_Pos          _U_(1)                                               /**< (OSCCTRL_INTFLAG) XOSC Clock Failure Detector Position */
#define OSCCTRL_INTFLAG_XOSCFAIL_Msk          (_U_(0x1) << OSCCTRL_INTFLAG_XOSCFAIL_Pos)           /**< (OSCCTRL_INTFLAG) XOSC Clock Failure Detector Mask */
#define OSCCTRL_INTFLAG_XOSCFAIL(value)       (OSCCTRL_INTFLAG_XOSCFAIL_Msk & ((value) << OSCCTRL_INTFLAG_XOSCFAIL_Pos))
#define OSCCTRL_INTFLAG_OSC48MRDY_Pos         _U_(4)                                               /**< (OSCCTRL_INTFLAG) OSC48M Ready Position */
#define OSCCTRL_INTFLAG_OSC48MRDY_Msk         (_U_(0x1) << OSCCTRL_INTFLAG_OSC48MRDY_Pos)          /**< (OSCCTRL_INTFLAG) OSC48M Ready Mask */
#define OSCCTRL_INTFLAG_OSC48MRDY(value)      (OSCCTRL_INTFLAG_OSC48MRDY_Msk & ((value) << OSCCTRL_INTFLAG_OSC48MRDY_Pos))
#define OSCCTRL_INTFLAG_DPLLLCKR_Pos          _U_(8)                                               /**< (OSCCTRL_INTFLAG) DPLL Lock Rise Position */
#define OSCCTRL_INTFLAG_DPLLLCKR_Msk          (_U_(0x1) << OSCCTRL_INTFLAG_DPLLLCKR_Pos)           /**< (OSCCTRL_INTFLAG) DPLL Lock Rise Mask */
#define OSCCTRL_INTFLAG_DPLLLCKR(value)       (OSCCTRL_INTFLAG_DPLLLCKR_Msk & ((value) << OSCCTRL_INTFLAG_DPLLLCKR_Pos))
#define OSCCTRL_INTFLAG_DPLLLCKF_Pos          _U_(9)                                               /**< (OSCCTRL_INTFLAG) DPLL Lock Fall Position */
#define OSCCTRL_INTFLAG_DPLLLCKF_Msk          (_U_(0x1) << OSCCTRL_INTFLAG_DPLLLCKF_Pos)           /**< (OSCCTRL_INTFLAG) DPLL Lock Fall Mask */
#define OSCCTRL_INTFLAG_DPLLLCKF(value)       (OSCCTRL_INTFLAG_DPLLLCKF_Msk & ((value) << OSCCTRL_INTFLAG_DPLLLCKF_Pos))
#define OSCCTRL_INTFLAG_DPLLLTO_Pos           _U_(10)                                              /**< (OSCCTRL_INTFLAG) DPLL Timeout Position */
#define OSCCTRL_INTFLAG_DPLLLTO_Msk           (_U_(0x1) << OSCCTRL_INTFLAG_DPLLLTO_Pos)            /**< (OSCCTRL_INTFLAG) DPLL Timeout Mask */
#define OSCCTRL_INTFLAG_DPLLLTO(value)        (OSCCTRL_INTFLAG_DPLLLTO_Msk & ((value) << OSCCTRL_INTFLAG_DPLLLTO_Pos))
#define OSCCTRL_INTFLAG_DPLLLDRTO_Pos         _U_(11)                                              /**< (OSCCTRL_INTFLAG) DPLL Ratio Ready Position */
#define OSCCTRL_INTFLAG_DPLLLDRTO_Msk         (_U_(0x1) << OSCCTRL_INTFLAG_DPLLLDRTO_Pos)          /**< (OSCCTRL_INTFLAG) DPLL Ratio Ready Mask */
#define OSCCTRL_INTFLAG_DPLLLDRTO(value)      (OSCCTRL_INTFLAG_DPLLLDRTO_Msk & ((value) << OSCCTRL_INTFLAG_DPLLLDRTO_Pos))
#define OSCCTRL_INTFLAG_Msk                   _U_(0x00000F13)                                      /**< (OSCCTRL_INTFLAG) Register Mask  */


/* -------- OSCCTRL_STATUS : (OSCCTRL Offset: 0x0C) ( R/ 32) Power and Clocks Status -------- */
#define OSCCTRL_STATUS_RESETVALUE             _U_(0x00)                                            /**<  (OSCCTRL_STATUS) Power and Clocks Status  Reset Value */

#define OSCCTRL_STATUS_XOSCRDY_Pos            _U_(0)                                               /**< (OSCCTRL_STATUS) XOSC Ready Position */
#define OSCCTRL_STATUS_XOSCRDY_Msk            (_U_(0x1) << OSCCTRL_STATUS_XOSCRDY_Pos)             /**< (OSCCTRL_STATUS) XOSC Ready Mask */
#define OSCCTRL_STATUS_XOSCRDY(value)         (OSCCTRL_STATUS_XOSCRDY_Msk & ((value) << OSCCTRL_STATUS_XOSCRDY_Pos))
#define OSCCTRL_STATUS_XOSCFAIL_Pos           _U_(1)                                               /**< (OSCCTRL_STATUS) XOSC Clock Failure Detector Position */
#define OSCCTRL_STATUS_XOSCFAIL_Msk           (_U_(0x1) << OSCCTRL_STATUS_XOSCFAIL_Pos)            /**< (OSCCTRL_STATUS) XOSC Clock Failure Detector Mask */
#define OSCCTRL_STATUS_XOSCFAIL(value)        (OSCCTRL_STATUS_XOSCFAIL_Msk & ((value) << OSCCTRL_STATUS_XOSCFAIL_Pos))
#define OSCCTRL_STATUS_XOSCCKSW_Pos           _U_(2)                                               /**< (OSCCTRL_STATUS) XOSC Clock Switch Position */
#define OSCCTRL_STATUS_XOSCCKSW_Msk           (_U_(0x1) << OSCCTRL_STATUS_XOSCCKSW_Pos)            /**< (OSCCTRL_STATUS) XOSC Clock Switch Mask */
#define OSCCTRL_STATUS_XOSCCKSW(value)        (OSCCTRL_STATUS_XOSCCKSW_Msk & ((value) << OSCCTRL_STATUS_XOSCCKSW_Pos))
#define OSCCTRL_STATUS_OSC48MRDY_Pos          _U_(4)                                               /**< (OSCCTRL_STATUS) OSC48M Ready Position */
#define OSCCTRL_STATUS_OSC48MRDY_Msk          (_U_(0x1) << OSCCTRL_STATUS_OSC48MRDY_Pos)           /**< (OSCCTRL_STATUS) OSC48M Ready Mask */
#define OSCCTRL_STATUS_OSC48MRDY(value)       (OSCCTRL_STATUS_OSC48MRDY_Msk & ((value) << OSCCTRL_STATUS_OSC48MRDY_Pos))
#define OSCCTRL_STATUS_DPLLLCKR_Pos           _U_(8)                                               /**< (OSCCTRL_STATUS) DPLL Lock Rise Position */
#define OSCCTRL_STATUS_DPLLLCKR_Msk           (_U_(0x1) << OSCCTRL_STATUS_DPLLLCKR_Pos)            /**< (OSCCTRL_STATUS) DPLL Lock Rise Mask */
#define OSCCTRL_STATUS_DPLLLCKR(value)        (OSCCTRL_STATUS_DPLLLCKR_Msk & ((value) << OSCCTRL_STATUS_DPLLLCKR_Pos))
#define OSCCTRL_STATUS_DPLLLCKF_Pos           _U_(9)                                               /**< (OSCCTRL_STATUS) DPLL Lock Fall Position */
#define OSCCTRL_STATUS_DPLLLCKF_Msk           (_U_(0x1) << OSCCTRL_STATUS_DPLLLCKF_Pos)            /**< (OSCCTRL_STATUS) DPLL Lock Fall Mask */
#define OSCCTRL_STATUS_DPLLLCKF(value)        (OSCCTRL_STATUS_DPLLLCKF_Msk & ((value) << OSCCTRL_STATUS_DPLLLCKF_Pos))
#define OSCCTRL_STATUS_DPLLTO_Pos             _U_(10)                                              /**< (OSCCTRL_STATUS) DPLL Timeout Position */
#define OSCCTRL_STATUS_DPLLTO_Msk             (_U_(0x1) << OSCCTRL_STATUS_DPLLTO_Pos)              /**< (OSCCTRL_STATUS) DPLL Timeout Mask */
#define OSCCTRL_STATUS_DPLLTO(value)          (OSCCTRL_STATUS_DPLLTO_Msk & ((value) << OSCCTRL_STATUS_DPLLTO_Pos))
#define OSCCTRL_STATUS_DPLLLDRTO_Pos          _U_(11)                                              /**< (OSCCTRL_STATUS) DPLL Ratio Ready Position */
#define OSCCTRL_STATUS_DPLLLDRTO_Msk          (_U_(0x1) << OSCCTRL_STATUS_DPLLLDRTO_Pos)           /**< (OSCCTRL_STATUS) DPLL Ratio Ready Mask */
#define OSCCTRL_STATUS_DPLLLDRTO(value)       (OSCCTRL_STATUS_DPLLLDRTO_Msk & ((value) << OSCCTRL_STATUS_DPLLLDRTO_Pos))
#define OSCCTRL_STATUS_Msk                    _U_(0x00000F17)                                      /**< (OSCCTRL_STATUS) Register Mask  */


/* -------- OSCCTRL_XOSCCTRL : (OSCCTRL Offset: 0x10) (R/W 16) External Multipurpose Crystal Oscillator (XOSC) Control -------- */
#define OSCCTRL_XOSCCTRL_RESETVALUE           _U_(0x80)                                            /**<  (OSCCTRL_XOSCCTRL) External Multipurpose Crystal Oscillator (XOSC) Control  Reset Value */

#define OSCCTRL_XOSCCTRL_ENABLE_Pos           _U_(1)                                               /**< (OSCCTRL_XOSCCTRL) Oscillator Enable Position */
#define OSCCTRL_XOSCCTRL_ENABLE_Msk           (_U_(0x1) << OSCCTRL_XOSCCTRL_ENABLE_Pos)            /**< (OSCCTRL_XOSCCTRL) Oscillator Enable Mask */
#define OSCCTRL_XOSCCTRL_ENABLE(value)        (OSCCTRL_XOSCCTRL_ENABLE_Msk & ((value) << OSCCTRL_XOSCCTRL_ENABLE_Pos))
#define OSCCTRL_XOSCCTRL_XTALEN_Pos           _U_(2)                                               /**< (OSCCTRL_XOSCCTRL) Crystal Oscillator Enable Position */
#define OSCCTRL_XOSCCTRL_XTALEN_Msk           (_U_(0x1) << OSCCTRL_XOSCCTRL_XTALEN_Pos)            /**< (OSCCTRL_XOSCCTRL) Crystal Oscillator Enable Mask */
#define OSCCTRL_XOSCCTRL_XTALEN(value)        (OSCCTRL_XOSCCTRL_XTALEN_Msk & ((value) << OSCCTRL_XOSCCTRL_XTALEN_Pos))
#define OSCCTRL_XOSCCTRL_CFDEN_Pos            _U_(3)                                               /**< (OSCCTRL_XOSCCTRL) Xosc Clock Failure Detector Enable Position */
#define OSCCTRL_XOSCCTRL_CFDEN_Msk            (_U_(0x1) << OSCCTRL_XOSCCTRL_CFDEN_Pos)             /**< (OSCCTRL_XOSCCTRL) Xosc Clock Failure Detector Enable Mask */
#define OSCCTRL_XOSCCTRL_CFDEN(value)         (OSCCTRL_XOSCCTRL_CFDEN_Msk & ((value) << OSCCTRL_XOSCCTRL_CFDEN_Pos))
#define OSCCTRL_XOSCCTRL_SWBEN_Pos            _U_(4)                                               /**< (OSCCTRL_XOSCCTRL) Xosc Clock Switch Enable Position */
#define OSCCTRL_XOSCCTRL_SWBEN_Msk            (_U_(0x1) << OSCCTRL_XOSCCTRL_SWBEN_Pos)             /**< (OSCCTRL_XOSCCTRL) Xosc Clock Switch Enable Mask */
#define OSCCTRL_XOSCCTRL_SWBEN(value)         (OSCCTRL_XOSCCTRL_SWBEN_Msk & ((value) << OSCCTRL_XOSCCTRL_SWBEN_Pos))
#define OSCCTRL_XOSCCTRL_RUNSTDBY_Pos         _U_(6)                                               /**< (OSCCTRL_XOSCCTRL) Run in Standby Position */
#define OSCCTRL_XOSCCTRL_RUNSTDBY_Msk         (_U_(0x1) << OSCCTRL_XOSCCTRL_RUNSTDBY_Pos)          /**< (OSCCTRL_XOSCCTRL) Run in Standby Mask */
#define OSCCTRL_XOSCCTRL_RUNSTDBY(value)      (OSCCTRL_XOSCCTRL_RUNSTDBY_Msk & ((value) << OSCCTRL_XOSCCTRL_RUNSTDBY_Pos))
#define OSCCTRL_XOSCCTRL_ONDEMAND_Pos         _U_(7)                                               /**< (OSCCTRL_XOSCCTRL) On Demand Control Position */
#define OSCCTRL_XOSCCTRL_ONDEMAND_Msk         (_U_(0x1) << OSCCTRL_XOSCCTRL_ONDEMAND_Pos)          /**< (OSCCTRL_XOSCCTRL) On Demand Control Mask */
#define OSCCTRL_XOSCCTRL_ONDEMAND(value)      (OSCCTRL_XOSCCTRL_ONDEMAND_Msk & ((value) << OSCCTRL_XOSCCTRL_ONDEMAND_Pos))
#define OSCCTRL_XOSCCTRL_GAIN_Pos             _U_(8)                                               /**< (OSCCTRL_XOSCCTRL) Oscillator Gain Position */
#define OSCCTRL_XOSCCTRL_GAIN_Msk             (_U_(0x7) << OSCCTRL_XOSCCTRL_GAIN_Pos)              /**< (OSCCTRL_XOSCCTRL) Oscillator Gain Mask */
#define OSCCTRL_XOSCCTRL_GAIN(value)          (OSCCTRL_XOSCCTRL_GAIN_Msk & ((value) << OSCCTRL_XOSCCTRL_GAIN_Pos))
#define   OSCCTRL_XOSCCTRL_GAIN_GAIN2_Val     _U_(0x0)                                             /**< (OSCCTRL_XOSCCTRL) 2 MHz  */
#define   OSCCTRL_XOSCCTRL_GAIN_GAIN4_Val     _U_(0x1)                                             /**< (OSCCTRL_XOSCCTRL) 4 MHz  */
#define   OSCCTRL_XOSCCTRL_GAIN_GAIN8_Val     _U_(0x2)                                             /**< (OSCCTRL_XOSCCTRL) 8 MHz  */
#define   OSCCTRL_XOSCCTRL_GAIN_GAIN16_Val    _U_(0x3)                                             /**< (OSCCTRL_XOSCCTRL) 16 MHz  */
#define   OSCCTRL_XOSCCTRL_GAIN_GAIN30_Val    _U_(0x4)                                             /**< (OSCCTRL_XOSCCTRL) 30 MHz  */
#define OSCCTRL_XOSCCTRL_GAIN_GAIN2           (OSCCTRL_XOSCCTRL_GAIN_GAIN2_Val << OSCCTRL_XOSCCTRL_GAIN_Pos) /**< (OSCCTRL_XOSCCTRL) 2 MHz Position  */
#define OSCCTRL_XOSCCTRL_GAIN_GAIN4           (OSCCTRL_XOSCCTRL_GAIN_GAIN4_Val << OSCCTRL_XOSCCTRL_GAIN_Pos) /**< (OSCCTRL_XOSCCTRL) 4 MHz Position  */
#define OSCCTRL_XOSCCTRL_GAIN_GAIN8           (OSCCTRL_XOSCCTRL_GAIN_GAIN8_Val << OSCCTRL_XOSCCTRL_GAIN_Pos) /**< (OSCCTRL_XOSCCTRL) 8 MHz Position  */
#define OSCCTRL_XOSCCTRL_GAIN_GAIN16          (OSCCTRL_XOSCCTRL_GAIN_GAIN16_Val << OSCCTRL_XOSCCTRL_GAIN_Pos) /**< (OSCCTRL_XOSCCTRL) 16 MHz Position  */
#define OSCCTRL_XOSCCTRL_GAIN_GAIN30          (OSCCTRL_XOSCCTRL_GAIN_GAIN30_Val << OSCCTRL_XOSCCTRL_GAIN_Pos) /**< (OSCCTRL_XOSCCTRL) 30 MHz Position  */
#define OSCCTRL_XOSCCTRL_AMPGC_Pos            _U_(11)                                              /**< (OSCCTRL_XOSCCTRL) Automatic Amplitude Gain Control Position */
#define OSCCTRL_XOSCCTRL_AMPGC_Msk            (_U_(0x1) << OSCCTRL_XOSCCTRL_AMPGC_Pos)             /**< (OSCCTRL_XOSCCTRL) Automatic Amplitude Gain Control Mask */
#define OSCCTRL_XOSCCTRL_AMPGC(value)         (OSCCTRL_XOSCCTRL_AMPGC_Msk & ((value) << OSCCTRL_XOSCCTRL_AMPGC_Pos))
#define OSCCTRL_XOSCCTRL_STARTUP_Pos          _U_(12)                                              /**< (OSCCTRL_XOSCCTRL) Start-Up Time Position */
#define OSCCTRL_XOSCCTRL_STARTUP_Msk          (_U_(0xF) << OSCCTRL_XOSCCTRL_STARTUP_Pos)           /**< (OSCCTRL_XOSCCTRL) Start-Up Time Mask */
#define OSCCTRL_XOSCCTRL_STARTUP(value)       (OSCCTRL_XOSCCTRL_STARTUP_Msk & ((value) << OSCCTRL_XOSCCTRL_STARTUP_Pos))
#define   OSCCTRL_XOSCCTRL_STARTUP_CYCLE1_Val _U_(0x0)                                             /**< (OSCCTRL_XOSCCTRL) 31 us  */
#define   OSCCTRL_XOSCCTRL_STARTUP_CYCLE2_Val _U_(0x1)                                             /**< (OSCCTRL_XOSCCTRL) 61 us  */
#define   OSCCTRL_XOSCCTRL_STARTUP_CYCLE4_Val _U_(0x2)                                             /**< (OSCCTRL_XOSCCTRL) 122 us  */
#define   OSCCTRL_XOSCCTRL_STARTUP_CYCLE8_Val _U_(0x3)                                             /**< (OSCCTRL_XOSCCTRL) 244 us  */
#define   OSCCTRL_XOSCCTRL_STARTUP_CYCLE16_Val _U_(0x4)                                             /**< (OSCCTRL_XOSCCTRL) 488 us  */
#define   OSCCTRL_XOSCCTRL_STARTUP_CYCLE32_Val _U_(0x5)                                             /**< (OSCCTRL_XOSCCTRL) 977 us  */
#define   OSCCTRL_XOSCCTRL_STARTUP_CYCLE64_Val _U_(0x6)                                             /**< (OSCCTRL_XOSCCTRL) 1953 us  */
#define   OSCCTRL_XOSCCTRL_STARTUP_CYCLE128_Val _U_(0x7)                                             /**< (OSCCTRL_XOSCCTRL) 3906 us  */
#define   OSCCTRL_XOSCCTRL_STARTUP_CYCLE256_Val _U_(0x8)                                             /**< (OSCCTRL_XOSCCTRL) 7813 us  */
#define   OSCCTRL_XOSCCTRL_STARTUP_CYCLE512_Val _U_(0x9)                                             /**< (OSCCTRL_XOSCCTRL) 15625 us  */
#define   OSCCTRL_XOSCCTRL_STARTUP_CYCLE1024_Val _U_(0xA)                                             /**< (OSCCTRL_XOSCCTRL) 31250 us  */
#define   OSCCTRL_XOSCCTRL_STARTUP_CYCLE2048_Val _U_(0xB)                                             /**< (OSCCTRL_XOSCCTRL) 62500 us  */
#define   OSCCTRL_XOSCCTRL_STARTUP_CYCLE4096_Val _U_(0xC)                                             /**< (OSCCTRL_XOSCCTRL) 125000 us  */
#define   OSCCTRL_XOSCCTRL_STARTUP_CYCLE8192_Val _U_(0xD)                                             /**< (OSCCTRL_XOSCCTRL) 250000 us  */
#define   OSCCTRL_XOSCCTRL_STARTUP_CYCLE16384_Val _U_(0xE)                                             /**< (OSCCTRL_XOSCCTRL) 500000 us  */
#define   OSCCTRL_XOSCCTRL_STARTUP_CYCLE32768_Val _U_(0xF)                                             /**< (OSCCTRL_XOSCCTRL) 1000000 us  */
#define OSCCTRL_XOSCCTRL_STARTUP_CYCLE1       (OSCCTRL_XOSCCTRL_STARTUP_CYCLE1_Val << OSCCTRL_XOSCCTRL_STARTUP_Pos) /**< (OSCCTRL_XOSCCTRL) 31 us Position  */
#define OSCCTRL_XOSCCTRL_STARTUP_CYCLE2       (OSCCTRL_XOSCCTRL_STARTUP_CYCLE2_Val << OSCCTRL_XOSCCTRL_STARTUP_Pos) /**< (OSCCTRL_XOSCCTRL) 61 us Position  */
#define OSCCTRL_XOSCCTRL_STARTUP_CYCLE4       (OSCCTRL_XOSCCTRL_STARTUP_CYCLE4_Val << OSCCTRL_XOSCCTRL_STARTUP_Pos) /**< (OSCCTRL_XOSCCTRL) 122 us Position  */
#define OSCCTRL_XOSCCTRL_STARTUP_CYCLE8       (OSCCTRL_XOSCCTRL_STARTUP_CYCLE8_Val << OSCCTRL_XOSCCTRL_STARTUP_Pos) /**< (OSCCTRL_XOSCCTRL) 244 us Position  */
#define OSCCTRL_XOSCCTRL_STARTUP_CYCLE16      (OSCCTRL_XOSCCTRL_STARTUP_CYCLE16_Val << OSCCTRL_XOSCCTRL_STARTUP_Pos) /**< (OSCCTRL_XOSCCTRL) 488 us Position  */
#define OSCCTRL_XOSCCTRL_STARTUP_CYCLE32      (OSCCTRL_XOSCCTRL_STARTUP_CYCLE32_Val << OSCCTRL_XOSCCTRL_STARTUP_Pos) /**< (OSCCTRL_XOSCCTRL) 977 us Position  */
#define OSCCTRL_XOSCCTRL_STARTUP_CYCLE64      (OSCCTRL_XOSCCTRL_STARTUP_CYCLE64_Val << OSCCTRL_XOSCCTRL_STARTUP_Pos) /**< (OSCCTRL_XOSCCTRL) 1953 us Position  */
#define OSCCTRL_XOSCCTRL_STARTUP_CYCLE128     (OSCCTRL_XOSCCTRL_STARTUP_CYCLE128_Val << OSCCTRL_XOSCCTRL_STARTUP_Pos) /**< (OSCCTRL_XOSCCTRL) 3906 us Position  */
#define OSCCTRL_XOSCCTRL_STARTUP_CYCLE256     (OSCCTRL_XOSCCTRL_STARTUP_CYCLE256_Val << OSCCTRL_XOSCCTRL_STARTUP_Pos) /**< (OSCCTRL_XOSCCTRL) 7813 us Position  */
#define OSCCTRL_XOSCCTRL_STARTUP_CYCLE512     (OSCCTRL_XOSCCTRL_STARTUP_CYCLE512_Val << OSCCTRL_XOSCCTRL_STARTUP_Pos) /**< (OSCCTRL_XOSCCTRL) 15625 us Position  */
#define OSCCTRL_XOSCCTRL_STARTUP_CYCLE1024    (OSCCTRL_XOSCCTRL_STARTUP_CYCLE1024_Val << OSCCTRL_XOSCCTRL_STARTUP_Pos) /**< (OSCCTRL_XOSCCTRL) 31250 us Position  */
#define OSCCTRL_XOSCCTRL_STARTUP_CYCLE2048    (OSCCTRL_XOSCCTRL_STARTUP_CYCLE2048_Val << OSCCTRL_XOSCCTRL_STARTUP_Pos) /**< (OSCCTRL_XOSCCTRL) 62500 us Position  */
#define OSCCTRL_XOSCCTRL_STARTUP_CYCLE4096    (OSCCTRL_XOSCCTRL_STARTUP_CYCLE4096_Val << OSCCTRL_XOSCCTRL_STARTUP_Pos) /**< (OSCCTRL_XOSCCTRL) 125000 us Position  */
#define OSCCTRL_XOSCCTRL_STARTUP_CYCLE8192    (OSCCTRL_XOSCCTRL_STARTUP_CYCLE8192_Val << OSCCTRL_XOSCCTRL_STARTUP_Pos) /**< (OSCCTRL_XOSCCTRL) 250000 us Position  */
#define OSCCTRL_XOSCCTRL_STARTUP_CYCLE16384   (OSCCTRL_XOSCCTRL_STARTUP_CYCLE16384_Val << OSCCTRL_XOSCCTRL_STARTUP_Pos) /**< (OSCCTRL_XOSCCTRL) 500000 us Position  */
#define OSCCTRL_XOSCCTRL_STARTUP_CYCLE32768   (OSCCTRL_XOSCCTRL_STARTUP_CYCLE32768_Val << OSCCTRL_XOSCCTRL_STARTUP_Pos) /**< (OSCCTRL_XOSCCTRL) 1000000 us Position  */
#define OSCCTRL_XOSCCTRL_Msk                  _U_(0xFFDE)                                          /**< (OSCCTRL_XOSCCTRL) Register Mask  */


/* -------- OSCCTRL_CFDPRESC : (OSCCTRL Offset: 0x12) (R/W 8) Clock Failure Detector Prescaler -------- */
#define OSCCTRL_CFDPRESC_RESETVALUE           _U_(0x00)                                            /**<  (OSCCTRL_CFDPRESC) Clock Failure Detector Prescaler  Reset Value */

#define OSCCTRL_CFDPRESC_CFDPRESC_Pos         _U_(0)                                               /**< (OSCCTRL_CFDPRESC) Clock Failure Detector Prescaler Position */
#define OSCCTRL_CFDPRESC_CFDPRESC_Msk         (_U_(0x7) << OSCCTRL_CFDPRESC_CFDPRESC_Pos)          /**< (OSCCTRL_CFDPRESC) Clock Failure Detector Prescaler Mask */
#define OSCCTRL_CFDPRESC_CFDPRESC(value)      (OSCCTRL_CFDPRESC_CFDPRESC_Msk & ((value) << OSCCTRL_CFDPRESC_CFDPRESC_Pos))
#define   OSCCTRL_CFDPRESC_CFDPRESC_DIV1_Val  _U_(0x0)                                             /**< (OSCCTRL_CFDPRESC) 48 MHz  */
#define   OSCCTRL_CFDPRESC_CFDPRESC_DIV2_Val  _U_(0x1)                                             /**< (OSCCTRL_CFDPRESC) 24 MHz  */
#define   OSCCTRL_CFDPRESC_CFDPRESC_DIV4_Val  _U_(0x2)                                             /**< (OSCCTRL_CFDPRESC) 12 MHz  */
#define   OSCCTRL_CFDPRESC_CFDPRESC_DIV8_Val  _U_(0x3)                                             /**< (OSCCTRL_CFDPRESC) 6 MHz  */
#define   OSCCTRL_CFDPRESC_CFDPRESC_DIV16_Val _U_(0x4)                                             /**< (OSCCTRL_CFDPRESC) 3 MHz  */
#define   OSCCTRL_CFDPRESC_CFDPRESC_DIV32_Val _U_(0x5)                                             /**< (OSCCTRL_CFDPRESC) 1.5 MHz  */
#define   OSCCTRL_CFDPRESC_CFDPRESC_DIV64_Val _U_(0x6)                                             /**< (OSCCTRL_CFDPRESC) 0.75 MHz  */
#define   OSCCTRL_CFDPRESC_CFDPRESC_DIV128_Val _U_(0x7)                                             /**< (OSCCTRL_CFDPRESC) 0.3125 MHz  */
#define OSCCTRL_CFDPRESC_CFDPRESC_DIV1        (OSCCTRL_CFDPRESC_CFDPRESC_DIV1_Val << OSCCTRL_CFDPRESC_CFDPRESC_Pos) /**< (OSCCTRL_CFDPRESC) 48 MHz Position  */
#define OSCCTRL_CFDPRESC_CFDPRESC_DIV2        (OSCCTRL_CFDPRESC_CFDPRESC_DIV2_Val << OSCCTRL_CFDPRESC_CFDPRESC_Pos) /**< (OSCCTRL_CFDPRESC) 24 MHz Position  */
#define OSCCTRL_CFDPRESC_CFDPRESC_DIV4        (OSCCTRL_CFDPRESC_CFDPRESC_DIV4_Val << OSCCTRL_CFDPRESC_CFDPRESC_Pos) /**< (OSCCTRL_CFDPRESC) 12 MHz Position  */
#define OSCCTRL_CFDPRESC_CFDPRESC_DIV8        (OSCCTRL_CFDPRESC_CFDPRESC_DIV8_Val << OSCCTRL_CFDPRESC_CFDPRESC_Pos) /**< (OSCCTRL_CFDPRESC) 6 MHz Position  */
#define OSCCTRL_CFDPRESC_CFDPRESC_DIV16       (OSCCTRL_CFDPRESC_CFDPRESC_DIV16_Val << OSCCTRL_CFDPRESC_CFDPRESC_Pos) /**< (OSCCTRL_CFDPRESC) 3 MHz Position  */
#define OSCCTRL_CFDPRESC_CFDPRESC_DIV32       (OSCCTRL_CFDPRESC_CFDPRESC_DIV32_Val << OSCCTRL_CFDPRESC_CFDPRESC_Pos) /**< (OSCCTRL_CFDPRESC) 1.5 MHz Position  */
#define OSCCTRL_CFDPRESC_CFDPRESC_DIV64       (OSCCTRL_CFDPRESC_CFDPRESC_DIV64_Val << OSCCTRL_CFDPRESC_CFDPRESC_Pos) /**< (OSCCTRL_CFDPRESC) 0.75 MHz Position  */
#define OSCCTRL_CFDPRESC_CFDPRESC_DIV128      (OSCCTRL_CFDPRESC_CFDPRESC_DIV128_Val << OSCCTRL_CFDPRESC_CFDPRESC_Pos) /**< (OSCCTRL_CFDPRESC) 0.3125 MHz Position  */
#define OSCCTRL_CFDPRESC_Msk                  _U_(0x07)                                            /**< (OSCCTRL_CFDPRESC) Register Mask  */


/* -------- OSCCTRL_EVCTRL : (OSCCTRL Offset: 0x13) (R/W 8) Event Control -------- */
#define OSCCTRL_EVCTRL_RESETVALUE             _U_(0x00)                                            /**<  (OSCCTRL_EVCTRL) Event Control  Reset Value */

#define OSCCTRL_EVCTRL_CFDEO_Pos              _U_(0)                                               /**< (OSCCTRL_EVCTRL) Clock Failure Detector Event Output Enable Position */
#define OSCCTRL_EVCTRL_CFDEO_Msk              (_U_(0x1) << OSCCTRL_EVCTRL_CFDEO_Pos)               /**< (OSCCTRL_EVCTRL) Clock Failure Detector Event Output Enable Mask */
#define OSCCTRL_EVCTRL_CFDEO(value)           (OSCCTRL_EVCTRL_CFDEO_Msk & ((value) << OSCCTRL_EVCTRL_CFDEO_Pos))
#define OSCCTRL_EVCTRL_Msk                    _U_(0x01)                                            /**< (OSCCTRL_EVCTRL) Register Mask  */


/* -------- OSCCTRL_OSC48MCTRL : (OSCCTRL Offset: 0x14) (R/W 8) 48MHz Internal Oscillator (OSC48M) Control -------- */
#define OSCCTRL_OSC48MCTRL_RESETVALUE         _U_(0x82)                                            /**<  (OSCCTRL_OSC48MCTRL) 48MHz Internal Oscillator (OSC48M) Control  Reset Value */

#define OSCCTRL_OSC48MCTRL_ENABLE_Pos         _U_(1)                                               /**< (OSCCTRL_OSC48MCTRL) Oscillator Enable Position */
#define OSCCTRL_OSC48MCTRL_ENABLE_Msk         (_U_(0x1) << OSCCTRL_OSC48MCTRL_ENABLE_Pos)          /**< (OSCCTRL_OSC48MCTRL) Oscillator Enable Mask */
#define OSCCTRL_OSC48MCTRL_ENABLE(value)      (OSCCTRL_OSC48MCTRL_ENABLE_Msk & ((value) << OSCCTRL_OSC48MCTRL_ENABLE_Pos))
#define OSCCTRL_OSC48MCTRL_RUNSTDBY_Pos       _U_(6)                                               /**< (OSCCTRL_OSC48MCTRL) Run in Standby Position */
#define OSCCTRL_OSC48MCTRL_RUNSTDBY_Msk       (_U_(0x1) << OSCCTRL_OSC48MCTRL_RUNSTDBY_Pos)        /**< (OSCCTRL_OSC48MCTRL) Run in Standby Mask */
#define OSCCTRL_OSC48MCTRL_RUNSTDBY(value)    (OSCCTRL_OSC48MCTRL_RUNSTDBY_Msk & ((value) << OSCCTRL_OSC48MCTRL_RUNSTDBY_Pos))
#define OSCCTRL_OSC48MCTRL_ONDEMAND_Pos       _U_(7)                                               /**< (OSCCTRL_OSC48MCTRL) On Demand Control Position */
#define OSCCTRL_OSC48MCTRL_ONDEMAND_Msk       (_U_(0x1) << OSCCTRL_OSC48MCTRL_ONDEMAND_Pos)        /**< (OSCCTRL_OSC48MCTRL) On Demand Control Mask */
#define OSCCTRL_OSC48MCTRL_ONDEMAND(value)    (OSCCTRL_OSC48MCTRL_ONDEMAND_Msk & ((value) << OSCCTRL_OSC48MCTRL_ONDEMAND_Pos))
#define OSCCTRL_OSC48MCTRL_Msk                _U_(0xC2)                                            /**< (OSCCTRL_OSC48MCTRL) Register Mask  */


/* -------- OSCCTRL_OSC48MDIV : (OSCCTRL Offset: 0x15) (R/W 8) OSC48M Divider -------- */
#define OSCCTRL_OSC48MDIV_RESETVALUE          _U_(0x0B)                                            /**<  (OSCCTRL_OSC48MDIV) OSC48M Divider  Reset Value */

#define OSCCTRL_OSC48MDIV_DIV_Pos             _U_(0)                                               /**< (OSCCTRL_OSC48MDIV) OSC48M Division Factor Position */
#define OSCCTRL_OSC48MDIV_DIV_Msk             (_U_(0xF) << OSCCTRL_OSC48MDIV_DIV_Pos)              /**< (OSCCTRL_OSC48MDIV) OSC48M Division Factor Mask */
#define OSCCTRL_OSC48MDIV_DIV(value)          (OSCCTRL_OSC48MDIV_DIV_Msk & ((value) << OSCCTRL_OSC48MDIV_DIV_Pos))
#define   OSCCTRL_OSC48MDIV_DIV_DIV1_Val      _U_(0x0)                                             /**< (OSCCTRL_OSC48MDIV) 48 MHz  */
#define   OSCCTRL_OSC48MDIV_DIV_DIV2_Val      _U_(0x1)                                             /**< (OSCCTRL_OSC48MDIV) 24 MHz  */
#define   OSCCTRL_OSC48MDIV_DIV_DIV3_Val      _U_(0x2)                                             /**< (OSCCTRL_OSC48MDIV) 16 MHz  */
#define   OSCCTRL_OSC48MDIV_DIV_DIV4_Val      _U_(0x3)                                             /**< (OSCCTRL_OSC48MDIV) 12 MHz  */
#define   OSCCTRL_OSC48MDIV_DIV_DIV5_Val      _U_(0x4)                                             /**< (OSCCTRL_OSC48MDIV) 9.6 MHz  */
#define   OSCCTRL_OSC48MDIV_DIV_DIV6_Val      _U_(0x5)                                             /**< (OSCCTRL_OSC48MDIV) 8 MHz  */
#define   OSCCTRL_OSC48MDIV_DIV_DIV7_Val      _U_(0x6)                                             /**< (OSCCTRL_OSC48MDIV) 6.86 MHz  */
#define   OSCCTRL_OSC48MDIV_DIV_DIV8_Val      _U_(0x7)                                             /**< (OSCCTRL_OSC48MDIV) 6 MHz  */
#define   OSCCTRL_OSC48MDIV_DIV_DIV9_Val      _U_(0x8)                                             /**< (OSCCTRL_OSC48MDIV) 5.33 MHz  */
#define   OSCCTRL_OSC48MDIV_DIV_DIV10_Val     _U_(0x9)                                             /**< (OSCCTRL_OSC48MDIV) 4.8 MHz  */
#define   OSCCTRL_OSC48MDIV_DIV_DIV11_Val     _U_(0xA)                                             /**< (OSCCTRL_OSC48MDIV) 4.36 MHz  */
#define   OSCCTRL_OSC48MDIV_DIV_DIV12_Val     _U_(0xB)                                             /**< (OSCCTRL_OSC48MDIV) 4 MHz  */
#define   OSCCTRL_OSC48MDIV_DIV_DIV13_Val     _U_(0xC)                                             /**< (OSCCTRL_OSC48MDIV) 3.69 MHz  */
#define   OSCCTRL_OSC48MDIV_DIV_DIV14_Val     _U_(0xD)                                             /**< (OSCCTRL_OSC48MDIV) 3.43 MHz  */
#define   OSCCTRL_OSC48MDIV_DIV_DIV15_Val     _U_(0xE)                                             /**< (OSCCTRL_OSC48MDIV) 3.2 MHz  */
#define   OSCCTRL_OSC48MDIV_DIV_DIV16_Val     _U_(0xF)                                             /**< (OSCCTRL_OSC48MDIV) 3 MHz  */
#define OSCCTRL_OSC48MDIV_DIV_DIV1            (OSCCTRL_OSC48MDIV_DIV_DIV1_Val << OSCCTRL_OSC48MDIV_DIV_Pos) /**< (OSCCTRL_OSC48MDIV) 48 MHz Position  */
#define OSCCTRL_OSC48MDIV_DIV_DIV2            (OSCCTRL_OSC48MDIV_DIV_DIV2_Val << OSCCTRL_OSC48MDIV_DIV_Pos) /**< (OSCCTRL_OSC48MDIV) 24 MHz Position  */
#define OSCCTRL_OSC48MDIV_DIV_DIV3            (OSCCTRL_OSC48MDIV_DIV_DIV3_Val << OSCCTRL_OSC48MDIV_DIV_Pos) /**< (OSCCTRL_OSC48MDIV) 16 MHz Position  */
#define OSCCTRL_OSC48MDIV_DIV_DIV4            (OSCCTRL_OSC48MDIV_DIV_DIV4_Val << OSCCTRL_OSC48MDIV_DIV_Pos) /**< (OSCCTRL_OSC48MDIV) 12 MHz Position  */
#define OSCCTRL_OSC48MDIV_DIV_DIV5            (OSCCTRL_OSC48MDIV_DIV_DIV5_Val << OSCCTRL_OSC48MDIV_DIV_Pos) /**< (OSCCTRL_OSC48MDIV) 9.6 MHz Position  */
#define OSCCTRL_OSC48MDIV_DIV_DIV6            (OSCCTRL_OSC48MDIV_DIV_DIV6_Val << OSCCTRL_OSC48MDIV_DIV_Pos) /**< (OSCCTRL_OSC48MDIV) 8 MHz Position  */
#define OSCCTRL_OSC48MDIV_DIV_DIV7            (OSCCTRL_OSC48MDIV_DIV_DIV7_Val << OSCCTRL_OSC48MDIV_DIV_Pos) /**< (OSCCTRL_OSC48MDIV) 6.86 MHz Position  */
#define OSCCTRL_OSC48MDIV_DIV_DIV8            (OSCCTRL_OSC48MDIV_DIV_DIV8_Val << OSCCTRL_OSC48MDIV_DIV_Pos) /**< (OSCCTRL_OSC48MDIV) 6 MHz Position  */
#define OSCCTRL_OSC48MDIV_DIV_DIV9            (OSCCTRL_OSC48MDIV_DIV_DIV9_Val << OSCCTRL_OSC48MDIV_DIV_Pos) /**< (OSCCTRL_OSC48MDIV) 5.33 MHz Position  */
#define OSCCTRL_OSC48MDIV_DIV_DIV10           (OSCCTRL_OSC48MDIV_DIV_DIV10_Val << OSCCTRL_OSC48MDIV_DIV_Pos) /**< (OSCCTRL_OSC48MDIV) 4.8 MHz Position  */
#define OSCCTRL_OSC48MDIV_DIV_DIV11           (OSCCTRL_OSC48MDIV_DIV_DIV11_Val << OSCCTRL_OSC48MDIV_DIV_Pos) /**< (OSCCTRL_OSC48MDIV) 4.36 MHz Position  */
#define OSCCTRL_OSC48MDIV_DIV_DIV12           (OSCCTRL_OSC48MDIV_DIV_DIV12_Val << OSCCTRL_OSC48MDIV_DIV_Pos) /**< (OSCCTRL_OSC48MDIV) 4 MHz Position  */
#define OSCCTRL_OSC48MDIV_DIV_DIV13           (OSCCTRL_OSC48MDIV_DIV_DIV13_Val << OSCCTRL_OSC48MDIV_DIV_Pos) /**< (OSCCTRL_OSC48MDIV) 3.69 MHz Position  */
#define OSCCTRL_OSC48MDIV_DIV_DIV14           (OSCCTRL_OSC48MDIV_DIV_DIV14_Val << OSCCTRL_OSC48MDIV_DIV_Pos) /**< (OSCCTRL_OSC48MDIV) 3.43 MHz Position  */
#define OSCCTRL_OSC48MDIV_DIV_DIV15           (OSCCTRL_OSC48MDIV_DIV_DIV15_Val << OSCCTRL_OSC48MDIV_DIV_Pos) /**< (OSCCTRL_OSC48MDIV) 3.2 MHz Position  */
#define OSCCTRL_OSC48MDIV_DIV_DIV16           (OSCCTRL_OSC48MDIV_DIV_DIV16_Val << OSCCTRL_OSC48MDIV_DIV_Pos) /**< (OSCCTRL_OSC48MDIV) 3 MHz Position  */
#define OSCCTRL_OSC48MDIV_Msk                 _U_(0x0F)                                            /**< (OSCCTRL_OSC48MDIV) Register Mask  */


/* -------- OSCCTRL_OSC48MSTUP : (OSCCTRL Offset: 0x16) (R/W 8) OSC48M Startup Time -------- */
#define OSCCTRL_OSC48MSTUP_RESETVALUE         _U_(0x07)                                            /**<  (OSCCTRL_OSC48MSTUP) OSC48M Startup Time  Reset Value */

#define OSCCTRL_OSC48MSTUP_STARTUP_Pos        _U_(0)                                               /**< (OSCCTRL_OSC48MSTUP) Startup Time Position */
#define OSCCTRL_OSC48MSTUP_STARTUP_Msk        (_U_(0x7) << OSCCTRL_OSC48MSTUP_STARTUP_Pos)         /**< (OSCCTRL_OSC48MSTUP) Startup Time Mask */
#define OSCCTRL_OSC48MSTUP_STARTUP(value)     (OSCCTRL_OSC48MSTUP_STARTUP_Msk & ((value) << OSCCTRL_OSC48MSTUP_STARTUP_Pos))
#define   OSCCTRL_OSC48MSTUP_STARTUP_CYCLE8_Val _U_(0x0)                                             /**< (OSCCTRL_OSC48MSTUP) 166 ns  */
#define   OSCCTRL_OSC48MSTUP_STARTUP_CYCLE16_Val _U_(0x1)                                             /**< (OSCCTRL_OSC48MSTUP) 333 ns  */
#define   OSCCTRL_OSC48MSTUP_STARTUP_CYCLE32_Val _U_(0x2)                                             /**< (OSCCTRL_OSC48MSTUP) 667 ns  */
#define   OSCCTRL_OSC48MSTUP_STARTUP_CYCLE64_Val _U_(0x3)                                             /**< (OSCCTRL_OSC48MSTUP) 1.333 us  */
#define   OSCCTRL_OSC48MSTUP_STARTUP_CYCLE128_Val _U_(0x4)                                             /**< (OSCCTRL_OSC48MSTUP) 2.667 us  */
#define   OSCCTRL_OSC48MSTUP_STARTUP_CYCLE256_Val _U_(0x5)                                             /**< (OSCCTRL_OSC48MSTUP) 5.333 us  */
#define   OSCCTRL_OSC48MSTUP_STARTUP_CYCLE512_Val _U_(0x6)                                             /**< (OSCCTRL_OSC48MSTUP) 10.667 us  */
#define   OSCCTRL_OSC48MSTUP_STARTUP_CYCLE1024_Val _U_(0x7)                                             /**< (OSCCTRL_OSC48MSTUP) 21.333 us  */
#define OSCCTRL_OSC48MSTUP_STARTUP_CYCLE8     (OSCCTRL_OSC48MSTUP_STARTUP_CYCLE8_Val << OSCCTRL_OSC48MSTUP_STARTUP_Pos) /**< (OSCCTRL_OSC48MSTUP) 166 ns Position  */
#define OSCCTRL_OSC48MSTUP_STARTUP_CYCLE16    (OSCCTRL_OSC48MSTUP_STARTUP_CYCLE16_Val << OSCCTRL_OSC48MSTUP_STARTUP_Pos) /**< (OSCCTRL_OSC48MSTUP) 333 ns Position  */
#define OSCCTRL_OSC48MSTUP_STARTUP_CYCLE32    (OSCCTRL_OSC48MSTUP_STARTUP_CYCLE32_Val << OSCCTRL_OSC48MSTUP_STARTUP_Pos) /**< (OSCCTRL_OSC48MSTUP) 667 ns Position  */
#define OSCCTRL_OSC48MSTUP_STARTUP_CYCLE64    (OSCCTRL_OSC48MSTUP_STARTUP_CYCLE64_Val << OSCCTRL_OSC48MSTUP_STARTUP_Pos) /**< (OSCCTRL_OSC48MSTUP) 1.333 us Position  */
#define OSCCTRL_OSC48MSTUP_STARTUP_CYCLE128   (OSCCTRL_OSC48MSTUP_STARTUP_CYCLE128_Val << OSCCTRL_OSC48MSTUP_STARTUP_Pos) /**< (OSCCTRL_OSC48MSTUP) 2.667 us Position  */
#define OSCCTRL_OSC48MSTUP_STARTUP_CYCLE256   (OSCCTRL_OSC48MSTUP_STARTUP_CYCLE256_Val << OSCCTRL_OSC48MSTUP_STARTUP_Pos) /**< (OSCCTRL_OSC48MSTUP) 5.333 us Position  */
#define OSCCTRL_OSC48MSTUP_STARTUP_CYCLE512   (OSCCTRL_OSC48MSTUP_STARTUP_CYCLE512_Val << OSCCTRL_OSC48MSTUP_STARTUP_Pos) /**< (OSCCTRL_OSC48MSTUP) 10.667 us Position  */
#define OSCCTRL_OSC48MSTUP_STARTUP_CYCLE1024  (OSCCTRL_OSC48MSTUP_STARTUP_CYCLE1024_Val << OSCCTRL_OSC48MSTUP_STARTUP_Pos) /**< (OSCCTRL_OSC48MSTUP) 21.333 us Position  */
#define OSCCTRL_OSC48MSTUP_Msk                _U_(0x07)                                            /**< (OSCCTRL_OSC48MSTUP) Register Mask  */


/* -------- OSCCTRL_OSC48MSYNCBUSY : (OSCCTRL Offset: 0x18) ( R/ 32) OSC48M Synchronization Busy -------- */
#define OSCCTRL_OSC48MSYNCBUSY_RESETVALUE     _U_(0x00)                                            /**<  (OSCCTRL_OSC48MSYNCBUSY) OSC48M Synchronization Busy  Reset Value */

#define OSCCTRL_OSC48MSYNCBUSY_OSC48MDIV_Pos  _U_(2)                                               /**< (OSCCTRL_OSC48MSYNCBUSY) OSC48MDIV Synchronization Status Position */
#define OSCCTRL_OSC48MSYNCBUSY_OSC48MDIV_Msk  (_U_(0x1) << OSCCTRL_OSC48MSYNCBUSY_OSC48MDIV_Pos)   /**< (OSCCTRL_OSC48MSYNCBUSY) OSC48MDIV Synchronization Status Mask */
#define OSCCTRL_OSC48MSYNCBUSY_OSC48MDIV(value) (OSCCTRL_OSC48MSYNCBUSY_OSC48MDIV_Msk & ((value) << OSCCTRL_OSC48MSYNCBUSY_OSC48MDIV_Pos))
#define OSCCTRL_OSC48MSYNCBUSY_Msk            _U_(0x00000004)                                      /**< (OSCCTRL_OSC48MSYNCBUSY) Register Mask  */


/* -------- OSCCTRL_DPLLCTRLA : (OSCCTRL Offset: 0x1C) (R/W 8) DPLL Control -------- */
#define OSCCTRL_DPLLCTRLA_RESETVALUE          _U_(0x80)                                            /**<  (OSCCTRL_DPLLCTRLA) DPLL Control  Reset Value */

#define OSCCTRL_DPLLCTRLA_ENABLE_Pos          _U_(1)                                               /**< (OSCCTRL_DPLLCTRLA) Enable Position */
#define OSCCTRL_DPLLCTRLA_ENABLE_Msk          (_U_(0x1) << OSCCTRL_DPLLCTRLA_ENABLE_Pos)           /**< (OSCCTRL_DPLLCTRLA) Enable Mask */
#define OSCCTRL_DPLLCTRLA_ENABLE(value)       (OSCCTRL_DPLLCTRLA_ENABLE_Msk & ((value) << OSCCTRL_DPLLCTRLA_ENABLE_Pos))
#define OSCCTRL_DPLLCTRLA_RUNSTDBY_Pos        _U_(6)                                               /**< (OSCCTRL_DPLLCTRLA) Run in Standby Position */
#define OSCCTRL_DPLLCTRLA_RUNSTDBY_Msk        (_U_(0x1) << OSCCTRL_DPLLCTRLA_RUNSTDBY_Pos)         /**< (OSCCTRL_DPLLCTRLA) Run in Standby Mask */
#define OSCCTRL_DPLLCTRLA_RUNSTDBY(value)     (OSCCTRL_DPLLCTRLA_RUNSTDBY_Msk & ((value) << OSCCTRL_DPLLCTRLA_RUNSTDBY_Pos))
#define OSCCTRL_DPLLCTRLA_ONDEMAND_Pos        _U_(7)                                               /**< (OSCCTRL_DPLLCTRLA) On Demand Position */
#define OSCCTRL_DPLLCTRLA_ONDEMAND_Msk        (_U_(0x1) << OSCCTRL_DPLLCTRLA_ONDEMAND_Pos)         /**< (OSCCTRL_DPLLCTRLA) On Demand Mask */
#define OSCCTRL_DPLLCTRLA_ONDEMAND(value)     (OSCCTRL_DPLLCTRLA_ONDEMAND_Msk & ((value) << OSCCTRL_DPLLCTRLA_ONDEMAND_Pos))
#define OSCCTRL_DPLLCTRLA_Msk                 _U_(0xC2)                                            /**< (OSCCTRL_DPLLCTRLA) Register Mask  */


/* -------- OSCCTRL_DPLLRATIO : (OSCCTRL Offset: 0x20) (R/W 32) DPLL Ratio Control -------- */
#define OSCCTRL_DPLLRATIO_RESETVALUE          _U_(0x00)                                            /**<  (OSCCTRL_DPLLRATIO) DPLL Ratio Control  Reset Value */

#define OSCCTRL_DPLLRATIO_LDR_Pos             _U_(0)                                               /**< (OSCCTRL_DPLLRATIO) Loop Divider Ratio Position */
#define OSCCTRL_DPLLRATIO_LDR_Msk             (_U_(0xFFF) << OSCCTRL_DPLLRATIO_LDR_Pos)            /**< (OSCCTRL_DPLLRATIO) Loop Divider Ratio Mask */
#define OSCCTRL_DPLLRATIO_LDR(value)          (OSCCTRL_DPLLRATIO_LDR_Msk & ((value) << OSCCTRL_DPLLRATIO_LDR_Pos))
#define OSCCTRL_DPLLRATIO_LDRFRAC_Pos         _U_(16)                                              /**< (OSCCTRL_DPLLRATIO) Loop Divider Ratio Fractional Part Position */
#define OSCCTRL_DPLLRATIO_LDRFRAC_Msk         (_U_(0xF) << OSCCTRL_DPLLRATIO_LDRFRAC_Pos)          /**< (OSCCTRL_DPLLRATIO) Loop Divider Ratio Fractional Part Mask */
#define OSCCTRL_DPLLRATIO_LDRFRAC(value)      (OSCCTRL_DPLLRATIO_LDRFRAC_Msk & ((value) << OSCCTRL_DPLLRATIO_LDRFRAC_Pos))
#define OSCCTRL_DPLLRATIO_Msk                 _U_(0x000F0FFF)                                      /**< (OSCCTRL_DPLLRATIO) Register Mask  */


/* -------- OSCCTRL_DPLLCTRLB : (OSCCTRL Offset: 0x24) (R/W 32) Digital Core Configuration -------- */
#define OSCCTRL_DPLLCTRLB_RESETVALUE          _U_(0x00)                                            /**<  (OSCCTRL_DPLLCTRLB) Digital Core Configuration  Reset Value */

#define OSCCTRL_DPLLCTRLB_FILTER_Pos          _U_(0)                                               /**< (OSCCTRL_DPLLCTRLB) Proportional Integral Filter Selection Position */
#define OSCCTRL_DPLLCTRLB_FILTER_Msk          (_U_(0x3) << OSCCTRL_DPLLCTRLB_FILTER_Pos)           /**< (OSCCTRL_DPLLCTRLB) Proportional Integral Filter Selection Mask */
#define OSCCTRL_DPLLCTRLB_FILTER(value)       (OSCCTRL_DPLLCTRLB_FILTER_Msk & ((value) << OSCCTRL_DPLLCTRLB_FILTER_Pos))
#define   OSCCTRL_DPLLCTRLB_FILTER_DEFAULT_Val _U_(0x0)                                             /**< (OSCCTRL_DPLLCTRLB) Default filter mode  */
#define   OSCCTRL_DPLLCTRLB_FILTER_LBFILT_Val _U_(0x1)                                             /**< (OSCCTRL_DPLLCTRLB) Low bandwidth filter  */
#define   OSCCTRL_DPLLCTRLB_FILTER_HBFILT_Val _U_(0x2)                                             /**< (OSCCTRL_DPLLCTRLB) High bandwidth filter  */
#define   OSCCTRL_DPLLCTRLB_FILTER_HDFILT_Val _U_(0x3)                                             /**< (OSCCTRL_DPLLCTRLB) High damping filter  */
#define OSCCTRL_DPLLCTRLB_FILTER_DEFAULT      (OSCCTRL_DPLLCTRLB_FILTER_DEFAULT_Val << OSCCTRL_DPLLCTRLB_FILTER_Pos) /**< (OSCCTRL_DPLLCTRLB) Default filter mode Position  */
#define OSCCTRL_DPLLCTRLB_FILTER_LBFILT       (OSCCTRL_DPLLCTRLB_FILTER_LBFILT_Val << OSCCTRL_DPLLCTRLB_FILTER_Pos) /**< (OSCCTRL_DPLLCTRLB) Low bandwidth filter Position  */
#define OSCCTRL_DPLLCTRLB_FILTER_HBFILT       (OSCCTRL_DPLLCTRLB_FILTER_HBFILT_Val << OSCCTRL_DPLLCTRLB_FILTER_Pos) /**< (OSCCTRL_DPLLCTRLB) High bandwidth filter Position  */
#define OSCCTRL_DPLLCTRLB_FILTER_HDFILT       (OSCCTRL_DPLLCTRLB_FILTER_HDFILT_Val << OSCCTRL_DPLLCTRLB_FILTER_Pos) /**< (OSCCTRL_DPLLCTRLB) High damping filter Position  */
#define OSCCTRL_DPLLCTRLB_LPEN_Pos            _U_(2)                                               /**< (OSCCTRL_DPLLCTRLB) Low-Power Enable Position */
#define OSCCTRL_DPLLCTRLB_LPEN_Msk            (_U_(0x1) << OSCCTRL_DPLLCTRLB_LPEN_Pos)             /**< (OSCCTRL_DPLLCTRLB) Low-Power Enable Mask */
#define OSCCTRL_DPLLCTRLB_LPEN(value)         (OSCCTRL_DPLLCTRLB_LPEN_Msk & ((value) << OSCCTRL_DPLLCTRLB_LPEN_Pos))
#define OSCCTRL_DPLLCTRLB_WUF_Pos             _U_(3)                                               /**< (OSCCTRL_DPLLCTRLB) Wake Up Fast Position */
#define OSCCTRL_DPLLCTRLB_WUF_Msk             (_U_(0x1) << OSCCTRL_DPLLCTRLB_WUF_Pos)              /**< (OSCCTRL_DPLLCTRLB) Wake Up Fast Mask */
#define OSCCTRL_DPLLCTRLB_WUF(value)          (OSCCTRL_DPLLCTRLB_WUF_Msk & ((value) << OSCCTRL_DPLLCTRLB_WUF_Pos))
#define OSCCTRL_DPLLCTRLB_REFCLK_Pos          _U_(4)                                               /**< (OSCCTRL_DPLLCTRLB) Reference Clock Selection Position */
#define OSCCTRL_DPLLCTRLB_REFCLK_Msk          (_U_(0x3) << OSCCTRL_DPLLCTRLB_REFCLK_Pos)           /**< (OSCCTRL_DPLLCTRLB) Reference Clock Selection Mask */
#define OSCCTRL_DPLLCTRLB_REFCLK(value)       (OSCCTRL_DPLLCTRLB_REFCLK_Msk & ((value) << OSCCTRL_DPLLCTRLB_REFCLK_Pos))
#define   OSCCTRL_DPLLCTRLB_REFCLK_XOSC32K_Val _U_(0x0)                                             /**< (OSCCTRL_DPLLCTRLB) XOSC32K clock reference  */
#define   OSCCTRL_DPLLCTRLB_REFCLK_XOSC_Val   _U_(0x1)                                             /**< (OSCCTRL_DPLLCTRLB) XOSC clock reference  */
#define   OSCCTRL_DPLLCTRLB_REFCLK_GCLK_Val   _U_(0x2)                                             /**< (OSCCTRL_DPLLCTRLB) GCLK clock reference  */
#define OSCCTRL_DPLLCTRLB_REFCLK_XOSC32K      (OSCCTRL_DPLLCTRLB_REFCLK_XOSC32K_Val << OSCCTRL_DPLLCTRLB_REFCLK_Pos) /**< (OSCCTRL_DPLLCTRLB) XOSC32K clock reference Position  */
#define OSCCTRL_DPLLCTRLB_REFCLK_XOSC         (OSCCTRL_DPLLCTRLB_REFCLK_XOSC_Val << OSCCTRL_DPLLCTRLB_REFCLK_Pos) /**< (OSCCTRL_DPLLCTRLB) XOSC clock reference Position  */
#define OSCCTRL_DPLLCTRLB_REFCLK_GCLK         (OSCCTRL_DPLLCTRLB_REFCLK_GCLK_Val << OSCCTRL_DPLLCTRLB_REFCLK_Pos) /**< (OSCCTRL_DPLLCTRLB) GCLK clock reference Position  */
#define OSCCTRL_DPLLCTRLB_LTIME_Pos           _U_(8)                                               /**< (OSCCTRL_DPLLCTRLB) Lock Time Position */
#define OSCCTRL_DPLLCTRLB_LTIME_Msk           (_U_(0x7) << OSCCTRL_DPLLCTRLB_LTIME_Pos)            /**< (OSCCTRL_DPLLCTRLB) Lock Time Mask */
#define OSCCTRL_DPLLCTRLB_LTIME(value)        (OSCCTRL_DPLLCTRLB_LTIME_Msk & ((value) << OSCCTRL_DPLLCTRLB_LTIME_Pos))
#define   OSCCTRL_DPLLCTRLB_LTIME_DEFAULT_Val _U_(0x0)                                             /**< (OSCCTRL_DPLLCTRLB) No time-out. Automatic lock.  */
#define   OSCCTRL_DPLLCTRLB_LTIME_8MS_Val     _U_(0x4)                                             /**< (OSCCTRL_DPLLCTRLB) Time-out if no lock within 8ms  */
#define   OSCCTRL_DPLLCTRLB_LTIME_9MS_Val     _U_(0x5)                                             /**< (OSCCTRL_DPLLCTRLB) Time-out if no lock within 9ms  */
#define   OSCCTRL_DPLLCTRLB_LTIME_10MS_Val    _U_(0x6)                                             /**< (OSCCTRL_DPLLCTRLB) Time-out if no lock within 10ms  */
#define   OSCCTRL_DPLLCTRLB_LTIME_11MS_Val    _U_(0x7)                                             /**< (OSCCTRL_DPLLCTRLB) Time-out if no lock within 11ms  */
#define OSCCTRL_DPLLCTRLB_LTIME_DEFAULT       (OSCCTRL_DPLLCTRLB_LTIME_DEFAULT_Val << OSCCTRL_DPLLCTRLB_LTIME_Pos) /**< (OSCCTRL_DPLLCTRLB) No time-out. Automatic lock. Position  */
#define OSCCTRL_DPLLCTRLB_LTIME_8MS           (OSCCTRL_DPLLCTRLB_LTIME_8MS_Val << OSCCTRL_DPLLCTRLB_LTIME_Pos) /**< (OSCCTRL_DPLLCTRLB) Time-out if no lock within 8ms Position  */
#define OSCCTRL_DPLLCTRLB_LTIME_9MS           (OSCCTRL_DPLLCTRLB_LTIME_9MS_Val << OSCCTRL_DPLLCTRLB_LTIME_Pos) /**< (OSCCTRL_DPLLCTRLB) Time-out if no lock within 9ms Position  */
#define OSCCTRL_DPLLCTRLB_LTIME_10MS          (OSCCTRL_DPLLCTRLB_LTIME_10MS_Val << OSCCTRL_DPLLCTRLB_LTIME_Pos) /**< (OSCCTRL_DPLLCTRLB) Time-out if no lock within 10ms Position  */
#define OSCCTRL_DPLLCTRLB_LTIME_11MS          (OSCCTRL_DPLLCTRLB_LTIME_11MS_Val << OSCCTRL_DPLLCTRLB_LTIME_Pos) /**< (OSCCTRL_DPLLCTRLB) Time-out if no lock within 11ms Position  */
#define OSCCTRL_DPLLCTRLB_LBYPASS_Pos         _U_(12)                                              /**< (OSCCTRL_DPLLCTRLB) Lock Bypass Position */
#define OSCCTRL_DPLLCTRLB_LBYPASS_Msk         (_U_(0x1) << OSCCTRL_DPLLCTRLB_LBYPASS_Pos)          /**< (OSCCTRL_DPLLCTRLB) Lock Bypass Mask */
#define OSCCTRL_DPLLCTRLB_LBYPASS(value)      (OSCCTRL_DPLLCTRLB_LBYPASS_Msk & ((value) << OSCCTRL_DPLLCTRLB_LBYPASS_Pos))
#define OSCCTRL_DPLLCTRLB_DIV_Pos             _U_(16)                                              /**< (OSCCTRL_DPLLCTRLB) Clock Divider Position */
#define OSCCTRL_DPLLCTRLB_DIV_Msk             (_U_(0x7FF) << OSCCTRL_DPLLCTRLB_DIV_Pos)            /**< (OSCCTRL_DPLLCTRLB) Clock Divider Mask */
#define OSCCTRL_DPLLCTRLB_DIV(value)          (OSCCTRL_DPLLCTRLB_DIV_Msk & ((value) << OSCCTRL_DPLLCTRLB_DIV_Pos))
#define OSCCTRL_DPLLCTRLB_Msk                 _U_(0x07FF173F)                                      /**< (OSCCTRL_DPLLCTRLB) Register Mask  */


/* -------- OSCCTRL_DPLLPRESC : (OSCCTRL Offset: 0x28) (R/W 8) DPLL Prescaler -------- */
#define OSCCTRL_DPLLPRESC_RESETVALUE          _U_(0x00)                                            /**<  (OSCCTRL_DPLLPRESC) DPLL Prescaler  Reset Value */

#define OSCCTRL_DPLLPRESC_PRESC_Pos           _U_(0)                                               /**< (OSCCTRL_DPLLPRESC) Output Clock Prescaler Position */
#define OSCCTRL_DPLLPRESC_PRESC_Msk           (_U_(0x3) << OSCCTRL_DPLLPRESC_PRESC_Pos)            /**< (OSCCTRL_DPLLPRESC) Output Clock Prescaler Mask */
#define OSCCTRL_DPLLPRESC_PRESC(value)        (OSCCTRL_DPLLPRESC_PRESC_Msk & ((value) << OSCCTRL_DPLLPRESC_PRESC_Pos))
#define   OSCCTRL_DPLLPRESC_PRESC_DIV1_Val    _U_(0x0)                                             /**< (OSCCTRL_DPLLPRESC) DPLL output is divided by 1  */
#define   OSCCTRL_DPLLPRESC_PRESC_DIV2_Val    _U_(0x1)                                             /**< (OSCCTRL_DPLLPRESC) DPLL output is divided by 2  */
#define   OSCCTRL_DPLLPRESC_PRESC_DIV4_Val    _U_(0x2)                                             /**< (OSCCTRL_DPLLPRESC) DPLL output is divided by 4  */
#define OSCCTRL_DPLLPRESC_PRESC_DIV1          (OSCCTRL_DPLLPRESC_PRESC_DIV1_Val << OSCCTRL_DPLLPRESC_PRESC_Pos) /**< (OSCCTRL_DPLLPRESC) DPLL output is divided by 1 Position  */
#define OSCCTRL_DPLLPRESC_PRESC_DIV2          (OSCCTRL_DPLLPRESC_PRESC_DIV2_Val << OSCCTRL_DPLLPRESC_PRESC_Pos) /**< (OSCCTRL_DPLLPRESC) DPLL output is divided by 2 Position  */
#define OSCCTRL_DPLLPRESC_PRESC_DIV4          (OSCCTRL_DPLLPRESC_PRESC_DIV4_Val << OSCCTRL_DPLLPRESC_PRESC_Pos) /**< (OSCCTRL_DPLLPRESC) DPLL output is divided by 4 Position  */
#define OSCCTRL_DPLLPRESC_Msk                 _U_(0x03)                                            /**< (OSCCTRL_DPLLPRESC) Register Mask  */


/* -------- OSCCTRL_DPLLSYNCBUSY : (OSCCTRL Offset: 0x2C) ( R/ 8) DPLL Synchronization Busy -------- */
#define OSCCTRL_DPLLSYNCBUSY_RESETVALUE       _U_(0x00)                                            /**<  (OSCCTRL_DPLLSYNCBUSY) DPLL Synchronization Busy  Reset Value */

#define OSCCTRL_DPLLSYNCBUSY_ENABLE_Pos       _U_(1)                                               /**< (OSCCTRL_DPLLSYNCBUSY) DPLL Enable Synchronization Status Position */
#define OSCCTRL_DPLLSYNCBUSY_ENABLE_Msk       (_U_(0x1) << OSCCTRL_DPLLSYNCBUSY_ENABLE_Pos)        /**< (OSCCTRL_DPLLSYNCBUSY) DPLL Enable Synchronization Status Mask */
#define OSCCTRL_DPLLSYNCBUSY_ENABLE(value)    (OSCCTRL_DPLLSYNCBUSY_ENABLE_Msk & ((value) << OSCCTRL_DPLLSYNCBUSY_ENABLE_Pos))
#define OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Pos    _U_(2)                                               /**< (OSCCTRL_DPLLSYNCBUSY) DPLL Ratio Synchronization Status Position */
#define OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Msk    (_U_(0x1) << OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Pos)     /**< (OSCCTRL_DPLLSYNCBUSY) DPLL Ratio Synchronization Status Mask */
#define OSCCTRL_DPLLSYNCBUSY_DPLLRATIO(value) (OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Msk & ((value) << OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Pos))
#define OSCCTRL_DPLLSYNCBUSY_DPLLPRESC_Pos    _U_(3)                                               /**< (OSCCTRL_DPLLSYNCBUSY) DPLL Prescaler Synchronization Status Position */
#define OSCCTRL_DPLLSYNCBUSY_DPLLPRESC_Msk    (_U_(0x1) << OSCCTRL_DPLLSYNCBUSY_DPLLPRESC_Pos)     /**< (OSCCTRL_DPLLSYNCBUSY) DPLL Prescaler Synchronization Status Mask */
#define OSCCTRL_DPLLSYNCBUSY_DPLLPRESC(value) (OSCCTRL_DPLLSYNCBUSY_DPLLPRESC_Msk & ((value) << OSCCTRL_DPLLSYNCBUSY_DPLLPRESC_Pos))
#define OSCCTRL_DPLLSYNCBUSY_Msk              _U_(0x0E)                                            /**< (OSCCTRL_DPLLSYNCBUSY) Register Mask  */


/* -------- OSCCTRL_DPLLSTATUS : (OSCCTRL Offset: 0x30) ( R/ 8) DPLL Status -------- */
#define OSCCTRL_DPLLSTATUS_RESETVALUE         _U_(0x00)                                            /**<  (OSCCTRL_DPLLSTATUS) DPLL Status  Reset Value */

#define OSCCTRL_DPLLSTATUS_LOCK_Pos           _U_(0)                                               /**< (OSCCTRL_DPLLSTATUS) DPLL Lock Status Position */
#define OSCCTRL_DPLLSTATUS_LOCK_Msk           (_U_(0x1) << OSCCTRL_DPLLSTATUS_LOCK_Pos)            /**< (OSCCTRL_DPLLSTATUS) DPLL Lock Status Mask */
#define OSCCTRL_DPLLSTATUS_LOCK(value)        (OSCCTRL_DPLLSTATUS_LOCK_Msk & ((value) << OSCCTRL_DPLLSTATUS_LOCK_Pos))
#define OSCCTRL_DPLLSTATUS_CLKRDY_Pos         _U_(1)                                               /**< (OSCCTRL_DPLLSTATUS) DPLL Clock Ready Position */
#define OSCCTRL_DPLLSTATUS_CLKRDY_Msk         (_U_(0x1) << OSCCTRL_DPLLSTATUS_CLKRDY_Pos)          /**< (OSCCTRL_DPLLSTATUS) DPLL Clock Ready Mask */
#define OSCCTRL_DPLLSTATUS_CLKRDY(value)      (OSCCTRL_DPLLSTATUS_CLKRDY_Msk & ((value) << OSCCTRL_DPLLSTATUS_CLKRDY_Pos))
#define OSCCTRL_DPLLSTATUS_Msk                _U_(0x03)                                            /**< (OSCCTRL_DPLLSTATUS) Register Mask  */


/* -------- OSCCTRL_CAL48M : (OSCCTRL Offset: 0x38) (R/W 32) 48MHz Oscillator Calibration -------- */
#define OSCCTRL_CAL48M_RESETVALUE             _U_(0x00)                                            /**<  (OSCCTRL_CAL48M) 48MHz Oscillator Calibration  Reset Value */

#define OSCCTRL_CAL48M_FCAL_Pos               _U_(0)                                               /**< (OSCCTRL_CAL48M) Frequency Calibration (48MHz) Position */
#define OSCCTRL_CAL48M_FCAL_Msk               (_U_(0x3F) << OSCCTRL_CAL48M_FCAL_Pos)               /**< (OSCCTRL_CAL48M) Frequency Calibration (48MHz) Mask */
#define OSCCTRL_CAL48M_FCAL(value)            (OSCCTRL_CAL48M_FCAL_Msk & ((value) << OSCCTRL_CAL48M_FCAL_Pos))
#define OSCCTRL_CAL48M_FRANGE_Pos             _U_(8)                                               /**< (OSCCTRL_CAL48M) Frequency Range (48MHz) Position */
#define OSCCTRL_CAL48M_FRANGE_Msk             (_U_(0x3) << OSCCTRL_CAL48M_FRANGE_Pos)              /**< (OSCCTRL_CAL48M) Frequency Range (48MHz) Mask */
#define OSCCTRL_CAL48M_FRANGE(value)          (OSCCTRL_CAL48M_FRANGE_Msk & ((value) << OSCCTRL_CAL48M_FRANGE_Pos))
#define OSCCTRL_CAL48M_TCAL_Pos               _U_(16)                                              /**< (OSCCTRL_CAL48M) Temperature Calibration (48MHz) Position */
#define OSCCTRL_CAL48M_TCAL_Msk               (_U_(0x3F) << OSCCTRL_CAL48M_TCAL_Pos)               /**< (OSCCTRL_CAL48M) Temperature Calibration (48MHz) Mask */
#define OSCCTRL_CAL48M_TCAL(value)            (OSCCTRL_CAL48M_TCAL_Msk & ((value) << OSCCTRL_CAL48M_TCAL_Pos))
#define OSCCTRL_CAL48M_Msk                    _U_(0x003F033F)                                      /**< (OSCCTRL_CAL48M) Register Mask  */


/** \brief OSCCTRL register offsets definitions */
#define OSCCTRL_INTENCLR_REG_OFST      (0x00)              /**< (OSCCTRL_INTENCLR) Interrupt Enable Clear Offset */
#define OSCCTRL_INTENSET_REG_OFST      (0x04)              /**< (OSCCTRL_INTENSET) Interrupt Enable Set Offset */
#define OSCCTRL_INTFLAG_REG_OFST       (0x08)              /**< (OSCCTRL_INTFLAG) Interrupt Flag Status and Clear Offset */
#define OSCCTRL_STATUS_REG_OFST        (0x0C)              /**< (OSCCTRL_STATUS) Power and Clocks Status Offset */
#define OSCCTRL_XOSCCTRL_REG_OFST      (0x10)              /**< (OSCCTRL_XOSCCTRL) External Multipurpose Crystal Oscillator (XOSC) Control Offset */
#define OSCCTRL_CFDPRESC_REG_OFST      (0x12)              /**< (OSCCTRL_CFDPRESC) Clock Failure Detector Prescaler Offset */
#define OSCCTRL_EVCTRL_REG_OFST        (0x13)              /**< (OSCCTRL_EVCTRL) Event Control Offset */
#define OSCCTRL_OSC48MCTRL_REG_OFST    (0x14)              /**< (OSCCTRL_OSC48MCTRL) 48MHz Internal Oscillator (OSC48M) Control Offset */
#define OSCCTRL_OSC48MDIV_REG_OFST     (0x15)              /**< (OSCCTRL_OSC48MDIV) OSC48M Divider Offset */
#define OSCCTRL_OSC48MSTUP_REG_OFST    (0x16)              /**< (OSCCTRL_OSC48MSTUP) OSC48M Startup Time Offset */
#define OSCCTRL_OSC48MSYNCBUSY_REG_OFST (0x18)              /**< (OSCCTRL_OSC48MSYNCBUSY) OSC48M Synchronization Busy Offset */
#define OSCCTRL_DPLLCTRLA_REG_OFST     (0x1C)              /**< (OSCCTRL_DPLLCTRLA) DPLL Control Offset */
#define OSCCTRL_DPLLRATIO_REG_OFST     (0x20)              /**< (OSCCTRL_DPLLRATIO) DPLL Ratio Control Offset */
#define OSCCTRL_DPLLCTRLB_REG_OFST     (0x24)              /**< (OSCCTRL_DPLLCTRLB) Digital Core Configuration Offset */
#define OSCCTRL_DPLLPRESC_REG_OFST     (0x28)              /**< (OSCCTRL_DPLLPRESC) DPLL Prescaler Offset */
#define OSCCTRL_DPLLSYNCBUSY_REG_OFST  (0x2C)              /**< (OSCCTRL_DPLLSYNCBUSY) DPLL Synchronization Busy Offset */
#define OSCCTRL_DPLLSTATUS_REG_OFST    (0x30)              /**< (OSCCTRL_DPLLSTATUS) DPLL Status Offset */
#define OSCCTRL_CAL48M_REG_OFST        (0x38)              /**< (OSCCTRL_CAL48M) 48MHz Oscillator Calibration Offset */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief OSCCTRL register API structure */
typedef struct
{  /* Oscillators Control */
  __IO  uint32_t                       OSCCTRL_INTENCLR;   /**< Offset: 0x00 (R/W  32) Interrupt Enable Clear */
  __IO  uint32_t                       OSCCTRL_INTENSET;   /**< Offset: 0x04 (R/W  32) Interrupt Enable Set */
  __IO  uint32_t                       OSCCTRL_INTFLAG;    /**< Offset: 0x08 (R/W  32) Interrupt Flag Status and Clear */
  __I   uint32_t                       OSCCTRL_STATUS;     /**< Offset: 0x0C (R/   32) Power and Clocks Status */
  __IO  uint16_t                       OSCCTRL_XOSCCTRL;   /**< Offset: 0x10 (R/W  16) External Multipurpose Crystal Oscillator (XOSC) Control */
  __IO  uint8_t                        OSCCTRL_CFDPRESC;   /**< Offset: 0x12 (R/W  8) Clock Failure Detector Prescaler */
  __IO  uint8_t                        OSCCTRL_EVCTRL;     /**< Offset: 0x13 (R/W  8) Event Control */
  __IO  uint8_t                        OSCCTRL_OSC48MCTRL; /**< Offset: 0x14 (R/W  8) 48MHz Internal Oscillator (OSC48M) Control */
  __IO  uint8_t                        OSCCTRL_OSC48MDIV;  /**< Offset: 0x15 (R/W  8) OSC48M Divider */
  __IO  uint8_t                        OSCCTRL_OSC48MSTUP; /**< Offset: 0x16 (R/W  8) OSC48M Startup Time */
  __I   uint8_t                        Reserved1[0x01];
  __I   uint32_t                       OSCCTRL_OSC48MSYNCBUSY; /**< Offset: 0x18 (R/   32) OSC48M Synchronization Busy */
  __IO  uint8_t                        OSCCTRL_DPLLCTRLA;  /**< Offset: 0x1C (R/W  8) DPLL Control */
  __I   uint8_t                        Reserved2[0x03];
  __IO  uint32_t                       OSCCTRL_DPLLRATIO;  /**< Offset: 0x20 (R/W  32) DPLL Ratio Control */
  __IO  uint32_t                       OSCCTRL_DPLLCTRLB;  /**< Offset: 0x24 (R/W  32) Digital Core Configuration */
  __IO  uint8_t                        OSCCTRL_DPLLPRESC;  /**< Offset: 0x28 (R/W  8) DPLL Prescaler */
  __I   uint8_t                        Reserved3[0x03];
  __I   uint8_t                        OSCCTRL_DPLLSYNCBUSY; /**< Offset: 0x2C (R/   8) DPLL Synchronization Busy */
  __I   uint8_t                        Reserved4[0x03];
  __I   uint8_t                        OSCCTRL_DPLLSTATUS; /**< Offset: 0x30 (R/   8) DPLL Status */
  __I   uint8_t                        Reserved5[0x07];
  __IO  uint32_t                       OSCCTRL_CAL48M;     /**< Offset: 0x38 (R/W  32) 48MHz Oscillator Calibration */
} oscctrl_registers_t;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* _SAMC21_OSCCTRL_COMPONENT_H_ */
