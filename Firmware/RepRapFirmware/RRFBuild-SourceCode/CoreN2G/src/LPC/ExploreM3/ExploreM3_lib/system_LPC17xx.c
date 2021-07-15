/**************************************************************************//**
 * @file     system_LPC17xx.c
 * @brief    CMSIS Cortex-M3 Device System Source File for
 *           NXP LPC17xx Device Series
 * @version  V1.11
 * @date     21. June 2011
 *
 * @note
 * Copyright (C) 2009-2011 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M
 * processor based microcontrollers.  This file can be freely distributed
 * within development tools that are supporting such ARM based processors.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/


#include <stdint.h>
#include "chip.h"
#include "iap.h"

//SD:: re-written to use LPCOpen functions

const uint32_t OscRateIn = 12000000; //12MHz crystal
const uint32_t RTCOscRateIn = 32768;
uint32_t SystemCoreClock; //global variable that holds the system core clock


// detect 17x[4-8] (100MHz) or 17x9 (120MHz)
static int can_120MHz()
{
    //Read the part numbers from IAP
    //LPC1769 = 0x26113F37
    //LPC1768 = 0x26013F37
    
    return Chip_IAP_ReadPID() & 0x00100000;
}


/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit (void)
{

    //Enable the Crystal
    Chip_Clock_EnableCrystal();
    while(!Chip_Clock_IsCrystalEnabled()) {}

    /* Disconnect the Main PLL if it is connected already */
    if (Chip_Clock_IsMainPLLConnected())
    {
       Chip_Clock_DisablePLL(SYSCTL_MAIN_PLL, SYSCTL_PLL_CONNECT);
    }

    /* Disable the PLL if it is enabled */
    if (Chip_Clock_IsMainPLLEnabled())
    {
       Chip_Clock_DisablePLL(SYSCTL_MAIN_PLL, SYSCTL_PLL_ENABLE);
    }

    
      
    /*
     - From Errata sheet Rev. 10.4 — 17 March 2020
     If the Peripheral Clock Registers (PCLKSEL0 and PCLKSEL1) are set or changed after PLL0
     is enabled and connected, the value written into the Peripheral Clock Selection Registers
     may not take effect. It is not possible to change the Peripheral Clock Selection settings
     once PLL0 is enabled and connected.
     */
    
    //Set all peripheral clocks to use cclk/4 by default
    LPC_SYSCTL->PCLKSEL[0]  = 0;
    LPC_SYSCTL->PCLKSEL[1]  = 0;
    
    //Set desired clocks to cclk/1
    Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_SSP0, SYSCTL_CLKDIV_1);
    Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_SSP1, SYSCTL_CLKDIV_1);
    Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_SSP0, SYSCTL_PCLK_UART0);
    Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_SSP0, SYSCTL_PCLK_UART1);
    Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_SSP0, SYSCTL_PCLK_UART2);
    Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_SSP0, SYSCTL_PCLK_UART3);
    Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_SSP0, SYSCTL_PCLK_RIT);
    
   
  /*
   * PLL0 MUST be 275 - 550MHz
   *
   * PLL0 = Fin * M * 2 / N
   *
   * Fcpu = PLL0 / D
   *
   * PLL0CFG = (M - 1) + ((N - 1) << 16)
   * CCLKCFG = D - 1
   *
   * Common combinations (assuming 12MHz crystal):
   *
   * |   Fcpu |--|   Fin |  M | N |   PLL0 | D | PLL0CFG | CCLKCFG |
   *    96MHz :2*  12MHz * 12 / 1 = 288MHz / 3   0x0000B       0x2
   *   100MHz :2*  12MHz * 25 / 2 = 300MHz / 3   0x10018       0x2
   *   120MHz :2*  12MHz * 15 / 1 = 360MHz / 3   0x0000E       0x2
   *
   */

    Chip_Clock_SetCPUClockDiv(0);
    Chip_Clock_SetMainPLLSource(SYSCTL_PLLCLKSRC_MAINOSC); //Select Main Oscillator as PLL0 Source


    if(can_120MHz())
    {
        Chip_Clock_SetupPLL(SYSCTL_MAIN_PLL, 14, 0); //PLL0, msel = (M-1), psel = (N-1)
    }
    else
    {
        Chip_Clock_SetupPLL(SYSCTL_MAIN_PLL, 24, 1); //PLL0, msel = (M-1), psel = (N-1)
    }
  
    Chip_Clock_EnablePLL(SYSCTL_MAIN_PLL, SYSCTL_PLL_ENABLE);

    Chip_Clock_SetCPUClockDiv(2); //clksel = (D-1)

    while (!Chip_Clock_IsMainPLLLocked()) {} /* Wait for the PLL to Lock */
    Chip_Clock_EnablePLL(SYSCTL_MAIN_PLL, SYSCTL_PLL_CONNECT); //PLL0 connect
    while(!Chip_Clock_IsMainPLLConnected() && !Chip_Clock_IsMainPLLEnabled()); //wait for PLL0 connect and enable
    
  /*
   * USBCLK = Fin * M, where M is (1..32)
   *
   * we need a USBCLK of 48MHz, so given a 12MHz crystal, M must be 4
   *
   * PLL1 = USBCLK * 2 * P, where P is one of (1, 2, 4, 8)
   *
   * PLL1 MUST be 156 to 320MHz.
   * P=2 gives 192MHz, the only valid value within range
   *
   * PLL1CFG = (log2(P) << 5) + (M - 1)
   *         = (1 << 5) + 3
   *         = 0x23 for a 12MHz crystal
   */
    

    //USB can only use PLL1 as clock source
    
    Chip_Clock_SetupPLL(SYSCTL_USB_PLL, 3, 1); //PLL1, msel = (M-1), psel = (P-1)
    Chip_Clock_EnablePLL(SYSCTL_USB_PLL, SYSCTL_PLL_ENABLE); // PLL1 Enable
    while (!Chip_Clock_IsUSBPLLLocked()); //wait for PLL1 to lock

    Chip_Clock_EnablePLL(SYSCTL_USB_PLL, SYSCTL_PLL_CONNECT); //PLL1 connect
    while(!Chip_Clock_IsUSBPLLConnected() && !Chip_Clock_IsUSBPLLEnabled()); //wait for PLL1 connect and enable


    //update the global system core clock rate
    SystemCoreClock = Chip_Clock_GetSystemClockRate();

    
    LPC_SYSCTL->PCONP = 0x42886CE; // enable select peripherals. Others will be turned on as necessary
    
    //Set the Flash memory access time
    Chip_SYSCTL_SetFLASHAccess(FLASHTIM_100MHZ_CPU); //this same value for both 100MHz and 120MHz

}
