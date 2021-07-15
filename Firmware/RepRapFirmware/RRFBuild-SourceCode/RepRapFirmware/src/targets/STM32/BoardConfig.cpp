/*
 * Board Config
 *
 *  Created on: 3 Feb 2019
 *      Author: sdavi
 */



#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include "Version.h"
#include "BoardConfig.h"
#include "RepRapFirmware.h"
#include "GCodes/GCodeResult.h"
#include "sd_mmc.h"
#include "SPI.h"
#include "HardwareSPI.h"
#include "Platform/Platform.h"

#include "HybridPWM.h"
#include "ff.h"
#include "SoftwareReset.h"
#include "ExceptionHandlers.h"

#include "pinmap.h"
//Single entry for Board name
static const boardConfigEntry_t boardEntryConfig[]=
{
    {"lpc.board", &lpcBoardName, nullptr, cvStringType},
    {"board", &lpcBoardName, nullptr, cvStringType},
};

//All other board configs
static const boardConfigEntry_t boardConfigs[]=
{
    {"leds.diagnostic", &DiagPin, nullptr, cvPinType},

    //Steppers
    {"stepper.powerEnablePin", &StepperPowerEnablePin, nullptr, cvPinType},
    {"stepper.enablePins", ENABLE_PINS, &MaxTotalDrivers, cvPinType},
    {"stepper.stepPins", STEP_PINS, &MaxTotalDrivers, cvPinType},
    {"stepper.directionPins", DIRECTION_PINS, &MaxTotalDrivers, cvPinType},
    {"stepper.digipotFactor", &digipotFactor, nullptr, cvFloatType},
#if HAS_SMART_DRIVERS
    {"stepper.TmcUartPins", TMC_PINS, &MaxTotalDrivers, cvPinType},
    {"stepper.numSmartDrivers", &totalSmartDrivers, nullptr, cvUint32Type},
#if SUPPORT_TMC51xx
    {"stepper.num5160Drivers", &num5160SmartDrivers, nullptr, cvUint32Type},
    {"stepper.spiChannel", &SmartDriversSpiChannel, nullptr, cvUint8Type},
#endif
#if HAS_STALL_DETECT && SUPPORT_TMC22xx
    {"stepper.TmcDiagPins", DriverDiagPins, &MaxTotalDrivers, cvPinType},
#endif
#endif
    //Heater sensors
    {"heat.tempSensePins", TEMP_SENSE_PINS, &NumThermistorInputs, cvPinType},
    {"heat.spiTempSensorCSPins", SpiTempSensorCsPins, &MaxSpiTempSensors, cvPinType},
    {"heat.spiTempSensorChannel", &TempSensorSSPChannel, nullptr, cvUint8Type},
    
    //ATX Power
    {"atx.powerPin", &ATX_POWER_PIN, nullptr, cvPinType},
    {"atx.powerPinInverted", &ATX_POWER_INVERTED, nullptr, cvBoolType},
    {"atx.initialPowerOn", &ATX_INITIAL_POWER_ON, nullptr, cvBoolType},

    //SDCards
    {"sdCard.internal.spiFrequencyHz", &InternalSDCardFrequency, nullptr, cvUint32Type},
    {"sdCard.external.csPin", &SdSpiCSPins[1], nullptr, cvPinType},
    {"sdCard.external.cardDetectPin", &SdCardDetectPins[1], nullptr, cvPinType},
    {"sdCard.external.spiFrequencyHz", &ExternalSDCardFrequency, nullptr, cvUint32Type},
    {"sdCard.external.spiChannel", &ExternalSDCardSSPChannel, nullptr, cvUint8Type},

#if SUPPORT_12864_LCD
    {"lcd.lcdCSPin", &LcdCSPin, nullptr, cvPinType},
    {"lcd.lcdBeepPin", &LcdBeepPin, nullptr, cvPinType},
    {"lcd.encoderPinA", &EncoderPinA, nullptr, cvPinType},
    {"lcd.encoderPinB", &EncoderPinB, nullptr, cvPinType},
    {"lcd.encoderPinSw", &EncoderPinSw, nullptr, cvPinType},
    {"lcd.lcdDCPin", &LcdA0Pin, nullptr, cvPinType},
    {"lcd.panelButtonPin", &PanelButtonPin, nullptr, cvPinType},
    {"lcd.spiChannel", &LcdSpiChannel, nullptr, cvUint8Type},
#endif
    
    {"softwareSPI.pins", SPIPins[3], &NumSPIPins, cvPinType}, //SCK, MISO, MOSI
    {"SPI0.pins", SPIPins[0], &NumSPIPins, cvPinType}, //SCK, MISO, MOSI
    {"SPI1.pins", SPIPins[1], &NumSPIPins, cvPinType}, //SCK, MISO, MOSI
    {"SPI2.pins", SPIPins[2], &NumSPIPins, cvPinType}, //SCK, MISO, MOSI
    {"SPI3.pins", SPIPins[3], &NumSPIPins, cvPinType}, //SCK, MISO, MOSI
    {"SPI4.pins", SPIPins[4], &NumSPIPins, cvPinType}, //SCK, MISO, MOSI
    {"SPI5.pins", SPIPins[5], &NumSPIPins, cvPinType}, //SCK, MISO, MOSI
    
#if HAS_WIFI_NETWORKING
    {"8266wifi.espDataReadyPin", &EspDataReadyPin, nullptr, cvPinType},
    {"8266wifi.lpcTfrReadyPin", &SamTfrReadyPin, nullptr, cvPinType},
    {"8266wifi.TfrReadyPin", &SamTfrReadyPin, nullptr, cvPinType},
    {"8266wifi.espResetPin", &EspResetPin, nullptr, cvPinType},
    {"8266wifi.csPin", &SamCsPin, nullptr, cvPinType},
    {"8266wifi.serialRxTxPins", &WifiSerialRxTxPins, &NumberSerialPins, cvPinType},
    {"8266wifi.spiChannel", &WiFiSpiChannel, nullptr, cvUint8Type},    
#endif

#if HAS_LINUX_INTERFACE
    {"sbc.lpcTfrReadyPin", &SbcTfrReadyPin, nullptr, cvPinType},
    {"sbc.TfrReadyPin", &SbcTfrReadyPin, nullptr, cvPinType},
    {"sbc.csPin", &SbcCsPin, nullptr, cvPinType},
    {"sbc.spiChannel", &SbcSpiChannel, nullptr, cvUint8Type},    
#endif

#if defined(SERIAL_AUX_DEVICE)
    {"serial.aux.rxTxPins", &AuxSerialRxTxPins, &NumberSerialPins, cvPinType},
#endif
#if defined(SERIAL_AUX2_DEVICE)
    {"serial.aux2.rxTxPins", &Aux2SerialRxTxPins, &NumberSerialPins, cvPinType},
#endif
    
    {"adc.prefilter.enable", &ADCEnablePreFilter, nullptr, cvBoolType},

#if SUPPORT_LED_STRIPS
    {"led.neopixelPin", &NeopixelOutPin, nullptr, cvPinType},
#endif

#if HAS_VOLTAGE_MONITOR
    {"power.VInDetectPin", &PowerMonitorVinDetectPin, nullptr, cvPinType},
    {"power.voltage", &VInDummyReading, nullptr, cvUint32Type},
#endif
#if SUPPORT_ACCELEROMETERS
    {"accelerometer.spiChannel", &AccelerometerSpiChannel, nullptr, cvUint8Type},
#endif

};

uint32_t crc32_for_byte(uint32_t r) 
{
    for(int j = 0; j < 8; ++j)
        r = (r & 1? 0: (uint32_t)0xEDB88320L) ^ r >> 1;
    return r ^ (uint32_t)0xFF000000L;
}

uint32_t crc32(const void *data, size_t n_bytes) 
{
    uint32_t table[0x100];
    uint32_t crc = 0;

    for(size_t i = 0; i < 0x100; ++i)
        table[i] = crc32_for_byte(i);
    for(size_t i = 0; i < n_bytes; ++i)
        crc = table[(uint8_t)crc ^ ((uint8_t*)data)[i]] ^ crc >> 8;
    return crc;
}


#if !HAS_MASS_STORAGE
// Provide dummy functions for locks etc. for ff when mass storage is disabled

extern "C"
{
    // Create a sync object. We already created it, we just need to copy the handle.
    int ff_cre_syncobj (BYTE vol, FF_SYNC_t* psy) noexcept
    {
        return 1;
    }

    // Lock sync object
    int ff_req_grant (FF_SYNC_t sy) noexcept
    {
        return 1;
    }

    // Unlock sync object
    void ff_rel_grant (FF_SYNC_t sy) noexcept
    {
    }

    // Delete a sync object
    int ff_del_syncobj (FF_SYNC_t sy) noexcept
    {
        return 1;        // nothing to do, we never delete the mutex
    }
}
#endif

static inline bool isSpaceOrTab(char c) noexcept
{
    return (c == ' ' || c == '\t');
}
    
BoardConfig::BoardConfig() noexcept
{
}

static void ConfigureGPIOPins() noexcept
{
    // loop through and set and pins that have special requirements from the board settings
    for (size_t lp = 0; lp < NumNamedLPCPins; ++lp)
    {
        switch (PinTable[lp].names[0])
        {
            case '+':
                pinMode(PinTable[lp].pin, OUTPUT_HIGH);
                break;
            case '-':
                pinMode(PinTable[lp].pin, OUTPUT_LOW);
                break;
            case '^':
                pinMode(PinTable[lp].pin, INPUT_PULLUP);
                break;
            default:
                break;
        }
    }
    // Handle special cases
    //Init pins for LCD
    //make sure to init ButtonPin as input incase user presses button
    if(PanelButtonPin != NoPin) pinMode(PanelButtonPin, INPUT); //unused
    if(LcdA0Pin != NoPin) pinMode(LcdA0Pin, OUTPUT_HIGH); //unused
    if(LcdBeepPin != NoPin) pinMode(LcdBeepPin, OUTPUT_LOW);
    // Set the 12864 display CS pin low to prevent it from receiving garbage due to other SPI traffic
    if(LcdCSPin != NoPin) pinMode(LcdCSPin, OUTPUT_LOW);

    //Init Diagnostcs Pin
    pinMode(DiagPin, OUTPUT_LOW);

    // Configure ATX power control
    if (ATX_POWER_PIN != NoPin)
        pinMode(ATX_POWER_PIN, (ATX_INITIAL_POWER_ON ^ ATX_POWER_INVERTED ? OUTPUT_HIGH : OUTPUT_LOW));
    if (StepperPowerEnablePin != NoPin)
        pinMode(StepperPowerEnablePin, OUTPUT_LOW);
}

static void ConfigureSPIPins(SSPChannel dev, Pin clk, Pin miso, Pin mosi)
{
    // Configure a single SPI device, we use DMA on SPI2 and SPI3
    switch(dev)
    {
    case SSP2:
        SPI::getSSPDevice(dev)->initPins(clk, miso, mosi, NoPin, DMA1_Stream3, DMA_CHANNEL_0, DMA1_Stream3_IRQn, DMA1_Stream4, DMA_CHANNEL_0, DMA1_Stream4_IRQn);
        break;
    case SSP3:
        SPI::getSSPDevice(dev)->initPins(clk, miso, mosi, NoPin, DMA1_Stream0, DMA_CHANNEL_0, DMA1_Stream0_IRQn, DMA1_Stream5, DMA_CHANNEL_0, DMA1_Stream5_IRQn);
        break;
    default:
        SPI::getSSPDevice(dev)->initPins(clk, miso, mosi, NoPin);
        break;
    }
}


// static char *ReadTerminal()
// {
//     static uint32_t pos;
//     static char line[20];
//     if (SERIAL_MAIN_DEVICE.available())
//     {
//         int ch = SERIAL_MAIN_DEVICE.read();
//         if ((ch == '\n' || ch == '\r') && pos > 0)
//         {
//             line[pos] = '\0';
//             pos = 0;
//             return line;
//         }
//         if (ch >= 0 && pos < 20)
//             line[pos++] = ch;
//     }
//     return (char *)"";
// }

static void FatalError(const char* fmt, ...)
{
    for(;;)
    {
        va_list vargs;
        va_start(vargs, fmt);
        reprap.GetPlatform().DebugMessage(fmt, vargs);
        va_end(vargs);
        delay(2000);
    }
}

#if 0
static void CheckDriverPins() noexcept
{
    for(size_t i=0; i<MaxTotalDrivers; i++)
    {
        if (ENABLE_PINS[i] != NoPin && STEP_PINS[i] != NoPin && DIRECTION_PINS[i] != NoPin)
        {
            pinMode(ENABLE_PINS[i], INPUT);
            bool state1 = IoPort::ReadPin(ENABLE_PINS[i]);
            pinMode(STEP_PINS[i], OUTPUT_LOW);
            delay(50);
            bool state2 = IoPort::ReadPin(ENABLE_PINS[i]);
            pinMode(STEP_PINS[i], INPUT);
            if (state1 != state2 && state2 == false)
            {
                FatalError("Possible short between step and enable pins on driver %d.\nPlease check driver installation/configuration.\n", i);
            }
        }
    }
}
#endif


// static void UnknownHardware(uint32_t sig)
// {
//     for(;;)
//     {
//         debugPrintf("\nRRF has been unable to identify the current hardware.\n");
//         debugPrintf("This may be because it is a new board or has a new bootloader installed.\n");
//         debugPrintf("To register the hardware configuration please contact TeamGloomy via our\n");
//         debugPrintf("discord server (https://discord.gg/uS97Qs7) and supply details of\n");
//         debugPrintf("the board and the board signature(0x%x).\n", (unsigned)sig);
//         debugPrintf("\nRRF can try and discover how to mount the SD card, but doing this may\n");
//         debugPrintf("turn on heaters or other devices. If you wish to continue with this automatic\n");
//         debugPrintf("search please ensure there is a valid SD card inserted in\n");
//         debugPrintf("the reader and type \"yes\".\n");
//         debugPrintf("Confirm automatic discovery: ");
//         for(int i = 0; i < 10000; i++)
//         {
//             delay(1);
//             char *line = ReadTerminal();
//             if (StringEqualsIgnoreCase(line, "yes"))
//                 return;
//             if (StringEqualsIgnoreCase(line, "pins"))
//             {
//                 for (int p = 0; p < P_END; p++)
//                 {
//                     uint32_t mode = pin_get_function((Pin)p);
//                     debugPrintf("Pin %c.%d fmode 0x%x (mode %x afnum %x)\n", (p >> 4) + 'A', (p & 0xf), (unsigned)mode, (unsigned)STM_PIN_FUNCTION(mode), (unsigned)STM_PIN_AFNUM(mode));
//                 }
//             }
//         }
//         debugPrintf("\n\n");
//     }
// }

// Determine how to access the SD card
static uint32_t signature;

typedef struct {
    SSPChannel device;
    Pin pins[6];
    uint32_t mode[6];
} SDCardConfig;

// These are our known SD card configurations
static constexpr SDCardConfig SDCardConfigs[] = {
    // {SSP1, {PA_5, PA_6, PB_5, PA_4, NoPin, NoPin}, {0x502, 0x502, 0x502, 0x1}}, // SKR Pro
    // {SSP1, {PA_5, PA_6, PA_7, PA_4, NoPin, NoPin}, {0x502, 0x502, 0x502, 0x1}}, // GTR
    {SSPSDIO, {PC_8, PC_9, PC_10, PC_11, PC_12, PD_2}, {0xc02, 0xc02, 0xc02, 0xc02, 0xc02, 0xc02}}, // Fly/SDIO
    // {SSP3, {PC_10, PC_11, PC_12, PC_9, NoPin, NoPin}, {0x602, 0x602, 0x602, 0x1}}, // MKS?
};

static bool TryConfig(FATFS *fs)
{
    const SDCardConfig *conf = &SDCardConfigs[0];
    // if (conf->device != SSPSDIO)
    // {
    //     ConfigureSPIPins(conf->device, conf->pins[0], conf->pins[1], conf->pins[2]);
    //     sd_mmc_setSSPChannel(0, conf->device, conf->pins[3]);
    // }
    // else
        sd_mmc_setSSPChannel(0, conf->device, NoPin);
    FRESULT rslt= f_mount (fs, "0:", 1);
    if (rslt == FR_OK)
    {
        return true;
    }
    // mount failed reset I/O pins to inputs
    // if (conf->device != SSPSDIO)
    //     ((HardwareSPI *)(SPI::getSSPDevice(conf->device)))->disable();
    for (size_t i = 0; i < ARRAY_SIZE(conf->pins); i++)
        pinMode(conf->pins[i], INPUT);    
    sd_mmc_setSSPChannel(0, SSPNONE, NoPin);
    return false;
}    

// static bool CheckPinConfig(uint32_t config)
// {
//     // check to see if the pins are currently set in the expected state
//     // The bootloader on many boards will leave the pins configured after
//     // accessing the SD card.
//     const SDCardConfig *conf = &SDCardConfigs[config];
//     for(size_t i = 0; i < ARRAY_SIZE(conf->pins); i++)
//         if (conf->pins[i] != NoPin && pin_get_function(conf->pins[i]) != conf->mode[i])
//             return false;
//     return true;
// }


static SSPChannel InitSDCard(uint32_t boardSig, FATFS *fs)
{
    // int conf = SD_NONE;
    // // First try to find a matching board
    // // for(uint32_t i = 0; i < ARRAY_SIZE(LPC_Boards) && conf == SD_NONE; i++)
    // //     for(uint32_t j = 0; j < MaxSignatures && conf == SD_NONE; j++)
    //         if (LPC_Boards[0].defaults.signatures[j] == boardSig)
    //         {
    //             conf = LPC_Boards[0].defaults.SDConfig;
    //             debugPrintf("Sig match 0x%x %d board %s SDConfig %d\n", (unsigned) boardSig, (int)i, LPC_Boards[i].boardName, conf);
    //         }
            
    // if (conf == SD_NONE)
    // {
    //     // failed to find matching signature, see if the bootloader has left things configured
    //     for(uint32_t i = 0; i < ARRAY_SIZE(SDCardConfigs); i++)
    //         if (CheckPinConfig(i))
    //         {
    //             conf = i;
    //             debugPrintf("loader match %d\n", (int)i);
    //         }
    // }

    // if (conf == SD_NONE)
    // {
    //     UnknownHardware(boardSig);
    // }
    // else
    // {
    //     for(int i = 0; i < 30; i++)
    //     {
    //         if (TryConfig(conf, fs))
    //             return SDCardConfigs[conf].device;
    //         debugPrintf("Unable to mount SD card. Please insert a card.\n");
    //         delay(2000);
    //     }
    //     FatalError("Unable to mount SD card, board signature is 0x%x.\n", (unsigned)boardSig);
    // }

    // // Now try each config in turn
    // for(uint32_t i = 0; i < ARRAY_SIZE(SDCardConfigs); i++)
    // {
    //     if (TryConfig(i, fs))
    //     {
    //         debugPrintf("SD card interface %d selected\n", (int)i);
    //         return SDCardConfigs[i].device;
    //     }
    // }
    if (TryConfig(fs))
    {
        debugPrintf("SD card interface %d selected\n", (int)0);
        return SDCardConfigs[0].device;
    }
    FatalError("Failed to mount SD card\n");
    return SSPNONE;
}

extern char _sccmram;						// defined in linker script
extern char _eccmram;					// defined in linker script

void BoardConfig::Init() noexcept
{

    constexpr char boardConfigPath[] = "0:/sys/board.txt";
    FIL configFile;
    FATFS *fs = new FATFS;
    FRESULT rslt;
    SSPChannel sdChannel;

    signature = crc32((char *)0x8000000, 8192);
    // We need to setup DMA and SPI devices before we can use File I/O
    // Using DMA2 for both TMC UART and the SD card causes corruption problems (see STM errata) so for now we use
    // polled I/O for the disk.
    NVIC_SetPriority(DMA2_Stream6_IRQn, NvicPrioritySpi);
    NVIC_SetPriority(DMA2_Stream3_IRQn, NvicPrioritySpi);
    NVIC_SetPriority(SDIO_IRQn, NvicPrioritySDIO);
    
    NVIC_SetPriority(DMA1_Stream3_IRQn, NvicPrioritySpi);
    NVIC_SetPriority(DMA1_Stream4_IRQn, NvicPrioritySpi);
    NVIC_SetPriority(DMA1_Stream0_IRQn, NvicPrioritySpi);
    NVIC_SetPriority(DMA1_Stream5_IRQn, NvicPrioritySpi);
#if STARTUP_DELAY
    delay(STARTUP_DELAY);
#endif
    ClearPinArrays();
#if !HAS_MASS_STORAGE
    sd_mmc_init(SdWriteProtectPins, SdSpiCSPins);
#endif
    // Mount the internal SD card
    sdChannel = InitSDCard(signature, fs);
    if (sdChannel != SSPNONE)
    {
        //Open File
        rslt = f_open (&configFile, boardConfigPath, FA_READ);
        if (rslt != FR_OK)
        {
            f_unmount ("0:");
            FatalError("Unable to read board configuration: %s...\n",boardConfigPath );
            return;
        }
    }
    else
    {
        // failed to mount card
        FatalError("Failed to mount sd card\n");
        return;
    }
    if(rslt == FR_OK)
    {
            
        reprap.GetPlatform().MessageF(UsbMessage, "Loading config from %s...\n", boardConfigPath );

        //First find the board entry to load the correct PinTable for looking up Pin by name
        BoardConfig::GetConfigKeys(&configFile, boardEntryConfig, (size_t) ARRAY_SIZE(boardEntryConfig));
        if(!SetBoard(lpcBoardName)) // load the Correct PinTable for the defined Board (RRF3)
        {
            //Failed to find string in known boards array
            SafeStrncpy(lpcBoardName, "generic", 8); //replace the string in lpcBoardName to "generic"
        }

        //Load all other config settings now that PinTable is loaded.
        f_lseek(&configFile, 0); //go back to beginning of config file
        BoardConfig::GetConfigKeys(&configFile, boardConfigs, (size_t) ARRAY_SIZE(boardConfigs));
        f_close(&configFile);
        f_unmount ("0:");
        delete fs;
        //Calculate STEP_DRIVER_MASK (used for parallel writes)
        STEP_DRIVER_MASK = 0;
        // Currently not implemented for STM32
        #if 0
        for(size_t i=0; i<MaxTotalDrivers; i++)
        {
            //It is assumed all pins will be on Port 2
            const Pin stepPin = STEP_PINS[i];
            if( stepPin != NoPin && (stepPin >> 5) == 2) // divide by 32 to get port number
            {
                STEP_DRIVER_MASK |= (1 << (stepPin & 0x1f)); //this is a bitmask of all the stepper pins on Port2 used for Parallel Writes
            }
            else
            {
                if(stepPin != NoPin)
                {
                    // configured step pins are not on the same port - not using parallel writes
                    hasStepPinsOnDifferentPorts = true;
                }
            }
        }
        #endif
        hasStepPinsOnDifferentPorts = true;
        
        //Does board have built in current control via digipots?
        if(digipotFactor > 1)
        {
            hasDriverCurrentControl = true;
        }
#if 0
        // anti-rotation detection feature disabled for now due to potential to damage some drivers
        CheckDriverPins();
#endif       
        //Setup the SPI Pins, note that the SD SPI device may already have been configured
        for(size_t i = 0; i < ARRAY_SIZE(SPIPins); i++)
            if (sdChannel != (SSPChannel)i)
                ConfigureSPIPins((SSPChannel)i, SPIPins[i][0], SPIPins[i][1], SPIPins[i][2]);
#if HAS_MASS_STORAGE
        // Set internal SD card frequency (if supported)
        sd_mmc_reinit_slot(0, NoPin, InternalSDCardFrequency);
        if (ExternalSDCardSSPChannel != SSPNONE && SdSpiCSPins[1] != NoPin)
        {
            sd_mmc_setSSPChannel(1, ExternalSDCardSSPChannel, SdSpiCSPins[1]);
            sd_mmc_reinit_slot(1, NoPin, ExternalSDCardFrequency);
        }
        // Update RRF settings
        MassStorage::Init2();
#endif
// FIXME
#if 0
        //Internal SDCard SPI Frequency
        sd_mmc_reinit_slot(0, SdSpiCSPins[0], InternalSDCardFrequency);
        
        //Configure the External SDCard
        if(SdSpiCSPins[1] != NoPin)
        {
            setPullup(SdCardDetectPins[1], true);
            //set the SSP Channel for External SDCard
            if(ExternalSDCardSSPChannel == SSP1 || ExternalSDCardSSPChannel == SSP2 || ExternalSDCardSSPChannel == SWSPI0)
            {
                sd_mmc_setSSPChannel(1, ExternalSDCardSSPChannel); //must be called before reinit
            }
            //set the CSPin and the frequency for the External SDCard
            sd_mmc_reinit_slot(1, SdSpiCSPins[1], ExternalSDCardFrequency);
        }
#endif
    #if HAS_LINUX_INTERFACE
        if(SbcCsPin != NoPin) pinMode(SbcCsPin, INPUT_PULLUP);
    #endif
    #if HAS_WIFI_NETWORKING
        if(SamCsPin != NoPin) pinMode(SamCsPin, OUTPUT_LOW);
        if(EspResetPin != NoPin) pinMode(EspResetPin, OUTPUT_LOW);
        
        if(WifiSerialRxTxPins[0] != NoPin && WifiSerialRxTxPins[1] != NoPin)
        {
            //Setup the Serial Port for ESP Wifi
            APIN_Serial1_RXD = WifiSerialRxTxPins[0];
            APIN_Serial1_TXD = WifiSerialRxTxPins[1];
            
            if(!SERIAL_WIFI_DEVICE.Configure(WifiSerialRxTxPins[0], WifiSerialRxTxPins[1]))
            {
                reprap.GetPlatform().MessageF(UsbMessage, "Failed to set WIFI Serial with pins %c.%d and %c.%d.\n", 'A'+(WifiSerialRxTxPins[0] >> 4), (WifiSerialRxTxPins[0] & 0xF), 'A'+(WifiSerialRxTxPins[1] >> 4), (WifiSerialRxTxPins[1] & 0xF) );
            }
        }
    #endif

    #if defined(SERIAL_AUX_DEVICE)
        //Configure Aux Serial
        if(AuxSerialRxTxPins[0] != NoPin && AuxSerialRxTxPins[1] != NoPin)
        {
            if(!SERIAL_AUX_DEVICE.Configure(AuxSerialRxTxPins[0], AuxSerialRxTxPins[1]))
            {
                reprap.GetPlatform().MessageF(UsbMessage, "Failed to set AUX Serial with pins %c.%d and %c.%d.\n", 'A'+(AuxSerialRxTxPins[0] >> 4), (AuxSerialRxTxPins[0] & 0xF), 'A'+(AuxSerialRxTxPins[1] >> 4), (AuxSerialRxTxPins[1] & 0xF) );
            }

        }
    #endif

    #if defined(SERIAL_AUX2_DEVICE)
        //Configure Aux2 Serial
        if(Aux2SerialRxTxPins[0] != NoPin && Aux2SerialRxTxPins[1] != NoPin)
        {
            if(!SERIAL_AUX2_DEVICE.Configure(Aux2SerialRxTxPins[0], Aux2SerialRxTxPins[1]))
            {
                reprap.GetPlatform().MessageF(UsbMessage, "Failed to set AUX2 Serial with pins %d.%d and %d.%d.\n", (Aux2SerialRxTxPins[0] >> 5), (Aux2SerialRxTxPins[0] & 0x1F), (Aux2SerialRxTxPins[1] >> 5), (Aux2SerialRxTxPins[1] & 0x1F) );
            }

        }
    #endif

        ConfigureGPIOPins();
    }
}


//Convert a pin string into a RRF Pin
//Handle formats such as A.23, A_23, PA_23 or PA.23
Pin BoardConfig::StringToPin(const char *strvalue) noexcept
{
    if(strvalue == nullptr) return NoPin;
    
    if(tolower(*strvalue) == 'p') strvalue++; //skip P
    //check size.. should be 3chars or 4 chars i.e. 0.1, 2.25, 1_23. 2nd char should be . or _
    uint8_t len = strlen(strvalue);
    if(((len == 3 || len == 4) && (*(strvalue+1) == '.' || *(strvalue+1) == '_')) || (len == 2 || len == 3))
    {
        const char *ptr = nullptr;
        const char ch = toupper(*strvalue);
        uint8_t port = ch - 'A';
        if(port <= 8)
        {
            // skip "." or "_"
            if ((*(strvalue+1) == '.' || *(strvalue+1) == '_'))
                strvalue += 2;
            else
                strvalue += 1;
            uint8_t pin = StrToI32(strvalue, &ptr);          
            if(ptr > strvalue && pin < 16)
            {
                //Convert the Port and Pin to match the arrays in CoreSTM
                Pin lpcpin = (Pin) ( (port << 4) | pin);
                return lpcpin;
            }
        }
    }
    
    return NoPin;
}

Pin BoardConfig::LookupPin(char *strvalue) noexcept
{
    //Lookup a pin by name
    LogicalPin lp;
    bool hwInverted;
    
    //convert string to lower case for LookupPinName
    for(char *l = strvalue; *l; l++) *l = tolower(*l);
    
    if(LookupPinName(strvalue, lp, hwInverted))
    {
        return (Pin)lp; //lookup succeeded, return the Pin
    }
                     
    //pin may not be in the pintable so check if the format is a correct pin (returns NoPin if not)
    return StringToPin(strvalue);
}



void BoardConfig::PrintValue(MessageType mtype, configValueType configType, void *variable) noexcept
{
    switch(configType)
    {
        case cvPinType:
            {
                Pin pin = *(Pin *)(variable);
                if(pin == NoPin)
                {
                    reprap.GetPlatform().MessageF(mtype, "NoPin ");
                }
                else
                {
                    reprap.GetPlatform().MessageF(mtype, "%c.%d ", 'A' + (pin >> 4), (pin & 0xF) );
                }
            }
            break;
        case cvBoolType:
            reprap.GetPlatform().MessageF(mtype, "%s ", (*(bool *)(variable) == true)?"true":"false" );
            break;
        case cvFloatType:
            reprap.GetPlatform().MessageF(mtype, "%.2f ",  (double) *(float *)(variable) );
            break;
        case cvUint8Type:
            reprap.GetPlatform().MessageF(mtype, "%u ",  *(uint8_t *)(variable) );
            break;
        case cvUint16Type:
            reprap.GetPlatform().MessageF(mtype, "%d ",  *(uint16_t *)(variable) );
            break;
        case cvUint32Type:
            reprap.GetPlatform().MessageF(mtype, "%lu ",  *(uint32_t *)(variable) );
            break;
        case cvStringType:
            reprap.GetPlatform().MessageF(mtype, "%s ",  (char *)(variable) );
            break;
        default:{
            
        }
    }
}


//Information printed by M122 P200
void BoardConfig::Diagnostics(MessageType mtype) noexcept
{
    reprap.GetPlatform().Message(mtype, "=== Diagnostics ===\n");

#ifdef DUET_NG
# if HAS_LINUX_INTERFACE
	reprap.GetPlatform().MessageF(mtype, "%s version %s running on %s (%s mode)", FIRMWARE_NAME, VERSION, reprap.GetPlatform().GetElectronicsString(),
						(reprap.UsingLinuxInterface()) ? "SBC" : "standalone");
# else
	reprap.GetPlatform().MessageF(mtype, "%s version %s running on %s", FIRMWARE_NAME, VERSION, reprap.GetPlatform().GetElectronicsString());
# endif
	const char* const expansionName = DuetExpansion::GetExpansionBoardName();
	reprap.GetPlatform().MessageF(mtype, (expansionName == nullptr) ? "\n" : " + %s\n", expansionName);
#elif LPC17xx
	reprap.GetPlatform().MessageF(mtype, "%s (%s) version %s running on %s at %dMhz\n", FIRMWARE_NAME, lpcBoardName, VERSION, reprap.GetPlatform().GetElectronicsString(), (int)SystemCoreClock/1000000);
#elif HAS_LINUX_INTERFACE
	reprap.GetPlatform().MessageF(mtype, "%s version %s running on %s (%s mode)\n", FIRMWARE_NAME, VERSION, reprap.GetPlatform().GetElectronicsString(),
						(reprap.UsingLinuxInterface()) ? "SBC" : "standalone");
#else
	reprap.GetPlatform().MessageF(mtype, "%s version %s running on %s\n", FIRMWARE_NAME, VERSION, reprap.GetPlatform().GetElectronicsString());
#endif

    reprap.GetPlatform().MessageF(mtype, "\n== Configurable Board.txt Settings ==\n");
    //Print the board name
    boardConfigEntry_t board = boardEntryConfig[1];
    reprap.GetPlatform().MessageF(mtype, "%s = ", board.key );
    BoardConfig::PrintValue(mtype, board.type, board.variable);
    reprap.GetPlatform().MessageF(mtype, "  Signature 0x%x\n\n", (unsigned int)signature);
    
    //Print rest of board configurations
    const size_t numConfigs = ARRAY_SIZE(boardConfigs);
    for(size_t i=0; i<numConfigs; i++)
    {
        boardConfigEntry_t next = boardConfigs[i];

        reprap.GetPlatform().MessageF(mtype, "%s = ", next.key );
        if(next.maxArrayEntries != nullptr)
        {
            reprap.GetPlatform().MessageF(mtype, "{ ");
            for(size_t p=0; p<*(next.maxArrayEntries); p++)
            {
                //TODO:: handle other values
                if(next.type == cvPinType){
                    BoardConfig::PrintValue(mtype, next.type, (void *)&((Pin *)(next.variable))[p]);
                }
            }
            reprap.GetPlatform().MessageF(mtype, "}\n");
        }
        else
        {
            BoardConfig::PrintValue(mtype, next.type, next.variable);
            reprap.GetPlatform().MessageF(mtype, "\n");

        }
    }

    // Display all pins
    reprap.GetPlatform().MessageF(mtype, "\n== Defined Pins ==\n");
    for (size_t lp = 0; lp < NumNamedLPCPins; ++lp)
    {
        reprap.GetPlatform().MessageF(mtype, "%s = ", PinTable[lp].names );
        BoardConfig::PrintValue(mtype, cvPinType, &PinTable[lp].pin);
        reprap.GetPlatform().MessageF(mtype, "\n");
    }
    
#if defined(SERIAL_AUX_DEVICE) || defined(SERIAL_AUX2_DEVICE) || HAS_WIFI_NETWORKING
    reprap.GetPlatform().MessageF(mtype, "\n== Hardware Serial ==\n");
    #if defined(SERIAL_AUX_DEVICE)
        reprap.GetPlatform().MessageF(mtype, "AUX Serial: %s%c\n", ((SERIAL_AUX_DEVICE.GetUARTPortNumber() == -1)?"Disabled": "UART "), (SERIAL_AUX_DEVICE.GetUARTPortNumber() == -1)?' ': ('0' + SERIAL_AUX_DEVICE.GetUARTPortNumber()));
    #endif
    #if defined(SERIAL_AUX2_DEVICE)
        reprap.GetPlatform().MessageF(mtype, "AUX2 Serial: %s%c\n", ((SERIAL_AUX2_DEVICE.GetUARTPortNumber() == -1)?"Disabled": "UART "), (SERIAL_AUX2_DEVICE.GetUARTPortNumber() == -1)?' ': ('0' + SERIAL_AUX2_DEVICE.GetUARTPortNumber()));
    #endif
    #if HAS_WIFI_NETWORKING
        reprap.GetPlatform().MessageF(mtype, "WIFI Serial: %s%c\n", ((SERIAL_WIFI_DEVICE.GetUARTPortNumber() == -1)?"Disabled": "UART "), (SERIAL_WIFI_DEVICE.GetUARTPortNumber() == -1)?' ': ('0' + SERIAL_WIFI_DEVICE.GetUARTPortNumber()));
    #endif
#endif
    
    

    reprap.GetPlatform().MessageF(mtype, "\n== PWM ==\n");
    for(uint8_t i=0; i<MaxPWMChannels; i++)
    {
		String<StringLength256> status;
		PWMPins[i].appendStatus(status.GetRef());
		reprap.GetPlatform().MessageF(mtype, "%u: %s\n", i, status.c_str());
	}

    reprap.GetPlatform().MessageF(mtype, "\n== MCU ==\n");
    reprap.GetPlatform().MessageF(mtype, "TS_CAL1 (30C) = %d\n", (int) (*TEMPSENSOR_CAL1_ADDR));
    reprap.GetPlatform().MessageF(mtype, "TS_CAL2 (110C) = %d\n", (int) (*TEMPSENSOR_CAL2_ADDR));
    reprap.GetPlatform().MessageF(mtype, "V_REFINCAL (30C 3.3V) = %d\n\n", (int) (*VREFINT_CAL_ADDR));
    uint32_t vrefintraw = AnalogInReadChannel(LegacyAnalogIn::GetVREFAdcChannel());
    float vref = 3.3f*((float)(GET_ADC_CAL(VREFINT_CAL_ADDR, VREFINT_CAL_DEF)))/(float)(vrefintraw >> (LegacyAnalogIn::AdcBits - 12));
    reprap.GetPlatform().MessageF(mtype, "V_REFINT raw %d\n", (int) vrefintraw);
    reprap.GetPlatform().MessageF(mtype, "V_REF  %f\n\n", (double)vref);
    float tmcuraw = (float)AnalogInReadChannel(LegacyAnalogIn::GetTemperatureAdcChannel());
    reprap.GetPlatform().MessageF(mtype, "T_MCU raw %d\n", (int) tmcuraw);
    reprap.GetPlatform().MessageF(mtype, "T_MCU cal %f\n", (double)(((110.0f - 30.0f)/(((float)(GET_ADC_CAL(TEMPSENSOR_CAL2_ADDR, TEMPSENSOR_CAL2_DEF))) - ((float)(GET_ADC_CAL(TEMPSENSOR_CAL1_ADDR, TEMPSENSOR_CAL1_DEF))))) * ((float)(tmcuraw / (float) (1 << (LegacyAnalogIn::AdcBits - 12))) - ((float)(GET_ADC_CAL(TEMPSENSOR_CAL1_ADDR, TEMPSENSOR_CAL1_DEF)))) + 30.0f)); 
    reprap.GetPlatform().MessageF(mtype, "T_MCU calc %f\n\n", (double)(((tmcuraw*3.3f)/(float)((1 << LegacyAnalogIn::AdcBits) - 1) - 0.76f)/0.0025f + 25.0f));
    tmcuraw = tmcuraw*vref/3.3f; 
    reprap.GetPlatform().MessageF(mtype, "T_MCU raw (corrected) %d\n", (int) tmcuraw);
    reprap.GetPlatform().MessageF(mtype, "T_MCU cal (corrected) %f\n", (double)(((110.0f - 30.0f)/(((float)(GET_ADC_CAL(TEMPSENSOR_CAL2_ADDR, TEMPSENSOR_CAL2_DEF))) - ((float)(GET_ADC_CAL(TEMPSENSOR_CAL1_ADDR, TEMPSENSOR_CAL1_DEF))))) * ((float)(tmcuraw / (float) (1 << (LegacyAnalogIn::AdcBits - 12))) - ((float)(GET_ADC_CAL(TEMPSENSOR_CAL1_ADDR, TEMPSENSOR_CAL1_DEF)))) + 30.0f)); 
    reprap.GetPlatform().MessageF(mtype, "T_MCU calc (corrected) %f\n", (double)(((tmcuraw*3.3f)/(float)((1 << LegacyAnalogIn::AdcBits) - 1) - 0.76f)/0.0025f + 25.0f));

}

void BoardConfig::PrintPinArray(MessageType mtype, Pin arr[], uint16_t numEntries) noexcept
{
    reprap.GetPlatform().MessageF(mtype, "[ ");
    for(uint8_t i=0; i<numEntries; i++)
    {
        if(arr[i] != NoPin)
        {
            reprap.GetPlatform().MessageF(mtype, "%d.%d ", (arr[i]>>5), (arr[i] & 0x1f));
        }
        else
        {
            reprap.GetPlatform().MessageF(mtype, "NoPin ");
        }
        
    }
    reprap.GetPlatform().MessageF(mtype, "]\n");
}


//Set a variable from a string using the specified data type
void BoardConfig::SetValueFromString(configValueType type, void *variable, char *valuePtr) noexcept
{
    switch(type)
    {
        case cvPinType:
            *(Pin *)(variable) = LookupPin(valuePtr);
            break;
            
        case cvBoolType:
            {
                bool res = false;
                
                if(strlen(valuePtr) == 1)
                {
                    //check for 0 or 1
                    if(valuePtr[0] == '1') res = true;
                }
                else if(strlen(valuePtr) == 4 && StringEqualsIgnoreCase(valuePtr, "true"))
                {
                    res = true;
                }
                *(bool *)(variable) = res;
            }
            break;
            
        case cvFloatType:
            {
                const char *ptr = nullptr;
                *(float *)(variable) = SafeStrtof(valuePtr, &ptr);
            }
            break;
        case cvUint8Type:
            {
                const char *ptr = nullptr;
                uint8_t val = StrToU32(valuePtr, &ptr);
                if(val < 0) val = 0;
                if(val > 0xFF) val = 0xFF;
                
                *(uint8_t *)(variable) = val;
            }
            break;
        case cvUint16Type:
            {
                const char *ptr = nullptr;
                uint16_t val = StrToU32(valuePtr, &ptr);
                if(val < 0) val = 0;
                if(val > 0xFFFF) val = 0xFFFF;
                
                *(uint16_t *)(variable) = val;
                    
            }
            break;
        case cvUint32Type:
            {
                const char *ptr = nullptr;
                *(uint32_t *)(variable) = StrToU32(valuePtr, &ptr);
            }
            break;
            
        case cvStringType:
            {
                
                //TODO:: string Type only handles Board Name variable
                if(strlen(valuePtr)+1 < MaxBoardNameLength)
                {
                    strcpy((char *)(variable), valuePtr);
                }
            }
            break;
            
        default:
            debugPrintf("Unhandled ValueType\n");
    }
}

static size_t ReadLine(FIL *fp, char *p, int len)
{
    int nc = 0;
    UINT rc;
    uint8_t s;
    len -= 1;    /* Make a room for the terminator */
    while (nc < len)
    {
        f_read(fp, &s, 1, &rc);
        if (rc != 1)
        {
            if (nc == 0) return -1;
            break;
        }
        if (s == '\r') continue;
        if (s == '\n') break;
        *p++ = s; nc++;
    }
    *p = 0;        /* Terminate the string */
    return nc;
}

bool BoardConfig::GetConfigKeys(FIL *configFile, const boardConfigEntry_t *boardConfigEntryArray, const size_t numConfigs) noexcept
{
    constexpr size_t maxLineLength = 120;
    char line[maxLineLength];

    int readLen = ReadLine(configFile, line, maxLineLength);
    while(readLen >= 0)
    {
        size_t len = (size_t) readLen;
        size_t pos = 0;
        while(pos < len && line[pos] != 0 && isSpaceOrTab(line[pos])) pos++; //eat leading whitespace

        if(pos < len){

            //check for comments
            if(line[pos] == '/' || line[pos] == '#')
            {
                //Comment - Skipping
            }
            else
            {
                const char* key = line + pos;
                while(pos < len && !isSpaceOrTab(line[pos]) && line[pos] != '=' && line[pos] != 0) pos++;
                line[pos] = 0;// null terminate the string (now contains the "key")

                pos++;

                //eat whitespace and = if needed
                while(pos < maxLineLength && line[pos] != 0 && (isSpaceOrTab(line[pos]) == true || line[pos] == '=') ) pos++; //skip spaces and =

                //debugPrintf("Key: %s", key);

                if(pos < len && line[pos] == '{')
                {
                    // { indicates the start of an array
                    //debugPrintf(" { ");
                    pos++; //skip the {

                    //Array of Values:
                    //TODO:: only Pin arrays are currently implemented
                    
                    //const size_t numConfigs = ARRAY_SIZE(boardConfigs);
                    for(size_t i=0; i<numConfigs; i++)
                    {
                        boardConfigEntry_t next = boardConfigEntryArray[i];
                        //Currently only handles Arrays of Pins
                        
                        
                        if(next.maxArrayEntries != nullptr /*&& next.type == cvPinType*/ && StringEqualsIgnoreCase(key, next.key))
                        {
                            //matched an entry in boardConfigEntryArray

                            //create a temp array to read into. Only copy the array entries into the final destination when we know the array is properly defined
                            const size_t maxArraySize = *next.maxArrayEntries;
                            
                            //Pin Array Type
                            Pin readArray[maxArraySize];

                            //eat whitespace
                            while(pos < maxLineLength && line[pos] != 0 && isSpaceOrTab(line[pos]) == true ) pos++;

                            bool searching = true;

                            size_t arrIdx = 0;

                            //search for values in Array
                            while( searching )
                            {
                                if(pos < maxLineLength)
                                {

                                    while(pos < maxLineLength && (isSpaceOrTab(line[pos]) == true)) pos++; // eat whitespace

                                    if(pos == maxLineLength)
                                    {
                                        debugPrintf("Got to end of line before end of array, line must be longer than maxLineLength");
                                        searching = false;
                                        break;
                                    }

                                    bool closedSuccessfully = false;
                                    //check brace isnt closed
                                    if(pos < maxLineLength && line[pos] == '}')
                                    {
                                        closedSuccessfully = true;
                                        arrIdx--; // we got the closing brace before getting a value this round, decrement arrIdx
                                    }
                                    else
                                    {

                                        if(arrIdx >= maxArraySize )
                                        {
                                            debugPrintf("Error : Too many entries defined in config for array\n");
                                            searching = false;
                                            break;
                                        }

                                        //Try to Read the next Value

                                        //should be at first char of value now
                                        char *valuePtr = line+pos;

                                        //read until end condition - space,comma,}  or null / # ;
                                        while(pos < maxLineLength && line[pos] != 0 && !isSpaceOrTab(line[pos]) && line[pos] != ',' && line[pos] != '}' && line[pos] != '/' && line[pos] != '#' && line[pos] != ';')
                                        {
                                            pos++;
                                        }

                                        //see if we ended due to comment, ;, or null
                                        if(pos == maxLineLength || line[pos] == 0 || line[pos] == '/' || line[pos] == '#' || line[pos]==';')
                                        {
                                            debugPrintf("Error: Array ended without Closing Brace?\n");
                                            searching = false;
                                            break;
                                        }

                                        //check if there is a closing brace after value without any whitespace, before it gets overwritten with a null
                                        if(line[pos] == '}')
                                        {
                                            closedSuccessfully = true;
                                        }

                                        line[pos] = 0; // null terminate the string

                                        //debugPrintf("%s ", valuePtr);

                                        //Put into the Temp Array
                                        if(arrIdx >= 0 && arrIdx<maxArraySize)
                                        {
                                            readArray[arrIdx] = LookupPin(valuePtr);
                                            
                                            //TODO:: HANDLE OTHER VALUE TYPES??
                                            

                                        }
                                    }

                                    if(closedSuccessfully == true)
                                    {
                                        //debugPrintf("}\n");
                                        //Array Closed - Finished Searching
                                        if(arrIdx >= 0 && arrIdx < maxArraySize) //arrIndx will be -1 if closed before reading any values
                                        {
                                            //All values read successfully, copy temp array into Final destination
                                            //dest array may be larger, dont overrite the default values
                                            for(size_t i=0; i<(arrIdx+1); i++ )
                                            {
                                                ((Pin *)(next.variable))[i] = readArray[i];
                                            }
                                            //Success!
                                            searching = false;
                                            break;

                                        }
                                        //failed to set values
                                        searching = false;
                                        break;
                                    }
                                    arrIdx++;
                                    pos++;
                                }
                                else
                                {
                                    debugPrintf("Unable to find values for Key\n");
                                    searching = false;
                                    break;
                                }
                            }//end while(searching)
                        }//end if matched key
                    }//end for

                }
                else
                {
                    //single value
                    if(pos < maxLineLength && line[pos] != 0)
                    {
                        //should be at first char of value now
                        char *valuePtr = line+pos;

                        //read until end condition - space, ;, comment, null,etc
                        while(pos < maxLineLength && line[pos] != 0 && !isSpaceOrTab(line[pos]) && line[pos] != ';' && line[pos] != '/') pos++;

                        //overrite the end condition with null....
                        line[pos] = 0; // null terminate the string (the "value")
                        //debugPrintf(" value is %s\n", valuePtr);
                        //Find the entry in boardConfigEntryArray using the key
                        //const size_t numConfigs = ARRAY_SIZE(boardConfigs);
                        for(size_t i=0; i<numConfigs; i++)
                        {
                            boardConfigEntry_t next = boardConfigEntryArray[i];
                            //Single Value config entries have nullptr for maxArrayEntries
                            if(next.maxArrayEntries == nullptr && StringEqualsIgnoreCase(key, next.key))
                            {
                                //debugPrintf("Setting value\n");
                                //match
                                BoardConfig::SetValueFromString(next.type, next.variable, valuePtr);
                            }
                        }
                    }
                }
            }
        }
        else
        {
            //Empty Line - Nothing to do here
        }

        readLen = ReadLine(configFile, line, maxLineLength); //attempt to read the next line
        //debugPrintf("ReadLine returns %d\n", readLen);
    }
    return false;
}

void assert_failed(uint8_t *file, uint32_t line)
{
    debugPrintf("Assert failed file %s line %d\n", file, (int)line);
}


#if HAS_LINUX_INTERFACE

// Routines to support firmware update from the Linux SBC.
static constexpr char firmwarePath[] = "0:/firmware.bin";
static FIL *firmwareFile = nullptr;
static FATFS *fs = nullptr;

bool BoardConfig::BeginFirmwareUpdate()
{
    bool res = true;
    FRESULT rslt;
    fs = new FATFS;
    firmwareFile = new FIL;
    rslt = f_mount (fs, "0:", 1);
    if (rslt == FR_OK)
    {
        //Open File, and zero length
        rslt = f_open (firmwareFile, firmwarePath, FA_WRITE|FA_CREATE_ALWAYS);
        if (rslt != FR_OK)
        {
            reprap.GetPlatform().MessageF(UsbMessage, "Unable to create firmware file: %s...\n", firmwarePath);
            f_unmount ("0:");
            res = false;
        }
    }
    else
    {
        // failed to mount card
        reprap.GetPlatform().MessageF(UsbMessage, "Failed to mount sd card\n");
        res = false;
    }
    if (!res)
    {
        delete firmwareFile;
        delete fs;
        firmwareFile = nullptr;
        fs = nullptr;
    }
    return res;
}

bool BoardConfig::WriteFirmwareData(const char *data, uint16_t length)
{
    FRESULT rslt;
    UINT written;
    if (firmwareFile == nullptr) return false;
    rslt = f_write(firmwareFile, data, length, &written);
    if (rslt != FR_OK || length != written)
        debugPrintf("Write to firmware file failed err %d length requested %d actual %d\n", rslt, length, written);
    return rslt == FR_OK && length == written;    
}

void BoardConfig::EndFirmwareUpdate()
{
    if (firmwareFile != nullptr)
    {
        FRESULT rslt = f_close(firmwareFile);
        if (rslt != FR_OK) debugPrintf("file close failed err %d\n", rslt);
        rslt = f_unmount("0:");
        if (rslt != FR_OK) debugPrintf("unmount failed err %d\n", rslt);
        delete fs;
        delete firmwareFile;
        fs = nullptr;
        firmwareFile = nullptr;
    }
    reprap.EmergencyStop();			// turn off heaters etc.
    debugPrintf("Restarting....\n");
    delay(1000);
    SoftwareReset(SoftwareResetReason::user); // Reboot
}
#endif




