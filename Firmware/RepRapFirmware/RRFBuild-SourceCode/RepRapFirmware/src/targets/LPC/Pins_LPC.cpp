#include "RepRapFirmware.h"
#include "Pins_LPC.h"
#include "BoardConfig.h"


//Default values for configurable variables.


//All I/Os default to input with pullup after reset (9.2.1 from manual)
//The Smoothie Bootloader turns off Pins 2.4, 2.5, 2.6 and 2.7 which are used as Heater pins

Pin TEMP_SENSE_PINS[NumThermistorInputs];
Pin SpiTempSensorCsPins[MaxSpiTempSensors] = { NoPin, NoPin };
SSPChannel TempSensorSSPChannel = SSP0;   //default SPI Temp sensor on SSP0

Pin ATX_POWER_PIN = NoPin;                  // Pin to use to control external power
bool ATX_POWER_INVERTED = false;            // Should the state of this pin be inverted
bool ATX_INITIAL_POWER_ON = true;           // Should external power be on/off at startup
bool ATX_POWER_STATE = true;                // We may not have an actual pin so use this to track state

//SDCard pins and settings
Pin SdCardDetectPins[NumSdCards] = { NoPin };
Pin SdSpiCSPins[NumSdCards] =      { P0_6 };    // Internal, external. Note:: ("slot" 0 in CORE is configured to be LCP SSP1 to match default RRF behaviour)
uint32_t ExternalSDCardFrequency = 4000000;             //default to 4MHz
#if HAS_LINUX_INTERFACE || HAS_WIFI_NETWORKING
    SSPChannel ExternalSDCardSSPChannel = SSPNONE;          // SSP0 used for network
#else
    SSPChannel ExternalSDCardSSPChannel = SSP0;             //default to SSP0
#endif
uint32_t InternalSDCardFrequency = 25000000;            //default to 25MHz


Pin LcdCSPin = NoPin;               //LCD Chip Select
Pin LcdA0Pin = NoPin;               //DataControl Pin (A0) if none used set to NoPin
Pin LcdBeepPin = NoPin;
Pin EncoderPinA = NoPin;
Pin EncoderPinB = NoPin;
Pin EncoderPinSw = NoPin;           //click
Pin PanelButtonPin = NoPin;         //Extra button on Viki and RRD Panels (reset/back etc)
SSPChannel LcdSpiChannel = SSP0;

Pin DiagPin = NoPin;

//Stepper settings
Pin ENABLE_PINS[NumDirectDrivers];
Pin STEP_PINS[NumDirectDrivers];
Pin DIRECTION_PINS[NumDirectDrivers];
#if HAS_SMART_DRIVERS
#if HAS_STALL_DETECT && SUPPORT_TMC22xx
    Pin DriverDiagPins[NumDirectDrivers];
#endif
Pin TMC_PINS[NumDirectDrivers];
size_t totalSmartDrivers;
size_t num5160SmartDrivers;
#endif
uint32_t STEP_DRIVER_MASK = 0;                          //SD: mask of the step pins on Port 2 used for writing to step pins in parallel
bool hasStepPinsOnDifferentPorts = false;               //for boards that don't have all step pins on port2
bool hasDriverCurrentControl = false;                   //Supports digipots to set stepper current
float digipotFactor = 0.0;                              //defualt factor for converting current to digipot value


Pin SoftwareSPIPins[3] = {NoPin, NoPin, NoPin};         //GPIO pins for softwareSPI (used with SharedSPI)
Pin SSP0Pins[4] = {SPI0_SCK, SPI0_MISO, SPI0_MOSI, SPI0_SSEL}; //GPIO pins for SSP0 (used with SharedSPI)


#if HAS_WIFI_NETWORKING
    Pin EspDataReadyPin = NoPin;
    Pin SamTfrReadyPin = NoPin;
    Pin EspResetPin = NoPin;

    Pin APIN_Serial1_TXD = NoPin;
    Pin APIN_Serial1_RXD = NoPin;

    Pin WifiSerialRxTxPins[NumberSerialPins] = {NoPin, NoPin};
#endif
    
//Aux Serial

#if defined(SERIAL_AUX_DEVICE)
    #if defined(__MBED__)
        Pin AuxSerialRxTxPins[NumberSerialPins] = {NoPin, NoPin}; //UART0 is the Main Serial on MBED so set Aux to nopin
    #else
        Pin AuxSerialRxTxPins[NumberSerialPins] = {P0_3, P0_2}; //Default to UART0
    #endif
#endif
#if defined(SERIAL_AUX2_DEVICE)
    Pin Aux2SerialRxTxPins[NumberSerialPins] = {NoPin, NoPin};
#endif

#if HAS_LINUX_INTERFACE
    Pin SbcTfrReadyPin = NoPin;
    Pin SbcCsPin = P0_16;
#endif

bool ADCEnablePreFilter = true;

#if SUPPORT_LED_STRIPS
Pin NeopixelOutPin = NoPin;
#endif

//BrownOut Detection
//The brownout interrupt is triggered when the supply voltage drops below approx 2.2V
//If the voltage falls below approx 1.8V the BOD will reset the CPU (and Brownout will be
//shown in M122 as the reset cause when it restarts).
//If the voltage falls below 1V this will trigger a Power-On reset (power on will be shown
//in M122 as the reset cause)
//Initial revision CPUs require Vdd to be above 3.0V as per the Errata sheet Rev. 10.4 — 17 March 2020
volatile uint32_t BrownoutEvents = 0;
void BOD_IRQHandler()
{
    BrownoutEvents++;
}

//Default to the Generic PinTable
PinEntry *PinTable = (PinEntry *) PinTable_Generic;
size_t NumNamedLPCPins = ARRAY_SIZE(PinTable_Generic);
char lpcBoardName[MaxBoardNameLength] = "generic";

bool IsEmptyPinArray(Pin *arr, size_t len) noexcept
{
    for(size_t i=0; i<len; i++)
    {
        if(arr[i] != NoPin) return false;
    }
    
    return true;
}

//If the dst array is empty, then copy the src array to dst array
void SetDefaultPinArray(const Pin *src, Pin *dst, size_t len) noexcept
{
    if(IsEmptyPinArray(dst, len))
    {
        //array is empty from board.txt config, set to defaults
        for(size_t i=0; i<len; i++)
        {
            dst[i] = src[i];
        }
    }
}

static void InitPinArray(Pin *dst, size_t len) noexcept
{
    for(size_t i=0; i<len; i++)
        dst[i] = NoPin;
}

void ClearPinArrays() noexcept
{
    //copy default settings (if not set in board.txt)
    InitPinArray(ENABLE_PINS, NumDirectDrivers);
    InitPinArray(STEP_PINS, NumDirectDrivers);
    InitPinArray(DIRECTION_PINS, NumDirectDrivers);
#if HAS_SMART_DRIVERS
    InitPinArray(TMC_PINS, NumDirectDrivers);
#endif
#if HAS_STALL_DETECT
    InitPinArray(DriverDiagPins, NumDirectDrivers);
#endif
    InitPinArray(TEMP_SENSE_PINS, NumThermistorInputs);
}


//Find Board settings from string
bool SetBoard(const char* bn) noexcept
{
    const size_t numBoards = ARRAY_SIZE(LPC_Boards);

    for(size_t i=0; i<numBoards; i++)
    {
        if(StringEqualsIgnoreCase(bn, LPC_Boards[i].boardName))
        {
            PinTable = (PinEntry *)LPC_Boards[i].boardPinTable;
            NumNamedLPCPins = LPC_Boards[i].numNamedEntries;

            //copy default settings (if not set in board.txt)
            SetDefaultPinArray(LPC_Boards[i].defaults.enablePins, ENABLE_PINS, LPC_Boards[i].defaults.numDrivers);
            SetDefaultPinArray(LPC_Boards[i].defaults.stepPins, STEP_PINS, LPC_Boards[i].defaults.numDrivers);
            SetDefaultPinArray(LPC_Boards[i].defaults.dirPins, DIRECTION_PINS, LPC_Boards[i].defaults.numDrivers);
#if HAS_SMART_DRIVERS
            SetDefaultPinArray(LPC_Boards[i].defaults.uartPins, TMC_PINS, LPC_Boards[i].defaults.numDrivers);
            totalSmartDrivers = LPC_Boards[i].defaults.numSmartDrivers;
#endif


            digipotFactor = LPC_Boards[i].defaults.digipotFactor;
                        
            return true;
        }
    }
    return false;
}



// Function to look up a pin name pass back the corresponding index into the pin table
// On this platform, the mapping from pin names to pins is fixed, so this is a simple lookup
bool LookupPinName(const char*pn, LogicalPin& lpin, bool& hardwareInverted) noexcept
{
    if (StringEqualsIgnoreCase(pn, NoPinName))
    {
        lpin = NoLogicalPin;
        hardwareInverted = false;
        return true;
    }
    
    for (size_t lp = 0; lp < NumNamedLPCPins; ++lp)
    {
        const char *q = PinTable[lp].names;
        while (*q != 0)
        {
            // Try the next alias in the list of names for this pin
            const char *p = pn;
            // skip hardware pin options
            if (*q == '+' || *q == '-' || *q == '^')
                ++q;
            bool hwInverted = (*q == '!');
            if (hwInverted)
            {
                ++q;
            }
            while (*q != ',' && *q != 0 && tolower(*p) == tolower(*q))
            {
                ++p;
                ++q;
            }
            if (*p == 0 && (*q == 0 || *q == ','))
            {
                // Found a match
                lpin = (LogicalPin)PinTable[lp].pin;
                hardwareInverted = hwInverted;
                return true;
            }
            
            // Skip to the start of the next alias
            while (*q != 0 && *q != ',')
            {
                ++q;
            }
            if (*q == ',')
            {
                ++q;
            }
        }
    }
    
    //pn did not match a label in the lookup table, so now
    //look up by classic port.pin format
    //Note: only pins in the selected board lookup table are suported.
    const Pin lpcPin = BoardConfig::StringToPin(pn);
    if(lpcPin != NoPin){
        lpin = (LogicalPin)lpcPin;
        hardwareInverted = false;
        return true;
    }
    return false;
}

// Return the string names associated with a pin
const char *GetPinNames(LogicalPin lp) noexcept
{
    for (size_t i = 0; i < NumNamedLPCPins; ++i)
    {
        if ((LogicalPin)(PinTable[i].pin) == lp)
            return PinTable[i].names;
    }
    // not found manufascture a name
    static char name[5];
    name[0] = '0' + (lp >> 5);
    name[1] = '.';
    if ((lp & 0xf) > 9)
    {
        name[2] = '1';
        name[3] = '0' + (lp & 0x1f) - 10;
        name[4] = '\0';
    }
    else
    {
        name[2] = '0' + (lp & 0x1f);
        name[4] = '\0';
    }
    // Next is very, very iffy, but ok for current usage!
    return (const char *)name;
}

