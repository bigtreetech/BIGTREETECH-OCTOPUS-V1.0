/***************************************************************************************************
                                   ExploreEmbedded	
****************************************************************************************************
 * File:   delay.c
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the library function for delay.
 
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
**************************************************************************************************/

#include "delay.h"




/*---------------------------------------------------------------------------------
                       void delay_us(unsigned int us_count)
 ----------------------------------------------------------------------------------
 * I/P Arguments: no of ticks (multiple of 1us)
 * Return value	: none

 * description  :
    This function suspends the tasks for specified ticks(in us).

-----------------------------------------------------------------------------------*/
void delay_us(unsigned int us_count)
{
  volatile unsigned int j=0,i=0;

  for(j=0;j<us_count;j++)
  {
    /* At 100Mhz, the below loop introduces
    DELAY of 1 us */
    for(i=0;i<MicroSecDelayCount;i++);
  }
}
