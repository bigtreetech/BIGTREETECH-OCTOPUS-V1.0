/**
 * \brief Component description for DIVAS
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
#ifndef _SAMC21_DIVAS_COMPONENT_H_
#define _SAMC21_DIVAS_COMPONENT_H_

/* ************************************************************************** */
/*   SOFTWARE API DEFINITION FOR DIVAS                                        */
/* ************************************************************************** */

/* -------- DIVAS_CTRLA : (DIVAS Offset: 0x00) (R/W 8) Control -------- */
#define DIVAS_CTRLA_RESETVALUE                _U_(0x00)                                            /**<  (DIVAS_CTRLA) Control  Reset Value */

#define DIVAS_CTRLA_SIGNED_Pos                _U_(0)                                               /**< (DIVAS_CTRLA) Signed Position */
#define DIVAS_CTRLA_SIGNED_Msk                (_U_(0x1) << DIVAS_CTRLA_SIGNED_Pos)                 /**< (DIVAS_CTRLA) Signed Mask */
#define DIVAS_CTRLA_SIGNED(value)             (DIVAS_CTRLA_SIGNED_Msk & ((value) << DIVAS_CTRLA_SIGNED_Pos))
#define DIVAS_CTRLA_DLZ_Pos                   _U_(1)                                               /**< (DIVAS_CTRLA) Disable Leading Zero Optimization Position */
#define DIVAS_CTRLA_DLZ_Msk                   (_U_(0x1) << DIVAS_CTRLA_DLZ_Pos)                    /**< (DIVAS_CTRLA) Disable Leading Zero Optimization Mask */
#define DIVAS_CTRLA_DLZ(value)                (DIVAS_CTRLA_DLZ_Msk & ((value) << DIVAS_CTRLA_DLZ_Pos))
#define DIVAS_CTRLA_Msk                       _U_(0x03)                                            /**< (DIVAS_CTRLA) Register Mask  */


/* -------- DIVAS_STATUS : (DIVAS Offset: 0x04) (R/W 8) Status -------- */
#define DIVAS_STATUS_RESETVALUE               _U_(0x00)                                            /**<  (DIVAS_STATUS) Status  Reset Value */

#define DIVAS_STATUS_BUSY_Pos                 _U_(0)                                               /**< (DIVAS_STATUS) DIVAS Accelerator Busy Position */
#define DIVAS_STATUS_BUSY_Msk                 (_U_(0x1) << DIVAS_STATUS_BUSY_Pos)                  /**< (DIVAS_STATUS) DIVAS Accelerator Busy Mask */
#define DIVAS_STATUS_BUSY(value)              (DIVAS_STATUS_BUSY_Msk & ((value) << DIVAS_STATUS_BUSY_Pos))
#define DIVAS_STATUS_DBZ_Pos                  _U_(1)                                               /**< (DIVAS_STATUS) Writing a one to this bit clears DBZ to zero Position */
#define DIVAS_STATUS_DBZ_Msk                  (_U_(0x1) << DIVAS_STATUS_DBZ_Pos)                   /**< (DIVAS_STATUS) Writing a one to this bit clears DBZ to zero Mask */
#define DIVAS_STATUS_DBZ(value)               (DIVAS_STATUS_DBZ_Msk & ((value) << DIVAS_STATUS_DBZ_Pos))
#define DIVAS_STATUS_Msk                      _U_(0x03)                                            /**< (DIVAS_STATUS) Register Mask  */


/* -------- DIVAS_DIVIDEND : (DIVAS Offset: 0x08) (R/W 32) Dividend -------- */
#define DIVAS_DIVIDEND_RESETVALUE             _U_(0x00)                                            /**<  (DIVAS_DIVIDEND) Dividend  Reset Value */

#define DIVAS_DIVIDEND_DIVIDEND_Pos           _U_(0)                                               /**< (DIVAS_DIVIDEND) DIVIDEND Position */
#define DIVAS_DIVIDEND_DIVIDEND_Msk           (_U_(0xFFFFFFFF) << DIVAS_DIVIDEND_DIVIDEND_Pos)     /**< (DIVAS_DIVIDEND) DIVIDEND Mask */
#define DIVAS_DIVIDEND_DIVIDEND(value)        (DIVAS_DIVIDEND_DIVIDEND_Msk & ((value) << DIVAS_DIVIDEND_DIVIDEND_Pos))
#define DIVAS_DIVIDEND_Msk                    _U_(0xFFFFFFFF)                                      /**< (DIVAS_DIVIDEND) Register Mask  */


/* -------- DIVAS_DIVISOR : (DIVAS Offset: 0x0C) (R/W 32) Divisor -------- */
#define DIVAS_DIVISOR_RESETVALUE              _U_(0x00)                                            /**<  (DIVAS_DIVISOR) Divisor  Reset Value */

#define DIVAS_DIVISOR_DIVISOR_Pos             _U_(0)                                               /**< (DIVAS_DIVISOR) DIVISOR Position */
#define DIVAS_DIVISOR_DIVISOR_Msk             (_U_(0xFFFFFFFF) << DIVAS_DIVISOR_DIVISOR_Pos)       /**< (DIVAS_DIVISOR) DIVISOR Mask */
#define DIVAS_DIVISOR_DIVISOR(value)          (DIVAS_DIVISOR_DIVISOR_Msk & ((value) << DIVAS_DIVISOR_DIVISOR_Pos))
#define DIVAS_DIVISOR_Msk                     _U_(0xFFFFFFFF)                                      /**< (DIVAS_DIVISOR) Register Mask  */


/* -------- DIVAS_RESULT : (DIVAS Offset: 0x10) ( R/ 32) Result -------- */
#define DIVAS_RESULT_RESETVALUE               _U_(0x00)                                            /**<  (DIVAS_RESULT) Result  Reset Value */

#define DIVAS_RESULT_RESULT_Pos               _U_(0)                                               /**< (DIVAS_RESULT) RESULT Position */
#define DIVAS_RESULT_RESULT_Msk               (_U_(0xFFFFFFFF) << DIVAS_RESULT_RESULT_Pos)         /**< (DIVAS_RESULT) RESULT Mask */
#define DIVAS_RESULT_RESULT(value)            (DIVAS_RESULT_RESULT_Msk & ((value) << DIVAS_RESULT_RESULT_Pos))
#define DIVAS_RESULT_Msk                      _U_(0xFFFFFFFF)                                      /**< (DIVAS_RESULT) Register Mask  */


/* -------- DIVAS_REM : (DIVAS Offset: 0x14) ( R/ 32) Remainder -------- */
#define DIVAS_REM_RESETVALUE                  _U_(0x00)                                            /**<  (DIVAS_REM) Remainder  Reset Value */

#define DIVAS_REM_REM_Pos                     _U_(0)                                               /**< (DIVAS_REM) REM Position */
#define DIVAS_REM_REM_Msk                     (_U_(0xFFFFFFFF) << DIVAS_REM_REM_Pos)               /**< (DIVAS_REM) REM Mask */
#define DIVAS_REM_REM(value)                  (DIVAS_REM_REM_Msk & ((value) << DIVAS_REM_REM_Pos))
#define DIVAS_REM_Msk                         _U_(0xFFFFFFFF)                                      /**< (DIVAS_REM) Register Mask  */


/* -------- DIVAS_SQRNUM : (DIVAS Offset: 0x18) (R/W 32) Square Root Input -------- */
#define DIVAS_SQRNUM_RESETVALUE               _U_(0x00)                                            /**<  (DIVAS_SQRNUM) Square Root Input  Reset Value */

#define DIVAS_SQRNUM_SQRNUM_Pos               _U_(0)                                               /**< (DIVAS_SQRNUM) Square Root Input Position */
#define DIVAS_SQRNUM_SQRNUM_Msk               (_U_(0xFFFFFFFF) << DIVAS_SQRNUM_SQRNUM_Pos)         /**< (DIVAS_SQRNUM) Square Root Input Mask */
#define DIVAS_SQRNUM_SQRNUM(value)            (DIVAS_SQRNUM_SQRNUM_Msk & ((value) << DIVAS_SQRNUM_SQRNUM_Pos))
#define DIVAS_SQRNUM_Msk                      _U_(0xFFFFFFFF)                                      /**< (DIVAS_SQRNUM) Register Mask  */


/** \brief DIVAS register offsets definitions */
#define DIVAS_CTRLA_REG_OFST           (0x00)              /**< (DIVAS_CTRLA) Control Offset */
#define DIVAS_STATUS_REG_OFST          (0x04)              /**< (DIVAS_STATUS) Status Offset */
#define DIVAS_DIVIDEND_REG_OFST        (0x08)              /**< (DIVAS_DIVIDEND) Dividend Offset */
#define DIVAS_DIVISOR_REG_OFST         (0x0C)              /**< (DIVAS_DIVISOR) Divisor Offset */
#define DIVAS_RESULT_REG_OFST          (0x10)              /**< (DIVAS_RESULT) Result Offset */
#define DIVAS_REM_REG_OFST             (0x14)              /**< (DIVAS_REM) Remainder Offset */
#define DIVAS_SQRNUM_REG_OFST          (0x18)              /**< (DIVAS_SQRNUM) Square Root Input Offset */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief DIVAS register API structure */
typedef struct
{  /* Divide and Square Root Accelerator */
  __IO  uint8_t                        DIVAS_CTRLA;        /**< Offset: 0x00 (R/W  8) Control */
  __I   uint8_t                        Reserved1[0x03];
  __IO  uint8_t                        DIVAS_STATUS;       /**< Offset: 0x04 (R/W  8) Status */
  __I   uint8_t                        Reserved2[0x03];
  __IO  uint32_t                       DIVAS_DIVIDEND;     /**< Offset: 0x08 (R/W  32) Dividend */
  __IO  uint32_t                       DIVAS_DIVISOR;      /**< Offset: 0x0C (R/W  32) Divisor */
  __I   uint32_t                       DIVAS_RESULT;       /**< Offset: 0x10 (R/   32) Result */
  __I   uint32_t                       DIVAS_REM;          /**< Offset: 0x14 (R/   32) Remainder */
  __IO  uint32_t                       DIVAS_SQRNUM;       /**< Offset: 0x18 (R/W  32) Square Root Input */
} divas_registers_t;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* _SAMC21_DIVAS_COMPONENT_H_ */
