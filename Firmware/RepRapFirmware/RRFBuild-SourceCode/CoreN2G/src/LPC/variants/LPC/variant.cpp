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
#include "CoreImp.h"
#include "variant.h"


void ConfigurePin(const PinDescription& pinDesc) noexcept
{
//UnUsed
    //pio_configure(pinDesc.pPort, pinDesc.ulPinType, pinDesc.ulPin, pinDesc.ulPinConfiguration);
}


extern const PinDescription g_APinDescription[]=
{
//   Port,      Attributes,                        ADCChannelNumber     PWM Channel,
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_0},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_1},
    {0,     PIN_ATTR_DIGITAL|PIN_ATTR_ANALOG,               ADC7,       NOT_ON_PWM}, //P0_2},
    {0,     PIN_ATTR_DIGITAL|PIN_ATTR_ANALOG,               ADC6,       NOT_ON_PWM}, //P0_3},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_4},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_5},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_6},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_7},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_8},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_9},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_10},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_11},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_12},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_13},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_14},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_15},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_16},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_17},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_18},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_19},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_20},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_21},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_22},
    {0,     PIN_ATTR_DIGITAL|PIN_ATTR_ANALOG,               ADC0,       NOT_ON_PWM}, //P0_23},
    {0,     PIN_ATTR_DIGITAL|PIN_ATTR_ANALOG,               ADC1,       NOT_ON_PWM}, //P0_24},
    {0,     PIN_ATTR_DIGITAL|PIN_ATTR_ANALOG,               ADC2,       NOT_ON_PWM}, //P0_25},
    {0,     PIN_ATTR_DIGITAL|PIN_ATTR_ANALOG|PIN_ATTR_DAC,  ADC3,       NOT_ON_PWM}, //P0_26},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_27},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_28},
    // 0_29 & 30 USB D+ & D-
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_29},
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_30},
    
    {0,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P0_31},
    
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_0},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_1},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_2},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_3},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_4},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_5},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_6},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_7},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_8},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_9},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_10},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_11},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_12},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_13},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_14},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_15},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_16},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_17},
    {1,     PIN_ATTR_DIGITAL|PIN_ATTR_PWM,                  NO_ADC,     PWM1_1}, //     P1_18},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_19},
    {1,     PIN_ATTR_DIGITAL|PIN_ATTR_PWM,                  NO_ADC,     PWM1_2}, //     P1_20},
    {1,     PIN_ATTR_DIGITAL|PIN_ATTR_PWM,                  NO_ADC,     PWM1_3}, //     P1_21},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_22},
    {1,     PIN_ATTR_DIGITAL|PIN_ATTR_PWM,                  NO_ADC,     PWM1_4}, //,     P1_23},
    {1,     PIN_ATTR_DIGITAL|PIN_ATTR_PWM,                  NO_ADC,     PWM1_5}, //,     P1_24},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_25},
    {1,     PIN_ATTR_DIGITAL|PIN_ATTR_PWM,                  NO_ADC,     PWM1_6}, //,     P1_26},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_27},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_28},
    {1,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P1_29},
    {1,     PIN_ATTR_DIGITAL|PIN_ATTR_ANALOG,               ADC4,       NOT_ON_PWM}, //P1_30},
    {1,     PIN_ATTR_DIGITAL|PIN_ATTR_ANALOG,               ADC5,       NOT_ON_PWM}, //P1_31},
    
    {2,     PIN_ATTR_DIGITAL|PIN_ATTR_PWM,                  NO_ADC,     PWM1_1}, //,     P2_0},
    {2,     PIN_ATTR_DIGITAL|PIN_ATTR_PWM,                  NO_ADC,     PWM1_2}, //,     P2_1},
    {2,     PIN_ATTR_DIGITAL|PIN_ATTR_PWM,                  NO_ADC,     PWM1_3}, //,     P2_2},
    {2,     PIN_ATTR_DIGITAL|PIN_ATTR_PWM,                  NO_ADC,     PWM1_4}, //,     P2_3},
    {2,     PIN_ATTR_DIGITAL|PIN_ATTR_PWM,                  NO_ADC,     PWM1_5}, //,     P2_4},
    {2,     PIN_ATTR_DIGITAL|PIN_ATTR_PWM,                  NO_ADC,     PWM1_6}, //,     P2_5},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_6},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_7},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_8},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_9},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_10},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_11},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_12},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_13},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_14},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_15},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_16},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_17},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_18},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_19},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_20},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_21},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_22},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_23},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_24},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_25},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_26},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_27},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_28},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_29},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_30},
    {2,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P2_31},
    
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_0},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_1},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_2},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_3},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_4},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_5},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_6},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_7},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_8},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_9},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_10},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_11},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_12},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_13},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_14},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_15},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_16},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_17},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_18},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_19},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_20},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_21},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_22},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_23},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_24},
    {3,     PIN_ATTR_DIGITAL|PIN_ATTR_PWM,                  NO_ADC,     PWM1_2}, //,     P3_25},
    {3,     PIN_ATTR_DIGITAL|PIN_ATTR_PWM,                  NO_ADC,     PWM1_3}, //,     P3_26},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_27},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_28},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_29},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_30},
    {3,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P3_31},
    
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_0},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_1},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_2},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_3},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_4},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_5},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_6},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_7},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_8},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_9},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_10},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_11},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_12},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_13},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_14},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_15},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_16},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_17},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_18},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_19},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_20},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_21},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_22},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_23},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_24},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_25},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_26},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_27},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_28},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_29},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_30},
    {4,     PIN_ATTR_DIGITAL,                               NO_ADC,     NOT_ON_PWM}, //P4_31},
    
};



void init( void ) noexcept
{
}



