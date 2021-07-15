/**
 * \brief Component description for SUPC
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
#ifndef _SAMC21_SUPC_COMPONENT_H_
#define _SAMC21_SUPC_COMPONENT_H_

/* ************************************************************************** */
/*   SOFTWARE API DEFINITION FOR SUPC                                         */
/* ************************************************************************** */

/* -------- SUPC_INTENCLR : (SUPC Offset: 0x00) (R/W 32) Interrupt Enable Clear -------- */
#define SUPC_INTENCLR_RESETVALUE              _U_(0x00)                                            /**<  (SUPC_INTENCLR) Interrupt Enable Clear  Reset Value */

#define SUPC_INTENCLR_BODVDDRDY_Pos           _U_(0)                                               /**< (SUPC_INTENCLR) BODVDD Ready Position */
#define SUPC_INTENCLR_BODVDDRDY_Msk           (_U_(0x1) << SUPC_INTENCLR_BODVDDRDY_Pos)            /**< (SUPC_INTENCLR) BODVDD Ready Mask */
#define SUPC_INTENCLR_BODVDDRDY(value)        (SUPC_INTENCLR_BODVDDRDY_Msk & ((value) << SUPC_INTENCLR_BODVDDRDY_Pos))
#define SUPC_INTENCLR_BODVDDDET_Pos           _U_(1)                                               /**< (SUPC_INTENCLR) BODVDD Detection Position */
#define SUPC_INTENCLR_BODVDDDET_Msk           (_U_(0x1) << SUPC_INTENCLR_BODVDDDET_Pos)            /**< (SUPC_INTENCLR) BODVDD Detection Mask */
#define SUPC_INTENCLR_BODVDDDET(value)        (SUPC_INTENCLR_BODVDDDET_Msk & ((value) << SUPC_INTENCLR_BODVDDDET_Pos))
#define SUPC_INTENCLR_BVDDSRDY_Pos            _U_(2)                                               /**< (SUPC_INTENCLR) BODVDD Synchronization Ready Position */
#define SUPC_INTENCLR_BVDDSRDY_Msk            (_U_(0x1) << SUPC_INTENCLR_BVDDSRDY_Pos)             /**< (SUPC_INTENCLR) BODVDD Synchronization Ready Mask */
#define SUPC_INTENCLR_BVDDSRDY(value)         (SUPC_INTENCLR_BVDDSRDY_Msk & ((value) << SUPC_INTENCLR_BVDDSRDY_Pos))
#define SUPC_INTENCLR_VREG33RDY_Pos           _U_(6)                                               /**< (SUPC_INTENCLR) VREG33 Ready Position */
#define SUPC_INTENCLR_VREG33RDY_Msk           (_U_(0x1) << SUPC_INTENCLR_VREG33RDY_Pos)            /**< (SUPC_INTENCLR) VREG33 Ready Mask */
#define SUPC_INTENCLR_VREG33RDY(value)        (SUPC_INTENCLR_VREG33RDY_Msk & ((value) << SUPC_INTENCLR_VREG33RDY_Pos))
#define SUPC_INTENCLR_Msk                     _U_(0x00000047)                                      /**< (SUPC_INTENCLR) Register Mask  */


/* -------- SUPC_INTENSET : (SUPC Offset: 0x04) (R/W 32) Interrupt Enable Set -------- */
#define SUPC_INTENSET_RESETVALUE              _U_(0x00)                                            /**<  (SUPC_INTENSET) Interrupt Enable Set  Reset Value */

#define SUPC_INTENSET_BODVDDRDY_Pos           _U_(0)                                               /**< (SUPC_INTENSET) BODVDD Ready Position */
#define SUPC_INTENSET_BODVDDRDY_Msk           (_U_(0x1) << SUPC_INTENSET_BODVDDRDY_Pos)            /**< (SUPC_INTENSET) BODVDD Ready Mask */
#define SUPC_INTENSET_BODVDDRDY(value)        (SUPC_INTENSET_BODVDDRDY_Msk & ((value) << SUPC_INTENSET_BODVDDRDY_Pos))
#define SUPC_INTENSET_BODVDDDET_Pos           _U_(1)                                               /**< (SUPC_INTENSET) BODVDD Detection Position */
#define SUPC_INTENSET_BODVDDDET_Msk           (_U_(0x1) << SUPC_INTENSET_BODVDDDET_Pos)            /**< (SUPC_INTENSET) BODVDD Detection Mask */
#define SUPC_INTENSET_BODVDDDET(value)        (SUPC_INTENSET_BODVDDDET_Msk & ((value) << SUPC_INTENSET_BODVDDDET_Pos))
#define SUPC_INTENSET_BVDDSRDY_Pos            _U_(2)                                               /**< (SUPC_INTENSET) BODVDD Synchronization Ready Position */
#define SUPC_INTENSET_BVDDSRDY_Msk            (_U_(0x1) << SUPC_INTENSET_BVDDSRDY_Pos)             /**< (SUPC_INTENSET) BODVDD Synchronization Ready Mask */
#define SUPC_INTENSET_BVDDSRDY(value)         (SUPC_INTENSET_BVDDSRDY_Msk & ((value) << SUPC_INTENSET_BVDDSRDY_Pos))
#define SUPC_INTENSET_VREG33RDY_Pos           _U_(6)                                               /**< (SUPC_INTENSET) VREG33 Ready Position */
#define SUPC_INTENSET_VREG33RDY_Msk           (_U_(0x1) << SUPC_INTENSET_VREG33RDY_Pos)            /**< (SUPC_INTENSET) VREG33 Ready Mask */
#define SUPC_INTENSET_VREG33RDY(value)        (SUPC_INTENSET_VREG33RDY_Msk & ((value) << SUPC_INTENSET_VREG33RDY_Pos))
#define SUPC_INTENSET_Msk                     _U_(0x00000047)                                      /**< (SUPC_INTENSET) Register Mask  */


/* -------- SUPC_INTFLAG : (SUPC Offset: 0x08) (R/W 32) Interrupt Flag Status and Clear -------- */
#define SUPC_INTFLAG_RESETVALUE               _U_(0x00)                                            /**<  (SUPC_INTFLAG) Interrupt Flag Status and Clear  Reset Value */

#define SUPC_INTFLAG_BODVDDRDY_Pos            _U_(0)                                               /**< (SUPC_INTFLAG) BODVDD Ready Position */
#define SUPC_INTFLAG_BODVDDRDY_Msk            (_U_(0x1) << SUPC_INTFLAG_BODVDDRDY_Pos)             /**< (SUPC_INTFLAG) BODVDD Ready Mask */
#define SUPC_INTFLAG_BODVDDRDY(value)         (SUPC_INTFLAG_BODVDDRDY_Msk & ((value) << SUPC_INTFLAG_BODVDDRDY_Pos))
#define SUPC_INTFLAG_BODVDDDET_Pos            _U_(1)                                               /**< (SUPC_INTFLAG) BODVDD Detection Position */
#define SUPC_INTFLAG_BODVDDDET_Msk            (_U_(0x1) << SUPC_INTFLAG_BODVDDDET_Pos)             /**< (SUPC_INTFLAG) BODVDD Detection Mask */
#define SUPC_INTFLAG_BODVDDDET(value)         (SUPC_INTFLAG_BODVDDDET_Msk & ((value) << SUPC_INTFLAG_BODVDDDET_Pos))
#define SUPC_INTFLAG_BVDDSRDY_Pos             _U_(2)                                               /**< (SUPC_INTFLAG) BODVDD Synchronization Ready Position */
#define SUPC_INTFLAG_BVDDSRDY_Msk             (_U_(0x1) << SUPC_INTFLAG_BVDDSRDY_Pos)              /**< (SUPC_INTFLAG) BODVDD Synchronization Ready Mask */
#define SUPC_INTFLAG_BVDDSRDY(value)          (SUPC_INTFLAG_BVDDSRDY_Msk & ((value) << SUPC_INTFLAG_BVDDSRDY_Pos))
#define SUPC_INTFLAG_VREG33RDY_Pos            _U_(6)                                               /**< (SUPC_INTFLAG) VREG33 Ready Position */
#define SUPC_INTFLAG_VREG33RDY_Msk            (_U_(0x1) << SUPC_INTFLAG_VREG33RDY_Pos)             /**< (SUPC_INTFLAG) VREG33 Ready Mask */
#define SUPC_INTFLAG_VREG33RDY(value)         (SUPC_INTFLAG_VREG33RDY_Msk & ((value) << SUPC_INTFLAG_VREG33RDY_Pos))
#define SUPC_INTFLAG_Msk                      _U_(0x00000047)                                      /**< (SUPC_INTFLAG) Register Mask  */


/* -------- SUPC_STATUS : (SUPC Offset: 0x0C) ( R/ 32) Power and Clocks Status -------- */
#define SUPC_STATUS_RESETVALUE                _U_(0x00)                                            /**<  (SUPC_STATUS) Power and Clocks Status  Reset Value */

#define SUPC_STATUS_BODVDDRDY_Pos             _U_(0)                                               /**< (SUPC_STATUS) BODVDD Ready Position */
#define SUPC_STATUS_BODVDDRDY_Msk             (_U_(0x1) << SUPC_STATUS_BODVDDRDY_Pos)              /**< (SUPC_STATUS) BODVDD Ready Mask */
#define SUPC_STATUS_BODVDDRDY(value)          (SUPC_STATUS_BODVDDRDY_Msk & ((value) << SUPC_STATUS_BODVDDRDY_Pos))
#define SUPC_STATUS_BODVDDDET_Pos             _U_(1)                                               /**< (SUPC_STATUS) BODVDD Detection Position */
#define SUPC_STATUS_BODVDDDET_Msk             (_U_(0x1) << SUPC_STATUS_BODVDDDET_Pos)              /**< (SUPC_STATUS) BODVDD Detection Mask */
#define SUPC_STATUS_BODVDDDET(value)          (SUPC_STATUS_BODVDDDET_Msk & ((value) << SUPC_STATUS_BODVDDDET_Pos))
#define SUPC_STATUS_BVDDSRDY_Pos              _U_(2)                                               /**< (SUPC_STATUS) BODVDD Synchronization Ready Position */
#define SUPC_STATUS_BVDDSRDY_Msk              (_U_(0x1) << SUPC_STATUS_BVDDSRDY_Pos)               /**< (SUPC_STATUS) BODVDD Synchronization Ready Mask */
#define SUPC_STATUS_BVDDSRDY(value)           (SUPC_STATUS_BVDDSRDY_Msk & ((value) << SUPC_STATUS_BVDDSRDY_Pos))
#define SUPC_STATUS_VREG33RDY_Pos             _U_(6)                                               /**< (SUPC_STATUS) VREG33 Ready Position */
#define SUPC_STATUS_VREG33RDY_Msk             (_U_(0x1) << SUPC_STATUS_VREG33RDY_Pos)              /**< (SUPC_STATUS) VREG33 Ready Mask */
#define SUPC_STATUS_VREG33RDY(value)          (SUPC_STATUS_VREG33RDY_Msk & ((value) << SUPC_STATUS_VREG33RDY_Pos))
#define SUPC_STATUS_Msk                       _U_(0x00000047)                                      /**< (SUPC_STATUS) Register Mask  */


/* -------- SUPC_BODVDD : (SUPC Offset: 0x10) (R/W 32) BODVDD Control -------- */
#define SUPC_BODVDD_RESETVALUE                _U_(0x00)                                            /**<  (SUPC_BODVDD) BODVDD Control  Reset Value */

#define SUPC_BODVDD_ENABLE_Pos                _U_(1)                                               /**< (SUPC_BODVDD) Enable Position */
#define SUPC_BODVDD_ENABLE_Msk                (_U_(0x1) << SUPC_BODVDD_ENABLE_Pos)                 /**< (SUPC_BODVDD) Enable Mask */
#define SUPC_BODVDD_ENABLE(value)             (SUPC_BODVDD_ENABLE_Msk & ((value) << SUPC_BODVDD_ENABLE_Pos))
#define SUPC_BODVDD_HYST_Pos                  _U_(2)                                               /**< (SUPC_BODVDD) Hysteresis Enable Position */
#define SUPC_BODVDD_HYST_Msk                  (_U_(0x1) << SUPC_BODVDD_HYST_Pos)                   /**< (SUPC_BODVDD) Hysteresis Enable Mask */
#define SUPC_BODVDD_HYST(value)               (SUPC_BODVDD_HYST_Msk & ((value) << SUPC_BODVDD_HYST_Pos))
#define SUPC_BODVDD_ACTION_Pos                _U_(3)                                               /**< (SUPC_BODVDD) Action when Threshold Crossed Position */
#define SUPC_BODVDD_ACTION_Msk                (_U_(0x3) << SUPC_BODVDD_ACTION_Pos)                 /**< (SUPC_BODVDD) Action when Threshold Crossed Mask */
#define SUPC_BODVDD_ACTION(value)             (SUPC_BODVDD_ACTION_Msk & ((value) << SUPC_BODVDD_ACTION_Pos))
#define   SUPC_BODVDD_ACTION_NONE_Val         _U_(0x0)                                             /**< (SUPC_BODVDD) No action  */
#define   SUPC_BODVDD_ACTION_RESET_Val        _U_(0x1)                                             /**< (SUPC_BODVDD) The BODVDD generates a reset  */
#define   SUPC_BODVDD_ACTION_INT_Val          _U_(0x2)                                             /**< (SUPC_BODVDD) The BODVDD generates an interrupt  */
#define SUPC_BODVDD_ACTION_NONE               (SUPC_BODVDD_ACTION_NONE_Val << SUPC_BODVDD_ACTION_Pos) /**< (SUPC_BODVDD) No action Position  */
#define SUPC_BODVDD_ACTION_RESET              (SUPC_BODVDD_ACTION_RESET_Val << SUPC_BODVDD_ACTION_Pos) /**< (SUPC_BODVDD) The BODVDD generates a reset Position  */
#define SUPC_BODVDD_ACTION_INT                (SUPC_BODVDD_ACTION_INT_Val << SUPC_BODVDD_ACTION_Pos) /**< (SUPC_BODVDD) The BODVDD generates an interrupt Position  */
#define SUPC_BODVDD_STDBYCFG_Pos              _U_(5)                                               /**< (SUPC_BODVDD) Configuration in Standby mode Position */
#define SUPC_BODVDD_STDBYCFG_Msk              (_U_(0x1) << SUPC_BODVDD_STDBYCFG_Pos)               /**< (SUPC_BODVDD) Configuration in Standby mode Mask */
#define SUPC_BODVDD_STDBYCFG(value)           (SUPC_BODVDD_STDBYCFG_Msk & ((value) << SUPC_BODVDD_STDBYCFG_Pos))
#define SUPC_BODVDD_RUNSTDBY_Pos              _U_(6)                                               /**< (SUPC_BODVDD) Run during Standby Position */
#define SUPC_BODVDD_RUNSTDBY_Msk              (_U_(0x1) << SUPC_BODVDD_RUNSTDBY_Pos)               /**< (SUPC_BODVDD) Run during Standby Mask */
#define SUPC_BODVDD_RUNSTDBY(value)           (SUPC_BODVDD_RUNSTDBY_Msk & ((value) << SUPC_BODVDD_RUNSTDBY_Pos))
#define SUPC_BODVDD_ACTCFG_Pos                _U_(8)                                               /**< (SUPC_BODVDD) Configuration in Active mode Position */
#define SUPC_BODVDD_ACTCFG_Msk                (_U_(0x1) << SUPC_BODVDD_ACTCFG_Pos)                 /**< (SUPC_BODVDD) Configuration in Active mode Mask */
#define SUPC_BODVDD_ACTCFG(value)             (SUPC_BODVDD_ACTCFG_Msk & ((value) << SUPC_BODVDD_ACTCFG_Pos))
#define SUPC_BODVDD_PSEL_Pos                  _U_(12)                                              /**< (SUPC_BODVDD) Prescaler Select Position */
#define SUPC_BODVDD_PSEL_Msk                  (_U_(0xF) << SUPC_BODVDD_PSEL_Pos)                   /**< (SUPC_BODVDD) Prescaler Select Mask */
#define SUPC_BODVDD_PSEL(value)               (SUPC_BODVDD_PSEL_Msk & ((value) << SUPC_BODVDD_PSEL_Pos))
#define   SUPC_BODVDD_PSEL_DIV2_Val           _U_(0x0)                                             /**< (SUPC_BODVDD) Divide clock by 2  */
#define   SUPC_BODVDD_PSEL_DIV4_Val           _U_(0x1)                                             /**< (SUPC_BODVDD) Divide clock by 4  */
#define   SUPC_BODVDD_PSEL_DIV8_Val           _U_(0x2)                                             /**< (SUPC_BODVDD) Divide clock by 8  */
#define   SUPC_BODVDD_PSEL_DIV16_Val          _U_(0x3)                                             /**< (SUPC_BODVDD) Divide clock by 16  */
#define   SUPC_BODVDD_PSEL_DIV32_Val          _U_(0x4)                                             /**< (SUPC_BODVDD) Divide clock by 32  */
#define   SUPC_BODVDD_PSEL_DIV64_Val          _U_(0x5)                                             /**< (SUPC_BODVDD) Divide clock by 64  */
#define   SUPC_BODVDD_PSEL_DIV128_Val         _U_(0x6)                                             /**< (SUPC_BODVDD) Divide clock by 128  */
#define   SUPC_BODVDD_PSEL_DIV256_Val         _U_(0x7)                                             /**< (SUPC_BODVDD) Divide clock by 256  */
#define   SUPC_BODVDD_PSEL_DIV512_Val         _U_(0x8)                                             /**< (SUPC_BODVDD) Divide clock by 512  */
#define   SUPC_BODVDD_PSEL_DIV1024_Val        _U_(0x9)                                             /**< (SUPC_BODVDD) Divide clock by 1024  */
#define   SUPC_BODVDD_PSEL_DIV2048_Val        _U_(0xA)                                             /**< (SUPC_BODVDD) Divide clock by 2048  */
#define   SUPC_BODVDD_PSEL_DIV4096_Val        _U_(0xB)                                             /**< (SUPC_BODVDD) Divide clock by 4096  */
#define   SUPC_BODVDD_PSEL_DIV8192_Val        _U_(0xC)                                             /**< (SUPC_BODVDD) Divide clock by 8192  */
#define   SUPC_BODVDD_PSEL_DIV16384_Val       _U_(0xD)                                             /**< (SUPC_BODVDD) Divide clock by 16384  */
#define   SUPC_BODVDD_PSEL_DIV32768_Val       _U_(0xE)                                             /**< (SUPC_BODVDD) Divide clock by 32768  */
#define   SUPC_BODVDD_PSEL_DIV65536_Val       _U_(0xF)                                             /**< (SUPC_BODVDD) Divide clock by 65536  */
#define SUPC_BODVDD_PSEL_DIV2                 (SUPC_BODVDD_PSEL_DIV2_Val << SUPC_BODVDD_PSEL_Pos)  /**< (SUPC_BODVDD) Divide clock by 2 Position  */
#define SUPC_BODVDD_PSEL_DIV4                 (SUPC_BODVDD_PSEL_DIV4_Val << SUPC_BODVDD_PSEL_Pos)  /**< (SUPC_BODVDD) Divide clock by 4 Position  */
#define SUPC_BODVDD_PSEL_DIV8                 (SUPC_BODVDD_PSEL_DIV8_Val << SUPC_BODVDD_PSEL_Pos)  /**< (SUPC_BODVDD) Divide clock by 8 Position  */
#define SUPC_BODVDD_PSEL_DIV16                (SUPC_BODVDD_PSEL_DIV16_Val << SUPC_BODVDD_PSEL_Pos) /**< (SUPC_BODVDD) Divide clock by 16 Position  */
#define SUPC_BODVDD_PSEL_DIV32                (SUPC_BODVDD_PSEL_DIV32_Val << SUPC_BODVDD_PSEL_Pos) /**< (SUPC_BODVDD) Divide clock by 32 Position  */
#define SUPC_BODVDD_PSEL_DIV64                (SUPC_BODVDD_PSEL_DIV64_Val << SUPC_BODVDD_PSEL_Pos) /**< (SUPC_BODVDD) Divide clock by 64 Position  */
#define SUPC_BODVDD_PSEL_DIV128               (SUPC_BODVDD_PSEL_DIV128_Val << SUPC_BODVDD_PSEL_Pos) /**< (SUPC_BODVDD) Divide clock by 128 Position  */
#define SUPC_BODVDD_PSEL_DIV256               (SUPC_BODVDD_PSEL_DIV256_Val << SUPC_BODVDD_PSEL_Pos) /**< (SUPC_BODVDD) Divide clock by 256 Position  */
#define SUPC_BODVDD_PSEL_DIV512               (SUPC_BODVDD_PSEL_DIV512_Val << SUPC_BODVDD_PSEL_Pos) /**< (SUPC_BODVDD) Divide clock by 512 Position  */
#define SUPC_BODVDD_PSEL_DIV1024              (SUPC_BODVDD_PSEL_DIV1024_Val << SUPC_BODVDD_PSEL_Pos) /**< (SUPC_BODVDD) Divide clock by 1024 Position  */
#define SUPC_BODVDD_PSEL_DIV2048              (SUPC_BODVDD_PSEL_DIV2048_Val << SUPC_BODVDD_PSEL_Pos) /**< (SUPC_BODVDD) Divide clock by 2048 Position  */
#define SUPC_BODVDD_PSEL_DIV4096              (SUPC_BODVDD_PSEL_DIV4096_Val << SUPC_BODVDD_PSEL_Pos) /**< (SUPC_BODVDD) Divide clock by 4096 Position  */
#define SUPC_BODVDD_PSEL_DIV8192              (SUPC_BODVDD_PSEL_DIV8192_Val << SUPC_BODVDD_PSEL_Pos) /**< (SUPC_BODVDD) Divide clock by 8192 Position  */
#define SUPC_BODVDD_PSEL_DIV16384             (SUPC_BODVDD_PSEL_DIV16384_Val << SUPC_BODVDD_PSEL_Pos) /**< (SUPC_BODVDD) Divide clock by 16384 Position  */
#define SUPC_BODVDD_PSEL_DIV32768             (SUPC_BODVDD_PSEL_DIV32768_Val << SUPC_BODVDD_PSEL_Pos) /**< (SUPC_BODVDD) Divide clock by 32768 Position  */
#define SUPC_BODVDD_PSEL_DIV65536             (SUPC_BODVDD_PSEL_DIV65536_Val << SUPC_BODVDD_PSEL_Pos) /**< (SUPC_BODVDD) Divide clock by 65536 Position  */
#define SUPC_BODVDD_LEVEL_Pos                 _U_(16)                                              /**< (SUPC_BODVDD) Threshold Level for VDD Position */
#define SUPC_BODVDD_LEVEL_Msk                 (_U_(0x3F) << SUPC_BODVDD_LEVEL_Pos)                 /**< (SUPC_BODVDD) Threshold Level for VDD Mask */
#define SUPC_BODVDD_LEVEL(value)              (SUPC_BODVDD_LEVEL_Msk & ((value) << SUPC_BODVDD_LEVEL_Pos))
#define SUPC_BODVDD_Msk                       _U_(0x003FF17E)                                      /**< (SUPC_BODVDD) Register Mask  */


/* -------- SUPC_VREG : (SUPC Offset: 0x18) (R/W 32) VREG Control -------- */
#define SUPC_VREG_RESETVALUE                  _U_(0x00)                                            /**<  (SUPC_VREG) VREG Control  Reset Value */

#define SUPC_VREG_ENABLE_Pos                  _U_(1)                                               /**< (SUPC_VREG) Enable Position */
#define SUPC_VREG_ENABLE_Msk                  (_U_(0x1) << SUPC_VREG_ENABLE_Pos)                   /**< (SUPC_VREG) Enable Mask */
#define SUPC_VREG_ENABLE(value)               (SUPC_VREG_ENABLE_Msk & ((value) << SUPC_VREG_ENABLE_Pos))
#define SUPC_VREG_RUNSTDBY_Pos                _U_(6)                                               /**< (SUPC_VREG) Run during Standby Position */
#define SUPC_VREG_RUNSTDBY_Msk                (_U_(0x1) << SUPC_VREG_RUNSTDBY_Pos)                 /**< (SUPC_VREG) Run during Standby Mask */
#define SUPC_VREG_RUNSTDBY(value)             (SUPC_VREG_RUNSTDBY_Msk & ((value) << SUPC_VREG_RUNSTDBY_Pos))
#define SUPC_VREG_Msk                         _U_(0x00000042)                                      /**< (SUPC_VREG) Register Mask  */


/* -------- SUPC_VREF : (SUPC Offset: 0x1C) (R/W 32) VREF Control -------- */
#define SUPC_VREF_RESETVALUE                  _U_(0x00)                                            /**<  (SUPC_VREF) VREF Control  Reset Value */

#define SUPC_VREF_TSEN_Pos                    _U_(1)                                               /**< (SUPC_VREF) Temperature Sensor Output Enable Position */
#define SUPC_VREF_TSEN_Msk                    (_U_(0x1) << SUPC_VREF_TSEN_Pos)                     /**< (SUPC_VREF) Temperature Sensor Output Enable Mask */
#define SUPC_VREF_TSEN(value)                 (SUPC_VREF_TSEN_Msk & ((value) << SUPC_VREF_TSEN_Pos))
#define SUPC_VREF_VREFOE_Pos                  _U_(2)                                               /**< (SUPC_VREF) Voltage Reference Output Enable Position */
#define SUPC_VREF_VREFOE_Msk                  (_U_(0x1) << SUPC_VREF_VREFOE_Pos)                   /**< (SUPC_VREF) Voltage Reference Output Enable Mask */
#define SUPC_VREF_VREFOE(value)               (SUPC_VREF_VREFOE_Msk & ((value) << SUPC_VREF_VREFOE_Pos))
#define SUPC_VREF_RUNSTDBY_Pos                _U_(6)                                               /**< (SUPC_VREF) Run during Standby Position */
#define SUPC_VREF_RUNSTDBY_Msk                (_U_(0x1) << SUPC_VREF_RUNSTDBY_Pos)                 /**< (SUPC_VREF) Run during Standby Mask */
#define SUPC_VREF_RUNSTDBY(value)             (SUPC_VREF_RUNSTDBY_Msk & ((value) << SUPC_VREF_RUNSTDBY_Pos))
#define SUPC_VREF_ONDEMAND_Pos                _U_(7)                                               /**< (SUPC_VREF) On Demand Control Position */
#define SUPC_VREF_ONDEMAND_Msk                (_U_(0x1) << SUPC_VREF_ONDEMAND_Pos)                 /**< (SUPC_VREF) On Demand Control Mask */
#define SUPC_VREF_ONDEMAND(value)             (SUPC_VREF_ONDEMAND_Msk & ((value) << SUPC_VREF_ONDEMAND_Pos))
#define SUPC_VREF_SEL_Pos                     _U_(16)                                              /**< (SUPC_VREF) Voltage Reference Selection Position */
#define SUPC_VREF_SEL_Msk                     (_U_(0xF) << SUPC_VREF_SEL_Pos)                      /**< (SUPC_VREF) Voltage Reference Selection Mask */
#define SUPC_VREF_SEL(value)                  (SUPC_VREF_SEL_Msk & ((value) << SUPC_VREF_SEL_Pos))
#define   SUPC_VREF_SEL_1V024_Val             _U_(0x0)                                             /**< (SUPC_VREF) 1.024V voltage reference typical value  */
#define   SUPC_VREF_SEL_2V048_Val             _U_(0x2)                                             /**< (SUPC_VREF) 2.048V voltage reference typical value  */
#define   SUPC_VREF_SEL_4V096_Val             _U_(0x3)                                             /**< (SUPC_VREF) 4.096V voltage reference typical value  */
#define SUPC_VREF_SEL_1V024                   (SUPC_VREF_SEL_1V024_Val << SUPC_VREF_SEL_Pos)       /**< (SUPC_VREF) 1.024V voltage reference typical value Position  */
#define SUPC_VREF_SEL_2V048                   (SUPC_VREF_SEL_2V048_Val << SUPC_VREF_SEL_Pos)       /**< (SUPC_VREF) 2.048V voltage reference typical value Position  */
#define SUPC_VREF_SEL_4V096                   (SUPC_VREF_SEL_4V096_Val << SUPC_VREF_SEL_Pos)       /**< (SUPC_VREF) 4.096V voltage reference typical value Position  */
#define SUPC_VREF_Msk                         _U_(0x000F00C6)                                      /**< (SUPC_VREF) Register Mask  */


/* -------- SUPC_VREG33 : (SUPC Offset: 0x20) (R/W 32) VREG33 Control -------- */
#define SUPC_VREG33_RESETVALUE                _U_(0x10)                                            /**<  (SUPC_VREG33) VREG33 Control  Reset Value */

#define SUPC_VREG33_ENABLE_Pos                _U_(1)                                               /**< (SUPC_VREG33) VREG33 Enable Position */
#define SUPC_VREG33_ENABLE_Msk                (_U_(0x1) << SUPC_VREG33_ENABLE_Pos)                 /**< (SUPC_VREG33) VREG33 Enable Mask */
#define SUPC_VREG33_ENABLE(value)             (SUPC_VREG33_ENABLE_Msk & ((value) << SUPC_VREG33_ENABLE_Pos))
#define SUPC_VREG33_ENRDY_Pos                 _U_(2)                                               /**< (SUPC_VREG33) VREG33 Ready Enable Position */
#define SUPC_VREG33_ENRDY_Msk                 (_U_(0x1) << SUPC_VREG33_ENRDY_Pos)                  /**< (SUPC_VREG33) VREG33 Ready Enable Mask */
#define SUPC_VREG33_ENRDY(value)              (SUPC_VREG33_ENRDY_Msk & ((value) << SUPC_VREG33_ENRDY_Pos))
#define SUPC_VREG33_BYPASS_Pos                _U_(3)                                               /**< (SUPC_VREG33) VREG33 Bypass Position */
#define SUPC_VREG33_BYPASS_Msk                (_U_(0x1) << SUPC_VREG33_BYPASS_Pos)                 /**< (SUPC_VREG33) VREG33 Bypass Mask */
#define SUPC_VREG33_BYPASS(value)             (SUPC_VREG33_BYPASS_Msk & ((value) << SUPC_VREG33_BYPASS_Pos))
#define SUPC_VREG33_ISOEN_Pos                 _U_(4)                                               /**< (SUPC_VREG33) Isolation Enable Position */
#define SUPC_VREG33_ISOEN_Msk                 (_U_(0x1) << SUPC_VREG33_ISOEN_Pos)                  /**< (SUPC_VREG33) Isolation Enable Mask */
#define SUPC_VREG33_ISOEN(value)              (SUPC_VREG33_ISOEN_Msk & ((value) << SUPC_VREG33_ISOEN_Pos))
#define SUPC_VREG33_Msk                       _U_(0x0000001E)                                      /**< (SUPC_VREG33) Register Mask  */


/** \brief SUPC register offsets definitions */
#define SUPC_INTENCLR_REG_OFST         (0x00)              /**< (SUPC_INTENCLR) Interrupt Enable Clear Offset */
#define SUPC_INTENSET_REG_OFST         (0x04)              /**< (SUPC_INTENSET) Interrupt Enable Set Offset */
#define SUPC_INTFLAG_REG_OFST          (0x08)              /**< (SUPC_INTFLAG) Interrupt Flag Status and Clear Offset */
#define SUPC_STATUS_REG_OFST           (0x0C)              /**< (SUPC_STATUS) Power and Clocks Status Offset */
#define SUPC_BODVDD_REG_OFST           (0x10)              /**< (SUPC_BODVDD) BODVDD Control Offset */
#define SUPC_VREG_REG_OFST             (0x18)              /**< (SUPC_VREG) VREG Control Offset */
#define SUPC_VREF_REG_OFST             (0x1C)              /**< (SUPC_VREF) VREF Control Offset */
#define SUPC_VREG33_REG_OFST           (0x20)              /**< (SUPC_VREG33) VREG33 Control Offset */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief SUPC register API structure */
typedef struct
{  /* Supply Controller */
  __IO  uint32_t                       SUPC_INTENCLR;      /**< Offset: 0x00 (R/W  32) Interrupt Enable Clear */
  __IO  uint32_t                       SUPC_INTENSET;      /**< Offset: 0x04 (R/W  32) Interrupt Enable Set */
  __IO  uint32_t                       SUPC_INTFLAG;       /**< Offset: 0x08 (R/W  32) Interrupt Flag Status and Clear */
  __I   uint32_t                       SUPC_STATUS;        /**< Offset: 0x0C (R/   32) Power and Clocks Status */
  __IO  uint32_t                       SUPC_BODVDD;        /**< Offset: 0x10 (R/W  32) BODVDD Control */
  __I   uint8_t                        Reserved1[0x04];
  __IO  uint32_t                       SUPC_VREG;          /**< Offset: 0x18 (R/W  32) VREG Control */
  __IO  uint32_t                       SUPC_VREF;          /**< Offset: 0x1C (R/W  32) VREF Control */
  __IO  uint32_t                       SUPC_VREG33;        /**< Offset: 0x20 (R/W  32) VREG33 Control */
} supc_registers_t;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* _SAMC21_SUPC_COMPONENT_H_ */
