/**
 * \brief Component description for SDADC
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
#ifndef _SAMC21_SDADC_COMPONENT_H_
#define _SAMC21_SDADC_COMPONENT_H_

/* ************************************************************************** */
/*   SOFTWARE API DEFINITION FOR SDADC                                        */
/* ************************************************************************** */

/* -------- SDADC_CTRLA : (SDADC Offset: 0x00) (R/W 8) Control A -------- */
#define SDADC_CTRLA_RESETVALUE                _U_(0x00)                                            /**<  (SDADC_CTRLA) Control A  Reset Value */

#define SDADC_CTRLA_SWRST_Pos                 _U_(0)                                               /**< (SDADC_CTRLA) Software Reset Position */
#define SDADC_CTRLA_SWRST_Msk                 (_U_(0x1) << SDADC_CTRLA_SWRST_Pos)                  /**< (SDADC_CTRLA) Software Reset Mask */
#define SDADC_CTRLA_SWRST(value)              (SDADC_CTRLA_SWRST_Msk & ((value) << SDADC_CTRLA_SWRST_Pos))
#define SDADC_CTRLA_ENABLE_Pos                _U_(1)                                               /**< (SDADC_CTRLA) Enable Position */
#define SDADC_CTRLA_ENABLE_Msk                (_U_(0x1) << SDADC_CTRLA_ENABLE_Pos)                 /**< (SDADC_CTRLA) Enable Mask */
#define SDADC_CTRLA_ENABLE(value)             (SDADC_CTRLA_ENABLE_Msk & ((value) << SDADC_CTRLA_ENABLE_Pos))
#define SDADC_CTRLA_RUNSTDBY_Pos              _U_(6)                                               /**< (SDADC_CTRLA) Run during Standby Position */
#define SDADC_CTRLA_RUNSTDBY_Msk              (_U_(0x1) << SDADC_CTRLA_RUNSTDBY_Pos)               /**< (SDADC_CTRLA) Run during Standby Mask */
#define SDADC_CTRLA_RUNSTDBY(value)           (SDADC_CTRLA_RUNSTDBY_Msk & ((value) << SDADC_CTRLA_RUNSTDBY_Pos))
#define SDADC_CTRLA_ONDEMAND_Pos              _U_(7)                                               /**< (SDADC_CTRLA) On Demand Control Position */
#define SDADC_CTRLA_ONDEMAND_Msk              (_U_(0x1) << SDADC_CTRLA_ONDEMAND_Pos)               /**< (SDADC_CTRLA) On Demand Control Mask */
#define SDADC_CTRLA_ONDEMAND(value)           (SDADC_CTRLA_ONDEMAND_Msk & ((value) << SDADC_CTRLA_ONDEMAND_Pos))
#define SDADC_CTRLA_Msk                       _U_(0xC3)                                            /**< (SDADC_CTRLA) Register Mask  */


/* -------- SDADC_REFCTRL : (SDADC Offset: 0x01) (R/W 8) Reference Control -------- */
#define SDADC_REFCTRL_RESETVALUE              _U_(0x00)                                            /**<  (SDADC_REFCTRL) Reference Control  Reset Value */

#define SDADC_REFCTRL_REFSEL_Pos              _U_(0)                                               /**< (SDADC_REFCTRL) Reference Selection Position */
#define SDADC_REFCTRL_REFSEL_Msk              (_U_(0x3) << SDADC_REFCTRL_REFSEL_Pos)               /**< (SDADC_REFCTRL) Reference Selection Mask */
#define SDADC_REFCTRL_REFSEL(value)           (SDADC_REFCTRL_REFSEL_Msk & ((value) << SDADC_REFCTRL_REFSEL_Pos))
#define   SDADC_REFCTRL_REFSEL_INTREF_Val     _U_(0x0)                                             /**< (SDADC_REFCTRL) Internal Bandgap Reference  */
#define   SDADC_REFCTRL_REFSEL_AREFB_Val      _U_(0x1)                                             /**< (SDADC_REFCTRL) External Reference  */
#define   SDADC_REFCTRL_REFSEL_DAC_Val        _U_(0x2)                                             /**< (SDADC_REFCTRL) Internal DAC Output  */
#define   SDADC_REFCTRL_REFSEL_INTVCC_Val     _U_(0x3)                                             /**< (SDADC_REFCTRL) VDDANA  */
#define SDADC_REFCTRL_REFSEL_INTREF           (SDADC_REFCTRL_REFSEL_INTREF_Val << SDADC_REFCTRL_REFSEL_Pos) /**< (SDADC_REFCTRL) Internal Bandgap Reference Position  */
#define SDADC_REFCTRL_REFSEL_AREFB            (SDADC_REFCTRL_REFSEL_AREFB_Val << SDADC_REFCTRL_REFSEL_Pos) /**< (SDADC_REFCTRL) External Reference Position  */
#define SDADC_REFCTRL_REFSEL_DAC              (SDADC_REFCTRL_REFSEL_DAC_Val << SDADC_REFCTRL_REFSEL_Pos) /**< (SDADC_REFCTRL) Internal DAC Output Position  */
#define SDADC_REFCTRL_REFSEL_INTVCC           (SDADC_REFCTRL_REFSEL_INTVCC_Val << SDADC_REFCTRL_REFSEL_Pos) /**< (SDADC_REFCTRL) VDDANA Position  */
#define SDADC_REFCTRL_REFRANGE_Pos            _U_(4)                                               /**< (SDADC_REFCTRL) Reference Range Position */
#define SDADC_REFCTRL_REFRANGE_Msk            (_U_(0x3) << SDADC_REFCTRL_REFRANGE_Pos)             /**< (SDADC_REFCTRL) Reference Range Mask */
#define SDADC_REFCTRL_REFRANGE(value)         (SDADC_REFCTRL_REFRANGE_Msk & ((value) << SDADC_REFCTRL_REFRANGE_Pos))
#define SDADC_REFCTRL_ONREFBUF_Pos            _U_(7)                                               /**< (SDADC_REFCTRL) Reference Buffer Position */
#define SDADC_REFCTRL_ONREFBUF_Msk            (_U_(0x1) << SDADC_REFCTRL_ONREFBUF_Pos)             /**< (SDADC_REFCTRL) Reference Buffer Mask */
#define SDADC_REFCTRL_ONREFBUF(value)         (SDADC_REFCTRL_ONREFBUF_Msk & ((value) << SDADC_REFCTRL_ONREFBUF_Pos))
#define SDADC_REFCTRL_Msk                     _U_(0xB3)                                            /**< (SDADC_REFCTRL) Register Mask  */


/* -------- SDADC_CTRLB : (SDADC Offset: 0x02) (R/W 16) Control B -------- */
#define SDADC_CTRLB_RESETVALUE                _U_(0x2000)                                          /**<  (SDADC_CTRLB) Control B  Reset Value */

#define SDADC_CTRLB_PRESCALER_Pos             _U_(0)                                               /**< (SDADC_CTRLB) Prescaler Configuration Position */
#define SDADC_CTRLB_PRESCALER_Msk             (_U_(0xFF) << SDADC_CTRLB_PRESCALER_Pos)             /**< (SDADC_CTRLB) Prescaler Configuration Mask */
#define SDADC_CTRLB_PRESCALER(value)          (SDADC_CTRLB_PRESCALER_Msk & ((value) << SDADC_CTRLB_PRESCALER_Pos))
#define   SDADC_CTRLB_PRESCALER_DIV2_Val      _U_(0x0)                                             /**< (SDADC_CTRLB) Peripheral clock divided by 2  */
#define   SDADC_CTRLB_PRESCALER_DIV4_Val      _U_(0x1)                                             /**< (SDADC_CTRLB) Peripheral clock divided by 4  */
#define   SDADC_CTRLB_PRESCALER_DIV8_Val      _U_(0x2)                                             /**< (SDADC_CTRLB) Peripheral clock divided by 8  */
#define   SDADC_CTRLB_PRESCALER_DIV16_Val     _U_(0x3)                                             /**< (SDADC_CTRLB) Peripheral clock divided by 16  */
#define   SDADC_CTRLB_PRESCALER_DIV32_Val     _U_(0x4)                                             /**< (SDADC_CTRLB) Peripheral clock divided by 32  */
#define   SDADC_CTRLB_PRESCALER_DIV64_Val     _U_(0x5)                                             /**< (SDADC_CTRLB) Peripheral clock divided by 64  */
#define   SDADC_CTRLB_PRESCALER_DIV128_Val    _U_(0x6)                                             /**< (SDADC_CTRLB) Peripheral clock divided by 128  */
#define   SDADC_CTRLB_PRESCALER_DIV256_Val    _U_(0x7)                                             /**< (SDADC_CTRLB) Peripheral clock divided by 256  */
#define SDADC_CTRLB_PRESCALER_DIV2            (SDADC_CTRLB_PRESCALER_DIV2_Val << SDADC_CTRLB_PRESCALER_Pos) /**< (SDADC_CTRLB) Peripheral clock divided by 2 Position  */
#define SDADC_CTRLB_PRESCALER_DIV4            (SDADC_CTRLB_PRESCALER_DIV4_Val << SDADC_CTRLB_PRESCALER_Pos) /**< (SDADC_CTRLB) Peripheral clock divided by 4 Position  */
#define SDADC_CTRLB_PRESCALER_DIV8            (SDADC_CTRLB_PRESCALER_DIV8_Val << SDADC_CTRLB_PRESCALER_Pos) /**< (SDADC_CTRLB) Peripheral clock divided by 8 Position  */
#define SDADC_CTRLB_PRESCALER_DIV16           (SDADC_CTRLB_PRESCALER_DIV16_Val << SDADC_CTRLB_PRESCALER_Pos) /**< (SDADC_CTRLB) Peripheral clock divided by 16 Position  */
#define SDADC_CTRLB_PRESCALER_DIV32           (SDADC_CTRLB_PRESCALER_DIV32_Val << SDADC_CTRLB_PRESCALER_Pos) /**< (SDADC_CTRLB) Peripheral clock divided by 32 Position  */
#define SDADC_CTRLB_PRESCALER_DIV64           (SDADC_CTRLB_PRESCALER_DIV64_Val << SDADC_CTRLB_PRESCALER_Pos) /**< (SDADC_CTRLB) Peripheral clock divided by 64 Position  */
#define SDADC_CTRLB_PRESCALER_DIV128          (SDADC_CTRLB_PRESCALER_DIV128_Val << SDADC_CTRLB_PRESCALER_Pos) /**< (SDADC_CTRLB) Peripheral clock divided by 128 Position  */
#define SDADC_CTRLB_PRESCALER_DIV256          (SDADC_CTRLB_PRESCALER_DIV256_Val << SDADC_CTRLB_PRESCALER_Pos) /**< (SDADC_CTRLB) Peripheral clock divided by 256 Position  */
#define SDADC_CTRLB_OSR_Pos                   _U_(8)                                               /**< (SDADC_CTRLB) Over Sampling Ratio Position */
#define SDADC_CTRLB_OSR_Msk                   (_U_(0x7) << SDADC_CTRLB_OSR_Pos)                    /**< (SDADC_CTRLB) Over Sampling Ratio Mask */
#define SDADC_CTRLB_OSR(value)                (SDADC_CTRLB_OSR_Msk & ((value) << SDADC_CTRLB_OSR_Pos))
#define   SDADC_CTRLB_OSR_OSR64_Val           _U_(0x0)                                             /**< (SDADC_CTRLB) Over Sampling Ratio is 64  */
#define   SDADC_CTRLB_OSR_OSR128_Val          _U_(0x1)                                             /**< (SDADC_CTRLB) Over Sampling Ratio is 128  */
#define   SDADC_CTRLB_OSR_OSR256_Val          _U_(0x2)                                             /**< (SDADC_CTRLB) Over Sampling Ratio is 256  */
#define   SDADC_CTRLB_OSR_OSR512_Val          _U_(0x3)                                             /**< (SDADC_CTRLB) Over Sampling Ratio is 512  */
#define   SDADC_CTRLB_OSR_OSR1024_Val         _U_(0x4)                                             /**< (SDADC_CTRLB) Over Sampling Ratio is 1024  */
#define SDADC_CTRLB_OSR_OSR64                 (SDADC_CTRLB_OSR_OSR64_Val << SDADC_CTRLB_OSR_Pos)   /**< (SDADC_CTRLB) Over Sampling Ratio is 64 Position  */
#define SDADC_CTRLB_OSR_OSR128                (SDADC_CTRLB_OSR_OSR128_Val << SDADC_CTRLB_OSR_Pos)  /**< (SDADC_CTRLB) Over Sampling Ratio is 128 Position  */
#define SDADC_CTRLB_OSR_OSR256                (SDADC_CTRLB_OSR_OSR256_Val << SDADC_CTRLB_OSR_Pos)  /**< (SDADC_CTRLB) Over Sampling Ratio is 256 Position  */
#define SDADC_CTRLB_OSR_OSR512                (SDADC_CTRLB_OSR_OSR512_Val << SDADC_CTRLB_OSR_Pos)  /**< (SDADC_CTRLB) Over Sampling Ratio is 512 Position  */
#define SDADC_CTRLB_OSR_OSR1024               (SDADC_CTRLB_OSR_OSR1024_Val << SDADC_CTRLB_OSR_Pos) /**< (SDADC_CTRLB) Over Sampling Ratio is 1024 Position  */
#define SDADC_CTRLB_SKPCNT_Pos                _U_(12)                                              /**< (SDADC_CTRLB) Skip Sample Count Position */
#define SDADC_CTRLB_SKPCNT_Msk                (_U_(0xF) << SDADC_CTRLB_SKPCNT_Pos)                 /**< (SDADC_CTRLB) Skip Sample Count Mask */
#define SDADC_CTRLB_SKPCNT(value)             (SDADC_CTRLB_SKPCNT_Msk & ((value) << SDADC_CTRLB_SKPCNT_Pos))
#define SDADC_CTRLB_Msk                       _U_(0xF7FF)                                          /**< (SDADC_CTRLB) Register Mask  */


/* -------- SDADC_EVCTRL : (SDADC Offset: 0x04) (R/W 8) Event Control -------- */
#define SDADC_EVCTRL_RESETVALUE               _U_(0x00)                                            /**<  (SDADC_EVCTRL) Event Control  Reset Value */

#define SDADC_EVCTRL_FLUSHEI_Pos              _U_(0)                                               /**< (SDADC_EVCTRL) Flush Event Input Enable Position */
#define SDADC_EVCTRL_FLUSHEI_Msk              (_U_(0x1) << SDADC_EVCTRL_FLUSHEI_Pos)               /**< (SDADC_EVCTRL) Flush Event Input Enable Mask */
#define SDADC_EVCTRL_FLUSHEI(value)           (SDADC_EVCTRL_FLUSHEI_Msk & ((value) << SDADC_EVCTRL_FLUSHEI_Pos))
#define SDADC_EVCTRL_STARTEI_Pos              _U_(1)                                               /**< (SDADC_EVCTRL) Start Conversion Event Input Enable Position */
#define SDADC_EVCTRL_STARTEI_Msk              (_U_(0x1) << SDADC_EVCTRL_STARTEI_Pos)               /**< (SDADC_EVCTRL) Start Conversion Event Input Enable Mask */
#define SDADC_EVCTRL_STARTEI(value)           (SDADC_EVCTRL_STARTEI_Msk & ((value) << SDADC_EVCTRL_STARTEI_Pos))
#define SDADC_EVCTRL_FLUSHINV_Pos             _U_(2)                                               /**< (SDADC_EVCTRL) Flush Event Invert Enable Position */
#define SDADC_EVCTRL_FLUSHINV_Msk             (_U_(0x1) << SDADC_EVCTRL_FLUSHINV_Pos)              /**< (SDADC_EVCTRL) Flush Event Invert Enable Mask */
#define SDADC_EVCTRL_FLUSHINV(value)          (SDADC_EVCTRL_FLUSHINV_Msk & ((value) << SDADC_EVCTRL_FLUSHINV_Pos))
#define SDADC_EVCTRL_STARTINV_Pos             _U_(3)                                               /**< (SDADC_EVCTRL) Satrt Event Invert Enable Position */
#define SDADC_EVCTRL_STARTINV_Msk             (_U_(0x1) << SDADC_EVCTRL_STARTINV_Pos)              /**< (SDADC_EVCTRL) Satrt Event Invert Enable Mask */
#define SDADC_EVCTRL_STARTINV(value)          (SDADC_EVCTRL_STARTINV_Msk & ((value) << SDADC_EVCTRL_STARTINV_Pos))
#define SDADC_EVCTRL_RESRDYEO_Pos             _U_(4)                                               /**< (SDADC_EVCTRL) Result Ready Event Out Position */
#define SDADC_EVCTRL_RESRDYEO_Msk             (_U_(0x1) << SDADC_EVCTRL_RESRDYEO_Pos)              /**< (SDADC_EVCTRL) Result Ready Event Out Mask */
#define SDADC_EVCTRL_RESRDYEO(value)          (SDADC_EVCTRL_RESRDYEO_Msk & ((value) << SDADC_EVCTRL_RESRDYEO_Pos))
#define SDADC_EVCTRL_WINMONEO_Pos             _U_(5)                                               /**< (SDADC_EVCTRL) Window Monitor Event Out Position */
#define SDADC_EVCTRL_WINMONEO_Msk             (_U_(0x1) << SDADC_EVCTRL_WINMONEO_Pos)              /**< (SDADC_EVCTRL) Window Monitor Event Out Mask */
#define SDADC_EVCTRL_WINMONEO(value)          (SDADC_EVCTRL_WINMONEO_Msk & ((value) << SDADC_EVCTRL_WINMONEO_Pos))
#define SDADC_EVCTRL_Msk                      _U_(0x3F)                                            /**< (SDADC_EVCTRL) Register Mask  */


/* -------- SDADC_INTENCLR : (SDADC Offset: 0x05) (R/W 8) Interrupt Enable Clear -------- */
#define SDADC_INTENCLR_RESETVALUE             _U_(0x00)                                            /**<  (SDADC_INTENCLR) Interrupt Enable Clear  Reset Value */

#define SDADC_INTENCLR_RESRDY_Pos             _U_(0)                                               /**< (SDADC_INTENCLR) Result Ready Interrupt Disable Position */
#define SDADC_INTENCLR_RESRDY_Msk             (_U_(0x1) << SDADC_INTENCLR_RESRDY_Pos)              /**< (SDADC_INTENCLR) Result Ready Interrupt Disable Mask */
#define SDADC_INTENCLR_RESRDY(value)          (SDADC_INTENCLR_RESRDY_Msk & ((value) << SDADC_INTENCLR_RESRDY_Pos))
#define SDADC_INTENCLR_OVERRUN_Pos            _U_(1)                                               /**< (SDADC_INTENCLR) Overrun Interrupt Disable Position */
#define SDADC_INTENCLR_OVERRUN_Msk            (_U_(0x1) << SDADC_INTENCLR_OVERRUN_Pos)             /**< (SDADC_INTENCLR) Overrun Interrupt Disable Mask */
#define SDADC_INTENCLR_OVERRUN(value)         (SDADC_INTENCLR_OVERRUN_Msk & ((value) << SDADC_INTENCLR_OVERRUN_Pos))
#define SDADC_INTENCLR_WINMON_Pos             _U_(2)                                               /**< (SDADC_INTENCLR) Window Monitor Interrupt Disable Position */
#define SDADC_INTENCLR_WINMON_Msk             (_U_(0x1) << SDADC_INTENCLR_WINMON_Pos)              /**< (SDADC_INTENCLR) Window Monitor Interrupt Disable Mask */
#define SDADC_INTENCLR_WINMON(value)          (SDADC_INTENCLR_WINMON_Msk & ((value) << SDADC_INTENCLR_WINMON_Pos))
#define SDADC_INTENCLR_Msk                    _U_(0x07)                                            /**< (SDADC_INTENCLR) Register Mask  */


/* -------- SDADC_INTENSET : (SDADC Offset: 0x06) (R/W 8) Interrupt Enable Set -------- */
#define SDADC_INTENSET_RESETVALUE             _U_(0x00)                                            /**<  (SDADC_INTENSET) Interrupt Enable Set  Reset Value */

#define SDADC_INTENSET_RESRDY_Pos             _U_(0)                                               /**< (SDADC_INTENSET) Result Ready Interrupt Enable Position */
#define SDADC_INTENSET_RESRDY_Msk             (_U_(0x1) << SDADC_INTENSET_RESRDY_Pos)              /**< (SDADC_INTENSET) Result Ready Interrupt Enable Mask */
#define SDADC_INTENSET_RESRDY(value)          (SDADC_INTENSET_RESRDY_Msk & ((value) << SDADC_INTENSET_RESRDY_Pos))
#define SDADC_INTENSET_OVERRUN_Pos            _U_(1)                                               /**< (SDADC_INTENSET) Overrun Interrupt Enable Position */
#define SDADC_INTENSET_OVERRUN_Msk            (_U_(0x1) << SDADC_INTENSET_OVERRUN_Pos)             /**< (SDADC_INTENSET) Overrun Interrupt Enable Mask */
#define SDADC_INTENSET_OVERRUN(value)         (SDADC_INTENSET_OVERRUN_Msk & ((value) << SDADC_INTENSET_OVERRUN_Pos))
#define SDADC_INTENSET_WINMON_Pos             _U_(2)                                               /**< (SDADC_INTENSET) Window Monitor Interrupt Enable Position */
#define SDADC_INTENSET_WINMON_Msk             (_U_(0x1) << SDADC_INTENSET_WINMON_Pos)              /**< (SDADC_INTENSET) Window Monitor Interrupt Enable Mask */
#define SDADC_INTENSET_WINMON(value)          (SDADC_INTENSET_WINMON_Msk & ((value) << SDADC_INTENSET_WINMON_Pos))
#define SDADC_INTENSET_Msk                    _U_(0x07)                                            /**< (SDADC_INTENSET) Register Mask  */


/* -------- SDADC_INTFLAG : (SDADC Offset: 0x07) (R/W 8) Interrupt Flag Status and Clear -------- */
#define SDADC_INTFLAG_RESETVALUE              _U_(0x00)                                            /**<  (SDADC_INTFLAG) Interrupt Flag Status and Clear  Reset Value */

#define SDADC_INTFLAG_RESRDY_Pos              _U_(0)                                               /**< (SDADC_INTFLAG) Result Ready Interrupt Flag Position */
#define SDADC_INTFLAG_RESRDY_Msk              (_U_(0x1) << SDADC_INTFLAG_RESRDY_Pos)               /**< (SDADC_INTFLAG) Result Ready Interrupt Flag Mask */
#define SDADC_INTFLAG_RESRDY(value)           (SDADC_INTFLAG_RESRDY_Msk & ((value) << SDADC_INTFLAG_RESRDY_Pos))
#define SDADC_INTFLAG_OVERRUN_Pos             _U_(1)                                               /**< (SDADC_INTFLAG) Overrun Interrupt Flag Position */
#define SDADC_INTFLAG_OVERRUN_Msk             (_U_(0x1) << SDADC_INTFLAG_OVERRUN_Pos)              /**< (SDADC_INTFLAG) Overrun Interrupt Flag Mask */
#define SDADC_INTFLAG_OVERRUN(value)          (SDADC_INTFLAG_OVERRUN_Msk & ((value) << SDADC_INTFLAG_OVERRUN_Pos))
#define SDADC_INTFLAG_WINMON_Pos              _U_(2)                                               /**< (SDADC_INTFLAG) Window Monitor Interrupt Flag Position */
#define SDADC_INTFLAG_WINMON_Msk              (_U_(0x1) << SDADC_INTFLAG_WINMON_Pos)               /**< (SDADC_INTFLAG) Window Monitor Interrupt Flag Mask */
#define SDADC_INTFLAG_WINMON(value)           (SDADC_INTFLAG_WINMON_Msk & ((value) << SDADC_INTFLAG_WINMON_Pos))
#define SDADC_INTFLAG_Msk                     _U_(0x07)                                            /**< (SDADC_INTFLAG) Register Mask  */


/* -------- SDADC_SEQSTATUS : (SDADC Offset: 0x08) ( R/ 8) Sequence Status -------- */
#define SDADC_SEQSTATUS_RESETVALUE            _U_(0x00)                                            /**<  (SDADC_SEQSTATUS) Sequence Status  Reset Value */

#define SDADC_SEQSTATUS_SEQSTATE_Pos          _U_(0)                                               /**< (SDADC_SEQSTATUS) Sequence State Position */
#define SDADC_SEQSTATUS_SEQSTATE_Msk          (_U_(0xF) << SDADC_SEQSTATUS_SEQSTATE_Pos)           /**< (SDADC_SEQSTATUS) Sequence State Mask */
#define SDADC_SEQSTATUS_SEQSTATE(value)       (SDADC_SEQSTATUS_SEQSTATE_Msk & ((value) << SDADC_SEQSTATUS_SEQSTATE_Pos))
#define SDADC_SEQSTATUS_SEQBUSY_Pos           _U_(7)                                               /**< (SDADC_SEQSTATUS) Sequence Busy Position */
#define SDADC_SEQSTATUS_SEQBUSY_Msk           (_U_(0x1) << SDADC_SEQSTATUS_SEQBUSY_Pos)            /**< (SDADC_SEQSTATUS) Sequence Busy Mask */
#define SDADC_SEQSTATUS_SEQBUSY(value)        (SDADC_SEQSTATUS_SEQBUSY_Msk & ((value) << SDADC_SEQSTATUS_SEQBUSY_Pos))
#define SDADC_SEQSTATUS_Msk                   _U_(0x8F)                                            /**< (SDADC_SEQSTATUS) Register Mask  */


/* -------- SDADC_INPUTCTRL : (SDADC Offset: 0x09) (R/W 8) Input Control -------- */
#define SDADC_INPUTCTRL_RESETVALUE            _U_(0x00)                                            /**<  (SDADC_INPUTCTRL) Input Control  Reset Value */

#define SDADC_INPUTCTRL_MUXSEL_Pos            _U_(0)                                               /**< (SDADC_INPUTCTRL) SDADC Input Selection Position */
#define SDADC_INPUTCTRL_MUXSEL_Msk            (_U_(0xF) << SDADC_INPUTCTRL_MUXSEL_Pos)             /**< (SDADC_INPUTCTRL) SDADC Input Selection Mask */
#define SDADC_INPUTCTRL_MUXSEL(value)         (SDADC_INPUTCTRL_MUXSEL_Msk & ((value) << SDADC_INPUTCTRL_MUXSEL_Pos))
#define   SDADC_INPUTCTRL_MUXSEL_AIN0_Val     _U_(0x0)                                             /**< (SDADC_INPUTCTRL) SDADC AIN0 Pin  */
#define   SDADC_INPUTCTRL_MUXSEL_AIN1_Val     _U_(0x1)                                             /**< (SDADC_INPUTCTRL) SDADC AIN1 Pin  */
#define   SDADC_INPUTCTRL_MUXSEL_AIN2_Val     _U_(0x2)                                             /**< (SDADC_INPUTCTRL) SDADC AIN2 Pin  */
#define SDADC_INPUTCTRL_MUXSEL_AIN0           (SDADC_INPUTCTRL_MUXSEL_AIN0_Val << SDADC_INPUTCTRL_MUXSEL_Pos) /**< (SDADC_INPUTCTRL) SDADC AIN0 Pin Position  */
#define SDADC_INPUTCTRL_MUXSEL_AIN1           (SDADC_INPUTCTRL_MUXSEL_AIN1_Val << SDADC_INPUTCTRL_MUXSEL_Pos) /**< (SDADC_INPUTCTRL) SDADC AIN1 Pin Position  */
#define SDADC_INPUTCTRL_MUXSEL_AIN2           (SDADC_INPUTCTRL_MUXSEL_AIN2_Val << SDADC_INPUTCTRL_MUXSEL_Pos) /**< (SDADC_INPUTCTRL) SDADC AIN2 Pin Position  */
#define SDADC_INPUTCTRL_Msk                   _U_(0x0F)                                            /**< (SDADC_INPUTCTRL) Register Mask  */


/* -------- SDADC_CTRLC : (SDADC Offset: 0x0A) (R/W 8) Control C -------- */
#define SDADC_CTRLC_RESETVALUE                _U_(0x00)                                            /**<  (SDADC_CTRLC) Control C  Reset Value */

#define SDADC_CTRLC_FREERUN_Pos               _U_(0)                                               /**< (SDADC_CTRLC) Free Running Mode Position */
#define SDADC_CTRLC_FREERUN_Msk               (_U_(0x1) << SDADC_CTRLC_FREERUN_Pos)                /**< (SDADC_CTRLC) Free Running Mode Mask */
#define SDADC_CTRLC_FREERUN(value)            (SDADC_CTRLC_FREERUN_Msk & ((value) << SDADC_CTRLC_FREERUN_Pos))
#define SDADC_CTRLC_Msk                       _U_(0x01)                                            /**< (SDADC_CTRLC) Register Mask  */


/* -------- SDADC_WINCTRL : (SDADC Offset: 0x0B) (R/W 8) Window Monitor Control -------- */
#define SDADC_WINCTRL_RESETVALUE              _U_(0x00)                                            /**<  (SDADC_WINCTRL) Window Monitor Control  Reset Value */

#define SDADC_WINCTRL_WINMODE_Pos             _U_(0)                                               /**< (SDADC_WINCTRL) Window Monitor Mode Position */
#define SDADC_WINCTRL_WINMODE_Msk             (_U_(0x7) << SDADC_WINCTRL_WINMODE_Pos)              /**< (SDADC_WINCTRL) Window Monitor Mode Mask */
#define SDADC_WINCTRL_WINMODE(value)          (SDADC_WINCTRL_WINMODE_Msk & ((value) << SDADC_WINCTRL_WINMODE_Pos))
#define SDADC_WINCTRL_Msk                     _U_(0x07)                                            /**< (SDADC_WINCTRL) Register Mask  */


/* -------- SDADC_WINLT : (SDADC Offset: 0x0C) (R/W 32) Window Monitor Lower Threshold -------- */
#define SDADC_WINLT_RESETVALUE                _U_(0x00)                                            /**<  (SDADC_WINLT) Window Monitor Lower Threshold  Reset Value */

#define SDADC_WINLT_WINLT_Pos                 _U_(0)                                               /**< (SDADC_WINLT) Window Lower Threshold Position */
#define SDADC_WINLT_WINLT_Msk                 (_U_(0xFFFFFF) << SDADC_WINLT_WINLT_Pos)             /**< (SDADC_WINLT) Window Lower Threshold Mask */
#define SDADC_WINLT_WINLT(value)              (SDADC_WINLT_WINLT_Msk & ((value) << SDADC_WINLT_WINLT_Pos))
#define SDADC_WINLT_Msk                       _U_(0x00FFFFFF)                                      /**< (SDADC_WINLT) Register Mask  */


/* -------- SDADC_WINUT : (SDADC Offset: 0x10) (R/W 32) Window Monitor Upper Threshold -------- */
#define SDADC_WINUT_RESETVALUE                _U_(0x00)                                            /**<  (SDADC_WINUT) Window Monitor Upper Threshold  Reset Value */

#define SDADC_WINUT_WINUT_Pos                 _U_(0)                                               /**< (SDADC_WINUT) Window Upper Threshold Position */
#define SDADC_WINUT_WINUT_Msk                 (_U_(0xFFFFFF) << SDADC_WINUT_WINUT_Pos)             /**< (SDADC_WINUT) Window Upper Threshold Mask */
#define SDADC_WINUT_WINUT(value)              (SDADC_WINUT_WINUT_Msk & ((value) << SDADC_WINUT_WINUT_Pos))
#define SDADC_WINUT_Msk                       _U_(0x00FFFFFF)                                      /**< (SDADC_WINUT) Register Mask  */


/* -------- SDADC_OFFSETCORR : (SDADC Offset: 0x14) (R/W 32) Offset Correction -------- */
#define SDADC_OFFSETCORR_RESETVALUE           _U_(0x00)                                            /**<  (SDADC_OFFSETCORR) Offset Correction  Reset Value */

#define SDADC_OFFSETCORR_OFFSETCORR_Pos       _U_(0)                                               /**< (SDADC_OFFSETCORR) Offset Correction Value Position */
#define SDADC_OFFSETCORR_OFFSETCORR_Msk       (_U_(0xFFFFFF) << SDADC_OFFSETCORR_OFFSETCORR_Pos)   /**< (SDADC_OFFSETCORR) Offset Correction Value Mask */
#define SDADC_OFFSETCORR_OFFSETCORR(value)    (SDADC_OFFSETCORR_OFFSETCORR_Msk & ((value) << SDADC_OFFSETCORR_OFFSETCORR_Pos))
#define SDADC_OFFSETCORR_Msk                  _U_(0x00FFFFFF)                                      /**< (SDADC_OFFSETCORR) Register Mask  */


/* -------- SDADC_GAINCORR : (SDADC Offset: 0x18) (R/W 16) Gain Correction -------- */
#define SDADC_GAINCORR_RESETVALUE             _U_(0x01)                                            /**<  (SDADC_GAINCORR) Gain Correction  Reset Value */

#define SDADC_GAINCORR_GAINCORR_Pos           _U_(0)                                               /**< (SDADC_GAINCORR) Gain Correction Value Position */
#define SDADC_GAINCORR_GAINCORR_Msk           (_U_(0x3FFF) << SDADC_GAINCORR_GAINCORR_Pos)         /**< (SDADC_GAINCORR) Gain Correction Value Mask */
#define SDADC_GAINCORR_GAINCORR(value)        (SDADC_GAINCORR_GAINCORR_Msk & ((value) << SDADC_GAINCORR_GAINCORR_Pos))
#define SDADC_GAINCORR_Msk                    _U_(0x3FFF)                                          /**< (SDADC_GAINCORR) Register Mask  */


/* -------- SDADC_SHIFTCORR : (SDADC Offset: 0x1A) (R/W 8) Shift Correction -------- */
#define SDADC_SHIFTCORR_RESETVALUE            _U_(0x00)                                            /**<  (SDADC_SHIFTCORR) Shift Correction  Reset Value */

#define SDADC_SHIFTCORR_SHIFTCORR_Pos         _U_(0)                                               /**< (SDADC_SHIFTCORR) Shift Correction Value Position */
#define SDADC_SHIFTCORR_SHIFTCORR_Msk         (_U_(0xF) << SDADC_SHIFTCORR_SHIFTCORR_Pos)          /**< (SDADC_SHIFTCORR) Shift Correction Value Mask */
#define SDADC_SHIFTCORR_SHIFTCORR(value)      (SDADC_SHIFTCORR_SHIFTCORR_Msk & ((value) << SDADC_SHIFTCORR_SHIFTCORR_Pos))
#define SDADC_SHIFTCORR_Msk                   _U_(0x0F)                                            /**< (SDADC_SHIFTCORR) Register Mask  */


/* -------- SDADC_SWTRIG : (SDADC Offset: 0x1C) (R/W 8) Software Trigger -------- */
#define SDADC_SWTRIG_RESETVALUE               _U_(0x00)                                            /**<  (SDADC_SWTRIG) Software Trigger  Reset Value */

#define SDADC_SWTRIG_FLUSH_Pos                _U_(0)                                               /**< (SDADC_SWTRIG) SDADC Flush Position */
#define SDADC_SWTRIG_FLUSH_Msk                (_U_(0x1) << SDADC_SWTRIG_FLUSH_Pos)                 /**< (SDADC_SWTRIG) SDADC Flush Mask */
#define SDADC_SWTRIG_FLUSH(value)             (SDADC_SWTRIG_FLUSH_Msk & ((value) << SDADC_SWTRIG_FLUSH_Pos))
#define SDADC_SWTRIG_START_Pos                _U_(1)                                               /**< (SDADC_SWTRIG) Start SDADC Conversion Position */
#define SDADC_SWTRIG_START_Msk                (_U_(0x1) << SDADC_SWTRIG_START_Pos)                 /**< (SDADC_SWTRIG) Start SDADC Conversion Mask */
#define SDADC_SWTRIG_START(value)             (SDADC_SWTRIG_START_Msk & ((value) << SDADC_SWTRIG_START_Pos))
#define SDADC_SWTRIG_Msk                      _U_(0x03)                                            /**< (SDADC_SWTRIG) Register Mask  */


/* -------- SDADC_SYNCBUSY : (SDADC Offset: 0x20) ( R/ 32) Synchronization Busy -------- */
#define SDADC_SYNCBUSY_RESETVALUE             _U_(0x00)                                            /**<  (SDADC_SYNCBUSY) Synchronization Busy  Reset Value */

#define SDADC_SYNCBUSY_SWRST_Pos              _U_(0)                                               /**< (SDADC_SYNCBUSY) SWRST Synchronization Busy Position */
#define SDADC_SYNCBUSY_SWRST_Msk              (_U_(0x1) << SDADC_SYNCBUSY_SWRST_Pos)               /**< (SDADC_SYNCBUSY) SWRST Synchronization Busy Mask */
#define SDADC_SYNCBUSY_SWRST(value)           (SDADC_SYNCBUSY_SWRST_Msk & ((value) << SDADC_SYNCBUSY_SWRST_Pos))
#define SDADC_SYNCBUSY_ENABLE_Pos             _U_(1)                                               /**< (SDADC_SYNCBUSY) ENABLE Synchronization Busy Position */
#define SDADC_SYNCBUSY_ENABLE_Msk             (_U_(0x1) << SDADC_SYNCBUSY_ENABLE_Pos)              /**< (SDADC_SYNCBUSY) ENABLE Synchronization Busy Mask */
#define SDADC_SYNCBUSY_ENABLE(value)          (SDADC_SYNCBUSY_ENABLE_Msk & ((value) << SDADC_SYNCBUSY_ENABLE_Pos))
#define SDADC_SYNCBUSY_CTRLC_Pos              _U_(2)                                               /**< (SDADC_SYNCBUSY) CTRLC Synchronization Busy Position */
#define SDADC_SYNCBUSY_CTRLC_Msk              (_U_(0x1) << SDADC_SYNCBUSY_CTRLC_Pos)               /**< (SDADC_SYNCBUSY) CTRLC Synchronization Busy Mask */
#define SDADC_SYNCBUSY_CTRLC(value)           (SDADC_SYNCBUSY_CTRLC_Msk & ((value) << SDADC_SYNCBUSY_CTRLC_Pos))
#define SDADC_SYNCBUSY_INPUTCTRL_Pos          _U_(3)                                               /**< (SDADC_SYNCBUSY) INPUTCTRL Synchronization Busy Position */
#define SDADC_SYNCBUSY_INPUTCTRL_Msk          (_U_(0x1) << SDADC_SYNCBUSY_INPUTCTRL_Pos)           /**< (SDADC_SYNCBUSY) INPUTCTRL Synchronization Busy Mask */
#define SDADC_SYNCBUSY_INPUTCTRL(value)       (SDADC_SYNCBUSY_INPUTCTRL_Msk & ((value) << SDADC_SYNCBUSY_INPUTCTRL_Pos))
#define SDADC_SYNCBUSY_WINCTRL_Pos            _U_(4)                                               /**< (SDADC_SYNCBUSY) WINCTRL Synchronization Busy Position */
#define SDADC_SYNCBUSY_WINCTRL_Msk            (_U_(0x1) << SDADC_SYNCBUSY_WINCTRL_Pos)             /**< (SDADC_SYNCBUSY) WINCTRL Synchronization Busy Mask */
#define SDADC_SYNCBUSY_WINCTRL(value)         (SDADC_SYNCBUSY_WINCTRL_Msk & ((value) << SDADC_SYNCBUSY_WINCTRL_Pos))
#define SDADC_SYNCBUSY_WINLT_Pos              _U_(5)                                               /**< (SDADC_SYNCBUSY) WINLT Synchronization Busy Position */
#define SDADC_SYNCBUSY_WINLT_Msk              (_U_(0x1) << SDADC_SYNCBUSY_WINLT_Pos)               /**< (SDADC_SYNCBUSY) WINLT Synchronization Busy Mask */
#define SDADC_SYNCBUSY_WINLT(value)           (SDADC_SYNCBUSY_WINLT_Msk & ((value) << SDADC_SYNCBUSY_WINLT_Pos))
#define SDADC_SYNCBUSY_WINUT_Pos              _U_(6)                                               /**< (SDADC_SYNCBUSY) WINUT Synchronization Busy Position */
#define SDADC_SYNCBUSY_WINUT_Msk              (_U_(0x1) << SDADC_SYNCBUSY_WINUT_Pos)               /**< (SDADC_SYNCBUSY) WINUT Synchronization Busy Mask */
#define SDADC_SYNCBUSY_WINUT(value)           (SDADC_SYNCBUSY_WINUT_Msk & ((value) << SDADC_SYNCBUSY_WINUT_Pos))
#define SDADC_SYNCBUSY_OFFSETCORR_Pos         _U_(7)                                               /**< (SDADC_SYNCBUSY) OFFSETCTRL Synchronization Busy Position */
#define SDADC_SYNCBUSY_OFFSETCORR_Msk         (_U_(0x1) << SDADC_SYNCBUSY_OFFSETCORR_Pos)          /**< (SDADC_SYNCBUSY) OFFSETCTRL Synchronization Busy Mask */
#define SDADC_SYNCBUSY_OFFSETCORR(value)      (SDADC_SYNCBUSY_OFFSETCORR_Msk & ((value) << SDADC_SYNCBUSY_OFFSETCORR_Pos))
#define SDADC_SYNCBUSY_GAINCORR_Pos           _U_(8)                                               /**< (SDADC_SYNCBUSY) GAINCORR Synchronization Busy Position */
#define SDADC_SYNCBUSY_GAINCORR_Msk           (_U_(0x1) << SDADC_SYNCBUSY_GAINCORR_Pos)            /**< (SDADC_SYNCBUSY) GAINCORR Synchronization Busy Mask */
#define SDADC_SYNCBUSY_GAINCORR(value)        (SDADC_SYNCBUSY_GAINCORR_Msk & ((value) << SDADC_SYNCBUSY_GAINCORR_Pos))
#define SDADC_SYNCBUSY_SHIFTCORR_Pos          _U_(9)                                               /**< (SDADC_SYNCBUSY) SHIFTCORR Synchronization Busy Position */
#define SDADC_SYNCBUSY_SHIFTCORR_Msk          (_U_(0x1) << SDADC_SYNCBUSY_SHIFTCORR_Pos)           /**< (SDADC_SYNCBUSY) SHIFTCORR Synchronization Busy Mask */
#define SDADC_SYNCBUSY_SHIFTCORR(value)       (SDADC_SYNCBUSY_SHIFTCORR_Msk & ((value) << SDADC_SYNCBUSY_SHIFTCORR_Pos))
#define SDADC_SYNCBUSY_SWTRIG_Pos             _U_(10)                                              /**< (SDADC_SYNCBUSY) SWTRG Synchronization Busy Position */
#define SDADC_SYNCBUSY_SWTRIG_Msk             (_U_(0x1) << SDADC_SYNCBUSY_SWTRIG_Pos)              /**< (SDADC_SYNCBUSY) SWTRG Synchronization Busy Mask */
#define SDADC_SYNCBUSY_SWTRIG(value)          (SDADC_SYNCBUSY_SWTRIG_Msk & ((value) << SDADC_SYNCBUSY_SWTRIG_Pos))
#define SDADC_SYNCBUSY_ANACTRL_Pos            _U_(11)                                              /**< (SDADC_SYNCBUSY) ANACTRL Synchronization Busy Position */
#define SDADC_SYNCBUSY_ANACTRL_Msk            (_U_(0x1) << SDADC_SYNCBUSY_ANACTRL_Pos)             /**< (SDADC_SYNCBUSY) ANACTRL Synchronization Busy Mask */
#define SDADC_SYNCBUSY_ANACTRL(value)         (SDADC_SYNCBUSY_ANACTRL_Msk & ((value) << SDADC_SYNCBUSY_ANACTRL_Pos))
#define SDADC_SYNCBUSY_Msk                    _U_(0x00000FFF)                                      /**< (SDADC_SYNCBUSY) Register Mask  */


/* -------- SDADC_RESULT : (SDADC Offset: 0x24) ( R/ 32) Result -------- */
#define SDADC_RESULT_RESETVALUE               _U_(0x00)                                            /**<  (SDADC_RESULT) Result  Reset Value */

#define SDADC_RESULT_RESULT_Pos               _U_(0)                                               /**< (SDADC_RESULT) Result Value Position */
#define SDADC_RESULT_RESULT_Msk               (_U_(0xFFFFFF) << SDADC_RESULT_RESULT_Pos)           /**< (SDADC_RESULT) Result Value Mask */
#define SDADC_RESULT_RESULT(value)            (SDADC_RESULT_RESULT_Msk & ((value) << SDADC_RESULT_RESULT_Pos))
#define SDADC_RESULT_RESERVED_Pos             _U_(24)                                              /**< (SDADC_RESULT) Reserved Position */
#define SDADC_RESULT_RESERVED_Msk             (_U_(0xFF) << SDADC_RESULT_RESERVED_Pos)             /**< (SDADC_RESULT) Reserved Mask */
#define SDADC_RESULT_RESERVED(value)          (SDADC_RESULT_RESERVED_Msk & ((value) << SDADC_RESULT_RESERVED_Pos))
#define SDADC_RESULT_Msk                      _U_(0xFFFFFFFF)                                      /**< (SDADC_RESULT) Register Mask  */


/* -------- SDADC_SEQCTRL : (SDADC Offset: 0x28) (R/W 8) Sequence Control -------- */
#define SDADC_SEQCTRL_RESETVALUE              _U_(0x00)                                            /**<  (SDADC_SEQCTRL) Sequence Control  Reset Value */

#define SDADC_SEQCTRL_SEQEN_Pos               _U_(0)                                               /**< (SDADC_SEQCTRL) Enable Positive Input in the Sequence Position */
#define SDADC_SEQCTRL_SEQEN_Msk               (_U_(0x7) << SDADC_SEQCTRL_SEQEN_Pos)                /**< (SDADC_SEQCTRL) Enable Positive Input in the Sequence Mask */
#define SDADC_SEQCTRL_SEQEN(value)            (SDADC_SEQCTRL_SEQEN_Msk & ((value) << SDADC_SEQCTRL_SEQEN_Pos))
#define SDADC_SEQCTRL_Msk                     _U_(0x07)                                            /**< (SDADC_SEQCTRL) Register Mask  */


/* -------- SDADC_ANACTRL : (SDADC Offset: 0x2C) (R/W 8) Analog Control -------- */
#define SDADC_ANACTRL_RESETVALUE              _U_(0x00)                                            /**<  (SDADC_ANACTRL) Analog Control  Reset Value */

#define SDADC_ANACTRL_CTRSDADC_Pos            _U_(0)                                               /**< (SDADC_ANACTRL) SDADC Control Position */
#define SDADC_ANACTRL_CTRSDADC_Msk            (_U_(0x3F) << SDADC_ANACTRL_CTRSDADC_Pos)            /**< (SDADC_ANACTRL) SDADC Control Mask */
#define SDADC_ANACTRL_CTRSDADC(value)         (SDADC_ANACTRL_CTRSDADC_Msk & ((value) << SDADC_ANACTRL_CTRSDADC_Pos))
#define SDADC_ANACTRL_ONCHOP_Pos              _U_(6)                                               /**< (SDADC_ANACTRL) Chopper Position */
#define SDADC_ANACTRL_ONCHOP_Msk              (_U_(0x1) << SDADC_ANACTRL_ONCHOP_Pos)               /**< (SDADC_ANACTRL) Chopper Mask */
#define SDADC_ANACTRL_ONCHOP(value)           (SDADC_ANACTRL_ONCHOP_Msk & ((value) << SDADC_ANACTRL_ONCHOP_Pos))
#define SDADC_ANACTRL_BUFTEST_Pos             _U_(7)                                               /**< (SDADC_ANACTRL) BUFTEST Position */
#define SDADC_ANACTRL_BUFTEST_Msk             (_U_(0x1) << SDADC_ANACTRL_BUFTEST_Pos)              /**< (SDADC_ANACTRL) BUFTEST Mask */
#define SDADC_ANACTRL_BUFTEST(value)          (SDADC_ANACTRL_BUFTEST_Msk & ((value) << SDADC_ANACTRL_BUFTEST_Pos))
#define SDADC_ANACTRL_Msk                     _U_(0xFF)                                            /**< (SDADC_ANACTRL) Register Mask  */


/* -------- SDADC_DBGCTRL : (SDADC Offset: 0x2E) (R/W 8) Debug Control -------- */
#define SDADC_DBGCTRL_RESETVALUE              _U_(0x00)                                            /**<  (SDADC_DBGCTRL) Debug Control  Reset Value */

#define SDADC_DBGCTRL_DBGRUN_Pos              _U_(0)                                               /**< (SDADC_DBGCTRL) Debug Run Position */
#define SDADC_DBGCTRL_DBGRUN_Msk              (_U_(0x1) << SDADC_DBGCTRL_DBGRUN_Pos)               /**< (SDADC_DBGCTRL) Debug Run Mask */
#define SDADC_DBGCTRL_DBGRUN(value)           (SDADC_DBGCTRL_DBGRUN_Msk & ((value) << SDADC_DBGCTRL_DBGRUN_Pos))
#define SDADC_DBGCTRL_Msk                     _U_(0x01)                                            /**< (SDADC_DBGCTRL) Register Mask  */


/** \brief SDADC register offsets definitions */
#define SDADC_CTRLA_REG_OFST           (0x00)              /**< (SDADC_CTRLA) Control A Offset */
#define SDADC_REFCTRL_REG_OFST         (0x01)              /**< (SDADC_REFCTRL) Reference Control Offset */
#define SDADC_CTRLB_REG_OFST           (0x02)              /**< (SDADC_CTRLB) Control B Offset */
#define SDADC_EVCTRL_REG_OFST          (0x04)              /**< (SDADC_EVCTRL) Event Control Offset */
#define SDADC_INTENCLR_REG_OFST        (0x05)              /**< (SDADC_INTENCLR) Interrupt Enable Clear Offset */
#define SDADC_INTENSET_REG_OFST        (0x06)              /**< (SDADC_INTENSET) Interrupt Enable Set Offset */
#define SDADC_INTFLAG_REG_OFST         (0x07)              /**< (SDADC_INTFLAG) Interrupt Flag Status and Clear Offset */
#define SDADC_SEQSTATUS_REG_OFST       (0x08)              /**< (SDADC_SEQSTATUS) Sequence Status Offset */
#define SDADC_INPUTCTRL_REG_OFST       (0x09)              /**< (SDADC_INPUTCTRL) Input Control Offset */
#define SDADC_CTRLC_REG_OFST           (0x0A)              /**< (SDADC_CTRLC) Control C Offset */
#define SDADC_WINCTRL_REG_OFST         (0x0B)              /**< (SDADC_WINCTRL) Window Monitor Control Offset */
#define SDADC_WINLT_REG_OFST           (0x0C)              /**< (SDADC_WINLT) Window Monitor Lower Threshold Offset */
#define SDADC_WINUT_REG_OFST           (0x10)              /**< (SDADC_WINUT) Window Monitor Upper Threshold Offset */
#define SDADC_OFFSETCORR_REG_OFST      (0x14)              /**< (SDADC_OFFSETCORR) Offset Correction Offset */
#define SDADC_GAINCORR_REG_OFST        (0x18)              /**< (SDADC_GAINCORR) Gain Correction Offset */
#define SDADC_SHIFTCORR_REG_OFST       (0x1A)              /**< (SDADC_SHIFTCORR) Shift Correction Offset */
#define SDADC_SWTRIG_REG_OFST          (0x1C)              /**< (SDADC_SWTRIG) Software Trigger Offset */
#define SDADC_SYNCBUSY_REG_OFST        (0x20)              /**< (SDADC_SYNCBUSY) Synchronization Busy Offset */
#define SDADC_RESULT_REG_OFST          (0x24)              /**< (SDADC_RESULT) Result Offset */
#define SDADC_SEQCTRL_REG_OFST         (0x28)              /**< (SDADC_SEQCTRL) Sequence Control Offset */
#define SDADC_ANACTRL_REG_OFST         (0x2C)              /**< (SDADC_ANACTRL) Analog Control Offset */
#define SDADC_DBGCTRL_REG_OFST         (0x2E)              /**< (SDADC_DBGCTRL) Debug Control Offset */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief SDADC register API structure */
typedef struct
{  /* Sigma-Delta Analog Digital Converter */
  __IO  uint8_t                        SDADC_CTRLA;        /**< Offset: 0x00 (R/W  8) Control A */
  __IO  uint8_t                        SDADC_REFCTRL;      /**< Offset: 0x01 (R/W  8) Reference Control */
  __IO  uint16_t                       SDADC_CTRLB;        /**< Offset: 0x02 (R/W  16) Control B */
  __IO  uint8_t                        SDADC_EVCTRL;       /**< Offset: 0x04 (R/W  8) Event Control */
  __IO  uint8_t                        SDADC_INTENCLR;     /**< Offset: 0x05 (R/W  8) Interrupt Enable Clear */
  __IO  uint8_t                        SDADC_INTENSET;     /**< Offset: 0x06 (R/W  8) Interrupt Enable Set */
  __IO  uint8_t                        SDADC_INTFLAG;      /**< Offset: 0x07 (R/W  8) Interrupt Flag Status and Clear */
  __I   uint8_t                        SDADC_SEQSTATUS;    /**< Offset: 0x08 (R/   8) Sequence Status */
  __IO  uint8_t                        SDADC_INPUTCTRL;    /**< Offset: 0x09 (R/W  8) Input Control */
  __IO  uint8_t                        SDADC_CTRLC;        /**< Offset: 0x0A (R/W  8) Control C */
  __IO  uint8_t                        SDADC_WINCTRL;      /**< Offset: 0x0B (R/W  8) Window Monitor Control */
  __IO  uint32_t                       SDADC_WINLT;        /**< Offset: 0x0C (R/W  32) Window Monitor Lower Threshold */
  __IO  uint32_t                       SDADC_WINUT;        /**< Offset: 0x10 (R/W  32) Window Monitor Upper Threshold */
  __IO  uint32_t                       SDADC_OFFSETCORR;   /**< Offset: 0x14 (R/W  32) Offset Correction */
  __IO  uint16_t                       SDADC_GAINCORR;     /**< Offset: 0x18 (R/W  16) Gain Correction */
  __IO  uint8_t                        SDADC_SHIFTCORR;    /**< Offset: 0x1A (R/W  8) Shift Correction */
  __I   uint8_t                        Reserved1[0x01];
  __IO  uint8_t                        SDADC_SWTRIG;       /**< Offset: 0x1C (R/W  8) Software Trigger */
  __I   uint8_t                        Reserved2[0x03];
  __I   uint32_t                       SDADC_SYNCBUSY;     /**< Offset: 0x20 (R/   32) Synchronization Busy */
  __I   uint32_t                       SDADC_RESULT;       /**< Offset: 0x24 (R/   32) Result */
  __IO  uint8_t                        SDADC_SEQCTRL;      /**< Offset: 0x28 (R/W  8) Sequence Control */
  __I   uint8_t                        Reserved3[0x03];
  __IO  uint8_t                        SDADC_ANACTRL;      /**< Offset: 0x2C (R/W  8) Analog Control */
  __I   uint8_t                        Reserved4[0x01];
  __IO  uint8_t                        SDADC_DBGCTRL;      /**< Offset: 0x2E (R/W  8) Debug Control */
} sdadc_registers_t;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* _SAMC21_SDADC_COMPONENT_H_ */
