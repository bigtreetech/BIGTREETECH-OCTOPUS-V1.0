#ifndef SMOOTHIEBOARD_H
#define SMOOTHIEBOARD_H

#include "../Pins_LPC.h"

// List of assignable pins and their mapping from names to MPU ports. This is indexed by logical pin number.
// The names must match user input that has been concerted to lowercase and had _ and - characters stripped out.
// Aliases are separate by the , character.
// If a pin name is prefixed by ! then this means the pin is hardware inverted. The same pin may have names for both the inverted and non-inverted cases,
// for example the inverted heater pins on the expansion connector are available as non-inverted servo pins on a DFueX.

//https://raw.githubusercontent.com/Bouni/smoothieboard-graphics/master/smoothieboard-wiring.png
constexpr PinEntry PinTable_Smoothieboard[] =
{

    //Thermistors
    {P0_23, "e0temp,t0"},
    {P0_24, "bedtemp,t1"},
    {P0_25, "e1temp,t2"},
    {P0_26, "t3,P0.26"},

    //Endstops
    {P1_24, "xstop,xmin"},
    {P1_25, "xstopmax,xmax"},
    {P1_26, "ystop,ymin"},
    {P1_27, "ystopmax,ymax"},
    {P1_28, "zstop,zmin"},
    {P1_29, "zstopmax,zmax"},

    //Heaters and Fans (Big and Small Mosfets}
    {P1_23, "e1heat,q5"  }, //(Big Mosfet)
    {P2_5, "bed,q6" },  //(Big Mosfet)
    {P2_7, "e0heat,q7" },  //(Big Mosfet)
    {P1_22, "q4,P1.22" },  //(Small Mosfet)
    {P2_4, "q8,P2.4" },  //(Small Mosfet)
    {P2_6, "fan0,q9" },  //(Small Mosfet)

    //Spare pins (also as LEDs)
    {P1_21, "led1,P1.21"},
    {P1_20, "led2,P1.20"},
    {P1_19, "led3,P1.19"},
    {P1_18, "led4,P1.18"},

    //Spare pins (or used for LCD)
    {P1_22, "P1.22"},
    {P1_23, "P1.23"},
    {P1_31, "P1.31"},
    {P1_30, "P1.30"},
    {P3_25, "P3.25"},
    {P3_26, "P3.26"},
    {P2_11, "P2.11"},
	{P2_12, "P2.12"},

};

constexpr BoardDefaults smoothieBoardDefaults = {
    5,
    {P0_4,  P0_10, P0_19, P0_21,  P4_29},   //enablePins
    {P2_0,  P2_1,  P2_2,  P2_3,   P2_8},    //stepPins
    {P0_5,  P0_11, P0_20, P0_22,  P2_13},   //dirPins
#if HAS_SMART_DRIVERS
    {NoPin, NoPin, NoPin, NoPin, NoPin},    //uartPins
    0,                                      // Smart drivers
#endif
    113.33,                                 //digiPot Factor    
};

#endif