Introduction
============
This document provides a brief overview of how the STM32F4 version of RRF makes use of the
MCU hardware.

GPIO
====
RRF makes use of the interrupt on change EXI feature for the WiFi, accelerometer, 
some filament sensors and the DHT sensor interfaces. This requires that the pins 
selected for these functions must be on different pins within a port. I.E.
if pin A.1 is used then no other 1 pin (B.1, C.1 etc) can be used. This applies
to the following GPIO pins:
* ESPTfrReady
* ESP chip select
* Accelerometer int1pin
* Other pins that may be used for filament sensors

GPIO pins are used to drive the stepper motor step/dir pins. If all of the step pins
are on the same port the RRF can use a more efficient mechanism when stepping multiple
drivers.

Timers
======
* TIM1 : Software UART (16bit Baud rate * 4 (overampling))
* TIM2 : Hardware PWM
* TIM3 : Hardware PWM
* TIM4 : Hardware PWM
* TIM5 : Step Timer (32 bit 1MHz)
* TIM6 : Unused
* TIM7 : Software PWM (16 bit 1MHz)
* TIM8 : Hardware PWM
* TIM9 : Hardware PWM
* TIM10 : Hardware PWM
* TIM11 : Hardware PWM
* TIM12 : Hardware PWM
* TIM13 : Hardware PWM
* TIM14 : Hardware PWM
* WWDG : Watchdog

PWM outputs
===========
* Hardware PWM is provided using the STM32F4 timers
* Each timer can drive up to 4 GPIO pins, all pins sharing a timer must use the same base frequency
* RRF supports up to 16 software driven PWM channels, these may be used with any GPIO pin

The current allocation of pins to timers is:
* TIM2: PA_0, PA_1, PA_2, PA_3, PA_15, PB_3, PB_10, PB_11
* TIM3: PB_0, PB_1, PB_4, PB_5, PC_7
* TIM4: PB_6, PB_7, PD_12, PD_14, PD_15
* TIM8: PA_5, PB_15, PC_6, PC_8, PC_9
* TIM9: PE_5, PE_6
* TIM10: PB_8, PF_6
* TIM11: PB_9, PF_7
* TIM12: PB_14 PH_6
* TIM13: PA_6, PF_8
* TIM14: PA_7, PF_9
In the current release there is a fixed mapping between a selected pin and the timer used to
drive it via PWM. Future versions may relax this and allow the selection of timer based on
pin and selected frequency.

SPI
===
* SPI1 : Shared SPI, Master, main usage SD card interface, does not use DMA
* SPI2 : Slave, SBC or WiFi interface, uses DMA (DMA1_Stream3, DMA1_Stream4)
* SPI3 : Shared SPI, Master, main usage TMC SPI interface (DMA1_Stream5, DMA1_Stream0) 
* SWSSP0 : Software SPI, Shared, main usage Thermocouples etc.
* SWSSP1 : Software SPI, Shared, main usage LCD display
* SWSSP2 : Software SPI, shared, main usage TMC SPI interface

Note the above usage for SPI2/SPI3 is the the most common configuration. It is possible
to operate both of these devices in Master or Slave mode and both make use of DMA.

We have seen problems when running SPI1 using DMA. It seems to cause corruption of the
GPIO regsiters being accessed via DMA for the software UART implementation. This problem
may be cuased by this silicon bug: 
2.1.10 DMA2 data corruption when managing AHB and APB peripherals in a concurrent way
See: https://www.st.com/resource/en/errata_sheet/dm00037591-stm32f405-407xx-and-stm32f415-417xx-device-limitations-stmicroelectronics.pdf

Because of this it is not recommended that SPI1 is operated using DMA unless this issue
has been investigated further and resolved. This probably means that SPI1 should not be
used for WiFi/SBC commications (which require operation at high speed in slave mode).

SDIO
====
* SDIO : SD card interface on some boards, uses DMA (DMA2_Stream3, DMA2_Stream6)

ADC
===
* ADC1 : 12Bit Analog in + internal ref + mcu temp, uses DMA (DMA2_Stream4)
* ADC2 : unused
* ADC3 : 12Bit Analog in, uses DMA (DMA2_Stream0)
The 12 bit ADC uses oversampling to provide an effective 14bit resolution.

DMA
===
* DMA1_Stream0 : SPI3 RX
* DMA1_Stream1 : Unused
* DMA1_Stream2 : Unused
* DMA1_Stream3 : SPI2 RX
* DMA1_Stream4 : SPI2 TX
* DMA1_Stream5 : SPI3 TX
* DMA1_Stream6 : unused
* DMA1_Stream7 : unused
* DMA2_Stream0 : ADC3
* DMA2_Stream1 : unused
* DMA2_Stream2 : unused
* DMA2_Stream3 : SDIO RX
* DMA2_Stream4 : ADC1
* DMA2_Stream5 : TIM1/GPIO (Soft UART)
* DMA2_Stream6 : SDIO TX
* DMA2_Stream7 : unused

CRC Unit
========
* CRC32 : Used for file I/O and SBC buffers

USARTs
======
RRF currently uses only two serial devices, AUX and the WiFi interface. These are
mapped based upon the selected pins to an actual hardware UART device. In versions 
prior to V3.3-beta3 the only hardware UARTS enabled were 1, 3 and 6. In v3.3-beta3
and later UARTS 1-6 are all available.

TMC drivers that have a UART interface are driven via a DMA based software UART
that can drive any pin in half duplex mode.

Flash Memory
============
* 0x8000000 : 32K Bootloader (provided by board)
* 0x8008000 : 16K Interrupt vectors and startup code (bootloader starts loading here)
* 0x800C000 : 16K Reset data (holds diagnostics from previous board resets)
* 0x8010000 : 1024K - 64K Main firmware start

RAM
===
* 0x20000000 : 128K General purpose RAM
* 0x10000000 : 64K CCMRAM used for task stacks and permanently allocated objects
Note that because DMA access is not allowed to CCMRAM care must be taken when selecting
objects to be placed in this area.

SD Card access and RRF configuration
====================================
To enable RRF to operate on a number of different boards it uses a file (board.txt) to specify how the
hardware is configured. This file along with a built in confguration for each board maps the MCU pins to
heaters, drivers etc. However this raises the question of how does RRF read the SD card?

RRF currently supports both SPI and SDIO access to SD cards. There are 3 SPI devices each of which can be
configured to use a selection of I/O pins. Different boards currently use different configurations. Prior
to V3.3 we actively probed the hardware to determine which configuration was in use. However this is risky
as the probing could turn on heaters or other hardware. From V3.3 onwards we make use of the following steps
to determine how to access the SD card:
1. We use a hash of the Bootloader area to identify known boards.
2. If no known board is discovered, we examine the current hardware configuration. The bootloader will often
leave the hardware configured for SD card access.
3. If the above fails we issue an error message and await user permission to actively probe the hardware.