// Configuration for RepRapWiFi

#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#define NO_WIFI_SLEEP	0

#define VERSION_MAIN	"1.26-01"

#ifdef LPCRRF
#ifdef EXTENDED_LISTEN
#define VERSION_HOSTSYS "LE"
#else
#define VERSION_HOSTSYS "L"
#endif
#elif defined(STM32F4)
#define VERSION_HOSTSYS "S"
#else
#define VERSION_HOSTSYS "D"
#endif

#if NO_WIFI_SLEEP
#define VERSION_SLEEP	"-nosleep"
#else
#define VERSION_SLEEP	""
#endif

#ifdef DEBUG
#define VERSION_DEBUG	"-D"
#else
#define VERSION_DEBUG	""
#endif

const char* const firmwareVersion = VERSION_MAIN VERSION_HOSTSYS VERSION_DEBUG VERSION_SLEEP;

// Define the maximum length (bytes) of file upload data per SPI packet. Use a multiple of the SD card sector or cluster size for efficiency.
// ************ This must be kept in step with the corresponding value in RepRapFirmware *************
const uint32_t maxSpiFileData = 2048;

// Define the SPI clock register
// Useful values of the register are:
// 0x1001	40MHz 1:1
// 0x2001	26.7MHz 1:2
// 0x2402	26.7MHz 1:2
// 0x2002	26.7MHz 2:1
// 0x3043	20MHz 2:2

// Define the SPI clock frequency
#ifdef LPCRRF
//SD:: LPC as a slave can only up to 1/12th PCLK. 7M was getting some errors, 6M seems stable.
const uint32_t defaultClockControl = 0x181001; //  80MHz/7/2 5.71MHz 1:1
#elif defined(STM32F4)
const uint32_t defaultClockControl = 0x4002;	// 80MHz/5 16MHz 3:2 - maybe!
#else
// The SAM occasionally transmits incorrect data at 40MHz, so we now use 26.7MHz.
// Due to the 15ns SCLK to MISO delay of the SAMD51, 2:1 is preferred over 1:2
const uint32_t defaultClockControl = 0x2002;		// 80MHz/3, mark:space 2:1
#endif


// Pin numbers
const int SamSSPin = 15;          // GPIO15, output to SAM, SS pin for SPI transfer
const int EspReqTransferPin = 0;  // GPIO0, output, indicates to the SAM that we want to send something
const int SamTfrReadyPin = 4;     // GPIO4, input, indicates that SAM is ready to execute an SPI transaction

const uint8_t Backlog = 8;

#define ARRAY_SIZE(_x) (sizeof(_x)/sizeof((_x)[0]))

#ifdef DEBUG
#define debugPrint(_str)			ets_printf("%s(%d): %s", __FILE__, __LINE__, _str)
#define debugPrintf(_format, ...)	ets_printf("%s(%d): ", __FILE__, __LINE__); ets_printf(_format, __VA_ARGS__)
#else
#define debugPrint(_format)			do {} while(false)
#define debugPrintf(_format, ...)	do {} while(false)
#endif

#define debugPrintAlways(_str)			ets_printf("%s(%d): %s", __FILE__, __LINE__, _str)
#define debugPrintfAlways(_format, ...)	ets_printf("%s(%d): ", __FILE__, __LINE__); ets_printf(_format, __VA_ARGS__)

#endif
