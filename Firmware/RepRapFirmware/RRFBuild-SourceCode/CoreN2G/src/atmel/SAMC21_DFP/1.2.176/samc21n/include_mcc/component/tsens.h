/**
 * \brief Component description for TSENS
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
#ifndef _SAMC21_TSENS_COMPONENT_H_
#define _SAMC21_TSENS_COMPONENT_H_

/* ************************************************************************** */
/*   SOFTWARE API DEFINITION FOR TSENS                                        */
/* ************************************************************************** */

/* -------- TSENS_CTRLA : (TSENS Offset: 0x00) (R/W 8) Control A Register -------- */
#define TSENS_CTRLA_RESETVALUE                _U_(0x00)                                            /**<  (TSENS_CTRLA) Control A Register  Reset Value */

#define TSENS_CTRLA_SWRST_Pos                 _U_(0)                                               /**< (TSENS_CTRLA) Software Reset Position */
#define TSENS_CTRLA_SWRST_Msk                 (_U_(0x1) << TSENS_CTRLA_SWRST_Pos)                  /**< (TSENS_CTRLA) Software Reset Mask */
#define TSENS_CTRLA_SWRST(value)              (TSENS_CTRLA_SWRST_Msk & ((value) << TSENS_CTRLA_SWRST_Pos))
#define TSENS_CTRLA_ENABLE_Pos                _U_(1)                                               /**< (TSENS_CTRLA) Enable Position */
#define TSENS_CTRLA_ENABLE_Msk                (_U_(0x1) << TSENS_CTRLA_ENABLE_Pos)                 /**< (TSENS_CTRLA) Enable Mask */
#define TSENS_CTRLA_ENABLE(value)             (TSENS_CTRLA_ENABLE_Msk & ((value) << TSENS_CTRLA_ENABLE_Pos))
#define TSENS_CTRLA_RUNSTDBY_Pos              _U_(6)                                               /**< (TSENS_CTRLA) Run in Standby Position */
#define TSENS_CTRLA_RUNSTDBY_Msk              (_U_(0x1) << TSENS_CTRLA_RUNSTDBY_Pos)               /**< (TSENS_CTRLA) Run in Standby Mask */
#define TSENS_CTRLA_RUNSTDBY(value)           (TSENS_CTRLA_RUNSTDBY_Msk & ((value) << TSENS_CTRLA_RUNSTDBY_Pos))
#define TSENS_CTRLA_Msk                       _U_(0x43)                                            /**< (TSENS_CTRLA) Register Mask  */


/* -------- TSENS_CTRLB : (TSENS Offset: 0x01) ( /W 8) Control B Register -------- */
#define TSENS_CTRLB_RESETVALUE                _U_(0x00)                                            /**<  (TSENS_CTRLB) Control B Register  Reset Value */

#define TSENS_CTRLB_START_Pos                 _U_(0)                                               /**< (TSENS_CTRLB) Start Measurement Position */
#define TSENS_CTRLB_START_Msk                 (_U_(0x1) << TSENS_CTRLB_START_Pos)                  /**< (TSENS_CTRLB) Start Measurement Mask */
#define TSENS_CTRLB_START(value)              (TSENS_CTRLB_START_Msk & ((value) << TSENS_CTRLB_START_Pos))
#define TSENS_CTRLB_Msk                       _U_(0x01)                                            /**< (TSENS_CTRLB) Register Mask  */


/* -------- TSENS_CTRLC : (TSENS Offset: 0x02) (R/W 8) Control C Register -------- */
#define TSENS_CTRLC_RESETVALUE                _U_(0x00)                                            /**<  (TSENS_CTRLC) Control C Register  Reset Value */

#define TSENS_CTRLC_WINMODE_Pos               _U_(0)                                               /**< (TSENS_CTRLC) Window Monitor Mode Position */
#define TSENS_CTRLC_WINMODE_Msk               (_U_(0x7) << TSENS_CTRLC_WINMODE_Pos)                /**< (TSENS_CTRLC) Window Monitor Mode Mask */
#define TSENS_CTRLC_WINMODE(value)            (TSENS_CTRLC_WINMODE_Msk & ((value) << TSENS_CTRLC_WINMODE_Pos))
#define   TSENS_CTRLC_WINMODE_DISABLE_Val     _U_(0x0)                                             /**< (TSENS_CTRLC) No window mode (default)  */
#define   TSENS_CTRLC_WINMODE_ABOVE_Val       _U_(0x1)                                             /**< (TSENS_CTRLC) VALUE greater than WINLT  */
#define   TSENS_CTRLC_WINMODE_BELOW_Val       _U_(0x2)                                             /**< (TSENS_CTRLC) VALUE less than WINUT  */
#define   TSENS_CTRLC_WINMODE_INSIDE_Val      _U_(0x3)                                             /**< (TSENS_CTRLC) VALUE greater than WINLT and VALUE less than WINUT  */
#define   TSENS_CTRLC_WINMODE_OUTSIDE_Val     _U_(0x4)                                             /**< (TSENS_CTRLC) VALUE less than WINLT or VALUE greater than WINUT  */
#define   TSENS_CTRLC_WINMODE_HYST_ABOVE_Val  _U_(0x5)                                             /**< (TSENS_CTRLC) VALUE greater than WINUT with hysteresis to WINLT  */
#define   TSENS_CTRLC_WINMODE_HYST_BELOW_Val  _U_(0x6)                                             /**< (TSENS_CTRLC) VALUE less than WINLST with hysteresis to WINUT  */
#define TSENS_CTRLC_WINMODE_DISABLE           (TSENS_CTRLC_WINMODE_DISABLE_Val << TSENS_CTRLC_WINMODE_Pos) /**< (TSENS_CTRLC) No window mode (default) Position  */
#define TSENS_CTRLC_WINMODE_ABOVE             (TSENS_CTRLC_WINMODE_ABOVE_Val << TSENS_CTRLC_WINMODE_Pos) /**< (TSENS_CTRLC) VALUE greater than WINLT Position  */
#define TSENS_CTRLC_WINMODE_BELOW             (TSENS_CTRLC_WINMODE_BELOW_Val << TSENS_CTRLC_WINMODE_Pos) /**< (TSENS_CTRLC) VALUE less than WINUT Position  */
#define TSENS_CTRLC_WINMODE_INSIDE            (TSENS_CTRLC_WINMODE_INSIDE_Val << TSENS_CTRLC_WINMODE_Pos) /**< (TSENS_CTRLC) VALUE greater than WINLT and VALUE less than WINUT Position  */
#define TSENS_CTRLC_WINMODE_OUTSIDE           (TSENS_CTRLC_WINMODE_OUTSIDE_Val << TSENS_CTRLC_WINMODE_Pos) /**< (TSENS_CTRLC) VALUE less than WINLT or VALUE greater than WINUT Position  */
#define TSENS_CTRLC_WINMODE_HYST_ABOVE        (TSENS_CTRLC_WINMODE_HYST_ABOVE_Val << TSENS_CTRLC_WINMODE_Pos) /**< (TSENS_CTRLC) VALUE greater than WINUT with hysteresis to WINLT Position  */
#define TSENS_CTRLC_WINMODE_HYST_BELOW        (TSENS_CTRLC_WINMODE_HYST_BELOW_Val << TSENS_CTRLC_WINMODE_Pos) /**< (TSENS_CTRLC) VALUE less than WINLST with hysteresis to WINUT Position  */
#define TSENS_CTRLC_FREERUN_Pos               _U_(4)                                               /**< (TSENS_CTRLC) Free Running Measurement Position */
#define TSENS_CTRLC_FREERUN_Msk               (_U_(0x1) << TSENS_CTRLC_FREERUN_Pos)                /**< (TSENS_CTRLC) Free Running Measurement Mask */
#define TSENS_CTRLC_FREERUN(value)            (TSENS_CTRLC_FREERUN_Msk & ((value) << TSENS_CTRLC_FREERUN_Pos))
#define TSENS_CTRLC_Msk                       _U_(0x17)                                            /**< (TSENS_CTRLC) Register Mask  */


/* -------- TSENS_EVCTRL : (TSENS Offset: 0x03) (R/W 8) Event Control Register -------- */
#define TSENS_EVCTRL_RESETVALUE               _U_(0x00)                                            /**<  (TSENS_EVCTRL) Event Control Register  Reset Value */

#define TSENS_EVCTRL_STARTEI_Pos              _U_(0)                                               /**< (TSENS_EVCTRL) Start Conversion Event Input Enable Position */
#define TSENS_EVCTRL_STARTEI_Msk              (_U_(0x1) << TSENS_EVCTRL_STARTEI_Pos)               /**< (TSENS_EVCTRL) Start Conversion Event Input Enable Mask */
#define TSENS_EVCTRL_STARTEI(value)           (TSENS_EVCTRL_STARTEI_Msk & ((value) << TSENS_EVCTRL_STARTEI_Pos))
#define TSENS_EVCTRL_STARTINV_Pos             _U_(1)                                               /**< (TSENS_EVCTRL) Start Conversion Event Invert Enable Position */
#define TSENS_EVCTRL_STARTINV_Msk             (_U_(0x1) << TSENS_EVCTRL_STARTINV_Pos)              /**< (TSENS_EVCTRL) Start Conversion Event Invert Enable Mask */
#define TSENS_EVCTRL_STARTINV(value)          (TSENS_EVCTRL_STARTINV_Msk & ((value) << TSENS_EVCTRL_STARTINV_Pos))
#define TSENS_EVCTRL_WINEO_Pos                _U_(2)                                               /**< (TSENS_EVCTRL) Window Monitor Event Out Position */
#define TSENS_EVCTRL_WINEO_Msk                (_U_(0x1) << TSENS_EVCTRL_WINEO_Pos)                 /**< (TSENS_EVCTRL) Window Monitor Event Out Mask */
#define TSENS_EVCTRL_WINEO(value)             (TSENS_EVCTRL_WINEO_Msk & ((value) << TSENS_EVCTRL_WINEO_Pos))
#define TSENS_EVCTRL_Msk                      _U_(0x07)                                            /**< (TSENS_EVCTRL) Register Mask  */


/* -------- TSENS_INTENCLR : (TSENS Offset: 0x04) (R/W 8) Interrupt Enable Clear Register -------- */
#define TSENS_INTENCLR_RESETVALUE             _U_(0x00)                                            /**<  (TSENS_INTENCLR) Interrupt Enable Clear Register  Reset Value */

#define TSENS_INTENCLR_RESRDY_Pos             _U_(0)                                               /**< (TSENS_INTENCLR) Result Ready Interrupt Enable Position */
#define TSENS_INTENCLR_RESRDY_Msk             (_U_(0x1) << TSENS_INTENCLR_RESRDY_Pos)              /**< (TSENS_INTENCLR) Result Ready Interrupt Enable Mask */
#define TSENS_INTENCLR_RESRDY(value)          (TSENS_INTENCLR_RESRDY_Msk & ((value) << TSENS_INTENCLR_RESRDY_Pos))
#define TSENS_INTENCLR_OVERRUN_Pos            _U_(1)                                               /**< (TSENS_INTENCLR) Overrun Interrupt Enable Position */
#define TSENS_INTENCLR_OVERRUN_Msk            (_U_(0x1) << TSENS_INTENCLR_OVERRUN_Pos)             /**< (TSENS_INTENCLR) Overrun Interrupt Enable Mask */
#define TSENS_INTENCLR_OVERRUN(value)         (TSENS_INTENCLR_OVERRUN_Msk & ((value) << TSENS_INTENCLR_OVERRUN_Pos))
#define TSENS_INTENCLR_WINMON_Pos             _U_(2)                                               /**< (TSENS_INTENCLR) Window Monitor Interrupt Enable Position */
#define TSENS_INTENCLR_WINMON_Msk             (_U_(0x1) << TSENS_INTENCLR_WINMON_Pos)              /**< (TSENS_INTENCLR) Window Monitor Interrupt Enable Mask */
#define TSENS_INTENCLR_WINMON(value)          (TSENS_INTENCLR_WINMON_Msk & ((value) << TSENS_INTENCLR_WINMON_Pos))
#define TSENS_INTENCLR_OVF_Pos                _U_(3)                                               /**< (TSENS_INTENCLR) Overflow Interrupt Enable Position */
#define TSENS_INTENCLR_OVF_Msk                (_U_(0x1) << TSENS_INTENCLR_OVF_Pos)                 /**< (TSENS_INTENCLR) Overflow Interrupt Enable Mask */
#define TSENS_INTENCLR_OVF(value)             (TSENS_INTENCLR_OVF_Msk & ((value) << TSENS_INTENCLR_OVF_Pos))
#define TSENS_INTENCLR_Msk                    _U_(0x0F)                                            /**< (TSENS_INTENCLR) Register Mask  */


/* -------- TSENS_INTENSET : (TSENS Offset: 0x05) (R/W 8) Interrupt Enable Set Register -------- */
#define TSENS_INTENSET_RESETVALUE             _U_(0x00)                                            /**<  (TSENS_INTENSET) Interrupt Enable Set Register  Reset Value */

#define TSENS_INTENSET_RESRDY_Pos             _U_(0)                                               /**< (TSENS_INTENSET) Result Ready Interrupt Enable Position */
#define TSENS_INTENSET_RESRDY_Msk             (_U_(0x1) << TSENS_INTENSET_RESRDY_Pos)              /**< (TSENS_INTENSET) Result Ready Interrupt Enable Mask */
#define TSENS_INTENSET_RESRDY(value)          (TSENS_INTENSET_RESRDY_Msk & ((value) << TSENS_INTENSET_RESRDY_Pos))
#define TSENS_INTENSET_OVERRUN_Pos            _U_(1)                                               /**< (TSENS_INTENSET) Overrun Interrupt Enable Position */
#define TSENS_INTENSET_OVERRUN_Msk            (_U_(0x1) << TSENS_INTENSET_OVERRUN_Pos)             /**< (TSENS_INTENSET) Overrun Interrupt Enable Mask */
#define TSENS_INTENSET_OVERRUN(value)         (TSENS_INTENSET_OVERRUN_Msk & ((value) << TSENS_INTENSET_OVERRUN_Pos))
#define TSENS_INTENSET_WINMON_Pos             _U_(2)                                               /**< (TSENS_INTENSET) Window Monitor Interrupt Enable Position */
#define TSENS_INTENSET_WINMON_Msk             (_U_(0x1) << TSENS_INTENSET_WINMON_Pos)              /**< (TSENS_INTENSET) Window Monitor Interrupt Enable Mask */
#define TSENS_INTENSET_WINMON(value)          (TSENS_INTENSET_WINMON_Msk & ((value) << TSENS_INTENSET_WINMON_Pos))
#define TSENS_INTENSET_OVF_Pos                _U_(3)                                               /**< (TSENS_INTENSET) Overflow Interrupt Enable Position */
#define TSENS_INTENSET_OVF_Msk                (_U_(0x1) << TSENS_INTENSET_OVF_Pos)                 /**< (TSENS_INTENSET) Overflow Interrupt Enable Mask */
#define TSENS_INTENSET_OVF(value)             (TSENS_INTENSET_OVF_Msk & ((value) << TSENS_INTENSET_OVF_Pos))
#define TSENS_INTENSET_Msk                    _U_(0x0F)                                            /**< (TSENS_INTENSET) Register Mask  */


/* -------- TSENS_INTFLAG : (TSENS Offset: 0x06) (R/W 8) Interrupt Flag Status and Clear Register -------- */
#define TSENS_INTFLAG_RESETVALUE              _U_(0x00)                                            /**<  (TSENS_INTFLAG) Interrupt Flag Status and Clear Register  Reset Value */

#define TSENS_INTFLAG_RESRDY_Pos              _U_(0)                                               /**< (TSENS_INTFLAG) Result Ready Position */
#define TSENS_INTFLAG_RESRDY_Msk              (_U_(0x1) << TSENS_INTFLAG_RESRDY_Pos)               /**< (TSENS_INTFLAG) Result Ready Mask */
#define TSENS_INTFLAG_RESRDY(value)           (TSENS_INTFLAG_RESRDY_Msk & ((value) << TSENS_INTFLAG_RESRDY_Pos))
#define TSENS_INTFLAG_OVERRUN_Pos             _U_(1)                                               /**< (TSENS_INTFLAG) Overrun Position */
#define TSENS_INTFLAG_OVERRUN_Msk             (_U_(0x1) << TSENS_INTFLAG_OVERRUN_Pos)              /**< (TSENS_INTFLAG) Overrun Mask */
#define TSENS_INTFLAG_OVERRUN(value)          (TSENS_INTFLAG_OVERRUN_Msk & ((value) << TSENS_INTFLAG_OVERRUN_Pos))
#define TSENS_INTFLAG_WINMON_Pos              _U_(2)                                               /**< (TSENS_INTFLAG) Window Monitor Position */
#define TSENS_INTFLAG_WINMON_Msk              (_U_(0x1) << TSENS_INTFLAG_WINMON_Pos)               /**< (TSENS_INTFLAG) Window Monitor Mask */
#define TSENS_INTFLAG_WINMON(value)           (TSENS_INTFLAG_WINMON_Msk & ((value) << TSENS_INTFLAG_WINMON_Pos))
#define TSENS_INTFLAG_OVF_Pos                 _U_(3)                                               /**< (TSENS_INTFLAG) Overflow Position */
#define TSENS_INTFLAG_OVF_Msk                 (_U_(0x1) << TSENS_INTFLAG_OVF_Pos)                  /**< (TSENS_INTFLAG) Overflow Mask */
#define TSENS_INTFLAG_OVF(value)              (TSENS_INTFLAG_OVF_Msk & ((value) << TSENS_INTFLAG_OVF_Pos))
#define TSENS_INTFLAG_Msk                     _U_(0x0F)                                            /**< (TSENS_INTFLAG) Register Mask  */


/* -------- TSENS_STATUS : (TSENS Offset: 0x07) ( R/ 8) Status Register -------- */
#define TSENS_STATUS_RESETVALUE               _U_(0x00)                                            /**<  (TSENS_STATUS) Status Register  Reset Value */

#define TSENS_STATUS_OVF_Pos                  _U_(0)                                               /**< (TSENS_STATUS) Result Overflow Position */
#define TSENS_STATUS_OVF_Msk                  (_U_(0x1) << TSENS_STATUS_OVF_Pos)                   /**< (TSENS_STATUS) Result Overflow Mask */
#define TSENS_STATUS_OVF(value)               (TSENS_STATUS_OVF_Msk & ((value) << TSENS_STATUS_OVF_Pos))
#define TSENS_STATUS_Msk                      _U_(0x01)                                            /**< (TSENS_STATUS) Register Mask  */


/* -------- TSENS_SYNCBUSY : (TSENS Offset: 0x08) ( R/ 32) Synchronization Busy Register -------- */
#define TSENS_SYNCBUSY_RESETVALUE             _U_(0x00)                                            /**<  (TSENS_SYNCBUSY) Synchronization Busy Register  Reset Value */

#define TSENS_SYNCBUSY_SWRST_Pos              _U_(0)                                               /**< (TSENS_SYNCBUSY) Software Reset Busy Position */
#define TSENS_SYNCBUSY_SWRST_Msk              (_U_(0x1) << TSENS_SYNCBUSY_SWRST_Pos)               /**< (TSENS_SYNCBUSY) Software Reset Busy Mask */
#define TSENS_SYNCBUSY_SWRST(value)           (TSENS_SYNCBUSY_SWRST_Msk & ((value) << TSENS_SYNCBUSY_SWRST_Pos))
#define TSENS_SYNCBUSY_ENABLE_Pos             _U_(1)                                               /**< (TSENS_SYNCBUSY) Enable Busy Position */
#define TSENS_SYNCBUSY_ENABLE_Msk             (_U_(0x1) << TSENS_SYNCBUSY_ENABLE_Pos)              /**< (TSENS_SYNCBUSY) Enable Busy Mask */
#define TSENS_SYNCBUSY_ENABLE(value)          (TSENS_SYNCBUSY_ENABLE_Msk & ((value) << TSENS_SYNCBUSY_ENABLE_Pos))
#define TSENS_SYNCBUSY_Msk                    _U_(0x00000003)                                      /**< (TSENS_SYNCBUSY) Register Mask  */


/* -------- TSENS_VALUE : (TSENS Offset: 0x0C) ( R/ 32) Value Register -------- */
#define TSENS_VALUE_RESETVALUE                _U_(0x00)                                            /**<  (TSENS_VALUE) Value Register  Reset Value */

#define TSENS_VALUE_VALUE_Pos                 _U_(0)                                               /**< (TSENS_VALUE) Measurement Value Position */
#define TSENS_VALUE_VALUE_Msk                 (_U_(0xFFFFFF) << TSENS_VALUE_VALUE_Pos)             /**< (TSENS_VALUE) Measurement Value Mask */
#define TSENS_VALUE_VALUE(value)              (TSENS_VALUE_VALUE_Msk & ((value) << TSENS_VALUE_VALUE_Pos))
#define TSENS_VALUE_Msk                       _U_(0x00FFFFFF)                                      /**< (TSENS_VALUE) Register Mask  */


/* -------- TSENS_WINLT : (TSENS Offset: 0x10) (R/W 32) Window Monitor Lower Threshold Register -------- */
#define TSENS_WINLT_RESETVALUE                _U_(0x00)                                            /**<  (TSENS_WINLT) Window Monitor Lower Threshold Register  Reset Value */

#define TSENS_WINLT_WINLT_Pos                 _U_(0)                                               /**< (TSENS_WINLT) Window Lower Threshold Position */
#define TSENS_WINLT_WINLT_Msk                 (_U_(0xFFFFFF) << TSENS_WINLT_WINLT_Pos)             /**< (TSENS_WINLT) Window Lower Threshold Mask */
#define TSENS_WINLT_WINLT(value)              (TSENS_WINLT_WINLT_Msk & ((value) << TSENS_WINLT_WINLT_Pos))
#define TSENS_WINLT_Msk                       _U_(0x00FFFFFF)                                      /**< (TSENS_WINLT) Register Mask  */


/* -------- TSENS_WINUT : (TSENS Offset: 0x14) (R/W 32) Window Monitor Upper Threshold Register -------- */
#define TSENS_WINUT_RESETVALUE                _U_(0x00)                                            /**<  (TSENS_WINUT) Window Monitor Upper Threshold Register  Reset Value */

#define TSENS_WINUT_WINUT_Pos                 _U_(0)                                               /**< (TSENS_WINUT) Window Upper Threshold Position */
#define TSENS_WINUT_WINUT_Msk                 (_U_(0xFFFFFF) << TSENS_WINUT_WINUT_Pos)             /**< (TSENS_WINUT) Window Upper Threshold Mask */
#define TSENS_WINUT_WINUT(value)              (TSENS_WINUT_WINUT_Msk & ((value) << TSENS_WINUT_WINUT_Pos))
#define TSENS_WINUT_Msk                       _U_(0x00FFFFFF)                                      /**< (TSENS_WINUT) Register Mask  */


/* -------- TSENS_GAIN : (TSENS Offset: 0x18) (R/W 32) Gain Register -------- */
#define TSENS_GAIN_RESETVALUE                 _U_(0x00)                                            /**<  (TSENS_GAIN) Gain Register  Reset Value */

#define TSENS_GAIN_GAIN_Pos                   _U_(0)                                               /**< (TSENS_GAIN) Time Amplifier Gain Position */
#define TSENS_GAIN_GAIN_Msk                   (_U_(0xFFFFFF) << TSENS_GAIN_GAIN_Pos)               /**< (TSENS_GAIN) Time Amplifier Gain Mask */
#define TSENS_GAIN_GAIN(value)                (TSENS_GAIN_GAIN_Msk & ((value) << TSENS_GAIN_GAIN_Pos))
#define TSENS_GAIN_Msk                        _U_(0x00FFFFFF)                                      /**< (TSENS_GAIN) Register Mask  */


/* -------- TSENS_OFFSET : (TSENS Offset: 0x1C) (R/W 32) Offset Register -------- */
#define TSENS_OFFSET_RESETVALUE               _U_(0x00)                                            /**<  (TSENS_OFFSET) Offset Register  Reset Value */

#define TSENS_OFFSET_OFFSETC_Pos              _U_(0)                                               /**< (TSENS_OFFSET) Offset Correction Position */
#define TSENS_OFFSET_OFFSETC_Msk              (_U_(0xFFFFFF) << TSENS_OFFSET_OFFSETC_Pos)          /**< (TSENS_OFFSET) Offset Correction Mask */
#define TSENS_OFFSET_OFFSETC(value)           (TSENS_OFFSET_OFFSETC_Msk & ((value) << TSENS_OFFSET_OFFSETC_Pos))
#define TSENS_OFFSET_Msk                      _U_(0x00FFFFFF)                                      /**< (TSENS_OFFSET) Register Mask  */


/* -------- TSENS_CAL : (TSENS Offset: 0x20) (R/W 32) Calibration Register -------- */
#define TSENS_CAL_RESETVALUE                  _U_(0x00)                                            /**<  (TSENS_CAL) Calibration Register  Reset Value */

#define TSENS_CAL_FCAL_Pos                    _U_(0)                                               /**< (TSENS_CAL) Frequency Calibration Position */
#define TSENS_CAL_FCAL_Msk                    (_U_(0x3F) << TSENS_CAL_FCAL_Pos)                    /**< (TSENS_CAL) Frequency Calibration Mask */
#define TSENS_CAL_FCAL(value)                 (TSENS_CAL_FCAL_Msk & ((value) << TSENS_CAL_FCAL_Pos))
#define TSENS_CAL_TCAL_Pos                    _U_(8)                                               /**< (TSENS_CAL) Temperature Calibration Position */
#define TSENS_CAL_TCAL_Msk                    (_U_(0x3F) << TSENS_CAL_TCAL_Pos)                    /**< (TSENS_CAL) Temperature Calibration Mask */
#define TSENS_CAL_TCAL(value)                 (TSENS_CAL_TCAL_Msk & ((value) << TSENS_CAL_TCAL_Pos))
#define TSENS_CAL_Msk                         _U_(0x00003F3F)                                      /**< (TSENS_CAL) Register Mask  */


/* -------- TSENS_DBGCTRL : (TSENS Offset: 0x24) (R/W 8) Debug Control Register -------- */
#define TSENS_DBGCTRL_RESETVALUE              _U_(0x00)                                            /**<  (TSENS_DBGCTRL) Debug Control Register  Reset Value */

#define TSENS_DBGCTRL_DBGRUN_Pos              _U_(0)                                               /**< (TSENS_DBGCTRL) Debug Run Position */
#define TSENS_DBGCTRL_DBGRUN_Msk              (_U_(0x1) << TSENS_DBGCTRL_DBGRUN_Pos)               /**< (TSENS_DBGCTRL) Debug Run Mask */
#define TSENS_DBGCTRL_DBGRUN(value)           (TSENS_DBGCTRL_DBGRUN_Msk & ((value) << TSENS_DBGCTRL_DBGRUN_Pos))
#define TSENS_DBGCTRL_Msk                     _U_(0x01)                                            /**< (TSENS_DBGCTRL) Register Mask  */


/** \brief TSENS register offsets definitions */
#define TSENS_CTRLA_REG_OFST           (0x00)              /**< (TSENS_CTRLA) Control A Register Offset */
#define TSENS_CTRLB_REG_OFST           (0x01)              /**< (TSENS_CTRLB) Control B Register Offset */
#define TSENS_CTRLC_REG_OFST           (0x02)              /**< (TSENS_CTRLC) Control C Register Offset */
#define TSENS_EVCTRL_REG_OFST          (0x03)              /**< (TSENS_EVCTRL) Event Control Register Offset */
#define TSENS_INTENCLR_REG_OFST        (0x04)              /**< (TSENS_INTENCLR) Interrupt Enable Clear Register Offset */
#define TSENS_INTENSET_REG_OFST        (0x05)              /**< (TSENS_INTENSET) Interrupt Enable Set Register Offset */
#define TSENS_INTFLAG_REG_OFST         (0x06)              /**< (TSENS_INTFLAG) Interrupt Flag Status and Clear Register Offset */
#define TSENS_STATUS_REG_OFST          (0x07)              /**< (TSENS_STATUS) Status Register Offset */
#define TSENS_SYNCBUSY_REG_OFST        (0x08)              /**< (TSENS_SYNCBUSY) Synchronization Busy Register Offset */
#define TSENS_VALUE_REG_OFST           (0x0C)              /**< (TSENS_VALUE) Value Register Offset */
#define TSENS_WINLT_REG_OFST           (0x10)              /**< (TSENS_WINLT) Window Monitor Lower Threshold Register Offset */
#define TSENS_WINUT_REG_OFST           (0x14)              /**< (TSENS_WINUT) Window Monitor Upper Threshold Register Offset */
#define TSENS_GAIN_REG_OFST            (0x18)              /**< (TSENS_GAIN) Gain Register Offset */
#define TSENS_OFFSET_REG_OFST          (0x1C)              /**< (TSENS_OFFSET) Offset Register Offset */
#define TSENS_CAL_REG_OFST             (0x20)              /**< (TSENS_CAL) Calibration Register Offset */
#define TSENS_DBGCTRL_REG_OFST         (0x24)              /**< (TSENS_DBGCTRL) Debug Control Register Offset */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief TSENS register API structure */
typedef struct
{  /* Temperature Sensor */
  __IO  uint8_t                        TSENS_CTRLA;        /**< Offset: 0x00 (R/W  8) Control A Register */
  __O   uint8_t                        TSENS_CTRLB;        /**< Offset: 0x01 ( /W  8) Control B Register */
  __IO  uint8_t                        TSENS_CTRLC;        /**< Offset: 0x02 (R/W  8) Control C Register */
  __IO  uint8_t                        TSENS_EVCTRL;       /**< Offset: 0x03 (R/W  8) Event Control Register */
  __IO  uint8_t                        TSENS_INTENCLR;     /**< Offset: 0x04 (R/W  8) Interrupt Enable Clear Register */
  __IO  uint8_t                        TSENS_INTENSET;     /**< Offset: 0x05 (R/W  8) Interrupt Enable Set Register */
  __IO  uint8_t                        TSENS_INTFLAG;      /**< Offset: 0x06 (R/W  8) Interrupt Flag Status and Clear Register */
  __I   uint8_t                        TSENS_STATUS;       /**< Offset: 0x07 (R/   8) Status Register */
  __I   uint32_t                       TSENS_SYNCBUSY;     /**< Offset: 0x08 (R/   32) Synchronization Busy Register */
  __I   uint32_t                       TSENS_VALUE;        /**< Offset: 0x0C (R/   32) Value Register */
  __IO  uint32_t                       TSENS_WINLT;        /**< Offset: 0x10 (R/W  32) Window Monitor Lower Threshold Register */
  __IO  uint32_t                       TSENS_WINUT;        /**< Offset: 0x14 (R/W  32) Window Monitor Upper Threshold Register */
  __IO  uint32_t                       TSENS_GAIN;         /**< Offset: 0x18 (R/W  32) Gain Register */
  __IO  uint32_t                       TSENS_OFFSET;       /**< Offset: 0x1C (R/W  32) Offset Register */
  __IO  uint32_t                       TSENS_CAL;          /**< Offset: 0x20 (R/W  32) Calibration Register */
  __IO  uint8_t                        TSENS_DBGCTRL;      /**< Offset: 0x24 (R/W  8) Debug Control Register */
} tsens_registers_t;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* _SAMC21_TSENS_COMPONENT_H_ */
