/*
  Copyright (c) 2011 Arduino.  All right reserved.

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

#ifndef _VARIANT_LPC
#define _VARIANT_LPC

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "Core.h"
#include "gpio.h"


#ifdef __cplusplus

//External SPI
constexpr gpioPins_et SPI0_MOSI = P0_18;
constexpr gpioPins_et SPI0_MISO = P0_17;
constexpr gpioPins_et SPI0_SCK  = P0_15;
constexpr gpioPins_et SPI0_SSEL = P0_16;


//Internal SDCard
constexpr gpioPins_et SPI1_MOSI = P0_9;
constexpr gpioPins_et SPI1_MISO = P0_8;
constexpr gpioPins_et SPI1_SCK  = P0_7;
constexpr gpioPins_et SPI1_SSEL = P0_6;


//i2c for DigitalPots
constexpr gpioPins_et SDA = P0_0;
constexpr gpioPins_et SCL = P0_1;

#endif //end __cplusplus

#endif /* _VARIANT_LPC */

