#ifndef AZSMZ_MINI_H
#define AZSMZ_MINI_H

#include "../Pins_LPC.h"

// List of assignable pins and their mapping from names to MPU ports. This is indexed by logical pin number.
// The names must match user input that has been concerted to lowercase and had _ and - characters stripped out.
// Aliases are separate by the , character.
// If a pin name is prefixed by ! then this means the pin is hardware inverted. The same pin may have names for both the inverted and non-inverted cases,
// for example the inverted heater pins on the expansion connector are available as non-inverted servo pins on a DFueX.

constexpr PinEntry PinTable_AZSMZ[] =
{

    //Thermistors
    //TODO:: need confirmation on the term assignments and names???
    {P0_23, "bedtemp,t0"},
    {P0_24, "e0temp,t1"},
    {P0_25, "e1temp,t2"},

    //Endstops
    {P1_24, "x,xstop"},
    {P1_26, "y,ystop"},
    {P1_28, "z,zstop"},
    {P1_29, "probe"},
    
    //Heaters and Fans
    {P2_5, "bed,d8"  },
    {P2_7, "e0heat,d9" },
    {P2_4, "e1heat,d10" },
    {P0_26, "Fan0,Fan1" },
    
    //servo
    {P1_23, "P1.23,servo0"},
    
    //Aux-2
    {P1_27, "P1.27"},
    {P1_25, "P1.25"},
    {P4_28, "P4.28"},
    {P1_30, "P1.30"},
    {P0_26, "P0.26"},
    {P2_6, "P2.6"},
    {P1_22, "P1.22"},
    {P3_26, "P3.26"},
    
    //Aux-3
    {P0_27, "sda,P0.27"},
    {P0_28, "scl,P0.28"},
    {P0_16, "ssel1,P0.16"},
    {P1_31, "P1.31"},
    {P3_25, "P3.25"}, 
};

constexpr BoardDefaults azsmzDefaults = {
    5,
    {P0_4,  P0_10, P0_19, P0_21,  P4_29},   //enablePins
    {P2_0,  P2_1,  P2_2,  P2_3,   P2_8},    //stepPins
    {P0_5,  P0_11, P0_20, P0_22,  P2_13},   //dirPins
#if HAS_SMART_DRIVERS
    {NoPin, NoPin, NoPin, NoPin, NoPin},    //uartPins
    0,                                      // Smart drivers
#endif
    0,                                      //digiPot Factor
};

#endif