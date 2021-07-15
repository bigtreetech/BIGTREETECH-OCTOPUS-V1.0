/***************************************************************************************************
                                   ExploreEmbedded    
****************************************************************************************************
 * File:   timer.h
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the function declaration and the SFR bit number for configuring and using the LPC1768 timers.
                 

The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the 
library works on any of development boards for respective controllers. However, ExploreEmbedded 
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information 
related to updates. 


GNU GENERAL PUBLIC LICENSE: 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. 

Errors and omissions should be reported to codelibraries@exploreembedded.com
 
 *SD: Updated
 
**************************************************************************************************/
#ifdef __cplusplus
 extern "C" {
#endif 

#ifndef _TIMERS_H_
#define _TIMERS_H_

#include "chip.h"

/*************************************************************************************************
                         SFR Bits of timers registers							   
**************************************************************************************************/
#define SBIT_PCTIM0  1
#define SBIT_PCTIM1  2
#define SBIT_PCTIM2  22
#define SBIT_PCTIM3  23

#define PCLK_TIMER0  2
#define PCLK_TIMER1  4   
#define PCLK_TIMER2  12
#define PCLK_TIMER3  14

#define SBIT_MR0I    0
#define SBIT_MR0R    1
#define SBIT_MR0S    2

#define SBIT_MR1I    3
#define SBIT_MR1R    4
#define SBIT_MR1S    5

#define SBIT_MR2I    6
#define SBIT_MR2R    7
#define SBIT_MR2S    8

#define SBIT_MR3I    9
#define SBIT_MR3R    10
#define SBIT_MR3S    11

//bits for IR MRx Interrupt Flag Match
#define SBIT_MRI0_IFM 0
#define SBIT_MRI1_IFM 1
#define SBIT_MRI2_IFM 2
#define SBIT_MRI3_IFM 3

     
#define SBIT_CNTEN   0

uint32_t getPrescalarForUs(uint8_t timerPclkBit_u8) noexcept;
uint32_t getPclk(uint8_t timerPclkBit_u8) noexcept;

     
#endif

#ifdef __cplusplus
}
#endif


