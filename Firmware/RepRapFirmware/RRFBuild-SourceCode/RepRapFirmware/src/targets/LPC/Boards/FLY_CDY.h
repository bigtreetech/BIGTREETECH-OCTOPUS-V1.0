#ifndef FLY_CDY_H
#define FLY_CDY_H

#include "../Pins_LPC.h"

// List of assignable pins and their mapping from names to MPU ports. This is indexed by logical pin number.
// The names must match user input that has been concerted to lowercase and had _ and - characters stripped out.
// Aliases are separate by the , character.
// If a pin name is prefixed by ! then this means the pin is hardware inverted. The same pin may have names for both the inverted and non-inverted cases,
// for example the inverted heater pins on the expansion connector are available as non-inverted servo pins on a DFueX.

constexpr PinEntry PinTable_FLY_CDY[] =
{
    //Thermistors
    {P0_23, "bedtemp,tb"},
    {P0_26, "e0temp,t0"},
    {P0_25, "e1temp,t1"},
    {P0_24, "e2temp,t2"},

    //Endstops
    {P1_29, "xmin,xstop"},
    {P1_28, "xmax,xstopmax"},
    {P1_27, "ymin,ystop"},
    {P1_25, "ymax,ystopmax"},
    {P1_22, "zmin,zstop"},
    {P0_27, "zmax,zstopmax"},

    //Heaters and Fans
    {P3_26, "bed" },
    {P3_25, "e0heat" },
    {P1_20, "e1heat" },
    {P1_23, "e2heat" },
    {P1_18, "fan0" },
    {P1_21, "fan1" },
    {P1_24, "fan2" },

    //Exp1
    {P2_7, "P2.7"}, 
    {P2_8, "P2.8"},
    {P0_22, "P0.22"}, 
    {P2_10, "P2.10"},
    {P1_19, "P1.19"},
    {P0_28, "P0.28"},
    {P1_30, "P1.30"},
    {P1_31, "P1.31"},

    //Exp2
    {P0_17, "P0.17"},
    {P0_15, "P0.15"},
    {P0_16, "P0.16"},
    {P0_18, "P0.18"},
    {P2_6, "P2.6"},

    //Servos
    {P1_26, "servo0" },

	//Wifi
	{P0_1, "wifi1"},
	{P0_0, "wifi2"},

	//screen
	{P0_2, "P0.2"},
	{P0_3, "P0.3"},

	//TMC-SPI Pins
	{P0_19, "P0.19"},  //SOFT MISO
	{P0_20, "P0.20"},  //SOFT MOSI
	{P0_21, "P0.21"},  //SCK

};

constexpr BoardDefaults FLY_CDY_Defaults = {
    6,
    {P1_0,  P1_8, P1_14, P1_17, P0_4,  P2_13},     //enablePins
    {P2_0,  P2_1, P2_2,  P2_3,  P2_4,  P2_5},      //stepPins
    {P1_1,  P1_9, P1_15, P4_29, P2_11, P0_11},      //dirPins
#if HAS_SMART_DRIVERS
    {P1_4, P1_10, P1_16, P4_28, P2_12, P0_10},    //uartPins
    6,                                      // Smart drivers
#endif
    0,                                      //digiPot Factor
};
#endif