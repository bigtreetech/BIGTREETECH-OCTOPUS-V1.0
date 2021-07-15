/**
 * \brief Header file for ATSAMC21N18A
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
#ifndef _SAMC21N18A_H_
#define _SAMC21N18A_H_

// Header version uses Semantic Versioning 2.0.0 (https://semver.org/)
#define HEADER_FORMAT_VERSION "2.0.0"

#define HEADER_FORMAT_VERSION_MAJOR (2)
#define HEADER_FORMAT_VERSION_MINOR (0)

/** \addtogroup SAMC21N18A_definitions SAMC21N18A definitions
  This file defines all structures and symbols for SAMC21N18A:
    - registers and bitfields
    - peripheral base address
    - peripheral ID
    - PIO definitions
 *  @{
 */

#ifdef __cplusplus
 extern "C" {
#endif

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  include <stdint.h>
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#if !defined(SKIP_INTEGER_LITERALS)
#  if defined(_U_) || defined(_L_) || defined(_UL_)
#    error "Integer Literals macros already defined elsewhere"
#  endif

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/* Macros that deal with adding suffixes to integer literal constants for C/C++ */
#  define _U_(x) (x ## U)    /**< C code: Unsigned integer literal constant value */
#  define _L_(x) (x ## L)    /**< C code: Long integer literal constant value */
#  define _UL_(x) (x ## UL)  /**< C code: Unsigned Long integer literal constant value */

#else /* Assembler */

#  define _U_(x) x    /**< Assembler: Unsigned integer literal constant value */
#  define _L_(x) x    /**< Assembler: Long integer literal constant value */
#  define _UL_(x) x   /**< Assembler: Unsigned Long integer literal constant value */
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* SKIP_INTEGER_LITERALS */
/** @}  end of Atmel Global Defines */

/* ************************************************************************** */
/*   CMSIS DEFINITIONS FOR SAMC21N18A                                         */
/* ************************************************************************** */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** Interrupt Number Definition */
typedef enum IRQn
{
/******  CORTEX-M0PLUS Processor Exceptions Numbers ******************************/
  Reset_IRQn                = -15, /**< -15 Reset Vector, invoked on Power up and warm reset */
  NonMaskableInt_IRQn       = -14, /**< -14 Non maskable Interrupt, cannot be stopped or preempted */
  HardFault_IRQn            = -13, /**< -13 Hard Fault, all classes of Fault    */
  SVCall_IRQn               =  -5, /**< -5  System Service Call via SVC instruction */
  PendSV_IRQn               =  -2, /**< -2  Pendable request for system service */
  SysTick_IRQn              =  -1, /**< -1  System Tick Timer                   */
/******  SAMC21N18A specific Interrupt Numbers ***********************************/
  MCLK_IRQn                 =   0, /**< 0   Shared between MCLK OSCCTRL OSC32KCTRL PAC PM SUPC (MCLK) */
  OSCCTRL_IRQn              =   0, /**< 0   Shared between MCLK OSCCTRL OSC32KCTRL PAC PM SUPC (OSCCTRL) */
  OSC32KCTRL_IRQn           =   0, /**< 0   Shared between MCLK OSCCTRL OSC32KCTRL PAC PM SUPC (OSC32KCTRL) */
  PAC_IRQn                  =   0, /**< 0   Shared between MCLK OSCCTRL OSC32KCTRL PAC PM SUPC (PAC) */
  PM_IRQn                   =   0, /**< 0   Shared between MCLK OSCCTRL OSC32KCTRL PAC PM SUPC (PM) */
  SUPC_IRQn                 =   0, /**< 0   Shared between MCLK OSCCTRL OSC32KCTRL PAC PM SUPC (SUPC) */
  WDT_IRQn                  =   1, /**< 1   Watchdog Timer (WDT)                */
  RTC_IRQn                  =   2, /**< 2   Real-Time Counter (RTC)             */
  EIC_IRQn                  =   3, /**< 3   External Interrupt Controller (EIC) */
  FREQM_IRQn                =   4, /**< 4   Frequency Meter (FREQM)             */
  TSENS_IRQn                =   5, /**< 5   Temperature Sensor (TSENS)          */
  NVMCTRL_IRQn              =   6, /**< 6   Non-Volatile Memory Controller (NVMCTRL) */
  DMAC_IRQn                 =   7, /**< 7   Direct Memory Access Controller (DMAC) */
  EVSYS_IRQn                =   8, /**< 8   Event System Interface (EVSYS)      */
  SERCOM0_IRQn              =   9, /**< 9   Shared between SERCOM0 SERCOM6 (SERCOM0) */
  SERCOM6_IRQn              =   9, /**< 9   Shared between SERCOM0 SERCOM6 (SERCOM6) */
  SERCOM1_IRQn              =  10, /**< 10  Shared between SERCOM1 SERCOM7 (SERCOM1) */
  SERCOM7_IRQn              =  10, /**< 10  Shared between SERCOM1 SERCOM7 (SERCOM7) */
  SERCOM2_IRQn              =  11, /**< 11  Serial Communication Interface (SERCOM2) */
  SERCOM3_IRQn              =  12, /**< 12  Serial Communication Interface (SERCOM3) */
  SERCOM4_IRQn              =  13, /**< 13  Serial Communication Interface (SERCOM4) */
  SERCOM5_IRQn              =  14, /**< 14  Serial Communication Interface (SERCOM5) */
  CAN0_IRQn                 =  15, /**< 15  Control Area Network (CAN0)         */
  CAN1_IRQn                 =  16, /**< 16  Control Area Network (CAN1)         */
  TCC0_IRQn                 =  17, /**< 17  Timer Counter Control (TCC0)        */
  TCC1_IRQn                 =  18, /**< 18  Timer Counter Control (TCC1)        */
  TCC2_IRQn                 =  19, /**< 19  Timer Counter Control (TCC2)        */
  TC0_IRQn                  =  20, /**< 20  Shared between TC0 TC5 (TC0)        */
  TC5_IRQn                  =  20, /**< 20  Shared between TC0 TC5 (TC5)        */
  TC1_IRQn                  =  21, /**< 21  Shared between TC1 TC6 (TC1)        */
  TC6_IRQn                  =  21, /**< 21  Shared between TC1 TC6 (TC6)        */
  TC2_IRQn                  =  22, /**< 22  Shared between TC2 TC7 (TC2)        */
  TC7_IRQn                  =  22, /**< 22  Shared between TC2 TC7 (TC7)        */
  TC3_IRQn                  =  23, /**< 23  Basic Timer Counter (TC3)           */
  TC4_IRQn                  =  24, /**< 24  Basic Timer Counter (TC4)           */
  ADC0_IRQn                 =  25, /**< 25  Analog Digital Converter (ADC0)     */
  ADC1_IRQn                 =  26, /**< 26  Analog Digital Converter (ADC1)     */
  AC_IRQn                   =  27, /**< 27  Analog Comparators (AC)             */
  DAC_IRQn                  =  28, /**< 28  Digital Analog Converter (DAC)      */
  SDADC_IRQn                =  29, /**< 29  Sigma-Delta Analog Digital Converter (SDADC) */
  PTC_IRQn                  =  30, /**< 30  Peripheral Touch Controller (PTC)   */

  PERIPH_MAX_IRQn           =  30  /**< Max peripheral ID */
} IRQn_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct _DeviceVectors
{
  /* Stack pointer */
  void* pvStack;
  /* Cortex-M handlers */
  void* pfnReset_Handler;                        /* -15 Reset Vector, invoked on Power up and warm reset */
  void* pfnNonMaskableInt_Handler;               /* -14 Non maskable Interrupt, cannot be stopped or preempted */
  void* pfnHardFault_Handler;                    /* -13 Hard Fault, all classes of Fault */
  void* pvReservedC12;
  void* pvReservedC11;
  void* pvReservedC10;
  void* pvReservedC9;
  void* pvReservedC8;
  void* pvReservedC7;
  void* pvReservedC6;
  void* pfnSVCall_Handler;                       /*  -5 System Service Call via SVC instruction */
  void* pvReservedC4;
  void* pvReservedC3;
  void* pfnPendSV_Handler;                       /*  -2 Pendable request for system service */
  void* pfnSysTick_Handler;                      /*  -1 System Tick Timer */

  /* Peripheral handlers */
  void* pfnSYSTEM_Handler;                       /*   0 System peripherals shared interrupt (MCLK OSCCTRL OSC32KCTRL PAC PM SUPC) */
  void* pfnWDT_Handler;                          /*   1 Watchdog Timer (WDT) */
  void* pfnRTC_Handler;                          /*   2 Real-Time Counter (RTC) */
  void* pfnEIC_Handler;                          /*   3 External Interrupt Controller (EIC) */
  void* pfnFREQM_Handler;                        /*   4 Frequency Meter (FREQM) */
  void* pfnTSENS_Handler;                        /*   5 Temperature Sensor (TSENS) */
  void* pfnNVMCTRL_Handler;                      /*   6 Non-Volatile Memory Controller (NVMCTRL) */
  void* pfnDMAC_Handler;                         /*   7 Direct Memory Access Controller (DMAC) */
  void* pfnEVSYS_Handler;                        /*   8 Event System Interface (EVSYS) */
  void* pfnSERCOM0_6_Handler;                    /*   9 Serial Communication Interface 0_6 (SERCOM0 SERCOM6) */
  void* pfnSERCOM1_7_Handler;                    /*  10 Serial Communication Interface 1_7 (SERCOM1 SERCOM7) */
  void* pfnSERCOM2_Handler;                      /*  11 Serial Communication Interface (SERCOM2) */
  void* pfnSERCOM3_Handler;                      /*  12 Serial Communication Interface (SERCOM3) */
  void* pfnSERCOM4_Handler;                      /*  13 Serial Communication Interface (SERCOM4) */
  void* pfnSERCOM5_Handler;                      /*  14 Serial Communication Interface (SERCOM5) */
  void* pfnCAN0_Handler;                         /*  15 Control Area Network (CAN0) */
  void* pfnCAN1_Handler;                         /*  16 Control Area Network (CAN1) */
  void* pfnTCC0_Handler;                         /*  17 Timer Counter Control (TCC0) */
  void* pfnTCC1_Handler;                         /*  18 Timer Counter Control (TCC1) */
  void* pfnTCC2_Handler;                         /*  19 Timer Counter Control (TCC2) */
  void* pfnTC0_5_Handler;                        /*  20 Timer/Counter 0_5 (TC0 TC5) */
  void* pfnTC1_6_Handler;                        /*  21 Timer/Counter 1_6 (TC1 TC6) */
  void* pfnTC2_7_Handler;                        /*  22 Timer/Counter 2_7 (TC2 TC7) */
  void* pfnTC3_Handler;                          /*  23 Basic Timer Counter (TC3) */
  void* pfnTC4_Handler;                          /*  24 Basic Timer Counter (TC4) */
  void* pfnADC0_Handler;                         /*  25 Analog Digital Converter (ADC0) */
  void* pfnADC1_Handler;                         /*  26 Analog Digital Converter (ADC1) */
  void* pfnAC_Handler;                           /*  27 Analog Comparators (AC) */
  void* pfnDAC_Handler;                          /*  28 Digital Analog Converter (DAC) */
  void* pfnSDADC_Handler;                        /*  29 Sigma-Delta Analog Digital Converter (SDADC) */
  void* pfnPTC_Handler;                          /*  30 Peripheral Touch Controller (PTC) */
} DeviceVectors;

#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#if !defined DONT_USE_PREDEFINED_CORE_HANDLERS
/* CORTEX-M0PLUS exception handlers */
void Reset_Handler                 ( void );
void NonMaskableInt_Handler        ( void );
void HardFault_Handler             ( void );
void SVCall_Handler                ( void );
void PendSV_Handler                ( void );
void SysTick_Handler               ( void );
#endif /* DONT_USE_PREDEFINED_CORE_HANDLERS */

#if !defined DONT_USE_PREDEFINED_PERIPHERALS_HANDLERS
/* Peripherals interrupt handlers */
void SYSTEM_Handler                ( void );
void WDT_Handler                   ( void );
void RTC_Handler                   ( void );
void EIC_Handler                   ( void );
void FREQM_Handler                 ( void );
void TSENS_Handler                 ( void );
void NVMCTRL_Handler               ( void );
void DMAC_Handler                  ( void );
void EVSYS_Handler                 ( void );
void SERCOM0_6_Handler             ( void );
void SERCOM1_7_Handler             ( void );
void SERCOM2_Handler               ( void );
void SERCOM3_Handler               ( void );
void SERCOM4_Handler               ( void );
void SERCOM5_Handler               ( void );
void CAN0_Handler                  ( void );
void CAN1_Handler                  ( void );
void TCC0_Handler                  ( void );
void TCC1_Handler                  ( void );
void TCC2_Handler                  ( void );
void TC0_5_Handler                 ( void );
void TC1_6_Handler                 ( void );
void TC2_7_Handler                 ( void );
void TC3_Handler                   ( void );
void TC4_Handler                   ( void );
void ADC0_Handler                  ( void );
void ADC1_Handler                  ( void );
void AC_Handler                    ( void );
void DAC_Handler                   ( void );
void SDADC_Handler                 ( void );
void PTC_Handler                   ( void );
#endif /* DONT_USE_PREDEFINED_PERIPHERALS_HANDLERS */
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/*
 * \brief Configuration of the CORTEX-M0PLUS Processor and Core Peripherals
 */
#define __MPU_PRESENT                  1 /**< MPU present or not                                                        */
#define __NVIC_PRIO_BITS               2 /**< Number of Bits used for Priority Levels                                   */
#define __VTOR_PRESENT                 1 /**< Vector Table Offset Register present or not                               */
#define __Vendor_SysTickConfig         0 /**< Set to 1 if different SysTick Config is used                              */
#define __ARCH_ARM                     1
#define __ARCH_ARM_CORTEX_M            1
#define __DEVICE_IS_SAM                1

/*
 * \brief CMSIS includes
 */
#include "core_cm0plus.h"
#if defined USE_CMSIS_INIT
#include "system_samc21.h"
#endif /* USE_CMSIS_INIT */

/** \defgroup SAMC21N18A_api Peripheral Software API
 *  @{
 */

/* ************************************************************************** */
/**  SOFTWARE PERIPHERAL API DEFINITION FOR SAMC21N18A                        */
/* ************************************************************************** */
#include "component/ac.h"
#include "component/adc.h"
#include "component/can.h"
#include "component/ccl.h"
#include "component/dac.h"
#include "component/divas.h"
#include "component/dmac.h"
#include "component/dsu.h"
#include "component/eic.h"
#include "component/evsys.h"
#include "component/freqm.h"
#include "component/gclk.h"
#include "component/hmatrixb.h"
#include "component/mclk.h"
#include "component/mtb.h"
#include "component/nvmctrl.h"
#include "component/oscctrl.h"
#include "component/osc32kctrl.h"
#include "component/pac.h"
#include "component/pm.h"
#include "component/port.h"
#include "component/ptc.h"
#include "component/rstc.h"
#include "component/rtc.h"
#include "component/sdadc.h"
#include "component/sercom.h"
#include "component/supc.h"
#include "component/tc.h"
#include "component/tcc.h"
#include "component/tsens.h"
#include "component/wdt.h"
/** @}  end of Peripheral Software API */

/** \addtogroup SAMC21N18A_id Peripheral Ids Definitions
 *  @{
 */

/* ************************************************************************** */
/*  PERIPHERAL ID DEFINITIONS FOR SAMC21N18A                                  */
/* ************************************************************************** */
#define ID_PAC           (  0) /**< \brief Peripheral Access Controller (PAC) */
#define ID_PM            (  1) /**< \brief Power Manager (PM) */
#define ID_MCLK          (  2) /**< \brief Main Clock (MCLK) */
#define ID_RSTC          (  3) /**< \brief Reset Controller (RSTC) */
#define ID_OSCCTRL       (  4) /**< \brief Oscillators Control (OSCCTRL) */
#define ID_OSC32KCTRL    (  5) /**< \brief 32k Oscillators Control (OSC32KCTRL) */
#define ID_SUPC          (  6) /**< \brief Supply Controller (SUPC) */
#define ID_GCLK          (  7) /**< \brief Generic Clock Generator (GCLK) */
#define ID_WDT           (  8) /**< \brief Watchdog Timer (WDT) */
#define ID_RTC           (  9) /**< \brief Real-Time Counter (RTC) */
#define ID_EIC           ( 10) /**< \brief External Interrupt Controller (EIC) */
#define ID_FREQM         ( 11) /**< \brief Frequency Meter (FREQM) */
#define ID_TSENS         ( 12) /**< \brief Temperature Sensor (TSENS) */
#define ID_PORT          ( 32) /**< \brief Port Module (PORT) */
#define ID_DSU           ( 33) /**< \brief Device Service Unit (DSU) */
#define ID_NVMCTRL       ( 34) /**< \brief Non-Volatile Memory Controller (NVMCTRL) */
#define ID_DMAC          ( 35) /**< \brief Direct Memory Access Controller (DMAC) */
#define ID_MTB           ( 36) /**< \brief Cortex-M0+ Micro-Trace Buffer (MTB) */
#define ID_HMATRIXHS     ( 37) /**< \brief HSB Matrix (HMATRIXHS) */
#define ID_EVSYS         ( 64) /**< \brief Event System Interface (EVSYS) */
#define ID_SERCOM0       ( 65) /**< \brief Serial Communication Interface (SERCOM0) */
#define ID_SERCOM1       ( 66) /**< \brief Serial Communication Interface (SERCOM1) */
#define ID_SERCOM2       ( 67) /**< \brief Serial Communication Interface (SERCOM2) */
#define ID_SERCOM3       ( 68) /**< \brief Serial Communication Interface (SERCOM3) */
#define ID_SERCOM4       ( 69) /**< \brief Serial Communication Interface (SERCOM4) */
#define ID_SERCOM5       ( 70) /**< \brief Serial Communication Interface (SERCOM5) */
#define ID_CAN0          ( 71) /**< \brief Control Area Network (CAN0) */
#define ID_CAN1          ( 72) /**< \brief Control Area Network (CAN1) */
#define ID_TCC0          ( 73) /**< \brief Timer Counter Control (TCC0) */
#define ID_TCC1          ( 74) /**< \brief Timer Counter Control (TCC1) */
#define ID_TCC2          ( 75) /**< \brief Timer Counter Control (TCC2) */
#define ID_TC0           ( 76) /**< \brief Basic Timer Counter (TC0) */
#define ID_TC1           ( 77) /**< \brief Basic Timer Counter (TC1) */
#define ID_TC2           ( 78) /**< \brief Basic Timer Counter (TC2) */
#define ID_TC3           ( 79) /**< \brief Basic Timer Counter (TC3) */
#define ID_TC4           ( 80) /**< \brief Basic Timer Counter (TC4) */
#define ID_ADC0          ( 81) /**< \brief Analog Digital Converter (ADC0) */
#define ID_ADC1          ( 82) /**< \brief Analog Digital Converter (ADC1) */
#define ID_SDADC         ( 83) /**< \brief Sigma-Delta Analog Digital Converter (SDADC) */
#define ID_AC            ( 84) /**< \brief Analog Comparators (AC) */
#define ID_DAC           ( 85) /**< \brief Digital Analog Converter (DAC) */
#define ID_PTC           ( 86) /**< \brief Peripheral Touch Controller (PTC) */
#define ID_CCL           ( 87) /**< \brief Configurable Custom Logic (CCL) */
#define ID_SERCOM6       ( 96) /**< \brief Serial Communication Interface (SERCOM6) */
#define ID_SERCOM7       ( 97) /**< \brief Serial Communication Interface (SERCOM7) */
#define ID_TC5           ( 98) /**< \brief Basic Timer Counter (TC5) */
#define ID_TC6           ( 99) /**< \brief Basic Timer Counter (TC6) */
#define ID_TC7           (100) /**< \brief Basic Timer Counter (TC7) */

#define ID_PERIPH_MAX    (100) /**< \brief Number of peripheral IDs */
/** @}  end of Peripheral Ids Definitions */

/** \addtogroup SAMC21N18A_base Peripheral Base Address Definitions
 *  @{
 */

/* ************************************************************************** */
/*   REGISTER STRUCTURE ADDRESS DEFINITIONS FOR SAMC21N18A                    */
/* ************************************************************************** */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#define AC_REGS                          ((ac_registers_t*)0x42005000)                 /**< \brief AC Registers Address         */
#define ADC0_REGS                        ((adc_registers_t*)0x42004400)                /**< \brief ADC0 Registers Address       */
#define ADC1_REGS                        ((adc_registers_t*)0x42004800)                /**< \brief ADC1 Registers Address       */
#define CAN0_REGS                        ((can_registers_t*)0x42001c00)                /**< \brief CAN0 Registers Address       */
#define CAN1_REGS                        ((can_registers_t*)0x42002000)                /**< \brief CAN1 Registers Address       */
#define CCL_REGS                         ((ccl_registers_t*)0x42005c00)                /**< \brief CCL Registers Address        */
#define DAC_REGS                         ((dac_registers_t*)0x42005400)                /**< \brief DAC Registers Address        */
#define DIVAS_REGS                       ((divas_registers_t*)0x48000000)              /**< \brief DIVAS Registers Address      */
#define DMAC_REGS                        ((dmac_registers_t*)0x41006000)               /**< \brief DMAC Registers Address       */
#define DSU_REGS                         ((dsu_registers_t*)0x41002000)                /**< \brief DSU Registers Address        */
#define EIC_REGS                         ((eic_registers_t*)0x40002800)                /**< \brief EIC Registers Address        */
#define EVSYS_REGS                       ((evsys_registers_t*)0x42000000)              /**< \brief EVSYS Registers Address      */
#define FREQM_REGS                       ((freqm_registers_t*)0x40002c00)              /**< \brief FREQM Registers Address      */
#define GCLK_REGS                        ((gclk_registers_t*)0x40001c00)               /**< \brief GCLK Registers Address       */
#define HMATRIXHS_REGS                   ((hmatrixb_registers_t*)0x4100a000)           /**< \brief HMATRIXHS Registers Address  */
#define MCLK_REGS                        ((mclk_registers_t*)0x40000800)               /**< \brief MCLK Registers Address       */
#define MTB_REGS                         ((mtb_registers_t*)0x41008000)                /**< \brief MTB Registers Address        */
#define NVMCTRL_REGS                     ((nvmctrl_registers_t*)0x41004000)            /**< \brief NVMCTRL Registers Address    */
#define OSCCTRL_REGS                     ((oscctrl_registers_t*)0x40001000)            /**< \brief OSCCTRL Registers Address    */
#define OSC32KCTRL_REGS                  ((osc32kctrl_registers_t*)0x40001400)         /**< \brief OSC32KCTRL Registers Address */
#define PAC_REGS                         ((pac_registers_t*)0x40000000)                /**< \brief PAC Registers Address        */
#define PM_REGS                          ((pm_registers_t*)0x40000400)                 /**< \brief PM Registers Address         */
#define PORT_REGS                        ((port_registers_t*)0x41000000)               /**< \brief PORT Registers Address       */
#define PORT_IOBUS_REGS                  ((port_registers_t*)0x60000000)               /**< \brief PORT Registers Address       */
#define PTC_REGS                         ((ptc_registers_t*)0x42005800)                /**< \brief PTC Registers Address        */
#define RSTC_REGS                        ((rstc_registers_t*)0x40000c00)               /**< \brief RSTC Registers Address       */
#define RTC_REGS                         ((rtc_registers_t*)0x40002400)                /**< \brief RTC Registers Address        */
#define SDADC_REGS                       ((sdadc_registers_t*)0x42004c00)              /**< \brief SDADC Registers Address      */
#define SERCOM0_REGS                     ((sercom_registers_t*)0x42000400)             /**< \brief SERCOM0 Registers Address    */
#define SERCOM1_REGS                     ((sercom_registers_t*)0x42000800)             /**< \brief SERCOM1 Registers Address    */
#define SERCOM2_REGS                     ((sercom_registers_t*)0x42000c00)             /**< \brief SERCOM2 Registers Address    */
#define SERCOM3_REGS                     ((sercom_registers_t*)0x42001000)             /**< \brief SERCOM3 Registers Address    */
#define SERCOM4_REGS                     ((sercom_registers_t*)0x42001400)             /**< \brief SERCOM4 Registers Address    */
#define SERCOM5_REGS                     ((sercom_registers_t*)0x42001800)             /**< \brief SERCOM5 Registers Address    */
#define SERCOM6_REGS                     ((sercom_registers_t*)0x43000000)             /**< \brief SERCOM6 Registers Address    */
#define SERCOM7_REGS                     ((sercom_registers_t*)0x43000400)             /**< \brief SERCOM7 Registers Address    */
#define SUPC_REGS                        ((supc_registers_t*)0x40001800)               /**< \brief SUPC Registers Address       */
#define TC0_REGS                         ((tc_registers_t*)0x42003000)                 /**< \brief TC0 Registers Address        */
#define TC1_REGS                         ((tc_registers_t*)0x42003400)                 /**< \brief TC1 Registers Address        */
#define TC2_REGS                         ((tc_registers_t*)0x42003800)                 /**< \brief TC2 Registers Address        */
#define TC3_REGS                         ((tc_registers_t*)0x42003c00)                 /**< \brief TC3 Registers Address        */
#define TC4_REGS                         ((tc_registers_t*)0x42004000)                 /**< \brief TC4 Registers Address        */
#define TC5_REGS                         ((tc_registers_t*)0x43000800)                 /**< \brief TC5 Registers Address        */
#define TC6_REGS                         ((tc_registers_t*)0x43000c00)                 /**< \brief TC6 Registers Address        */
#define TC7_REGS                         ((tc_registers_t*)0x43001000)                 /**< \brief TC7 Registers Address        */
#define TCC0_REGS                        ((tcc_registers_t*)0x42002400)                /**< \brief TCC0 Registers Address       */
#define TCC1_REGS                        ((tcc_registers_t*)0x42002800)                /**< \brief TCC1 Registers Address       */
#define TCC2_REGS                        ((tcc_registers_t*)0x42002c00)                /**< \brief TCC2 Registers Address       */
#define TSENS_REGS                       ((tsens_registers_t*)0x40003000)              /**< \brief TSENS Registers Address      */
#define WDT_REGS                         ((wdt_registers_t*)0x40002000)                /**< \brief WDT Registers Address        */
#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Peripheral Base Address Definitions */

/** \addtogroup SAMC21N18A_base Peripheral Base Address Definitions
 *  @{
 */

/* ************************************************************************** */
/*   BASE ADDRESS DEFINITIONS FOR SAMC21N18A                                  */
/* ************************************************************************** */
#define AC_BASE_ADDRESS                  _UL_(0x42005000)                              /**< \brief AC Base Address */
#define ADC0_BASE_ADDRESS                _UL_(0x42004400)                              /**< \brief ADC0 Base Address */
#define ADC1_BASE_ADDRESS                _UL_(0x42004800)                              /**< \brief ADC1 Base Address */
#define CAN0_BASE_ADDRESS                _UL_(0x42001c00)                              /**< \brief CAN0 Base Address */
#define CAN1_BASE_ADDRESS                _UL_(0x42002000)                              /**< \brief CAN1 Base Address */
#define CCL_BASE_ADDRESS                 _UL_(0x42005c00)                              /**< \brief CCL Base Address */
#define DAC_BASE_ADDRESS                 _UL_(0x42005400)                              /**< \brief DAC Base Address */
#define DIVAS_BASE_ADDRESS               _UL_(0x48000000)                              /**< \brief DIVAS Base Address */
#define DMAC_BASE_ADDRESS                _UL_(0x41006000)                              /**< \brief DMAC Base Address */
#define DSU_BASE_ADDRESS                 _UL_(0x41002000)                              /**< \brief DSU Base Address */
#define EIC_BASE_ADDRESS                 _UL_(0x40002800)                              /**< \brief EIC Base Address */
#define EVSYS_BASE_ADDRESS               _UL_(0x42000000)                              /**< \brief EVSYS Base Address */
#define FREQM_BASE_ADDRESS               _UL_(0x40002c00)                              /**< \brief FREQM Base Address */
#define GCLK_BASE_ADDRESS                _UL_(0x40001c00)                              /**< \brief GCLK Base Address */
#define HMATRIXHS_BASE_ADDRESS           _UL_(0x4100a000)                              /**< \brief HMATRIXHS Base Address */
#define MCLK_BASE_ADDRESS                _UL_(0x40000800)                              /**< \brief MCLK Base Address */
#define MTB_BASE_ADDRESS                 _UL_(0x41008000)                              /**< \brief MTB Base Address */
#define NVMCTRL_BASE_ADDRESS             _UL_(0x41004000)                              /**< \brief NVMCTRL Base Address */
#define OSCCTRL_BASE_ADDRESS             _UL_(0x40001000)                              /**< \brief OSCCTRL Base Address */
#define OSC32KCTRL_BASE_ADDRESS          _UL_(0x40001400)                              /**< \brief OSC32KCTRL Base Address */
#define PAC_BASE_ADDRESS                 _UL_(0x40000000)                              /**< \brief PAC Base Address */
#define PM_BASE_ADDRESS                  _UL_(0x40000400)                              /**< \brief PM Base Address */
#define PORT_BASE_ADDRESS                _UL_(0x41000000)                              /**< \brief PORT Base Address */
#define PORT_IOBUS_BASE_ADDRESS          _UL_(0x60000000)                              /**< \brief PORT Base Address */
#define PTC_BASE_ADDRESS                 _UL_(0x42005800)                              /**< \brief PTC Base Address */
#define RSTC_BASE_ADDRESS                _UL_(0x40000c00)                              /**< \brief RSTC Base Address */
#define RTC_BASE_ADDRESS                 _UL_(0x40002400)                              /**< \brief RTC Base Address */
#define SDADC_BASE_ADDRESS               _UL_(0x42004c00)                              /**< \brief SDADC Base Address */
#define SERCOM0_BASE_ADDRESS             _UL_(0x42000400)                              /**< \brief SERCOM0 Base Address */
#define SERCOM1_BASE_ADDRESS             _UL_(0x42000800)                              /**< \brief SERCOM1 Base Address */
#define SERCOM2_BASE_ADDRESS             _UL_(0x42000c00)                              /**< \brief SERCOM2 Base Address */
#define SERCOM3_BASE_ADDRESS             _UL_(0x42001000)                              /**< \brief SERCOM3 Base Address */
#define SERCOM4_BASE_ADDRESS             _UL_(0x42001400)                              /**< \brief SERCOM4 Base Address */
#define SERCOM5_BASE_ADDRESS             _UL_(0x42001800)                              /**< \brief SERCOM5 Base Address */
#define SERCOM6_BASE_ADDRESS             _UL_(0x43000000)                              /**< \brief SERCOM6 Base Address */
#define SERCOM7_BASE_ADDRESS             _UL_(0x43000400)                              /**< \brief SERCOM7 Base Address */
#define SUPC_BASE_ADDRESS                _UL_(0x40001800)                              /**< \brief SUPC Base Address */
#define TC0_BASE_ADDRESS                 _UL_(0x42003000)                              /**< \brief TC0 Base Address */
#define TC1_BASE_ADDRESS                 _UL_(0x42003400)                              /**< \brief TC1 Base Address */
#define TC2_BASE_ADDRESS                 _UL_(0x42003800)                              /**< \brief TC2 Base Address */
#define TC3_BASE_ADDRESS                 _UL_(0x42003c00)                              /**< \brief TC3 Base Address */
#define TC4_BASE_ADDRESS                 _UL_(0x42004000)                              /**< \brief TC4 Base Address */
#define TC5_BASE_ADDRESS                 _UL_(0x43000800)                              /**< \brief TC5 Base Address */
#define TC6_BASE_ADDRESS                 _UL_(0x43000c00)                              /**< \brief TC6 Base Address */
#define TC7_BASE_ADDRESS                 _UL_(0x43001000)                              /**< \brief TC7 Base Address */
#define TCC0_BASE_ADDRESS                _UL_(0x42002400)                              /**< \brief TCC0 Base Address */
#define TCC1_BASE_ADDRESS                _UL_(0x42002800)                              /**< \brief TCC1 Base Address */
#define TCC2_BASE_ADDRESS                _UL_(0x42002c00)                              /**< \brief TCC2 Base Address */
#define TSENS_BASE_ADDRESS               _UL_(0x40003000)                              /**< \brief TSENS Base Address */
#define WDT_BASE_ADDRESS                 _UL_(0x40002000)                              /**< \brief WDT Base Address */
/** @}  end of Peripheral Base Address Definitions */

/** \addtogroup SAMC21N18A_pio Peripheral Pio Definitions
 *  @{
 */

/* ************************************************************************** */
/*   PIO DEFINITIONS FOR SAMC21N18A                                           */
/* ************************************************************************** */
#include "pio/samc21n18a.h"
/** @}  end of Peripheral Pio Definitions */

/* ************************************************************************** */
/*   MEMORY MAPPING DEFINITIONS FOR SAMC21N18A                                */
/* ************************************************************************** */

#define FLASH_SIZE                     _UL_(0x00040000)    /*  256kB Memory segment type: flash */
#define FLASH_PAGE_SIZE                _UL_(        64)
#define FLASH_NB_OF_PAGES              _UL_(      4096)

#define CAL_SIZE                       _UL_(0x00000008)    /*    0kB Memory segment type: fuses */
#define LOCKBIT_SIZE                   _UL_(0x00000004)    /*    0kB Memory segment type: fuses */
#define OTP1_SIZE                      _UL_(0x00000008)    /*    0kB Memory segment type: fuses */
#define OTP2_SIZE                      _UL_(0x00000008)    /*    0kB Memory segment type: fuses */
#define OTP3_SIZE                      _UL_(0x00000008)    /*    0kB Memory segment type: fuses */
#define OTP4_SIZE                      _UL_(0x00000008)    /*    0kB Memory segment type: fuses */
#define OTP5_SIZE                      _UL_(0x00000008)    /*    0kB Memory segment type: fuses */
#define TEMP_LOG_SIZE                  _UL_(0x00000008)    /*    0kB Memory segment type: fuses */
#define USER_PAGE_SIZE                 _UL_(0x00000100)    /*    0kB Memory segment type: user_page */
#define USER_PAGE_PAGE_SIZE            _UL_(        64)
#define USER_PAGE_NB_OF_PAGES          _UL_(         4)

#define RWW_SIZE                       _UL_(0x00002000)    /*    8kB Memory segment type: flash */
#define RWW_PAGE_SIZE                  _UL_(        64)
#define RWW_NB_OF_PAGES                _UL_(       128)

#define HSRAM_SIZE                     _UL_(0x00008000)    /*   32kB Memory segment type: ram */
#define HPB0_SIZE                      _UL_(0x00004000)    /*   16kB Memory segment type: io */
#define HPB1_SIZE                      _UL_(0x00010000)    /*   64kB Memory segment type: io */
#define HPB2_SIZE                      _UL_(0x00008000)    /*   32kB Memory segment type: io */
#define HPB3_SIZE                      _UL_(0x00008000)    /*   32kB Memory segment type: io */
#define DIVAS_SIZE                     _UL_(0x00000020)    /*    0kB Memory segment type: io */
#define PPB_SIZE                       _UL_(0x00100000)    /* 1024kB Memory segment type: io */
#define SCS_SIZE                       _UL_(0x00001000)    /*    4kB Memory segment type: io */
#define PERIPHERALS_SIZE               _UL_(0x20000000)    /* 524288kB Memory segment type: io */

#define FLASH_ADDR                     _UL_(0x00000000)    /**< FLASH base address (type: flash)*/
#define CAL_ADDR                       _UL_(0x00800000)    /**< CAL base address (type: fuses)*/
#define LOCKBIT_ADDR                   _UL_(0x00802000)    /**< LOCKBIT base address (type: fuses)*/
#define OTP1_ADDR                      _UL_(0x00806000)    /**< OTP1 base address (type: fuses)*/
#define OTP2_ADDR                      _UL_(0x00806008)    /**< OTP2 base address (type: fuses)*/
#define OTP3_ADDR                      _UL_(0x00806010)    /**< OTP3 base address (type: fuses)*/
#define OTP4_ADDR                      _UL_(0x00806018)    /**< OTP4 base address (type: fuses)*/
#define OTP5_ADDR                      _UL_(0x00806020)    /**< OTP5 base address (type: fuses)*/
#define TEMP_LOG_ADDR                  _UL_(0x00806030)    /**< TEMP_LOG base address (type: fuses)*/
#define USER_PAGE_ADDR                 _UL_(0x00804000)    /**< USER_PAGE base address (type: user_page)*/
#define RWW_ADDR                       _UL_(0x00400000)    /**< RWW base address (type: flash)*/
#define HSRAM_ADDR                     _UL_(0x20000000)    /**< HSRAM base address (type: ram)*/
#define HPB0_ADDR                      _UL_(0x40000000)    /**< HPB0 base address (type: io)*/
#define HPB1_ADDR                      _UL_(0x41000000)    /**< HPB1 base address (type: io)*/
#define HPB2_ADDR                      _UL_(0x42000000)    /**< HPB2 base address (type: io)*/
#define HPB3_ADDR                      _UL_(0x43000000)    /**< HPB3 base address (type: io)*/
#define DIVAS_ADDR                     _UL_(0x48000000)    /**< DIVAS base address (type: io)*/
#define PPB_ADDR                       _UL_(0xe0000000)    /**< PPB base address (type: io)*/
#define SCS_ADDR                       _UL_(0xe000e000)    /**< SCS base address (type: io)*/
#define PERIPHERALS_ADDR               _UL_(0x40000000)    /**< PERIPHERALS base address (type: io)*/

/* ************************************************************************** */
/**  DEVICE SIGNATURES FOR SAMC21N18A                                         */
/* ************************************************************************** */
#define DSU_DID                        _UL_(0X11011420)

/* ************************************************************************** */
/**  ELECTRICAL DEFINITIONS FOR SAMC21N18A                                    */
/* ************************************************************************** */

/* ************************************************************************** */
/** Event Generator IDs for SAMC21N18A */
/* ************************************************************************** */
#define EVENT_ID_GEN_OSCCTRL_XOSC_FAIL                    1 /**< ID for OSCCTRL event generator XOSC_FAIL */
#define EVENT_ID_GEN_OSC32KCTRL_XOSC32K_FAIL              2 /**< ID for OSC32KCTRL event generator XOSC32K_FAIL */
#define EVENT_ID_GEN_RTC_CMP_0                            3 /**< ID for RTC event generator CMP_0 */
#define EVENT_ID_GEN_RTC_CMP_1                            4 /**< ID for RTC event generator CMP_1 */
#define EVENT_ID_GEN_RTC_OVF                              5 /**< ID for RTC event generator OVF */
#define EVENT_ID_GEN_RTC_PER_0                            6 /**< ID for RTC event generator PER_0 */
#define EVENT_ID_GEN_RTC_PER_1                            7 /**< ID for RTC event generator PER_1 */
#define EVENT_ID_GEN_RTC_PER_2                            8 /**< ID for RTC event generator PER_2 */
#define EVENT_ID_GEN_RTC_PER_3                            9 /**< ID for RTC event generator PER_3 */
#define EVENT_ID_GEN_RTC_PER_4                           10 /**< ID for RTC event generator PER_4 */
#define EVENT_ID_GEN_RTC_PER_5                           11 /**< ID for RTC event generator PER_5 */
#define EVENT_ID_GEN_RTC_PER_6                           12 /**< ID for RTC event generator PER_6 */
#define EVENT_ID_GEN_RTC_PER_7                           13 /**< ID for RTC event generator PER_7 */
#define EVENT_ID_GEN_EIC_EXTINT_0                        14 /**< ID for EIC event generator EXTINT_0 */
#define EVENT_ID_GEN_EIC_EXTINT_1                        15 /**< ID for EIC event generator EXTINT_1 */
#define EVENT_ID_GEN_EIC_EXTINT_2                        16 /**< ID for EIC event generator EXTINT_2 */
#define EVENT_ID_GEN_EIC_EXTINT_3                        17 /**< ID for EIC event generator EXTINT_3 */
#define EVENT_ID_GEN_EIC_EXTINT_4                        18 /**< ID for EIC event generator EXTINT_4 */
#define EVENT_ID_GEN_EIC_EXTINT_5                        19 /**< ID for EIC event generator EXTINT_5 */
#define EVENT_ID_GEN_EIC_EXTINT_6                        20 /**< ID for EIC event generator EXTINT_6 */
#define EVENT_ID_GEN_EIC_EXTINT_7                        21 /**< ID for EIC event generator EXTINT_7 */
#define EVENT_ID_GEN_EIC_EXTINT_8                        22 /**< ID for EIC event generator EXTINT_8 */
#define EVENT_ID_GEN_EIC_EXTINT_9                        23 /**< ID for EIC event generator EXTINT_9 */
#define EVENT_ID_GEN_EIC_EXTINT_10                       24 /**< ID for EIC event generator EXTINT_10 */
#define EVENT_ID_GEN_EIC_EXTINT_11                       25 /**< ID for EIC event generator EXTINT_11 */
#define EVENT_ID_GEN_EIC_EXTINT_12                       26 /**< ID for EIC event generator EXTINT_12 */
#define EVENT_ID_GEN_EIC_EXTINT_13                       27 /**< ID for EIC event generator EXTINT_13 */
#define EVENT_ID_GEN_EIC_EXTINT_14                       28 /**< ID for EIC event generator EXTINT_14 */
#define EVENT_ID_GEN_EIC_EXTINT_15                       29 /**< ID for EIC event generator EXTINT_15 */
#define EVENT_ID_GEN_TSENS_WINMON                        30 /**< ID for TSENS event generator WINMON */
#define EVENT_ID_GEN_DMAC_CH_0                           31 /**< ID for DMAC event generator CH_0 */
#define EVENT_ID_GEN_DMAC_CH_1                           32 /**< ID for DMAC event generator CH_1 */
#define EVENT_ID_GEN_DMAC_CH_2                           33 /**< ID for DMAC event generator CH_2 */
#define EVENT_ID_GEN_DMAC_CH_3                           34 /**< ID for DMAC event generator CH_3 */
#define EVENT_ID_GEN_TCC0_OVF                            35 /**< ID for TCC0 event generator OVF */
#define EVENT_ID_GEN_TCC0_TRG                            36 /**< ID for TCC0 event generator TRG */
#define EVENT_ID_GEN_TCC0_CNT                            37 /**< ID for TCC0 event generator CNT */
#define EVENT_ID_GEN_TCC0_MC_0                           38 /**< ID for TCC0 event generator MC_0 */
#define EVENT_ID_GEN_TCC0_MC_1                           39 /**< ID for TCC0 event generator MC_1 */
#define EVENT_ID_GEN_TCC0_MC_2                           40 /**< ID for TCC0 event generator MC_2 */
#define EVENT_ID_GEN_TCC0_MC_3                           41 /**< ID for TCC0 event generator MC_3 */
#define EVENT_ID_GEN_TCC1_OVF                            42 /**< ID for TCC1 event generator OVF */
#define EVENT_ID_GEN_TCC1_TRG                            43 /**< ID for TCC1 event generator TRG */
#define EVENT_ID_GEN_TCC1_CNT                            44 /**< ID for TCC1 event generator CNT */
#define EVENT_ID_GEN_TCC1_MC_0                           45 /**< ID for TCC1 event generator MC_0 */
#define EVENT_ID_GEN_TCC1_MC_1                           46 /**< ID for TCC1 event generator MC_1 */
#define EVENT_ID_GEN_TCC2_OVF                            47 /**< ID for TCC2 event generator OVF */
#define EVENT_ID_GEN_TCC2_TRG                            48 /**< ID for TCC2 event generator TRG */
#define EVENT_ID_GEN_TCC2_CNT                            49 /**< ID for TCC2 event generator CNT */
#define EVENT_ID_GEN_TCC2_MC_0                           50 /**< ID for TCC2 event generator MC_0 */
#define EVENT_ID_GEN_TCC2_MC_1                           51 /**< ID for TCC2 event generator MC_1 */
#define EVENT_ID_GEN_TC0_OVF                             52 /**< ID for TC0 event generator OVF */
#define EVENT_ID_GEN_TC0_MC_0                            53 /**< ID for TC0 event generator MC_0 */
#define EVENT_ID_GEN_TC0_MC_1                            54 /**< ID for TC0 event generator MC_1 */
#define EVENT_ID_GEN_TC1_OVF                             55 /**< ID for TC1 event generator OVF */
#define EVENT_ID_GEN_TC1_MC_0                            56 /**< ID for TC1 event generator MC_0 */
#define EVENT_ID_GEN_TC1_MC_1                            57 /**< ID for TC1 event generator MC_1 */
#define EVENT_ID_GEN_TC2_OVF                             58 /**< ID for TC2 event generator OVF */
#define EVENT_ID_GEN_TC2_MC_0                            59 /**< ID for TC2 event generator MC_0 */
#define EVENT_ID_GEN_TC2_MC_1                            60 /**< ID for TC2 event generator MC_1 */
#define EVENT_ID_GEN_TC3_OVF                             61 /**< ID for TC3 event generator OVF */
#define EVENT_ID_GEN_TC3_MC_0                            62 /**< ID for TC3 event generator MC_0 */
#define EVENT_ID_GEN_TC3_MC_1                            63 /**< ID for TC3 event generator MC_1 */
#define EVENT_ID_GEN_TC4_OVF                             64 /**< ID for TC4 event generator OVF */
#define EVENT_ID_GEN_TC4_MC_0                            65 /**< ID for TC4 event generator MC_0 */
#define EVENT_ID_GEN_TC4_MC_1                            66 /**< ID for TC4 event generator MC_1 */
#define EVENT_ID_GEN_ADC0_RESRDY                         67 /**< ID for ADC0 event generator RESRDY */
#define EVENT_ID_GEN_ADC0_WINMON                         68 /**< ID for ADC0 event generator WINMON */
#define EVENT_ID_GEN_ADC1_RESRDY                         69 /**< ID for ADC1 event generator RESRDY */
#define EVENT_ID_GEN_ADC1_WINMON                         70 /**< ID for ADC1 event generator WINMON */
#define EVENT_ID_GEN_SDADC_RESRDY                        71 /**< ID for SDADC event generator RESRDY */
#define EVENT_ID_GEN_SDADC_WINMON                        72 /**< ID for SDADC event generator WINMON */
#define EVENT_ID_GEN_AC_COMP_0                           73 /**< ID for AC event generator COMP_0 */
#define EVENT_ID_GEN_AC_COMP_1                           74 /**< ID for AC event generator COMP_1 */
#define EVENT_ID_GEN_AC_COMP_2                           75 /**< ID for AC event generator COMP_2 */
#define EVENT_ID_GEN_AC_COMP_3                           76 /**< ID for AC event generator COMP_3 */
#define EVENT_ID_GEN_AC_WIN_0                            77 /**< ID for AC event generator WIN_0 */
#define EVENT_ID_GEN_AC_WIN_1                            78 /**< ID for AC event generator WIN_1 */
#define EVENT_ID_GEN_DAC_EMPTY                           79 /**< ID for DAC event generator EMPTY */
#define EVENT_ID_GEN_CCL_LUTOUT_0                        82 /**< ID for CCL event generator LUTOUT_0 */
#define EVENT_ID_GEN_CCL_LUTOUT_1                        83 /**< ID for CCL event generator LUTOUT_1 */
#define EVENT_ID_GEN_CCL_LUTOUT_2                        84 /**< ID for CCL event generator LUTOUT_2 */
#define EVENT_ID_GEN_CCL_LUTOUT_3                        85 /**< ID for CCL event generator LUTOUT_3 */
#define EVENT_ID_GEN_PAC_ACCERR                          86 /**< ID for PAC event generator ACCERR */
#define EVENT_ID_GEN_TC5_OVF                             88 /**< ID for TC5 event generator OVF */
#define EVENT_ID_GEN_TC5_MC_0                            89 /**< ID for TC5 event generator MC_0 */
#define EVENT_ID_GEN_TC5_MC_1                            90 /**< ID for TC5 event generator MC_1 */
#define EVENT_ID_GEN_TC6_OVF                             91 /**< ID for TC6 event generator OVF */
#define EVENT_ID_GEN_TC6_MC_0                            92 /**< ID for TC6 event generator MC_0 */
#define EVENT_ID_GEN_TC6_MC_1                            93 /**< ID for TC6 event generator MC_1 */
#define EVENT_ID_GEN_TC7_OVF                             94 /**< ID for TC7 event generator OVF */
#define EVENT_ID_GEN_TC7_MC_0                            95 /**< ID for TC7 event generator MC_0 */
#define EVENT_ID_GEN_TC7_MC_1                            96 /**< ID for TC7 event generator MC_1 */

/* ************************************************************************** */
/** Event User IDs for SAMC21N18A */
/* ************************************************************************** */
#define EVENT_ID_USER_TSENS_START                         0 /**< ID for TSENS event user START */
#define EVENT_ID_USER_PORT_EV_0                           1 /**< ID for PORT event user EV_0 */
#define EVENT_ID_USER_PORT_EV_1                           2 /**< ID for PORT event user EV_1 */
#define EVENT_ID_USER_PORT_EV_2                           3 /**< ID for PORT event user EV_2 */
#define EVENT_ID_USER_PORT_EV_3                           4 /**< ID for PORT event user EV_3 */
#define EVENT_ID_USER_DMAC_CH_0                           5 /**< ID for DMAC event user CH_0 */
#define EVENT_ID_USER_DMAC_CH_1                           6 /**< ID for DMAC event user CH_1 */
#define EVENT_ID_USER_DMAC_CH_2                           7 /**< ID for DMAC event user CH_2 */
#define EVENT_ID_USER_DMAC_CH_3                           8 /**< ID for DMAC event user CH_3 */
#define EVENT_ID_USER_TCC0_EV_0                           9 /**< ID for TCC0 event user EV_0 */
#define EVENT_ID_USER_TCC0_EV_1                          10 /**< ID for TCC0 event user EV_1 */
#define EVENT_ID_USER_TCC0_MC_0                          11 /**< ID for TCC0 event user MC_0 */
#define EVENT_ID_USER_TCC0_MC_1                          12 /**< ID for TCC0 event user MC_1 */
#define EVENT_ID_USER_TCC0_MC_2                          13 /**< ID for TCC0 event user MC_2 */
#define EVENT_ID_USER_TCC0_MC_3                          14 /**< ID for TCC0 event user MC_3 */
#define EVENT_ID_USER_TCC1_EV_0                          15 /**< ID for TCC1 event user EV_0 */
#define EVENT_ID_USER_TCC1_EV_1                          16 /**< ID for TCC1 event user EV_1 */
#define EVENT_ID_USER_TCC1_MC_0                          17 /**< ID for TCC1 event user MC_0 */
#define EVENT_ID_USER_TCC1_MC_1                          18 /**< ID for TCC1 event user MC_1 */
#define EVENT_ID_USER_TCC2_EV_0                          19 /**< ID for TCC2 event user EV_0 */
#define EVENT_ID_USER_TCC2_EV_1                          20 /**< ID for TCC2 event user EV_1 */
#define EVENT_ID_USER_TCC2_MC_0                          21 /**< ID for TCC2 event user MC_0 */
#define EVENT_ID_USER_TCC2_MC_1                          22 /**< ID for TCC2 event user MC_1 */
#define EVENT_ID_USER_TC0_EVU                            23 /**< ID for TC0 event user EVU */
#define EVENT_ID_USER_TC1_EVU                            24 /**< ID for TC1 event user EVU */
#define EVENT_ID_USER_TC2_EVU                            25 /**< ID for TC2 event user EVU */
#define EVENT_ID_USER_TC3_EVU                            26 /**< ID for TC3 event user EVU */
#define EVENT_ID_USER_TC4_EVU                            27 /**< ID for TC4 event user EVU */
#define EVENT_ID_USER_ADC0_START                         28 /**< ID for ADC0 event user START */
#define EVENT_ID_USER_ADC0_SYNC                          29 /**< ID for ADC0 event user SYNC */
#define EVENT_ID_USER_ADC1_START                         30 /**< ID for ADC1 event user START */
#define EVENT_ID_USER_ADC1_SYNC                          31 /**< ID for ADC1 event user SYNC */
#define EVENT_ID_USER_SDADC_START                        32 /**< ID for SDADC event user START */
#define EVENT_ID_USER_SDADC_FLUSH                        33 /**< ID for SDADC event user FLUSH */
#define EVENT_ID_USER_AC_SOC_0                           34 /**< ID for AC event user SOC_0 */
#define EVENT_ID_USER_AC_SOC_1                           35 /**< ID for AC event user SOC_1 */
#define EVENT_ID_USER_AC_SOC_2                           36 /**< ID for AC event user SOC_2 */
#define EVENT_ID_USER_AC_SOC_3                           37 /**< ID for AC event user SOC_3 */
#define EVENT_ID_USER_DAC_START                          38 /**< ID for DAC event user START */
#define EVENT_ID_USER_CCL_LUTIN_0                        40 /**< ID for CCL event user LUTIN_0 */
#define EVENT_ID_USER_CCL_LUTIN_1                        41 /**< ID for CCL event user LUTIN_1 */
#define EVENT_ID_USER_CCL_LUTIN_2                        42 /**< ID for CCL event user LUTIN_2 */
#define EVENT_ID_USER_CCL_LUTIN_3                        43 /**< ID for CCL event user LUTIN_3 */
#define EVENT_ID_USER_MTB_START                          45 /**< ID for MTB event user START */
#define EVENT_ID_USER_MTB_STOP                           46 /**< ID for MTB event user STOP */
#define EVENT_ID_USER_TC5_EVU                            47 /**< ID for TC5 event user EVU */
#define EVENT_ID_USER_TC6_EVU                            48 /**< ID for TC6 event user EVU */
#define EVENT_ID_USER_TC7_EVU                            49 /**< ID for TC7 event user EVU */

#ifdef __cplusplus
}
#endif

/** @}  end of SAMC21N18A definitions */


#endif /* _SAMC21N18A_H_ */

