#ifndef MKSSBASE_H
#define MKSSBASE_H

#include "../Pins_LPC.h"


// List of assignable pins and their mapping from names to MPU ports. This is indexed by logical pin number.
// The names must match user input that has been concerted to lowercase and had _ and - characters stripped out.
// Aliases are separate by the , character.
// If a pin name is prefixed by ! then this means the pin is hardware inverted. The same pin may have names for both the inverted and non-inverted cases,
// for example the inverted heater pins on the expansion connector are available as non-inverted servo pins on a DFueX.

constexpr PinEntry PinTable_MKSSbase1_3[] =
{
    //Thermistors
    {P0_23, "bedtemp,th1"},
    {P0_24, "e0temp,th2"},
    {P0_25, "e1temp,th3"},
    {P0_26, "th4"},

    //Endstops (although they are labeled x- and x+ on the - and + get stripped out in RRF so we will use i.e. xmin/xmax
    {P1_24, "xstop,xmin"},
    {P1_25, "xstopmax,xmax"},
    {P1_26, "ystop,ymin"},
    {P1_27, "ystopmax,ymax"},
    {P1_28, "zstop,zmin"},
    {P1_29, "zstopmax,zmax"},

    //Heaters and Fans
    {P2_5, "bed"},
    {P2_7, "e0heat,e1"},
    {P2_6, "e1heat,e2"},
    {P2_4, "fan0,fan"},

    //J7
    {P0_17, "P0.17"},
    {P0_16, "P0.16"},
    {P0_14, "P0.14"},
    
    //J8
    {P1_22, "P1.22"},
    {P1_23, "P1.23"},
    {P2_12, "P2.12"},
    {P2_11, "P2.11"},
    {P4_28, "P4.28"},
    
    //aux-1
	{P0_2, "P0.2"},
	{P0_3, "P0.3"},
    
    //Exp1
    {P1_31, "P1.31"},
    {P0_18, "P0.18"},
    {P0_14, "P0.14"},
    {P1_30, "P1.30"},
    
    //Exp2
    {P0_8, "P0.8"},
    {P3_25, "P3.25"},
    {P3_26, "P3.26"},
    {P0_27, "P0.27"},
    {P0_7, "P0.7"},
    {P0_28, "P0.28"},
    {P0_9, "P0.9"},
    
};

constexpr BoardDefaults mkssbase1_3_Defaults = {
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