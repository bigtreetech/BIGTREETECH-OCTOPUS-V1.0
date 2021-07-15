#ifndef BIQU_SKR_H
#define BIQU_SKR_H

#include "../Pins_STM32.h"

// constexpr PinEntry PinTable_BTT_SKR_2[] =
// {
//     //Thermistors
//     {PA_1, "bedtemp,tb"},
//     {PA_2, "e0temp,th0"},
//     {PA_3, "e1temp,th1"},

//     //Endstops
//     {PC_1, "xstop,x-stop"},
//     {PC_3, "ystop,y-stop"},
//     {PC_0, "zstop,z-stop"},
//     {PC_2, "e0stop,e0det"},
//     {PA_0, "e1stop,e1det"},

//     //Servos
//     {PE_5,  "servo0" },

//     //Probe
//     {PE_4, "probe"},

//     //Heaters and Fans (Big and Small Mosfets}
//     {PD_7,  "bed,hbed" },
//     {PB_3,  "e0heat,heat0" },
//     {PB_4,  "e1heat,heat1" },
//     {PB_7,  "fan0,fan" },
//     {PB_6,  "fan1" },
//     {PB_5,  "fan2" },

//     //EXP1
//     {PE_9, "LCDCS"},
//     {PB_2, "LCDENCA"},
//     {PE_7, "LCDENCB"},
//     {PC_5, "LCDBEEP"},
//     {PB_0, "LCDBTN"},
//     {PE_10, "LCDD4"},
//     {PB_1, "LCDEN"},

//     //Neopixel
//     {PE_6, "Neopixel,PE6"},

//     //TFT
//     {PA_9, "TX1,tft-tx"},
//     {PA_10, "RX1,tft-rx"},

//     //WIFI UART
//     {PD_8, "PD8"},
//     {PD_9, "PD9"},

//     //SPI
//     {PE_0, "X-CS,PE0"},
//     {PD_3, "Y-CS,PD3"},
//     {PD_0, "Z-CS,PD0"},
//     {PC_6, "E0-CS,PC6"},
//     {PD_12, "E1-CS,PD12"},
//     {PA_14, "MISO,PA14"},
//     {PE_14, "MOSI,PE14"},
//     {PE_15, "SCK,PE15"},

//     //I2C
//     {PB_8, "SCL1,PB8"},
//     {PB_9, "SDA1,PB9"},

//     //WIFI
//     {PC_14, "PC14"}, //RST
//     {PB_10, "PB10"}, //IO0
//     {PB_11, "PB11"}, //IO4
//     {PB_12, "PB12"}, //CS
//     {PB_13, "PB13"}, //CLK
//     {PB_14, "PB14"}, //MISO
//     {PB_15, "PB15"}, //MOSI

//     //PSON
//     {PE_8, "PSON,PE8"},

//     //PWRDET
//     {PC_15, "PWRDET,PC15"},

//     //Status LED
//     {PA_13, "LED,PA13"},

//     //Safe power
//     {PC_13, "SP,PC13"},
// };

// constexpr BoardDefaults btt_skr_2_Defaults = {
//     {0xb75b00a7},                 				// Signatures
//     SD_SDIO,                                  // SD Card access
//     {   //CLK, MISO, MOSI
//         {PA_5, PA_6, PA_7},                     //SPI0
//         {PB_13, PB_14, PB_15},                  //SPI1
//         {NoPin, NoPin, NoPin},                  //SPI2
//         {NoPin, NoPin, NoPin},                  //SPI3
//         {NoPin, NoPin, NoPin},                  //SPI4
//         {NoPin, NoPin, NoPin},                  //SPI5
//     },
//     5,							// Number of drivers
//     {PE_3, PD_6, PD_1, PC_7, PD_13}, // enablePins
//     {PE_2, PD_5, PA_15, PD_15, PD_11},  // stepPins
//     {PE_1, PD_4, PA_8, PD_14, PD_10},	// dirPins
// #if TMC_SOFT_UART
//     {PE_0, PD_3, PD_0, PC_6, PD_12},	// uartpins
//     5,							// Smart drivers
// #endif
//     0,							// digiPot Factor
// #if HAS_VOLTAGE_MONITOR
//     NoPin,
// #endif
//     PC_13,
// };

constexpr PinEntry PinTable_BTT_OCTOPUS[] =
{
    //Thermistors
    {PF_3, "bedtemp,tb"},
    {PF_4, "e0temp,th0"},
    {PF_5, "e1temp,th1"},
    {PF_6, "e2temp,th2"},
    {PF_7, "e3temp,th3"},

    //Endstops
    {PG_6, "xstop,x-stop"},
    {PG_9, "ystop,y-stop"},
    {PG_10, "zstop,z-stop"},
    {PG_11, "e0stop,e0det"},
    {PG_12, "e1stop,e1det"},
    {PG_13, "e2stop,e2det"},
    {PG_14, "e3stop,e3det"},
    {PG_15, "e4stop,e4det"},

    //Servos
    {PB_6,  "servo0" },

    //Probe
    {PB_7, "probe"},

    //Heaters and Fans (Big and Small Mosfets}
    {PA_1,  "bed,hbed" },
    {PA_2,  "e0heat,heat0" },
    {PA_3,  "e1heat,heat1" },
    {PB_10, "e2heat,heat2" },
    {PB_11, "e3heat,heat3" },
    {PA_8,  "fan0,fan" },
    {PE_5,  "fan1" },
    {PD_12, "fan2" },
    {PD_13, "fan3" },
    {PD_14, "fan4" },
    {PD_15, "fan5" },

    //EXP1
    {PE_10, "LCDCS"},
    {PB_2, "LCDENCA"},
    {PB_1, "LCDENCB"},
    {PE_8, "LCDBEEP"},
    {PE_7, "LCDBTN"},
    {PE_12, "LCDD4"},
    {PE_9, "LCDEN"},

    //Neopixel
    {PB_0, "Neopixel,PB0"},

    //TFT
    {PA_9, "TX1,tft-tx"},
    {PA_10, "RX1,tft-rx"},

    //WIFI UART
    {PD_8, "PD8"},
    {PD_9, "PD9"},

    //SPI
    {PC_4, "X-CS,PC4"},
    {PD_11, "Y-CS,PD11"},
    {PC_6, "Z-CS,PC6"},
    {PC_7, "E0-CS,PC7"},
    {PF_2, "E1-CS,PF2"},
    {PE_4, "E2-CS,PE4"},
    {PE_1, "E3-CS,PE1"},
    {PD_3, "E4-CS,PD3"},
    {PA_6, "MISO,PA6"},
    {PA_7, "MOSI,PA7"},
    {PA_5, "SCK,PA5"},

    //I2C
    {PB_8, "SCL1,PB8"},
    {PB_9, "SDA1,PB9"},

    //WIFI
    {PG_7,  "PG7"}, //RST
    {PD_7,  "PD7"}, //IO0
    {PD_10, "PD10"}, //IO4
    {PB_12, "PB12"}, //CS
    {PB_13, "PB13"}, //CLK
    {PC_2,  "PC2"}, //MISO
    {PC_3,  "PC3"}, //MOSI

    //PSON
    {PE_11, "PSON,PE11"},

    //PWRDET
    {PC_0, "PWRDET,PC0"},

    //Status LED
    {PA_13, "LED,PA13"},
};

constexpr BoardDefaults btt_octopus_Defaults = {
    {0xb75b00a7},                 				// Signatures
    SD_SDIO,                                  // SD Card access
    {   //CLK, MISO, MOSI
        {PA_5, PA_6, PA_7},                     //SPI0
        {PB_13, PC_2, PC_3},                  //SPI1
        {PB_3,  PB_4,  PB_5},                     //SPI2
        {NoPin, NoPin, NoPin},                  //SPI3
        {NoPin, NoPin, NoPin},                  //SPI4
        {NoPin, NoPin, NoPin},                  //SPI5
    },
    8,							// Number of drivers
    {PF_14, PF_15, PG_5, PA_0, PG_2, PF_1, PD_4, PE_0}, // enablePins
    {PF_13, PG_0, PF_11, PG_4, PF_9, PC_13, PE_2, PE_6},  // stepPins
    {PF_12, PG_1, PG_3, PC_1, PF_10, PF_0, PE_3, PA_14},	// dirPins
#if TMC_SOFT_UART
    {PC_4, PD_11, PC_6, PC_7, PF_2, PE_4, PE_1, PD_3},	// uartpins
    8,							// Smart drivers
#endif
    0,							// digiPot Factor
#if HAS_VOLTAGE_MONITOR
    NoPin,
#endif
    NoPin,
};

#endif