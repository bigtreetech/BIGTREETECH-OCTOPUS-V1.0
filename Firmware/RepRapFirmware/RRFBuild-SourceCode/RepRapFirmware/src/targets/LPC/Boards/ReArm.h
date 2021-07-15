#ifndef REARM_H
#define REARM_H

#include "../Pins_LPC.h"

// List of assignable pins and their mapping from names to MPU ports. This is indexed by logical pin number.
// The names must match user input that has been concerted to lowercase and had _ and - characters stripped out.
// Aliases are separate by the , character.
// If a pin name is prefixed by ! then this means the pin is hardware inverted. The same pin may have names for both the inverted and non-inverted cases,
// for example the inverted heater pins on the expansion connector are available as non-inverted servo pins on a DFueX.

//NOTE:: In general RAMPS silk/official pinout is used as the labels since most of the connections are on the RAMPS shield
constexpr PinEntry PinTable_Rearm[] =
{

    //Thermistors
    {P0_23, "e0temp,t0"},        //Ext0 Therm
    {P0_24, "bedtemp,t1"},        //Bed Therm
    {P0_25, "e1temp,t2"},        //Ext1 Therm
    
    //Endstops (although they are labeled x- and x+ on the - and + get stripped out in RRF so we will use i.e. xmin/xmax
    {P1_24, "xstop,xmin"},
    {P1_25, "xstopmax,xmax"},
    {P1_26, "ystop,ymin"},
    {P1_27, "ystopmax,ymax"},
    {P1_29, "zstop,zmin"},
    {P1_28, "zstopmax,zmax"},

    //Heaters and Fans (Mosfets)
    {P2_7, "bed,d8"  },            //HB Mosfet
    {P2_4, "e1heat,d9" },             //HE2 Mosfet
    {P2_5, "e0heat,d10" },            //HE1 Mosfet

    //Servos (only max of 3 servos can be configured_
    {P1_20, "servo0,d11"},     //PWM1[2]
    {P1_21, "servo1,d6"},      //PWM1[3]
    {P1_19, "servo2,d5"},
    {P1_18, "servo3,d4"},      //PWM1[1]
    
    //Ramps  AUX1 Pins
    //P0_2 D1 (TXD0)  (Used by AUX Serial)
    //P0_3 D0 (RXD0)  (Used by Aux Serial)
    {P0_27, "d57,P0.27"},
    {P0_28, "d58,P0.28"},

    //Ramps Aux2 Pins
    {P0_26, "d63,P0.26"},       //(ADC3, DAC)
    //D40,     (NC)
    //D42,     (NC)
    //A11/D65, (NC)
    {P2_6, "d59,P2.6"},               //a5 (overlaps J3)
    //A10/D64, (NC)
    //D44,     (NC)
    //A12/D66  (NC)
    
    //Ramps Aux3 Pins
    //{P0_15, "sck,d52"},
    //{P0_17, "miso,d50"},
    {P1_23, "d53,P1.23"},              //(overlaps J3)
    //{P0_18, "mosi,d51"},         //(overlaps Aux4)
    {P1_31, "d49,P1.31"},
    
    //Ramps Aux4 Pins
    //D32, (NC)
    //D47, (NC)
    //D45, (NC)
    //D43, (NC)
    {P1_22, "d41,P1.22"},
    //D39, (NC)
    {P1_30, "d37,P1.30"},
    {P2_11, "d35,P2.11"},
    {P3_25, "d33,P3.25"},
    {P3_26, "d31,P3.26"},
    //D29, (NC)
    //D27, (NC)
    //D25, (NC)
    //{P0_15, "d23"},              //(SCK)  (Overlaps Aux3)
    //{P0_18, "d17"},              //(MOSI) (overlaps Aux3)
    {P0_16, "d16,P0.16"},              //(CS)
    
    //Ramps I2C Header
    {P0_0, "sca,d20,P0.0"},        //labelled on board as 20
    {P0_1, "scl,d21,P0.1"},        //labelled on board as 21
        
    //ReArm Headers
    //J3
    //P0_15, SCLK (overlaps Aux3/4)
    //P0_16, (Overlaps  Aux4)
    //{P1_23, "d53,P1.23"},               //PWM1[4]			Commented out as overlaps with Aux 3
    //{P2_11, "d35,P2.11"},			Commented out as overlaps with Aux 4
    //{P1_31, "d49,P1.31"},			Commented out as overlaps with Aux 3
    //P0_18, MOSI (overlaps Aux4/Aux3)
    //{P2_6, "d59,P2.6"},			Commented out as overlaps with Aux 2
    //P0_17, MISO (overlaps Aux3)
    //{P3_25, "d33,P3.25"},               //PWM1[2] 			Commented out as overlaps with Aux 4
    //{P3_26, "d31,P3.26"},               //PWM1[3] 			Commented out as overlaps with Aux 4
    
    //J5
    //{P1_22, "d41,P1.22"},			Commented out as overlaps with Aux 4
    //{P1_30, "d37,P1.30"},			Commented out as overlaps with Aux 4
    //P1_21, d6     PWM1[3] //overlaps with Servos
    //P0_26, a9/d63 //Overlaps Aux2
    

    //Misc
    {P2_12, "pson,P2.12"}, //PS-ON
    {P4_28, "play,P4.28"}, //Play LED

};

constexpr BoardDefaults rearmDefaults = {
    5,
    {P0_10, P0_19, P0_21, P0_4, P4_29},     //enablePins
    {P2_1,  P2_2,  P2_3,  P2_0, P2_8},      //stepPins
    {P0_11, P0_20, P0_22, P0_5, P2_13},     //dirPins
#if HAS_SMART_DRIVERS
    {NoPin, NoPin, NoPin, NoPin, NoPin},    //uartPins
    0,                                      // Smart drivers
#endif
    0,                                      //digiPot Factor
};

#endif