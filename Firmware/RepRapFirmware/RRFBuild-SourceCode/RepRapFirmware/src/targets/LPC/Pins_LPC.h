#ifndef PINS_LPC_H__
#define PINS_LPC_H__

#include "Microstepping.h"
#include "sd_mmc.h"
#include "RepRapFirmware.h"
#include "chip.h"
#include "NVMEmulation.h"

#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif

#define FIRMWARE_NAME "RepRapFirmware for LPC176x based Boards"

// Default board type
#define DEFAULT_BOARD_TYPE BoardType::Lpc
#define ELECTRONICS "LPC176x"
#define LPC_ELECTRONICS_STRING "LPC176x"
#define LPC_BOARD_STRING "LPC176x"

#define FIRMWARE_FILE       "firmware.bin"
#define WIFI_FIRMWARE_FILE  "DuetWiFiServer.bin" // Firmware to be loaded onto the ESP board

//needed to compile
#define IAP_FIRMWARE_FILE       "firmware.bin"
#define IAP_UPDATE_FILE         "N/A"
#define IAP_UPDATE_FILE_SBC     "firmware.bin"
#define IAP_IMAGE_START         0

#define FLASH_DATA_LENGTH (32*1024) //size of the Software Reset Data in Flash (Last Sector = 32K)


#if defined(ESP8266WIFI)
    constexpr size_t NumFirmwareUpdateModules = 5;        // 3 modules, plus one for manual upload to WiFi module (module 2 is now unused)
#else
    constexpr size_t NumFirmwareUpdateModules = 5;
#endif

// Features definition
#define SUPPORT_OBJECT_MODEL             1
#define HAS_CPU_TEMP_SENSOR		         0	// enabling the CPU temperature sensor disables Due pin 13 due to bug in SAM3X
#define HAS_HIGH_SPEED_SD		         0
#define HAS_VOLTAGE_MONITOR		         0
#define ACTIVE_LOW_HEAT_ON		         0
#define HAS_VREF_MONITOR                 0

#define SUPPORT_INKJET		             0	// set nonzero to support inkjet control
#define SUPPORT_ROLAND		             0	// set nonzero to support Roland mill
#define SUPPORT_SCANNER		             0	// set nonzero to support FreeLSS scanners
#define SUPPORT_IOBITS		             0	// set to support P parameter in G0/G1 commands
#define SUPPORT_DHT_SENSOR	             0	// set nonzero to support DHT temperature/humidity sensors
#define SUPPORT_WORKPLACE_COORDINATES    1
#define SUPPORT_LASER                    1

#define SUPPORT_FTP                      0

#define HAS_ATX_POWER_MONITOR            1

#define SUPPORT_LED_STRIPS               1
#define SUPPORT_ASYNC_MOVES		         0
#define ALLOCATE_DEFAULT_PORTS           0

#if defined(LPC_NETWORKING)
    //LPC Ethernet
    #define HAS_RTOSPLUSTCP_NETWORKING   1
    #define SUPPORT_12864_LCD            0
    #define HAS_WIFI_NETWORKING          0
    #define HAS_MASS_STORAGE             1
    #define SUPPORT_TELNET               0

    #define BOARD_NAME          "LPC176x Ethernet"
    #define BOARD_SHORT_NAME    "LPCEth"

#elif defined(ESP8266WIFI)
    #define HAS_RTOSPLUSTCP_NETWORKING   0
    #define SUPPORT_12864_LCD            0
    #define HAS_WIFI_NETWORKING          1
    #define HAS_MASS_STORAGE             1
    #define SUPPORT_TELNET               0

    #define BOARD_NAME          "LPC176x WiFi"
    #define BOARD_SHORT_NAME    "LPCWiFi"

#elif defined(LPC_SBC)
    #define HAS_RTOSPLUSTCP_NETWORKING   0
    #define SUPPORT_12864_LCD            0
    #define HAS_WIFI_NETWORKING          0
    #define HAS_MASS_STORAGE             0
    #define HAS_LINUX_INTERFACE          1
    #define SUPPORT_TELNET               1

    #define BOARD_NAME          "LPC176x SBC"
    #define BOARD_SHORT_NAME    "LPCSBC"

#else
    #define HAS_RTOSPLUSTCP_NETWORKING   0
    #define SUPPORT_12864_LCD            1
    #define HAS_WIFI_NETWORKING          0
    #define HAS_MASS_STORAGE             1
    #define SUPPORT_TELNET               0

    #define BOARD_NAME          "LPC176x"
    #define BOARD_SHORT_NAME    "LPC"

#endif


// The physical capabilities of the machine
constexpr size_t NumDirectDrivers = 7;               // The maximum number of drives supported by the electronics
#if defined(SUPPORT_TMC22xx)
    constexpr size_t MaxSmartDrivers = NumDirectDrivers;            // The maximum number of smart drivers
    constexpr size_t NumTmcDriversSenseChannels = 1;
    #define TMC_SOFT_UART                   1
    #define TMC22xx_HAS_ENABLE_PINS			1
    #define TMC22xx_VARIABLE_NUM_DRIVERS	1
    #define TMC22xx_USE_SLAVEADDR           0
    #define TMC22xx_HAS_MUX                 0
    #define HAS_STALL_DETECT                1
#else
    constexpr size_t MaxSmartDrivers = 0;            // The maximum number of smart drivers
    #define TMC_SOFT_UART 0
#endif

constexpr size_t MaxSensors = 32;

constexpr size_t MaxHeaters = 3;                     // The maximum number of heaters in the machine
constexpr size_t MaxMonitorsPerHeater = 2;

constexpr size_t MaxBedHeaters = 1;
constexpr size_t MaxChamberHeaters = 1;
constexpr int8_t DefaultBedHeater = 0;
constexpr int8_t DefaultE0Heater = 1;                // Index of the default first extruder heater, used only for the legacy status response

constexpr size_t NumThermistorInputs = 4;

constexpr size_t MaxZProbes = 1;
constexpr size_t MaxGpInPorts = 5;
constexpr size_t MaxGpOutPorts = 5;

constexpr size_t MinAxes = 3;                        // The minimum and default number of axes
constexpr size_t MaxAxes = 5;                        // The maximum number of movement axes in the machine, usually just X, Y and Z, <= DRIVES
constexpr size_t MaxDriversPerAxis = 3;              // The maximum number of stepper drivers assigned to one axis

constexpr size_t MaxExtruders = 2;                   // The maximum number of extruders
constexpr size_t NumDefaultExtruders = 1;            // The number of drivers that we configure as extruders by default

constexpr size_t MaxAxesPlusExtruders = 7;

constexpr size_t MaxHeatersPerTool = 2;
constexpr size_t MaxExtrudersPerTool = 2;

constexpr size_t MaxFans = 3;

constexpr unsigned int MaxTriggers = 16;            // Must be <= 32 because we store a bitmap of pending triggers in a uint32_t

constexpr size_t MaxSpindles = 2;                    // Maximum number of configurable spindles

//Steppers
// HAS_SMART_DRIVERS is defined in Pins.h, we duplicate it for the board files to use
#define HAS_SMART_DRIVERS		(SUPPORT_TMC2660 || SUPPORT_TMC22xx || SUPPORT_TMC51xx)
extern Pin ENABLE_PINS[NumDirectDrivers];
extern Pin STEP_PINS[NumDirectDrivers];
extern Pin DIRECTION_PINS[NumDirectDrivers];
#if HAS_SMART_DRIVERS
extern Pin DriverDiagPins[NumDirectDrivers];
extern size_t totalSmartDrivers;
extern size_t num5160SmartDrivers;
extern Pin TMC_PINS[NumDirectDrivers];
#endif
#if TMC_SOFT_UART
    constexpr Pin GlobalTmc22xxEnablePin = NoPin;			// The pin that drives ENN of all drivers
    constexpr uint32_t DriversBaudRate = 50000;
#endif

extern uint32_t STEP_DRIVER_MASK; // Mask for parallel write to all steppers on port 2 (calculated in after loading board.txt)
extern bool hasStepPinsOnDifferentPorts;
extern bool hasDriverCurrentControl;
extern float digipotFactor;

constexpr uint32_t DefaultStandstillCurrentPercent = 100;

//Smoothie uses MCP4451 for current control
// Indices for motor current digipots (X,Y,Z,E) - E is on 2nd digipot chip
constexpr uint8_t POT_WIPES[5] = { 0, 1, 2, 3, 0};


// HEATERS - The bed is assumed to be the at index 0
extern Pin TEMP_SENSE_PINS[NumThermistorInputs];

// Default thermistor betas
constexpr float BED_R25 = 100000.0;
constexpr float BED_BETA = 3988.0;
constexpr float BED_SHC = 0.0;
constexpr float EXT_R25 = 100000.0;
constexpr float EXT_BETA = 4388.0;
constexpr float EXT_SHC = 0.0;

// Thermistor series resistor value in Ohms
constexpr float DefaultThermistorSeriesR = 4700.0;

constexpr size_t MaxSpiTempSensors = 2;
extern Pin SpiTempSensorCsPins[MaxSpiTempSensors];  // Digital pins the 31855s have their select lines tied to
extern SSPChannel TempSensorSSPChannel;

#if HAS_LINUX_INTERFACE
    extern Pin SbcTfrReadyPin;
    extern Pin SbcCsPin;
#endif

// Power control
extern Pin ATX_POWER_PIN;// Digital pin number that controls the ATX power on/off
extern bool ATX_POWER_INVERTED;
extern bool ATX_INITIAL_POWER_ON;
extern bool ATX_POWER_STATE;

//SD: Internal SDCard is on SSP1
//    MOSI, MISO, SCLK, CS
//    P0_9, P0_8, P0_7, P0_6

//SD:: 2nd SDCard can be connected to SSP0
//    MOSI, MISO, SCLK
//    P0_18 P0_17 P0_15

// SD cards
constexpr size_t NumSdCards = _DRIVES; //_DRIVES is defined in CoreLPC (and used by FatFS) allow one internal and one external
extern Pin SdCardDetectPins[NumSdCards];
constexpr Pin SdWriteProtectPins[NumSdCards] = { NoPin }; //unused on LPC boards
extern Pin SdSpiCSPins[NumSdCards];
extern uint32_t InternalSDCardFrequency;
extern uint32_t ExternalSDCardFrequency;
extern SSPChannel ExternalSDCardSSPChannel;


//LCD
constexpr uint32_t LcdSpiClockFrequency = 2000000;    // 2.0MHz
extern SSPChannel LcdSpiChannel;
extern Pin LcdCSPin;
extern Pin LcdA0Pin;
extern Pin LcdBeepPin;
extern Pin EncoderPinA;
extern Pin EncoderPinB;
extern Pin EncoderPinSw;
extern Pin PanelButtonPin;

extern Pin DiagPin;
constexpr bool DiagOnPolarity = true;

extern bool ADCEnablePreFilter;

constexpr size_t NumSoftwareSPIPins = 3;
extern Pin SoftwareSPIPins[3]; //GPIO pins for softwareSPI (used with SharedSPI)
constexpr size_t NumSSP0Pins = 4;
extern Pin SSP0Pins[];         //GPIO pins for SSP0 (used with SharedSPI)


#define SERIAL_AUX_DEVICE   UART_Slot0
#define SERIAL_WIFI_DEVICE  UART_Slot1
//#define SERIAL_AUX2_DEVICE  UART_Slot2

constexpr size_t NumSerialChannels = 2;				// The number of serial IO channels (USB + AUX)
constexpr size_t NumberSerialPins = 2;
extern Pin AuxSerialRxTxPins[NumberSerialPins];

#if defined(SERIAL_AUX2_DEVICE)
    extern Pin Aux2SerialRxTxPins[NumberSerialPins];
#endif

// Use TX0/RX0 for the auxiliary serial line
#if defined(__MBED__)
    #define SERIAL_MAIN_DEVICE  Serial0 //TX0/RX0 connected to via seperate USB
#else
    #define SERIAL_MAIN_DEVICE  Serial  //USB
#endif


#if defined(ESP8266WIFI)
    extern Pin EspDataReadyPin;
    extern Pin SamTfrReadyPin;
    extern Pin EspResetPin;
    constexpr Pin SamCsPin = P0_16; //CS for SSP0
    constexpr LPC175X_6X_IRQn_Type ESP_SPI_IRQn = SSP0_IRQn;

    extern Pin APIN_Serial1_TXD;
    extern Pin APIN_Serial1_RXD;
    extern Pin WifiSerialRxTxPins[NumberSerialPins];

    // Compatibility with existing RRF Code
    constexpr Pin APIN_ESP_SPI_MISO = SPI0_MISO;
    constexpr Pin APIN_ESP_SPI_SCK = SPI0_SCK;
    constexpr SSPChannel ESP_SPI = SSP0;

#endif

#if SUPPORT_LED_STRIPS
extern Pin NeopixelOutPin;
#endif

//Timer 0 is used for Step Generation
#define STEP_TC             (LPC_TIMER0)
#define STEP_TC_IRQN        TIMER0_IRQn
#define STEP_TC_HANDLER     TIMER0_IRQHandler

extern volatile uint32_t BrownoutEvents;

struct PinEntry
{
    Pin GetPin() const  noexcept{ return pin; }
    const char* GetNames() const  noexcept{ return names; }
    
    Pin pin;
    const char *names;
};

extern PinEntry *PinTable;
extern size_t NumNamedLPCPins;



bool LookupPinName(const char *pn, LogicalPin& lpin, bool& hardwareInverted) noexcept;
const char *GetPinNames(LogicalPin lp) noexcept;

#if ALLOCATE_DEFAULT_PORTS
constexpr const char *DefaultEndstopPinNames[] = { "nil", "nil", "nil" };
constexpr const char *DefaultZProbePinNames = "nil";
constexpr const char *DefaultFanPinNames[] = { "nil", "nil" };
constexpr PwmFrequency DefaultFanPwmFrequencies[] = { DefaultFanPwmFreq };
#endif


//Boards

bool SetBoard(const char* bn)  noexcept;
void ClearPinArrays() noexcept;

constexpr size_t MaxBoardNameLength = 20;
extern char lpcBoardName[MaxBoardNameLength];

struct BoardDefaults
{
    const uint32_t numDrivers;
    const Pin enablePins[NumDirectDrivers];
    const Pin stepPins[NumDirectDrivers];
    const Pin dirPins[NumDirectDrivers];
#if HAS_SMART_DRIVERS
    const Pin uartPins[NumDirectDrivers];
    const uint32_t numSmartDrivers;
#endif
    const float digipotFactor;    
};

struct BoardEntry
{
    const char *boardName;
    const PinEntry *boardPinTable;
    const size_t numNamedEntries;
    const BoardDefaults defaults;
};


#include "Boards/AzteegX5Mini.h"
#include "Boards/ReArm.h"
#include "Boards/Mbed.h"
#include "Boards/Smoothieboard.h"
#include "Boards/MKSSBase.h"
#include "Boards/MKSSGenL.h"
#include "Boards/AzsmzMini.h"
#include "Boards/BIQU_SKR.h"
#include "Boards/Generic.h"
#include "Boards/FLY_CDY.h"


//Known boards with built in stepper configurations and pin table 
constexpr BoardEntry LPC_Boards[] =
{
#if defined(__MBED__)
    {"mbed",             PinTable_Mbed,             ARRAY_SIZE(PinTable_Mbed),             mbedDefaults}, //for debugging
#else
    {"generic",          PinTable_Generic,          ARRAY_SIZE(PinTable_Generic),          genericDefaults},

    //known boards
    {"smoothieboard",    PinTable_Smoothieboard,    ARRAY_SIZE(PinTable_Smoothieboard),    smoothieBoardDefaults},
    {"rearm",            PinTable_Rearm,            ARRAY_SIZE(PinTable_Rearm),            rearmDefaults},
    {"mkssbase_1.3",     PinTable_MKSSbase1_3,      ARRAY_SIZE(PinTable_MKSSbase1_3),      mkssbase1_3_Defaults},
	{"mkssgenl_1.0",     PinTable_MKSSGenL1_0,      ARRAY_SIZE(PinTable_MKSSGenL1_0),      mkssgenl1_0_Defaults},
	{"mkssgenl_2.0",     PinTable_MKSSGenL2_0,      ARRAY_SIZE(PinTable_MKSSGenL2_0),      mkssgenl2_0_Defaults},
    {"azsmzmini",        PinTable_AZSMZ,            ARRAY_SIZE(PinTable_AZSMZ),            azsmzDefaults},
    {"biquskr_1.1",      PinTable_BIQU_SKR_v1_1,    ARRAY_SIZE(PinTable_BIQU_SKR_v1_1),    biquskr_1_1_Defaults},
    {"biquskr_1.3",      PinTable_BIQU_SKR_v1_3,    ARRAY_SIZE(PinTable_BIQU_SKR_v1_3),    biquskr_1_3_Defaults},
    {"biquskr_1.4",      PinTable_BIQU_SKR_v1_4,    ARRAY_SIZE(PinTable_BIQU_SKR_v1_4),    biquskr_1_4_Defaults},
    {"biquskr_e3t",      PinTable_BIQU_SKR_E3T,     ARRAY_SIZE(PinTable_BIQU_SKR_E3T),     biquskr_E3T_Defaults},
    {"azteegx5mini_1.1", PinTable_AzteegX5MiniV1_1, ARRAY_SIZE(PinTable_AzteegX5MiniV1_1), azteegX5Mini1_1Defaults},
	{"azteegx5mini_2",   PinTable_AzteegX5MiniV2,   ARRAY_SIZE(PinTable_AzteegX5MiniV2),   azteegX5Mini2Defaults},
    {"azteegx5mini_3",   PinTable_AzteegX5MiniV3,   ARRAY_SIZE(PinTable_AzteegX5MiniV3),   azteegX5Mini3Defaults},
    {"fly_cdy",          PinTable_FLY_CDY,          ARRAY_SIZE(PinTable_FLY_CDY),          FLY_CDY_Defaults},
#endif
};


//This needs to be const as its used in other places to create arrays
//Use the largest size which is the "generic" pintable
constexpr unsigned int NumNamedPins = P_END;



namespace StepPins
{
    // *** These next three functions must use the same bit assignments in the drivers bitmap ***
    // Each stepper driver must be assigned one bit in a 32-bit word, in such a way that multiple drivers can be stepped efficiently
    // and more or less simultaneously by doing parallel writes to several bits in one or more output ports.
    // All our step pins are on port D, so the bitmap is just the map of step bits in port D.
    
    // Calculate the step bit for a driver. This doesn't need to be fast. It must return 0 if the driver is remote.
    static inline uint32_t CalcDriverBitmap(size_t driver)  noexcept
    {
        if (driver >= NumDirectDrivers)
        {
            return 0;
        }

        if(STEP_PINS[driver] == NoPin ) return 0;
        if(hasStepPinsOnDifferentPorts == true )
        {
            //treat these pins one by one instead of parallel writes for now. Using driver pos in bitmap
            return 1u << driver ;
        }
        //Pins are on the same port,
        return 1u << (STEP_PINS[driver] & 0x1f); //lower 5-bits contains the bit number of a 32bit port
    }
    
    // Set the specified step pins high
    // This needs to be as fast as possible, so we do a parallel write to the port(s).
    static inline void StepDriversHigh(uint32_t driverMap)  noexcept
    {
        if(hasStepPinsOnDifferentPorts == true )
        {
            //Using driver pos in bitmap to match position in STEP_PINS
            uint8_t pos=0;
            while (driverMap!=0 && pos < NumDirectDrivers)
            {
                if(driverMap & 0x01)
                {
                    if(STEP_PINS[pos] != NoPin) GPIO_PinWrite(STEP_PINS[pos], 1); //set high
                }
                driverMap = driverMap >> 1;
                pos++;
            }
        }
        else
        {
            //pins all on port 2, parallel write
            LPC_GPIO2->SET = driverMap;
        }
    }
    
    // Set all step pins low
    // This needs to be as fast as possible, so we do a parallel write to the port(s).
    // We rely on only those port bits that are step pins being set in the STEP_DRIVER_MASK variable
    static inline void StepDriversLow(uint32_t driverMap) noexcept
    {
        if(hasStepPinsOnDifferentPorts == true )
        {
            //Using driver pos in bitmap to match position in STEP_PINS
            uint8_t pos=0;
            while (driverMap!=0 && pos < NumDirectDrivers)
            {
                if(driverMap & 0x01)
                {
                    if(STEP_PINS[pos] != NoPin) GPIO_PinWrite(STEP_PINS[pos], 0); //set low
                }
                driverMap = driverMap >> 1;
                pos++;
            }
        }
        else
        {
            //pins all on port 2, parallel write
            LPC_GPIO2->CLR = STEP_DRIVER_MASK; //clear only pins that are 1 in the mask
        }
    }
}




#endif