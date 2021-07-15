#ifndef MKSSGenL_H
#define MKSSGenL_H

#include "../Pins_LPC.h"


// List of assignable pins and their mapping from names to MPU ports. This is indexed by logical pin number.
// The names must match user input that has been concerted to lowercase and had _ and - characters stripped out.
// Aliases are separate by the , character.
// If a pin name is prefixed by ! then this means the pin is hardware inverted. The same pin may have names for both the inverted and non-inverted cases,
// for example the inverted heater pins on the expansion connector are available as non-inverted servo pins on a DFueX.

constexpr PinEntry PinTable_MKSSGenL1_0[] =
{
    //Thermistors
    {P0_23, "e0temp,th1"},
    {P0_24, "bedtemp,TB"},
    {P0_25, "e1temp,th2"},

    //Endstops (although they are labeled x- and x+ on the - and + get stripped out in RRF so we will use i.e. xmin/xmax
    {P1_24, "zstopmax,Z+"},
    {P1_25, "zstop,Z-"},
    {P1_26, "ystopmax,Y+"},
    {P1_27, "ystop,Y-"},
    {P1_28, "xstopmax,X+"},
    {P1_29, "xstop,X-"},

    //Heaters and Fans
    {P2_5, "bed"},
    {P2_7, "e0heat,e1"},
    {P2_6, "e1heat,e2"},
    {P2_4, "fan0,fan"},
	
	//servo
	{P1_23, "servo0,P1.23" },
	{P2_0, "servo1,P2.0" },
 
    //Spare pins (also as LEDs)
    {P1_21, "led1,P1.21"},
    {P1_20, "led2,P1.20"},
    {P1_19, "led3,P1.19"},
    {P1_18, "led4,P1.18"},
    
    //Exp1
    {P1_31, "P1.31"},
	{P1_30, "P1.30"},
    {P0_18, "P0.18"},
	{P0_16, "P0.16"},
    {P0_15, "P0.15"},    
    {P0_17, "P0.17"},
	{P1_0, "P1.0"},
	{P1_22, "P1.22"},
    
    //Exp2
    {P0_8, "P0.8"},
	{P0_7, "P0.7"},
    {P3_25, "P3.25"},
	{P0_28, "P0.28"},
    {P3_26, "P3.26"},
	{P0_9, "P0.9"},
    {P0_27, "P0.27"}, 

	//TMC-SPI Pins
	{P4_28, "P4.28"},
	{P0_4, "P0.4"},
	{P0_5, "P0.5"},

	//aux-1
	{P0_2, "P0.2"},
	{P0_3, "P0.3"},	
    
};

constexpr BoardDefaults mkssgenl1_0_Defaults = {
    5,
    {P2_1,  P2_8, P0_21, P2_12,  P0_10},   //enablePins
    {P2_2,  P0_19,  P0_22,  P2_13,   P0_1},    //stepPins
    {P2_3,  P0_20, P2_11, P0_11,  P0_0},   //dirPins
#if HAS_SMART_DRIVERS
    {P1_4, P1_9, P1_14, P1_16, P4_29},    //uartPins
    5,                                      // Smart drivers
#endif
    0,                                 //digiPot Factor
};

constexpr PinEntry PinTable_MKSSGenL2_0[] =
{
    //Thermistors
    {P0_23, "e0temp,th1"},
    {P0_24, "bedtemp,TB"},
    {P0_25, "e1temp,th2"},

    //Endstops (although they are labeled x- and x+ on the - and + get stripped out in RRF so we will use i.e. xmin/xmax
    {P1_24, "zstopmax,Z+"},
    {P1_25, "zstop,Z-"},
    {P1_26, "ystopmax,Y+"},
    {P1_27, "ystop,Y-"},
    {P1_28, "xstopmax,X+"},
    {P1_29, "xstop,X-"},

    //Heaters and Fans
    {P2_5, "bed"},
    {P2_7, "e0heat,e1"},
    {P2_6, "e1heat,e2"},
    {P2_4, "fan0,P2.4"},
	{P1_4, "fan1,P1.4"},
	
	//servo
	{P1_23, "servo0,P1.23" },
	{P2_0, "servo1,P2.0" },
 
    //Spare pins (also as LEDs)
    {P1_21, "led4,P1.21"},
    {P1_20, "led3,P1.20"},
    {P1_19, "led2,P1.19"},
    {P1_18, "led1,P1.18"},
    
    //Exp1
    {P1_31, "P1.31"},
	{P1_30, "P1.30"},
    {P0_18, "P0.18"},
	{P0_16, "P0.16"},
    {P0_15, "P0.15"},    
    {P0_17, "P0.17"},
	{P1_0, "P1.0"},
	{P1_22, "P1.22"},
    
    //Exp2
    {P0_8, "P0.8"},
	{P0_7, "P0.7"},
    {P3_25, "P3.25"},
	{P0_28, "P0.28"},
    {P3_26, "P3.26"},
	{P0_9, "P0.9"},
    {P0_27, "P0.27"},   
	
	//TMC-SPI Pins
	{P1_16, "P1.16"},
	{P0_4, "P0.4"},
	{P0_5, "P0.5"},
	
	//other
	{P0_26, "P0.26"},
	
	//aux-1
	{P0_2, "P0.2"},
	{P0_3, "P0.3"},
	
	//wifi
	{P4_28, "P4.28"},
	{P4_29, "P4.29"},
    
};

constexpr BoardDefaults mkssgenl2_0_Defaults = {
    5,
    {P2_1,  P2_8, P0_21, P2_12,  P0_10},   //enablePins
    {P2_2,  P0_19,  P0_22,  P2_13,   P1_9},    //stepPins
    {P2_3,  P0_20, P2_11, P0_11,  P1_14},   //dirPins
#if HAS_SMART_DRIVERS
    {P1_1, P1_8, P1_10, P1_15, P1_17},    //uartPins
    5,                                      // Smart drivers
#endif
    0,                                 //digiPot Factor
};

#endif