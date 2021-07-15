/***************************************************************************************************
                                   ExploreEmbedded    
****************************************************************************************************
 * File:   timer.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the functions for configuring and using the LPC1768 timers.
                 

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
 
 
 SD: Modified for RRF
 
**************************************************************************************************/

#include "chip.h"
#include "timer.h"
#include "stdutils.h"

/***************************************************************************************************
            uint32_t getPrescalarForUs(uint8_t timerPclkBit_u8)
****************************************************************************************************
 * I/P Arguments: 
                uint8_t: Start bit of the timer in PCLKSELx register.
                         Refer data sheet for more info on PCLKSEL0/PCLKSEL1 registers

 * Return value: 
               uint32_t: Prescalar counter value for 1us. 

 * description :
                 This functions calculates the prescalar value for 1us for the requested timer.
                 It first gets the pclk bit info from PCLKSELx registers.
                 Later the bits are decoded to get the peripheral clock value.
                 Finally the pclk is divided by 1000000 to get the prescalar count for 1us.                
****************************************************************************************************/
uint32_t getPrescalarForUs(uint8_t timerPclkBit_u8)
{
    uint32_t pclk,prescalarForUs;

    if(timerPclkBit_u8<=4)
    {
        pclk = (LPC_SYSCTL->PCLKSEL[0] >> timerPclkBit_u8) & 0x03;  /* get the pclk info for required timer0/1 */
    }
    else
    {
        pclk = (LPC_SYSCTL->PCLKSEL[1] >> timerPclkBit_u8) & 0x03;  /* get the pclk info for required timer2/3 */
    }
    switch ( pclk )                                    /* Decode the bits to determine the pclk*/
    {
    case 0x00:
        pclk = SystemCoreClock/4;
        break;

    case 0x01:
        pclk = SystemCoreClock;
        break; 

    case 0x02:
        pclk = SystemCoreClock/2;
        break; 

    case 0x03:
        pclk = SystemCoreClock/8;
        break;
    }

    prescalarForUs =pclk/1000000 - 1;                      /* Prescalar for 1us (1000000Counts/sec) */

    return prescalarForUs;
}



//SD Function to get pclk for timer
uint32_t getPclk(uint8_t timerPclkBit_u8){
    
    uint32_t pclk;
    
    if(timerPclkBit_u8<=4)
    {
        pclk = (LPC_SYSCTL->PCLKSEL[0] >> timerPclkBit_u8) & 0x03;  /* get the pclk info for required timer0/1 */
    }
    else
    {
        pclk = (LPC_SYSCTL->PCLKSEL[1] >> timerPclkBit_u8) & 0x03;  /* get the pclk info for required timer2/3 */
    }
    switch ( pclk )                                    /* Decode the bits to determine the pclk*/
    {
        case 0x00:
            pclk = SystemCoreClock/4;
            break;
            
        case 0x01:
            pclk = SystemCoreClock;
            break;
            
        case 0x02:
            pclk = SystemCoreClock/2;
            break;
            
        case 0x03:
            pclk = SystemCoreClock/8;
            break;
    }
    
    return pclk;
    
}
