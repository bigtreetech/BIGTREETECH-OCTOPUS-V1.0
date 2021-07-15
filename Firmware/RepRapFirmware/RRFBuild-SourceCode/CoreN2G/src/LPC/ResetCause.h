/*
  Copyright (c) 2012 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef RESETCAUSE_H
#define RESETCAUSE_H

#ifdef __cplusplus
extern "C" {
#endif

//LPC Reset Reason definitions
#define RSID_POR      (1<<0)  //Power On Reset
#define RSID_EXTR     (1<<1)  //Assetion of RESET signal
#define RSID_WDTR     (1<<2)  // Watchdog Timeout Reset
#define RSID_BODR     (1<<3)  // Brown Out Detect Reset
#define RSID_SYSRESET (1<<4)  // System softare Reset
#define RSID_LOCKUP   (1<<5)  // CPU Lockup


    

#ifdef __cplusplus
}
#endif

#endif
