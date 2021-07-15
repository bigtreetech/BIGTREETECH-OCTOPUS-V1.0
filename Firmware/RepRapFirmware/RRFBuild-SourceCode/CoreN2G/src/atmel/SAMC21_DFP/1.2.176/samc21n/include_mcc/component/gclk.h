/**
 * \brief Component description for GCLK
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
#ifndef _SAMC21_GCLK_COMPONENT_H_
#define _SAMC21_GCLK_COMPONENT_H_

/* ************************************************************************** */
/*   SOFTWARE API DEFINITION FOR GCLK                                         */
/* ************************************************************************** */

/* -------- GCLK_CTRLA : (GCLK Offset: 0x00) (R/W 8) Control -------- */
#define GCLK_CTRLA_RESETVALUE                 _U_(0x00)                                            /**<  (GCLK_CTRLA) Control  Reset Value */

#define GCLK_CTRLA_SWRST_Pos                  _U_(0)                                               /**< (GCLK_CTRLA) Software Reset Position */
#define GCLK_CTRLA_SWRST_Msk                  (_U_(0x1) << GCLK_CTRLA_SWRST_Pos)                   /**< (GCLK_CTRLA) Software Reset Mask */
#define GCLK_CTRLA_SWRST(value)               (GCLK_CTRLA_SWRST_Msk & ((value) << GCLK_CTRLA_SWRST_Pos))
#define GCLK_CTRLA_Msk                        _U_(0x01)                                            /**< (GCLK_CTRLA) Register Mask  */


/* -------- GCLK_SYNCBUSY : (GCLK Offset: 0x04) ( R/ 32) Synchronization Busy -------- */
#define GCLK_SYNCBUSY_RESETVALUE              _U_(0x00)                                            /**<  (GCLK_SYNCBUSY) Synchronization Busy  Reset Value */

#define GCLK_SYNCBUSY_SWRST_Pos               _U_(0)                                               /**< (GCLK_SYNCBUSY) Software Reset Synchroniation Busy bit Position */
#define GCLK_SYNCBUSY_SWRST_Msk               (_U_(0x1) << GCLK_SYNCBUSY_SWRST_Pos)                /**< (GCLK_SYNCBUSY) Software Reset Synchroniation Busy bit Mask */
#define GCLK_SYNCBUSY_SWRST(value)            (GCLK_SYNCBUSY_SWRST_Msk & ((value) << GCLK_SYNCBUSY_SWRST_Pos))
#define GCLK_SYNCBUSY_GENCTRL0_Pos            _U_(2)                                               /**< (GCLK_SYNCBUSY) Generic Clock Generator Control 0 Synchronization Busy bits Position */
#define GCLK_SYNCBUSY_GENCTRL0_Msk            (_U_(0x1) << GCLK_SYNCBUSY_GENCTRL0_Pos)             /**< (GCLK_SYNCBUSY) Generic Clock Generator Control 0 Synchronization Busy bits Mask */
#define GCLK_SYNCBUSY_GENCTRL0(value)         (GCLK_SYNCBUSY_GENCTRL0_Msk & ((value) << GCLK_SYNCBUSY_GENCTRL0_Pos))
#define   GCLK_SYNCBUSY_GENCTRL0_GCLK0_Val    _U_(0x1)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 0  */
#define   GCLK_SYNCBUSY_GENCTRL0_GCLK1_Val    _U_(0x2)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 1  */
#define   GCLK_SYNCBUSY_GENCTRL0_GCLK2_Val    _U_(0x4)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 2  */
#define   GCLK_SYNCBUSY_GENCTRL0_GCLK3_Val    _U_(0x8)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 3  */
#define   GCLK_SYNCBUSY_GENCTRL0_GCLK4_Val    _U_(0x10)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 4  */
#define   GCLK_SYNCBUSY_GENCTRL0_GCLK5_Val    _U_(0x20)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 5  */
#define   GCLK_SYNCBUSY_GENCTRL0_GCLK6_Val    _U_(0x40)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 6  */
#define   GCLK_SYNCBUSY_GENCTRL0_GCLK7_Val    _U_(0x80)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 7  */
#define   GCLK_SYNCBUSY_GENCTRL0_GCLK8_Val    _U_(0x100)                                           /**< (GCLK_SYNCBUSY) Generic clock generator 8  */
#define GCLK_SYNCBUSY_GENCTRL0_GCLK0          (GCLK_SYNCBUSY_GENCTRL0_GCLK0_Val << GCLK_SYNCBUSY_GENCTRL0_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 0 Position  */
#define GCLK_SYNCBUSY_GENCTRL0_GCLK1          (GCLK_SYNCBUSY_GENCTRL0_GCLK1_Val << GCLK_SYNCBUSY_GENCTRL0_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 1 Position  */
#define GCLK_SYNCBUSY_GENCTRL0_GCLK2          (GCLK_SYNCBUSY_GENCTRL0_GCLK2_Val << GCLK_SYNCBUSY_GENCTRL0_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 2 Position  */
#define GCLK_SYNCBUSY_GENCTRL0_GCLK3          (GCLK_SYNCBUSY_GENCTRL0_GCLK3_Val << GCLK_SYNCBUSY_GENCTRL0_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 3 Position  */
#define GCLK_SYNCBUSY_GENCTRL0_GCLK4          (GCLK_SYNCBUSY_GENCTRL0_GCLK4_Val << GCLK_SYNCBUSY_GENCTRL0_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 4 Position  */
#define GCLK_SYNCBUSY_GENCTRL0_GCLK5          (GCLK_SYNCBUSY_GENCTRL0_GCLK5_Val << GCLK_SYNCBUSY_GENCTRL0_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 5 Position  */
#define GCLK_SYNCBUSY_GENCTRL0_GCLK6          (GCLK_SYNCBUSY_GENCTRL0_GCLK6_Val << GCLK_SYNCBUSY_GENCTRL0_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 6 Position  */
#define GCLK_SYNCBUSY_GENCTRL0_GCLK7          (GCLK_SYNCBUSY_GENCTRL0_GCLK7_Val << GCLK_SYNCBUSY_GENCTRL0_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 7 Position  */
#define GCLK_SYNCBUSY_GENCTRL0_GCLK8          (GCLK_SYNCBUSY_GENCTRL0_GCLK8_Val << GCLK_SYNCBUSY_GENCTRL0_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 8 Position  */
#define GCLK_SYNCBUSY_GENCTRL1_Pos            _U_(3)                                               /**< (GCLK_SYNCBUSY) Generic Clock Generator Control 1 Synchronization Busy bits Position */
#define GCLK_SYNCBUSY_GENCTRL1_Msk            (_U_(0x1) << GCLK_SYNCBUSY_GENCTRL1_Pos)             /**< (GCLK_SYNCBUSY) Generic Clock Generator Control 1 Synchronization Busy bits Mask */
#define GCLK_SYNCBUSY_GENCTRL1(value)         (GCLK_SYNCBUSY_GENCTRL1_Msk & ((value) << GCLK_SYNCBUSY_GENCTRL1_Pos))
#define   GCLK_SYNCBUSY_GENCTRL1_GCLK0_Val    _U_(0x1)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 0  */
#define   GCLK_SYNCBUSY_GENCTRL1_GCLK1_Val    _U_(0x2)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 1  */
#define   GCLK_SYNCBUSY_GENCTRL1_GCLK2_Val    _U_(0x4)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 2  */
#define   GCLK_SYNCBUSY_GENCTRL1_GCLK3_Val    _U_(0x8)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 3  */
#define   GCLK_SYNCBUSY_GENCTRL1_GCLK4_Val    _U_(0x10)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 4  */
#define   GCLK_SYNCBUSY_GENCTRL1_GCLK5_Val    _U_(0x20)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 5  */
#define   GCLK_SYNCBUSY_GENCTRL1_GCLK6_Val    _U_(0x40)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 6  */
#define   GCLK_SYNCBUSY_GENCTRL1_GCLK7_Val    _U_(0x80)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 7  */
#define   GCLK_SYNCBUSY_GENCTRL1_GCLK8_Val    _U_(0x100)                                           /**< (GCLK_SYNCBUSY) Generic clock generator 8  */
#define GCLK_SYNCBUSY_GENCTRL1_GCLK0          (GCLK_SYNCBUSY_GENCTRL1_GCLK0_Val << GCLK_SYNCBUSY_GENCTRL1_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 0 Position  */
#define GCLK_SYNCBUSY_GENCTRL1_GCLK1          (GCLK_SYNCBUSY_GENCTRL1_GCLK1_Val << GCLK_SYNCBUSY_GENCTRL1_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 1 Position  */
#define GCLK_SYNCBUSY_GENCTRL1_GCLK2          (GCLK_SYNCBUSY_GENCTRL1_GCLK2_Val << GCLK_SYNCBUSY_GENCTRL1_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 2 Position  */
#define GCLK_SYNCBUSY_GENCTRL1_GCLK3          (GCLK_SYNCBUSY_GENCTRL1_GCLK3_Val << GCLK_SYNCBUSY_GENCTRL1_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 3 Position  */
#define GCLK_SYNCBUSY_GENCTRL1_GCLK4          (GCLK_SYNCBUSY_GENCTRL1_GCLK4_Val << GCLK_SYNCBUSY_GENCTRL1_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 4 Position  */
#define GCLK_SYNCBUSY_GENCTRL1_GCLK5          (GCLK_SYNCBUSY_GENCTRL1_GCLK5_Val << GCLK_SYNCBUSY_GENCTRL1_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 5 Position  */
#define GCLK_SYNCBUSY_GENCTRL1_GCLK6          (GCLK_SYNCBUSY_GENCTRL1_GCLK6_Val << GCLK_SYNCBUSY_GENCTRL1_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 6 Position  */
#define GCLK_SYNCBUSY_GENCTRL1_GCLK7          (GCLK_SYNCBUSY_GENCTRL1_GCLK7_Val << GCLK_SYNCBUSY_GENCTRL1_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 7 Position  */
#define GCLK_SYNCBUSY_GENCTRL1_GCLK8          (GCLK_SYNCBUSY_GENCTRL1_GCLK8_Val << GCLK_SYNCBUSY_GENCTRL1_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 8 Position  */
#define GCLK_SYNCBUSY_GENCTRL2_Pos            _U_(4)                                               /**< (GCLK_SYNCBUSY) Generic Clock Generator Control 2 Synchronization Busy bits Position */
#define GCLK_SYNCBUSY_GENCTRL2_Msk            (_U_(0x1) << GCLK_SYNCBUSY_GENCTRL2_Pos)             /**< (GCLK_SYNCBUSY) Generic Clock Generator Control 2 Synchronization Busy bits Mask */
#define GCLK_SYNCBUSY_GENCTRL2(value)         (GCLK_SYNCBUSY_GENCTRL2_Msk & ((value) << GCLK_SYNCBUSY_GENCTRL2_Pos))
#define   GCLK_SYNCBUSY_GENCTRL2_GCLK0_Val    _U_(0x1)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 0  */
#define   GCLK_SYNCBUSY_GENCTRL2_GCLK1_Val    _U_(0x2)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 1  */
#define   GCLK_SYNCBUSY_GENCTRL2_GCLK2_Val    _U_(0x4)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 2  */
#define   GCLK_SYNCBUSY_GENCTRL2_GCLK3_Val    _U_(0x8)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 3  */
#define   GCLK_SYNCBUSY_GENCTRL2_GCLK4_Val    _U_(0x10)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 4  */
#define   GCLK_SYNCBUSY_GENCTRL2_GCLK5_Val    _U_(0x20)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 5  */
#define   GCLK_SYNCBUSY_GENCTRL2_GCLK6_Val    _U_(0x40)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 6  */
#define   GCLK_SYNCBUSY_GENCTRL2_GCLK7_Val    _U_(0x80)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 7  */
#define   GCLK_SYNCBUSY_GENCTRL2_GCLK8_Val    _U_(0x100)                                           /**< (GCLK_SYNCBUSY) Generic clock generator 8  */
#define GCLK_SYNCBUSY_GENCTRL2_GCLK0          (GCLK_SYNCBUSY_GENCTRL2_GCLK0_Val << GCLK_SYNCBUSY_GENCTRL2_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 0 Position  */
#define GCLK_SYNCBUSY_GENCTRL2_GCLK1          (GCLK_SYNCBUSY_GENCTRL2_GCLK1_Val << GCLK_SYNCBUSY_GENCTRL2_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 1 Position  */
#define GCLK_SYNCBUSY_GENCTRL2_GCLK2          (GCLK_SYNCBUSY_GENCTRL2_GCLK2_Val << GCLK_SYNCBUSY_GENCTRL2_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 2 Position  */
#define GCLK_SYNCBUSY_GENCTRL2_GCLK3          (GCLK_SYNCBUSY_GENCTRL2_GCLK3_Val << GCLK_SYNCBUSY_GENCTRL2_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 3 Position  */
#define GCLK_SYNCBUSY_GENCTRL2_GCLK4          (GCLK_SYNCBUSY_GENCTRL2_GCLK4_Val << GCLK_SYNCBUSY_GENCTRL2_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 4 Position  */
#define GCLK_SYNCBUSY_GENCTRL2_GCLK5          (GCLK_SYNCBUSY_GENCTRL2_GCLK5_Val << GCLK_SYNCBUSY_GENCTRL2_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 5 Position  */
#define GCLK_SYNCBUSY_GENCTRL2_GCLK6          (GCLK_SYNCBUSY_GENCTRL2_GCLK6_Val << GCLK_SYNCBUSY_GENCTRL2_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 6 Position  */
#define GCLK_SYNCBUSY_GENCTRL2_GCLK7          (GCLK_SYNCBUSY_GENCTRL2_GCLK7_Val << GCLK_SYNCBUSY_GENCTRL2_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 7 Position  */
#define GCLK_SYNCBUSY_GENCTRL2_GCLK8          (GCLK_SYNCBUSY_GENCTRL2_GCLK8_Val << GCLK_SYNCBUSY_GENCTRL2_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 8 Position  */
#define GCLK_SYNCBUSY_GENCTRL3_Pos            _U_(5)                                               /**< (GCLK_SYNCBUSY) Generic Clock Generator Control 3 Synchronization Busy bits Position */
#define GCLK_SYNCBUSY_GENCTRL3_Msk            (_U_(0x1) << GCLK_SYNCBUSY_GENCTRL3_Pos)             /**< (GCLK_SYNCBUSY) Generic Clock Generator Control 3 Synchronization Busy bits Mask */
#define GCLK_SYNCBUSY_GENCTRL3(value)         (GCLK_SYNCBUSY_GENCTRL3_Msk & ((value) << GCLK_SYNCBUSY_GENCTRL3_Pos))
#define   GCLK_SYNCBUSY_GENCTRL3_GCLK0_Val    _U_(0x1)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 0  */
#define   GCLK_SYNCBUSY_GENCTRL3_GCLK1_Val    _U_(0x2)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 1  */
#define   GCLK_SYNCBUSY_GENCTRL3_GCLK2_Val    _U_(0x4)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 2  */
#define   GCLK_SYNCBUSY_GENCTRL3_GCLK3_Val    _U_(0x8)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 3  */
#define   GCLK_SYNCBUSY_GENCTRL3_GCLK4_Val    _U_(0x10)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 4  */
#define   GCLK_SYNCBUSY_GENCTRL3_GCLK5_Val    _U_(0x20)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 5  */
#define   GCLK_SYNCBUSY_GENCTRL3_GCLK6_Val    _U_(0x40)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 6  */
#define   GCLK_SYNCBUSY_GENCTRL3_GCLK7_Val    _U_(0x80)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 7  */
#define   GCLK_SYNCBUSY_GENCTRL3_GCLK8_Val    _U_(0x100)                                           /**< (GCLK_SYNCBUSY) Generic clock generator 8  */
#define GCLK_SYNCBUSY_GENCTRL3_GCLK0          (GCLK_SYNCBUSY_GENCTRL3_GCLK0_Val << GCLK_SYNCBUSY_GENCTRL3_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 0 Position  */
#define GCLK_SYNCBUSY_GENCTRL3_GCLK1          (GCLK_SYNCBUSY_GENCTRL3_GCLK1_Val << GCLK_SYNCBUSY_GENCTRL3_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 1 Position  */
#define GCLK_SYNCBUSY_GENCTRL3_GCLK2          (GCLK_SYNCBUSY_GENCTRL3_GCLK2_Val << GCLK_SYNCBUSY_GENCTRL3_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 2 Position  */
#define GCLK_SYNCBUSY_GENCTRL3_GCLK3          (GCLK_SYNCBUSY_GENCTRL3_GCLK3_Val << GCLK_SYNCBUSY_GENCTRL3_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 3 Position  */
#define GCLK_SYNCBUSY_GENCTRL3_GCLK4          (GCLK_SYNCBUSY_GENCTRL3_GCLK4_Val << GCLK_SYNCBUSY_GENCTRL3_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 4 Position  */
#define GCLK_SYNCBUSY_GENCTRL3_GCLK5          (GCLK_SYNCBUSY_GENCTRL3_GCLK5_Val << GCLK_SYNCBUSY_GENCTRL3_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 5 Position  */
#define GCLK_SYNCBUSY_GENCTRL3_GCLK6          (GCLK_SYNCBUSY_GENCTRL3_GCLK6_Val << GCLK_SYNCBUSY_GENCTRL3_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 6 Position  */
#define GCLK_SYNCBUSY_GENCTRL3_GCLK7          (GCLK_SYNCBUSY_GENCTRL3_GCLK7_Val << GCLK_SYNCBUSY_GENCTRL3_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 7 Position  */
#define GCLK_SYNCBUSY_GENCTRL3_GCLK8          (GCLK_SYNCBUSY_GENCTRL3_GCLK8_Val << GCLK_SYNCBUSY_GENCTRL3_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 8 Position  */
#define GCLK_SYNCBUSY_GENCTRL4_Pos            _U_(6)                                               /**< (GCLK_SYNCBUSY) Generic Clock Generator Control 4 Synchronization Busy bits Position */
#define GCLK_SYNCBUSY_GENCTRL4_Msk            (_U_(0x1) << GCLK_SYNCBUSY_GENCTRL4_Pos)             /**< (GCLK_SYNCBUSY) Generic Clock Generator Control 4 Synchronization Busy bits Mask */
#define GCLK_SYNCBUSY_GENCTRL4(value)         (GCLK_SYNCBUSY_GENCTRL4_Msk & ((value) << GCLK_SYNCBUSY_GENCTRL4_Pos))
#define   GCLK_SYNCBUSY_GENCTRL4_GCLK0_Val    _U_(0x1)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 0  */
#define   GCLK_SYNCBUSY_GENCTRL4_GCLK1_Val    _U_(0x2)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 1  */
#define   GCLK_SYNCBUSY_GENCTRL4_GCLK2_Val    _U_(0x4)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 2  */
#define   GCLK_SYNCBUSY_GENCTRL4_GCLK3_Val    _U_(0x8)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 3  */
#define   GCLK_SYNCBUSY_GENCTRL4_GCLK4_Val    _U_(0x10)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 4  */
#define   GCLK_SYNCBUSY_GENCTRL4_GCLK5_Val    _U_(0x20)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 5  */
#define   GCLK_SYNCBUSY_GENCTRL4_GCLK6_Val    _U_(0x40)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 6  */
#define   GCLK_SYNCBUSY_GENCTRL4_GCLK7_Val    _U_(0x80)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 7  */
#define   GCLK_SYNCBUSY_GENCTRL4_GCLK8_Val    _U_(0x100)                                           /**< (GCLK_SYNCBUSY) Generic clock generator 8  */
#define GCLK_SYNCBUSY_GENCTRL4_GCLK0          (GCLK_SYNCBUSY_GENCTRL4_GCLK0_Val << GCLK_SYNCBUSY_GENCTRL4_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 0 Position  */
#define GCLK_SYNCBUSY_GENCTRL4_GCLK1          (GCLK_SYNCBUSY_GENCTRL4_GCLK1_Val << GCLK_SYNCBUSY_GENCTRL4_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 1 Position  */
#define GCLK_SYNCBUSY_GENCTRL4_GCLK2          (GCLK_SYNCBUSY_GENCTRL4_GCLK2_Val << GCLK_SYNCBUSY_GENCTRL4_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 2 Position  */
#define GCLK_SYNCBUSY_GENCTRL4_GCLK3          (GCLK_SYNCBUSY_GENCTRL4_GCLK3_Val << GCLK_SYNCBUSY_GENCTRL4_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 3 Position  */
#define GCLK_SYNCBUSY_GENCTRL4_GCLK4          (GCLK_SYNCBUSY_GENCTRL4_GCLK4_Val << GCLK_SYNCBUSY_GENCTRL4_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 4 Position  */
#define GCLK_SYNCBUSY_GENCTRL4_GCLK5          (GCLK_SYNCBUSY_GENCTRL4_GCLK5_Val << GCLK_SYNCBUSY_GENCTRL4_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 5 Position  */
#define GCLK_SYNCBUSY_GENCTRL4_GCLK6          (GCLK_SYNCBUSY_GENCTRL4_GCLK6_Val << GCLK_SYNCBUSY_GENCTRL4_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 6 Position  */
#define GCLK_SYNCBUSY_GENCTRL4_GCLK7          (GCLK_SYNCBUSY_GENCTRL4_GCLK7_Val << GCLK_SYNCBUSY_GENCTRL4_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 7 Position  */
#define GCLK_SYNCBUSY_GENCTRL4_GCLK8          (GCLK_SYNCBUSY_GENCTRL4_GCLK8_Val << GCLK_SYNCBUSY_GENCTRL4_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 8 Position  */
#define GCLK_SYNCBUSY_GENCTRL5_Pos            _U_(7)                                               /**< (GCLK_SYNCBUSY) Generic Clock Generator Control 5 Synchronization Busy bits Position */
#define GCLK_SYNCBUSY_GENCTRL5_Msk            (_U_(0x1) << GCLK_SYNCBUSY_GENCTRL5_Pos)             /**< (GCLK_SYNCBUSY) Generic Clock Generator Control 5 Synchronization Busy bits Mask */
#define GCLK_SYNCBUSY_GENCTRL5(value)         (GCLK_SYNCBUSY_GENCTRL5_Msk & ((value) << GCLK_SYNCBUSY_GENCTRL5_Pos))
#define   GCLK_SYNCBUSY_GENCTRL5_GCLK0_Val    _U_(0x1)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 0  */
#define   GCLK_SYNCBUSY_GENCTRL5_GCLK1_Val    _U_(0x2)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 1  */
#define   GCLK_SYNCBUSY_GENCTRL5_GCLK2_Val    _U_(0x4)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 2  */
#define   GCLK_SYNCBUSY_GENCTRL5_GCLK3_Val    _U_(0x8)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 3  */
#define   GCLK_SYNCBUSY_GENCTRL5_GCLK4_Val    _U_(0x10)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 4  */
#define   GCLK_SYNCBUSY_GENCTRL5_GCLK5_Val    _U_(0x20)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 5  */
#define   GCLK_SYNCBUSY_GENCTRL5_GCLK6_Val    _U_(0x40)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 6  */
#define   GCLK_SYNCBUSY_GENCTRL5_GCLK7_Val    _U_(0x80)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 7  */
#define   GCLK_SYNCBUSY_GENCTRL5_GCLK8_Val    _U_(0x100)                                           /**< (GCLK_SYNCBUSY) Generic clock generator 8  */
#define GCLK_SYNCBUSY_GENCTRL5_GCLK0          (GCLK_SYNCBUSY_GENCTRL5_GCLK0_Val << GCLK_SYNCBUSY_GENCTRL5_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 0 Position  */
#define GCLK_SYNCBUSY_GENCTRL5_GCLK1          (GCLK_SYNCBUSY_GENCTRL5_GCLK1_Val << GCLK_SYNCBUSY_GENCTRL5_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 1 Position  */
#define GCLK_SYNCBUSY_GENCTRL5_GCLK2          (GCLK_SYNCBUSY_GENCTRL5_GCLK2_Val << GCLK_SYNCBUSY_GENCTRL5_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 2 Position  */
#define GCLK_SYNCBUSY_GENCTRL5_GCLK3          (GCLK_SYNCBUSY_GENCTRL5_GCLK3_Val << GCLK_SYNCBUSY_GENCTRL5_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 3 Position  */
#define GCLK_SYNCBUSY_GENCTRL5_GCLK4          (GCLK_SYNCBUSY_GENCTRL5_GCLK4_Val << GCLK_SYNCBUSY_GENCTRL5_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 4 Position  */
#define GCLK_SYNCBUSY_GENCTRL5_GCLK5          (GCLK_SYNCBUSY_GENCTRL5_GCLK5_Val << GCLK_SYNCBUSY_GENCTRL5_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 5 Position  */
#define GCLK_SYNCBUSY_GENCTRL5_GCLK6          (GCLK_SYNCBUSY_GENCTRL5_GCLK6_Val << GCLK_SYNCBUSY_GENCTRL5_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 6 Position  */
#define GCLK_SYNCBUSY_GENCTRL5_GCLK7          (GCLK_SYNCBUSY_GENCTRL5_GCLK7_Val << GCLK_SYNCBUSY_GENCTRL5_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 7 Position  */
#define GCLK_SYNCBUSY_GENCTRL5_GCLK8          (GCLK_SYNCBUSY_GENCTRL5_GCLK8_Val << GCLK_SYNCBUSY_GENCTRL5_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 8 Position  */
#define GCLK_SYNCBUSY_GENCTRL6_Pos            _U_(8)                                               /**< (GCLK_SYNCBUSY) Generic Clock Generator Control 6 Synchronization Busy bits Position */
#define GCLK_SYNCBUSY_GENCTRL6_Msk            (_U_(0x1) << GCLK_SYNCBUSY_GENCTRL6_Pos)             /**< (GCLK_SYNCBUSY) Generic Clock Generator Control 6 Synchronization Busy bits Mask */
#define GCLK_SYNCBUSY_GENCTRL6(value)         (GCLK_SYNCBUSY_GENCTRL6_Msk & ((value) << GCLK_SYNCBUSY_GENCTRL6_Pos))
#define   GCLK_SYNCBUSY_GENCTRL6_GCLK0_Val    _U_(0x1)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 0  */
#define   GCLK_SYNCBUSY_GENCTRL6_GCLK1_Val    _U_(0x2)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 1  */
#define   GCLK_SYNCBUSY_GENCTRL6_GCLK2_Val    _U_(0x4)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 2  */
#define   GCLK_SYNCBUSY_GENCTRL6_GCLK3_Val    _U_(0x8)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 3  */
#define   GCLK_SYNCBUSY_GENCTRL6_GCLK4_Val    _U_(0x10)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 4  */
#define   GCLK_SYNCBUSY_GENCTRL6_GCLK5_Val    _U_(0x20)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 5  */
#define   GCLK_SYNCBUSY_GENCTRL6_GCLK6_Val    _U_(0x40)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 6  */
#define   GCLK_SYNCBUSY_GENCTRL6_GCLK7_Val    _U_(0x80)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 7  */
#define   GCLK_SYNCBUSY_GENCTRL6_GCLK8_Val    _U_(0x100)                                           /**< (GCLK_SYNCBUSY) Generic clock generator 8  */
#define GCLK_SYNCBUSY_GENCTRL6_GCLK0          (GCLK_SYNCBUSY_GENCTRL6_GCLK0_Val << GCLK_SYNCBUSY_GENCTRL6_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 0 Position  */
#define GCLK_SYNCBUSY_GENCTRL6_GCLK1          (GCLK_SYNCBUSY_GENCTRL6_GCLK1_Val << GCLK_SYNCBUSY_GENCTRL6_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 1 Position  */
#define GCLK_SYNCBUSY_GENCTRL6_GCLK2          (GCLK_SYNCBUSY_GENCTRL6_GCLK2_Val << GCLK_SYNCBUSY_GENCTRL6_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 2 Position  */
#define GCLK_SYNCBUSY_GENCTRL6_GCLK3          (GCLK_SYNCBUSY_GENCTRL6_GCLK3_Val << GCLK_SYNCBUSY_GENCTRL6_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 3 Position  */
#define GCLK_SYNCBUSY_GENCTRL6_GCLK4          (GCLK_SYNCBUSY_GENCTRL6_GCLK4_Val << GCLK_SYNCBUSY_GENCTRL6_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 4 Position  */
#define GCLK_SYNCBUSY_GENCTRL6_GCLK5          (GCLK_SYNCBUSY_GENCTRL6_GCLK5_Val << GCLK_SYNCBUSY_GENCTRL6_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 5 Position  */
#define GCLK_SYNCBUSY_GENCTRL6_GCLK6          (GCLK_SYNCBUSY_GENCTRL6_GCLK6_Val << GCLK_SYNCBUSY_GENCTRL6_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 6 Position  */
#define GCLK_SYNCBUSY_GENCTRL6_GCLK7          (GCLK_SYNCBUSY_GENCTRL6_GCLK7_Val << GCLK_SYNCBUSY_GENCTRL6_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 7 Position  */
#define GCLK_SYNCBUSY_GENCTRL6_GCLK8          (GCLK_SYNCBUSY_GENCTRL6_GCLK8_Val << GCLK_SYNCBUSY_GENCTRL6_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 8 Position  */
#define GCLK_SYNCBUSY_GENCTRL7_Pos            _U_(9)                                               /**< (GCLK_SYNCBUSY) Generic Clock Generator Control 7 Synchronization Busy bits Position */
#define GCLK_SYNCBUSY_GENCTRL7_Msk            (_U_(0x1) << GCLK_SYNCBUSY_GENCTRL7_Pos)             /**< (GCLK_SYNCBUSY) Generic Clock Generator Control 7 Synchronization Busy bits Mask */
#define GCLK_SYNCBUSY_GENCTRL7(value)         (GCLK_SYNCBUSY_GENCTRL7_Msk & ((value) << GCLK_SYNCBUSY_GENCTRL7_Pos))
#define   GCLK_SYNCBUSY_GENCTRL7_GCLK0_Val    _U_(0x1)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 0  */
#define   GCLK_SYNCBUSY_GENCTRL7_GCLK1_Val    _U_(0x2)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 1  */
#define   GCLK_SYNCBUSY_GENCTRL7_GCLK2_Val    _U_(0x4)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 2  */
#define   GCLK_SYNCBUSY_GENCTRL7_GCLK3_Val    _U_(0x8)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 3  */
#define   GCLK_SYNCBUSY_GENCTRL7_GCLK4_Val    _U_(0x10)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 4  */
#define   GCLK_SYNCBUSY_GENCTRL7_GCLK5_Val    _U_(0x20)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 5  */
#define   GCLK_SYNCBUSY_GENCTRL7_GCLK6_Val    _U_(0x40)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 6  */
#define   GCLK_SYNCBUSY_GENCTRL7_GCLK7_Val    _U_(0x80)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 7  */
#define   GCLK_SYNCBUSY_GENCTRL7_GCLK8_Val    _U_(0x100)                                           /**< (GCLK_SYNCBUSY) Generic clock generator 8  */
#define GCLK_SYNCBUSY_GENCTRL7_GCLK0          (GCLK_SYNCBUSY_GENCTRL7_GCLK0_Val << GCLK_SYNCBUSY_GENCTRL7_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 0 Position  */
#define GCLK_SYNCBUSY_GENCTRL7_GCLK1          (GCLK_SYNCBUSY_GENCTRL7_GCLK1_Val << GCLK_SYNCBUSY_GENCTRL7_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 1 Position  */
#define GCLK_SYNCBUSY_GENCTRL7_GCLK2          (GCLK_SYNCBUSY_GENCTRL7_GCLK2_Val << GCLK_SYNCBUSY_GENCTRL7_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 2 Position  */
#define GCLK_SYNCBUSY_GENCTRL7_GCLK3          (GCLK_SYNCBUSY_GENCTRL7_GCLK3_Val << GCLK_SYNCBUSY_GENCTRL7_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 3 Position  */
#define GCLK_SYNCBUSY_GENCTRL7_GCLK4          (GCLK_SYNCBUSY_GENCTRL7_GCLK4_Val << GCLK_SYNCBUSY_GENCTRL7_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 4 Position  */
#define GCLK_SYNCBUSY_GENCTRL7_GCLK5          (GCLK_SYNCBUSY_GENCTRL7_GCLK5_Val << GCLK_SYNCBUSY_GENCTRL7_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 5 Position  */
#define GCLK_SYNCBUSY_GENCTRL7_GCLK6          (GCLK_SYNCBUSY_GENCTRL7_GCLK6_Val << GCLK_SYNCBUSY_GENCTRL7_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 6 Position  */
#define GCLK_SYNCBUSY_GENCTRL7_GCLK7          (GCLK_SYNCBUSY_GENCTRL7_GCLK7_Val << GCLK_SYNCBUSY_GENCTRL7_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 7 Position  */
#define GCLK_SYNCBUSY_GENCTRL7_GCLK8          (GCLK_SYNCBUSY_GENCTRL7_GCLK8_Val << GCLK_SYNCBUSY_GENCTRL7_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 8 Position  */
#define GCLK_SYNCBUSY_GENCTRL8_Pos            _U_(10)                                              /**< (GCLK_SYNCBUSY) Generic Clock Generator Control 8 Synchronization Busy bits Position */
#define GCLK_SYNCBUSY_GENCTRL8_Msk            (_U_(0x1) << GCLK_SYNCBUSY_GENCTRL8_Pos)             /**< (GCLK_SYNCBUSY) Generic Clock Generator Control 8 Synchronization Busy bits Mask */
#define GCLK_SYNCBUSY_GENCTRL8(value)         (GCLK_SYNCBUSY_GENCTRL8_Msk & ((value) << GCLK_SYNCBUSY_GENCTRL8_Pos))
#define   GCLK_SYNCBUSY_GENCTRL8_GCLK0_Val    _U_(0x1)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 0  */
#define   GCLK_SYNCBUSY_GENCTRL8_GCLK1_Val    _U_(0x2)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 1  */
#define   GCLK_SYNCBUSY_GENCTRL8_GCLK2_Val    _U_(0x4)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 2  */
#define   GCLK_SYNCBUSY_GENCTRL8_GCLK3_Val    _U_(0x8)                                             /**< (GCLK_SYNCBUSY) Generic clock generator 3  */
#define   GCLK_SYNCBUSY_GENCTRL8_GCLK4_Val    _U_(0x10)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 4  */
#define   GCLK_SYNCBUSY_GENCTRL8_GCLK5_Val    _U_(0x20)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 5  */
#define   GCLK_SYNCBUSY_GENCTRL8_GCLK6_Val    _U_(0x40)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 6  */
#define   GCLK_SYNCBUSY_GENCTRL8_GCLK7_Val    _U_(0x80)                                            /**< (GCLK_SYNCBUSY) Generic clock generator 7  */
#define   GCLK_SYNCBUSY_GENCTRL8_GCLK8_Val    _U_(0x100)                                           /**< (GCLK_SYNCBUSY) Generic clock generator 8  */
#define GCLK_SYNCBUSY_GENCTRL8_GCLK0          (GCLK_SYNCBUSY_GENCTRL8_GCLK0_Val << GCLK_SYNCBUSY_GENCTRL8_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 0 Position  */
#define GCLK_SYNCBUSY_GENCTRL8_GCLK1          (GCLK_SYNCBUSY_GENCTRL8_GCLK1_Val << GCLK_SYNCBUSY_GENCTRL8_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 1 Position  */
#define GCLK_SYNCBUSY_GENCTRL8_GCLK2          (GCLK_SYNCBUSY_GENCTRL8_GCLK2_Val << GCLK_SYNCBUSY_GENCTRL8_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 2 Position  */
#define GCLK_SYNCBUSY_GENCTRL8_GCLK3          (GCLK_SYNCBUSY_GENCTRL8_GCLK3_Val << GCLK_SYNCBUSY_GENCTRL8_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 3 Position  */
#define GCLK_SYNCBUSY_GENCTRL8_GCLK4          (GCLK_SYNCBUSY_GENCTRL8_GCLK4_Val << GCLK_SYNCBUSY_GENCTRL8_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 4 Position  */
#define GCLK_SYNCBUSY_GENCTRL8_GCLK5          (GCLK_SYNCBUSY_GENCTRL8_GCLK5_Val << GCLK_SYNCBUSY_GENCTRL8_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 5 Position  */
#define GCLK_SYNCBUSY_GENCTRL8_GCLK6          (GCLK_SYNCBUSY_GENCTRL8_GCLK6_Val << GCLK_SYNCBUSY_GENCTRL8_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 6 Position  */
#define GCLK_SYNCBUSY_GENCTRL8_GCLK7          (GCLK_SYNCBUSY_GENCTRL8_GCLK7_Val << GCLK_SYNCBUSY_GENCTRL8_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 7 Position  */
#define GCLK_SYNCBUSY_GENCTRL8_GCLK8          (GCLK_SYNCBUSY_GENCTRL8_GCLK8_Val << GCLK_SYNCBUSY_GENCTRL8_Pos) /**< (GCLK_SYNCBUSY) Generic clock generator 8 Position  */
#define GCLK_SYNCBUSY_Msk                     _U_(0x000007FD)                                      /**< (GCLK_SYNCBUSY) Register Mask  */

#define GCLK_SYNCBUSY_GENCTRL_Pos             _U_(2)                                               /**< (GCLK_SYNCBUSY Position) Generic Clock Generator Control 8 Synchronization Busy bits */
#define GCLK_SYNCBUSY_GENCTRL_Msk             (_U_(0x1FF) << GCLK_SYNCBUSY_GENCTRL_Pos)            /**< (GCLK_SYNCBUSY Mask) GENCTRL */
#define GCLK_SYNCBUSY_GENCTRL(value)          (GCLK_SYNCBUSY_GENCTRL_Msk & ((value) << GCLK_SYNCBUSY_GENCTRL_Pos)) 

/* -------- GCLK_GENCTRL : (GCLK Offset: 0x20) (R/W 32) Generic Clock Generator Control -------- */
#define GCLK_GENCTRL_RESETVALUE               _U_(0x00)                                            /**<  (GCLK_GENCTRL) Generic Clock Generator Control  Reset Value */

#define GCLK_GENCTRL_SRC_Pos                  _U_(0)                                               /**< (GCLK_GENCTRL) Source Select Position */
#define GCLK_GENCTRL_SRC_Msk                  (_U_(0x7) << GCLK_GENCTRL_SRC_Pos)                   /**< (GCLK_GENCTRL) Source Select Mask */
#define GCLK_GENCTRL_SRC(value)               (GCLK_GENCTRL_SRC_Msk & ((value) << GCLK_GENCTRL_SRC_Pos))
#define   GCLK_GENCTRL_SRC_XOSC_Val           _U_(0x0)                                             /**< (GCLK_GENCTRL) XOSC oscillator output  */
#define   GCLK_GENCTRL_SRC_GCLKIN_Val         _U_(0x1)                                             /**< (GCLK_GENCTRL) Generator input pad  */
#define   GCLK_GENCTRL_SRC_GCLKGEN1_Val       _U_(0x2)                                             /**< (GCLK_GENCTRL) Generic clock generator 1 output  */
#define   GCLK_GENCTRL_SRC_OSCULP32K_Val      _U_(0x3)                                             /**< (GCLK_GENCTRL) OSCULP32K oscillator output  */
#define   GCLK_GENCTRL_SRC_OSC32K_Val         _U_(0x4)                                             /**< (GCLK_GENCTRL) OSC32K oscillator output  */
#define   GCLK_GENCTRL_SRC_XOSC32K_Val        _U_(0x5)                                             /**< (GCLK_GENCTRL) XOSC32K oscillator output  */
#define   GCLK_GENCTRL_SRC_OSC48M_Val         _U_(0x6)                                             /**< (GCLK_GENCTRL) OSC48M oscillator output  */
#define   GCLK_GENCTRL_SRC_DPLL96M_Val        _U_(0x7)                                             /**< (GCLK_GENCTRL) DPLL96M output  */
#define GCLK_GENCTRL_SRC_XOSC                 (GCLK_GENCTRL_SRC_XOSC_Val << GCLK_GENCTRL_SRC_Pos)  /**< (GCLK_GENCTRL) XOSC oscillator output Position  */
#define GCLK_GENCTRL_SRC_GCLKIN               (GCLK_GENCTRL_SRC_GCLKIN_Val << GCLK_GENCTRL_SRC_Pos) /**< (GCLK_GENCTRL) Generator input pad Position  */
#define GCLK_GENCTRL_SRC_GCLKGEN1             (GCLK_GENCTRL_SRC_GCLKGEN1_Val << GCLK_GENCTRL_SRC_Pos) /**< (GCLK_GENCTRL) Generic clock generator 1 output Position  */
#define GCLK_GENCTRL_SRC_OSCULP32K            (GCLK_GENCTRL_SRC_OSCULP32K_Val << GCLK_GENCTRL_SRC_Pos) /**< (GCLK_GENCTRL) OSCULP32K oscillator output Position  */
#define GCLK_GENCTRL_SRC_OSC32K               (GCLK_GENCTRL_SRC_OSC32K_Val << GCLK_GENCTRL_SRC_Pos) /**< (GCLK_GENCTRL) OSC32K oscillator output Position  */
#define GCLK_GENCTRL_SRC_XOSC32K              (GCLK_GENCTRL_SRC_XOSC32K_Val << GCLK_GENCTRL_SRC_Pos) /**< (GCLK_GENCTRL) XOSC32K oscillator output Position  */
#define GCLK_GENCTRL_SRC_OSC48M               (GCLK_GENCTRL_SRC_OSC48M_Val << GCLK_GENCTRL_SRC_Pos) /**< (GCLK_GENCTRL) OSC48M oscillator output Position  */
#define GCLK_GENCTRL_SRC_DPLL96M              (GCLK_GENCTRL_SRC_DPLL96M_Val << GCLK_GENCTRL_SRC_Pos) /**< (GCLK_GENCTRL) DPLL96M output Position  */
#define GCLK_GENCTRL_GENEN_Pos                _U_(8)                                               /**< (GCLK_GENCTRL) Generic Clock Generator Enable Position */
#define GCLK_GENCTRL_GENEN_Msk                (_U_(0x1) << GCLK_GENCTRL_GENEN_Pos)                 /**< (GCLK_GENCTRL) Generic Clock Generator Enable Mask */
#define GCLK_GENCTRL_GENEN(value)             (GCLK_GENCTRL_GENEN_Msk & ((value) << GCLK_GENCTRL_GENEN_Pos))
#define GCLK_GENCTRL_IDC_Pos                  _U_(9)                                               /**< (GCLK_GENCTRL) Improve Duty Cycle Position */
#define GCLK_GENCTRL_IDC_Msk                  (_U_(0x1) << GCLK_GENCTRL_IDC_Pos)                   /**< (GCLK_GENCTRL) Improve Duty Cycle Mask */
#define GCLK_GENCTRL_IDC(value)               (GCLK_GENCTRL_IDC_Msk & ((value) << GCLK_GENCTRL_IDC_Pos))
#define GCLK_GENCTRL_OOV_Pos                  _U_(10)                                              /**< (GCLK_GENCTRL) Output Off Value Position */
#define GCLK_GENCTRL_OOV_Msk                  (_U_(0x1) << GCLK_GENCTRL_OOV_Pos)                   /**< (GCLK_GENCTRL) Output Off Value Mask */
#define GCLK_GENCTRL_OOV(value)               (GCLK_GENCTRL_OOV_Msk & ((value) << GCLK_GENCTRL_OOV_Pos))
#define GCLK_GENCTRL_OE_Pos                   _U_(11)                                              /**< (GCLK_GENCTRL) Output Enable Position */
#define GCLK_GENCTRL_OE_Msk                   (_U_(0x1) << GCLK_GENCTRL_OE_Pos)                    /**< (GCLK_GENCTRL) Output Enable Mask */
#define GCLK_GENCTRL_OE(value)                (GCLK_GENCTRL_OE_Msk & ((value) << GCLK_GENCTRL_OE_Pos))
#define GCLK_GENCTRL_DIVSEL_Pos               _U_(12)                                              /**< (GCLK_GENCTRL) Divide Selection Position */
#define GCLK_GENCTRL_DIVSEL_Msk               (_U_(0x1) << GCLK_GENCTRL_DIVSEL_Pos)                /**< (GCLK_GENCTRL) Divide Selection Mask */
#define GCLK_GENCTRL_DIVSEL(value)            (GCLK_GENCTRL_DIVSEL_Msk & ((value) << GCLK_GENCTRL_DIVSEL_Pos))
#define   GCLK_GENCTRL_DIVSEL_DIV1_Val        _U_(0x0)                                             /**< (GCLK_GENCTRL) Divide input directly by divider factor  */
#define   GCLK_GENCTRL_DIVSEL_DIV2_Val        _U_(0x1)                                             /**< (GCLK_GENCTRL) Divide input by 2^(divider factor+ 1)  */
#define GCLK_GENCTRL_DIVSEL_DIV1              (GCLK_GENCTRL_DIVSEL_DIV1_Val << GCLK_GENCTRL_DIVSEL_Pos) /**< (GCLK_GENCTRL) Divide input directly by divider factor Position  */
#define GCLK_GENCTRL_DIVSEL_DIV2              (GCLK_GENCTRL_DIVSEL_DIV2_Val << GCLK_GENCTRL_DIVSEL_Pos) /**< (GCLK_GENCTRL) Divide input by 2^(divider factor+ 1) Position  */
#define GCLK_GENCTRL_RUNSTDBY_Pos             _U_(13)                                              /**< (GCLK_GENCTRL) Run in Standby Position */
#define GCLK_GENCTRL_RUNSTDBY_Msk             (_U_(0x1) << GCLK_GENCTRL_RUNSTDBY_Pos)              /**< (GCLK_GENCTRL) Run in Standby Mask */
#define GCLK_GENCTRL_RUNSTDBY(value)          (GCLK_GENCTRL_RUNSTDBY_Msk & ((value) << GCLK_GENCTRL_RUNSTDBY_Pos))
#define GCLK_GENCTRL_DIV_Pos                  _U_(16)                                              /**< (GCLK_GENCTRL) Division Factor Position */
#define GCLK_GENCTRL_DIV_Msk                  (_U_(0xFFFF) << GCLK_GENCTRL_DIV_Pos)                /**< (GCLK_GENCTRL) Division Factor Mask */
#define GCLK_GENCTRL_DIV(value)               (GCLK_GENCTRL_DIV_Msk & ((value) << GCLK_GENCTRL_DIV_Pos))
#define GCLK_GENCTRL_Msk                      _U_(0xFFFF3F07)                                      /**< (GCLK_GENCTRL) Register Mask  */


/* -------- GCLK_PCHCTRL : (GCLK Offset: 0x80) (R/W 32) Peripheral Clock Control -------- */
#define GCLK_PCHCTRL_RESETVALUE               _U_(0x00)                                            /**<  (GCLK_PCHCTRL) Peripheral Clock Control  Reset Value */

#define GCLK_PCHCTRL_GEN_Pos                  _U_(0)                                               /**< (GCLK_PCHCTRL) Generic Clock Generator Position */
#define GCLK_PCHCTRL_GEN_Msk                  (_U_(0xF) << GCLK_PCHCTRL_GEN_Pos)                   /**< (GCLK_PCHCTRL) Generic Clock Generator Mask */
#define GCLK_PCHCTRL_GEN(value)               (GCLK_PCHCTRL_GEN_Msk & ((value) << GCLK_PCHCTRL_GEN_Pos))
#define   GCLK_PCHCTRL_GEN_GCLK0_Val          _U_(0x0)                                             /**< (GCLK_PCHCTRL) Generic clock generator 0  */
#define   GCLK_PCHCTRL_GEN_GCLK1_Val          _U_(0x1)                                             /**< (GCLK_PCHCTRL) Generic clock generator 1  */
#define   GCLK_PCHCTRL_GEN_GCLK2_Val          _U_(0x2)                                             /**< (GCLK_PCHCTRL) Generic clock generator 2  */
#define   GCLK_PCHCTRL_GEN_GCLK3_Val          _U_(0x3)                                             /**< (GCLK_PCHCTRL) Generic clock generator 3  */
#define   GCLK_PCHCTRL_GEN_GCLK4_Val          _U_(0x4)                                             /**< (GCLK_PCHCTRL) Generic clock generator 4  */
#define   GCLK_PCHCTRL_GEN_GCLK5_Val          _U_(0x5)                                             /**< (GCLK_PCHCTRL) Generic clock generator 5  */
#define   GCLK_PCHCTRL_GEN_GCLK6_Val          _U_(0x6)                                             /**< (GCLK_PCHCTRL) Generic clock generator 6  */
#define   GCLK_PCHCTRL_GEN_GCLK7_Val          _U_(0x7)                                             /**< (GCLK_PCHCTRL) Generic clock generator 7  */
#define   GCLK_PCHCTRL_GEN_GCLK8_Val          _U_(0x8)                                             /**< (GCLK_PCHCTRL) Generic clock generator 8  */
#define GCLK_PCHCTRL_GEN_GCLK0                (GCLK_PCHCTRL_GEN_GCLK0_Val << GCLK_PCHCTRL_GEN_Pos) /**< (GCLK_PCHCTRL) Generic clock generator 0 Position  */
#define GCLK_PCHCTRL_GEN_GCLK1                (GCLK_PCHCTRL_GEN_GCLK1_Val << GCLK_PCHCTRL_GEN_Pos) /**< (GCLK_PCHCTRL) Generic clock generator 1 Position  */
#define GCLK_PCHCTRL_GEN_GCLK2                (GCLK_PCHCTRL_GEN_GCLK2_Val << GCLK_PCHCTRL_GEN_Pos) /**< (GCLK_PCHCTRL) Generic clock generator 2 Position  */
#define GCLK_PCHCTRL_GEN_GCLK3                (GCLK_PCHCTRL_GEN_GCLK3_Val << GCLK_PCHCTRL_GEN_Pos) /**< (GCLK_PCHCTRL) Generic clock generator 3 Position  */
#define GCLK_PCHCTRL_GEN_GCLK4                (GCLK_PCHCTRL_GEN_GCLK4_Val << GCLK_PCHCTRL_GEN_Pos) /**< (GCLK_PCHCTRL) Generic clock generator 4 Position  */
#define GCLK_PCHCTRL_GEN_GCLK5                (GCLK_PCHCTRL_GEN_GCLK5_Val << GCLK_PCHCTRL_GEN_Pos) /**< (GCLK_PCHCTRL) Generic clock generator 5 Position  */
#define GCLK_PCHCTRL_GEN_GCLK6                (GCLK_PCHCTRL_GEN_GCLK6_Val << GCLK_PCHCTRL_GEN_Pos) /**< (GCLK_PCHCTRL) Generic clock generator 6 Position  */
#define GCLK_PCHCTRL_GEN_GCLK7                (GCLK_PCHCTRL_GEN_GCLK7_Val << GCLK_PCHCTRL_GEN_Pos) /**< (GCLK_PCHCTRL) Generic clock generator 7 Position  */
#define GCLK_PCHCTRL_GEN_GCLK8                (GCLK_PCHCTRL_GEN_GCLK8_Val << GCLK_PCHCTRL_GEN_Pos) /**< (GCLK_PCHCTRL) Generic clock generator 8 Position  */
#define GCLK_PCHCTRL_CHEN_Pos                 _U_(6)                                               /**< (GCLK_PCHCTRL) Channel Enable Position */
#define GCLK_PCHCTRL_CHEN_Msk                 (_U_(0x1) << GCLK_PCHCTRL_CHEN_Pos)                  /**< (GCLK_PCHCTRL) Channel Enable Mask */
#define GCLK_PCHCTRL_CHEN(value)              (GCLK_PCHCTRL_CHEN_Msk & ((value) << GCLK_PCHCTRL_CHEN_Pos))
#define GCLK_PCHCTRL_WRTLOCK_Pos              _U_(7)                                               /**< (GCLK_PCHCTRL) Write Lock Position */
#define GCLK_PCHCTRL_WRTLOCK_Msk              (_U_(0x1) << GCLK_PCHCTRL_WRTLOCK_Pos)               /**< (GCLK_PCHCTRL) Write Lock Mask */
#define GCLK_PCHCTRL_WRTLOCK(value)           (GCLK_PCHCTRL_WRTLOCK_Msk & ((value) << GCLK_PCHCTRL_WRTLOCK_Pos))
#define GCLK_PCHCTRL_Msk                      _U_(0x000000CF)                                      /**< (GCLK_PCHCTRL) Register Mask  */


/** \brief GCLK register offsets definitions */
#define GCLK_CTRLA_REG_OFST            (0x00)              /**< (GCLK_CTRLA) Control Offset */
#define GCLK_SYNCBUSY_REG_OFST         (0x04)              /**< (GCLK_SYNCBUSY) Synchronization Busy Offset */
#define GCLK_GENCTRL_REG_OFST          (0x20)              /**< (GCLK_GENCTRL) Generic Clock Generator Control Offset */
#define GCLK_PCHCTRL_REG_OFST          (0x80)              /**< (GCLK_PCHCTRL) Peripheral Clock Control Offset */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief GCLK register API structure */
typedef struct
{  /* Generic Clock Generator */
  __IO  uint8_t                        GCLK_CTRLA;         /**< Offset: 0x00 (R/W  8) Control */
  __I   uint8_t                        Reserved1[0x03];
  __I   uint32_t                       GCLK_SYNCBUSY;      /**< Offset: 0x04 (R/   32) Synchronization Busy */
  __I   uint8_t                        Reserved2[0x18];
  __IO  uint32_t                       GCLK_GENCTRL[9];    /**< Offset: 0x20 (R/W  32) Generic Clock Generator Control */
  __I   uint8_t                        Reserved3[0x3C];
  __IO  uint32_t                       GCLK_PCHCTRL[46];   /**< Offset: 0x80 (R/W  32) Peripheral Clock Control */
} gclk_registers_t;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* _SAMC21_GCLK_COMPONENT_H_ */
