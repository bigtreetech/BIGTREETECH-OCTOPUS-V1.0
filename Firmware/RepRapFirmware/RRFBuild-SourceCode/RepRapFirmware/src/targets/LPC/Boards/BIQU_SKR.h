#ifndef BIQU_SKR_H
#define BIQU_SKR_H

#include "../Pins_LPC.h"

// List of assignable pins and their mapping from names to MPU ports. This is indexed by logical pin number.
// The names must match user input that has been concerted to lowercase and had _ and - characters stripped out.
// Aliases are separate by the , character.
// If a pin name is prefixed by ! then this means the pin is hardware inverted. The same pin may have names for both the inverted and non-inverted cases,
// for example the inverted heater pins on the expansion connector are available as non-inverted servo pins on a DFueX.

constexpr PinEntry PinTable_BIQU_SKR_v1_1[] =
{
    //Thermistors
    {P0_23, "bedtemp,tb"},
    {P0_24, "e0temp,th0"},
    {P0_25, "e1temp,th1"},

    //Endstops
    {P1_29, "xstop,xmin"},
    {P1_28, "xstopmax,xmax"},
    {P1_27, "ystop,ymin"},
    {P1_26, "ystopmax,ymax"},
    {P1_25, "zstop,zmin"},
    {P1_24, "zstopmax,zmax"},

    //Heaters and Fans (Big and Small Mosfets}
    {P2_5, "bed,hbed" },
    {P2_7, "e0heat,he0" },
    {P2_4, "e1heat,he1" },
    {P2_3, "fan0,fan" },

    //Exp1
    {P0_15, "P0.15"}, //SSP0 SCK
    {P0_16, "P0.16"},
    {P0_18, "P0.18"}, //SSP0 MOSI
    {P2_11, "P2.11"},
    {P1_30, "P1.30"},

    //Exp2
    {P1_31, "P1.31"},
    //0.18
    {P3_25, "P3.25"},
    {P1_23, "P1.23"},
    {P3_26, "P3.26"},
    {P0_17, "P0.17"}, //SSP0 MISO

    //LCD/SD/SPI header (most overlap with exp1/2)
    //0.15
    //0.18
    //0.16
    {P2_6, "P2.6"},
    {P1_23, "P1.23"},
    //0.17
    //2.11
    {P3_25, "P3.25"},
    //1.31
    {P3_26, "P3.26"},
	
	//aux-1
	{P0_2, "P0.2"},
	{P0_3, "P0.3"},
};

constexpr BoardDefaults biquskr_1_1_Defaults = {
    5,
    {P4_28, P2_0, P0_19, P2_12, P0_10},     //enablePins
    {P0_4,  P2_1, P0_20, P0_11, P0_1},      //stepPins
    {P0_5,  P2_2, P0_21, P2_13, P0_0},      //dirPins
#if HAS_SMART_DRIVERS
    {NoPin, NoPin, NoPin, NoPin, NoPin},    //uartPins
    0,                                      // Smart drivers
#endif
    0,                                      //digiPot Factor
};

// BIQU SKR version 1.3
constexpr PinEntry PinTable_BIQU_SKR_v1_3[] =
{
    //Thermistors
    {P0_23, "bedtemp,tb"},
    {P0_24, "e0temp,th0"},
    {P0_25, "e1temp,th1"},
    
    //Endstops
    {P1_29, "xstop,x-"},
    {P1_28, "xstopmax,x+"},
    {P1_27, "ystop,y-"},
    {P1_26, "ystopmax,y+"},
    {P1_25, "zstop,z-"},
    {P1_24, "zstopmax,z+"},
    
    //Heaters and Fans (Big and Small Mosfets}
    {P2_5, "bed,hbed" },
    {P2_7, "e0heat,he0" },
    {P2_4, "e1heat,he1" },
    {P2_3, "fan0,fan" },
    
    //Servos
    {P2_0, "servo,servo0" },
    
    //EXP1
    {P1_23, "P1.23"},
    {P1_22, "P1.22"},
    {P1_21, "P1.21"},
    {P1_20, "P1.20"},
    {P1_19, "P1.19"},
    {P1_18, "P1.18"},
    {P0_28, "P0.28"},
    {P1_30, "P1.30"},
    
    //EXP2
    {P1_31, "P1.31"},
    {P0_18, "0.18"}, //SSP0 MOSI
    {P3_25, "P3.25"},
    {P0_16, "P0.16"},
    {P3_26, "P3.26"},
    {P0_15, "0.15"}, //SSP0 SCK
    {P0_17, "0.17"}, //SSP0 MISO
    
    //MONI-SD
    {P0_27, "data2,P0.27"},
    //following pins are the same as the internal sdcard
    //{P0_8, "0.8"}, //SSP1 MISO
    //{P0_7, "0.7"}, //SSP1 SCK
    //{P0_9, "0.9"}, //SSP1 MOSI
    //{P0_6, "0.6"}, //SEL (SD CS)

    //Other Headers on v1.3 Boards
    //TMC2208-UART
    //      Tx      Rx
    //X     4.29    1.17
    //Y     1.16    1.15
    //Z     1.14    1.10
    //E0    1.9     1.8
    //E1    1.4     1.1

    //TMC2130-SPI (Note SPI pins are not on a HW SPI channel)
    //XCS  1.17
    //YCS  1.15
    //ZCS  1.10
    //E0CS 1.8
    //E1CS 1.1

    //MISO 0.5
    //MOSI 4.28
    //SCK  0.4
	
	//aux-1
	{P0_2, "P0.2"},
	{P0_3, "P0.3"},
};

constexpr BoardDefaults biquskr_1_3_Defaults = {
    7,
    {P2_1, P2_8,  P0_21, P2_12,  P0_10, P1_18, P1_23},    //enablePins
    {P2_2, P0_19, P0_22, P2_13,  P0_1, P1_21, P1_20},     //stepPins
    {P2_6, P0_20, P2_11, P0_11,  P0_0, P1_19, P1_22},     //dirPins
#if HAS_SMART_DRIVERS
    {P1_17, P1_15, P1_10, P1_8, P1_1, P3_25, P3_26},      //uartPins
    5,                                      // Smart drivers
#endif
    0                                       //digiPot Factor
};

// BIQU SKR version 1.4
constexpr PinEntry PinTable_BIQU_SKR_v1_4[] =
{
    //Thermistors
    {P0_23, "e1temp,th1"},
    {P0_24, "e0temp,th0"},
    {P0_25, "bedtemp,tb"},

    //Endstops
    {P1_29, "xstop,x-stop"},
    {P1_28, "ystop,y-stop"},
    {P1_27, "zstop,z-stop"},
    {P1_26, "e0stop,e0det"},
    {P1_25, "e1stop,e1det"},
	{P1_0, "pwrdet,P1.0"},
	{P0_10, "probe"},
	
    //Heaters and Fans (Big and Small Mosfets}
    {P2_5, "bed,hbed" },
    {P2_7, "e0heat,he0" },
    {P2_4, "e1heat,he1" },
    {P2_3, "fan0,fan" },

    //Servos
    {P2_0, "servo0" },
	
	//Neopixel
	{P1_24, "neopixel,P1.24"},

    //EXP1
    {P1_23, "P1.23"},
    {P1_22, "P1.22"},
    {P1_21, "P1.21"},
    {P1_20, "P1.20"},
    {P1_19, "P1.19"},
    {P1_18, "P1.18"},
    {P0_28, "P0.28"},
    {P1_30, "P1.30"},

    //EXP2
    {P1_31, "P1.31"},
    {P0_18, "0.18"}, //SSP0 MOSI
    {P3_25, "P3.25"},
    {P0_16, "P0.16"},
    {P3_26, "P3.26"},
    {P0_15, "0.15"}, //SSP0 SCK
    {P0_17, "0.17"}, //SSP0 MISO

    //MONI-SD
    {P0_27, "data2,P0.27"},

	//Wifi
	{P4_28, "wifi1,P4.28"},
	{P4_29, "wifi2,P4.29"},
	
	//i2c
	{P0_0, "i2c1,P0.0"},
	{P0_1, "i2c2,P0.1"},
	
	//SPI
	{P0_26, "SPI1,P0.26"},
	{P0_7, "P0.7"},
	{P0_8, "P0.8"},
	{P0_9, "P0.9"},
	
	//tft
	{P0_2, "P0.2"},
	{P0_3, "P0.3"},
	
    //Other Headers on v1.4 Boards
    //TMC2208-UART
    //      Tx      Rx
    //X     4.29    1.17
    //Y     1.16    1.15
    //Z     1.14    1.10
    //E0    1.9     1.8
    //E1    1.4     1.1

    //TMC2130-UART (Note SPI pins are not on a HW SPI channel)
    //XCS  1.10
    //YCS  1.09
    //ZCS  1.08
    //E0CS 1.04
    //E1CS 1.01

    //MISO 0.5
    //MOSI 1.17
    //SCK  0.4
};

constexpr BoardDefaults biquskr_1_4_Defaults = {
    7,
    {P2_1, P2_8,  P0_21, P2_12,  P1_16, P1_18, P1_23},    //enablePins
    {P2_2, P0_19, P0_22, P2_13,  P1_15, P1_21, P1_20},    //stepPins
    {P2_6, P0_20, P2_11, P0_11,  P1_14, P1_19, P1_22},    //dirPins
#if HAS_SMART_DRIVERS
    {P1_10, P1_9, P1_8, P1_4, P1_1, P3_25, P3_26},        //uartPins
    5,                                      // Smart drivers
#endif
    0                                       //digiPot Factor
};


constexpr PinEntry PinTable_BIQU_SKR_E3T[] =
{
    //Thermistors
    {P0_25, "bedtemp,tb"},
    {P0_24, "e0temp,t0"},
    {P0_23, "e1temp,t1"},
	{P1_30, "mbtemp"},

    //Endstops
    {P1_29, "xstop"},
    {P1_28, "ystop"},
    {P1_27, "zstop"},
    {P1_26, "e0stop"},
    {P1_25, "e1stop"},
    {P1_23, "servo"},
    {P1_22, "probe"},
    {P1_20, "ptdet"},

    //Heaters and Fans
    {P2_5, "bed" },
    {P2_3, "e0heat" },
    {P2_4, "e1heat" },
    {P2_1, "fan0" },
    {P2_2, "fan1" },

    //Exp1
    {P2_8, "P2.8"}, 
    {P0_16, "P0.16"},
    {P0_19, "P0.19"}, 
    {P0_20, "P0.20"},
    {P0_15, "P0.15"},
    {P0_17, "P0.17"},
    {P0_18, "P0.18"},

    //PS On
    {P1_21, "pson"},

    //EEProm
    {P0_0, "eeprom0,SDA1"},
    {P0_1, "eeprom1,SCL1"},
	
	//AUX2
	{P0_10, "SDA2"},
    {P0_11, "SCL2"},
	{P0_27, "SDA0"},
    {P0_28, "SCL0"},

    //Neopixel
    {P1_24, "neopixel"},

    // TMC Standby pins, force low to enable
    {P3_26, "-sbyx"},
    {P3_25, "-sbyy"},
    {P1_18, "-sbyz"},
    {P1_19, "-sbye0"},
    {P2_13, "-sbye1"},
	
	//TFT
	{P0_3, "P0.3"},
	{P0_2, "P0.2"},
	
	//Status
	{P0_26, "LED,P0.26"},
};

constexpr BoardDefaults biquskr_E3T_Defaults = {
    5,
    {P1_0,  P1_9, P1_16, P0_4, P0_21},     //enablePins
    {P1_4,  P1_14, P4_29,  P2_6,  P2_11},      //stepPins
    {P1_8,  P1_15, P4_28, P2_7, P2_12},      //dirPins
#if HAS_SMART_DRIVERS
    {P1_1, P1_10, P1_17, P0_5, P0_22},    //uartPins
    5,                                      // Smart drivers
#endif
    0,                                      //digiPot Factor
};
#endif