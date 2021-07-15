# CoreN2G

## Overview

This is a hardware abstraction layer for SAMD5x, SAME5x and SAMC21 processors. It performs roughly the same functions as project CoreNG does for SAM3X, SAM4E, SAM4S and SAME7 processors. However, it has been written from scratch (with help from ASF4 code) and the API is different.

The SAME5x builds are also suitable for use on SAMD processors, provided that the client does not try to use any features that are not available on the target processor, such as Ethernet or CAN.

## Main differences from CoreNG

1. This project provides a very limited API to C clients. C client files should #include <Core.h> which declares the available functions. C++ client files should #include <CoreIO.h> instead.

2. This project includes the C/C++ startup code, but not the main() function. The client must provide main(), which must set up the clocks and flash wait states and call CoreInit(). However, this project assumes standard configurations for the clocks. GCLK0 is always the main processor clock. On the SAME5x, GCLK1 is a slow clock (because only GCLK1 allows a large clock divider), GCLK2 is a raw clock from the main crystal (because the Duet 3 Mini needs that on the GCLK2 output pin which feeds the Ethernet PHY), GCLK3 runs at half the processor clock speed so that it can be used for SERCOMs, TCs and TCCs; and GCLK4 is a 48MHz clock for USB and CAN. On the SAMC21, most peripherals can run at 48MHz so they can use GCLK0. Client projects may program other generic clocks for their own use.

3. CoreInit() only initialises functions that are typically needed by all clients, such as the DMA manager. This is to avoid pulling in functions that the client may not need. In particular, the client must call AnalogIn::Init() and AnalogOut::Init() if it uses those modules.

4. Serial I/O devices and USB devices are not declared or defined in this project. The client must do that if it needs them and must declare the corresponding interrupt service routines.

5. Tables of pin functions are application-dependent; therefore they live in the application. The client application should derive the pin table entry struct from struct PinDescriptionBase provided by this project. The client must provide function GetPinDescription(Pin p) so that functions in CoreN2G can retrieve the details of a pin. It should return nullptr if the pin is out of range or otherwise not available.

6. CoreN2G is FreeRTOS-aware. There are separate build configurations using RTOS (use for running firmware) and not using RTOS (used for IAP and bootloaders).

7. Analog input is managed by a separate task, which must be created by the client. Currently, analog input is not available in non-RTOS builds.

## Functions that the client project must provide

### extern "C" void AppInit() noexcept
This is called by CoreN2G to initialise the application.

### extern "C" voidAppMain() noexcept
This is called by CoreN2G to run the application. It must not return.

### extern const PinDescriptionBase \*GetPinDescription(Pin p) noexcept;
This is called by CoreNG to get the pin table entry for the specified pin. It should range-check the pin and return nullptr if the pin number is out of range, or the pin is not available for general I/O.

### extern uint32_t GetSdhcClockSpeed() noexcept;
This must be provided if the application uses the SD card low-level driver provided by CoreN2G. It returns the clock frequency provided to the SDHC peipheral.

## Startup sequence

The reset vector in the exception table points to Reset_Handler() which is defined in the appropriate startup file, e.g. src/SAME5x/startup_samc54.c. This performs the standard C and C++ initialisation functions. It then calls AppInit() follows by AppMain(). It does not expect AppMain to return.

AppInit() should call CoreInit(). If the application uses analog input, it should also call AnalogIn::Init(). If it uses PWM output, it should call AnalogOut::Init().

The client project must also initialise the 1000Hz Systick interrupt. If the application uses FreeRTOS, this will be done by FreeRTOS; but you must provide function vApplicationTickHook which is called by FreeRTOS, and that must call CoreSysTick() which this project provides. If the application doesn't use FreeRTOS then it must set up Systick itself and provide the systick handler, which must call CoreSysTick().

DC, 2020-07-27
