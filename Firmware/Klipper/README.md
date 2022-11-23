# [切换到中文版](./README_zh_cn.md)

# How to use Klipper on Octopus (Pro)

## NOTE: 

* This motherboard comes with bootloader which allows firmware update through SD card. We recommend using SD card to update firmware instead of DFU. If you have ever used DFU to upload firmware, you can use the instructions [here](/Firmware/DFU%20Update%20bootloader) to restore the bootloader of this motherboard. And pay attention to distinguish whether your motherboard MCU is `STM32F446` or `STM32F429`.

## Pinout
### Raspberry pi pinout
<img src=Images/rpi_pinout.jpg width="800" /><br/>

### Ocotpus V1.0/V1.1 pinout(Thanks [Thomas White](https://www.facebook.com/groups/505736576548648/user/100000740067128/) for the pinout of Octopus)
<img src=Images/octopus_pinout.png width="1600" /><br/>

### Ocotpus Pro pinout
<img src=Images/octopus_pro_pinout.png width="1600" /><br/>

## Wiring diagram
### Raspberry pi is powered by an external +5V adapter and communicates with Octopus (Pro) via USB
<img src=Images/wiring_usb.jpg width="1600" /><br/>

### Raspberry pi is powered by the motherboard +5V and communicates with the Octopus V1.0/V1.1 via UART
<img src=Images/wiring_uart.jpg width="1600" /><br/>

### Raspberry pi is powered by the motherboard +5V and communicates with the Octopus Pro via UART
<img src=Images/pro_wiring_uart.jpg width="1600" /><br/>

## Build Firmware Image

1. `STM32F446` Precompiled firmware(The source code version used is [Commits on Jun 28, 2021](https://github.com/Klipper3d/klipper/commit/430578957f37f42815ffea900cbc3459d6fd0888))
   * [firmware-F446-USB.bin](./firmware-F446-USB.bin) Use USB to communicate with raspberry pi. Connect the type-A USB of raspberry pi with the type-C of motherboard directly to communicate normally.
   * [firmware-F446-USART2.bin](./firmware-F446-USART2.bin) Use USART2 to communicate with raspberry pi. Connect the UART-TX of raspberry pi with the USART-RX2 of motherboard and connect the UART-RX of raspberry pi with the USART-TX2 of motherboard directly to communicate normally.

2. `STM32F429` Precompiled firmware(The source code version used is [Commits on Oct 17, 2021](https://github.com/Klipper3d/klipper/commit/5c10001bc525701f0ef004041cbbf093522f6de6))
   * [firmware-F429-USB.bin](./firmware-F429-USB.bin) Use USB to communicate with raspberry pi. Connect the type-A USB of raspberry pi with the type-C of motherboard directly to communicate normally.
   * [firmware-F429-USART2.bin](./firmware-F429-USART2.bin) Use USART2 to communicate with raspberry pi. Connect the UART-TX of raspberry pi with the USART-RX2 of motherboard and connect the UART-RX of raspberry pi with the USART-TX2 of motherboard directly to communicate normally.

3. Build your own firmware<br/>
   ***NOTE: Pay attention to distinguish the type of MCU on your motherboard, `STM32F446 + 12 MHz crystal + 32KiB bootloader`， `STM32F429 + 8 MHz crystal + 32KiB bootloader`, `STM32F407 + 8 MHz crystal + 32KiB bootloader` or  `STM32FH723 + 25 MHz crystal + 128KiB bootloader`***
   1. Refer to [klipper's official installation](https://www.klipper3d.org/Installation.html) to download klipper source code to raspberry pi
   2. `Building the micro-controller` with the configuration shown below.
      * [*] Enable extra low-level configuration options
      * Micro-controller Architecture = `STMicroelectronics STM32`
      * Processor model = `STM32F446`, `STM32F429`, `STM32F407` or `STM32H723` (Depends on the MCU of your motherboard)
      * Bootloader offset = `32KiB bootloader`(for `STM32F446`, `STM32F429` & `STM32F407`) or `128KiB bootloader`(for `STM32H723`)
      * Clock Reference = `12 MHz crystal`(for `STM32F446`), `8 MHz crystal`(for `STM32F429` & `STM32F407`) or `25 MHz crystal`(for `STM32H723`)
      * IF USE USB
         * Communication interface = `USB (on PA11/PA12)`
      * ElSE IF USE USART2
         * Communication interface = `Serial (on USART2 PD6/PD5)`
      * ELSE
         * Communication interface = `The port you want`

      <img src=Images/octopus_f446_klipper_menuconfig.png width="800" /><br/>
      <img src=Images/octopus_f429_klipper_menuconfig.png width="800" /><br/>
      <img src=Images/octopus_f407_klipper_menuconfig.png width="800" /><br/>
      <img src=Images/octopus_h723_klipper_menuconfig.png width="800" /><br/>
   3. Once the configuration is selected, press `q` to exit,  and "Yes" when  asked to save the configuration.
   4. Run the command `make`
   5. The `klipper.bin` file will be generated in the folder `home/pi/kliiper/out` when the `make` command completed. And you can use the windows computer under the same LAN as raspberry pi to copy `klipper.bin` from raspberry pi to the computer with `pscp` command in the CMD terminal. such as `pscp -C pi@192.168.0.101:/home/pi/klipper/out/klipper.bin c:\klipper.bin`(The terminal may prompt that `The server's host key is not cached` and ask `Store key in cache?((y/n)`, Please type `y` to store. And then it will ask for a password, please type the default password `raspberry` for raspberry pi)

## Firmware Installation
### Option 1: DFU Firmware Install
   * Requires a USB connection
   * Requires the installation of an extra jumper on the Octopus

   1. Power off Octopus
   2. Install a jumper between BOOT0 and 3.3V
   3. Connect Octopus & Pi via USB-C
   4. Power on Octopus
   5. from your ssh session, run `lsusb`. and find the ID of the dfu device.
   6. run `make flash FLASH_DEVICE=1234:5678` replace 1234:5678 with the ID from the previous step
   7. power off the Octopus
   8. remove the jumper from BOOT0 and 3.3V
   9. Power on the Octopus
   10. You can confirm that the flash was successful, by running `ls /dev/serial/by-id`.  if the flash was successful, this should now show a klipper device, similar to:

   ![](./Images/stm32f446_id.png)

   (note: this test is not appicable if the firmware was compiled for UART, rather than USB)

### Option 2: SDcard Firmware Install

* Works regardless of USB vs UART
* Requires a microSD card

1. You can use the method in [Build Firmware Image 3.5](#build-firmware-image) or use a tool such as `cyberduck` or `winscp` to copy the `klipper.bin` file from your pi to your computer.
2. Renamed the `firmware-F4xx-USB.bin`, `firmware-F4xx-USART2.bin` or the `klipper.bin`(in folder `home/pi/kliiper/out` build by yourself) to `firmware.bin`<br/>
**Important:** If the file is not renamed, the bootloader will not be updated properly.
3. Copy the `firmware.bin` to the root directory of SD card (make sure SD card is in FAT32 format)
4. power off the Octopus
5. insert the microSD card
6. power on the Octopus
7. after a few seconds, the Octopus should be flashed
8. you can confirm that the flash was successful, by running `ls /dev/serial/by-id`.  if the flash was successful, this should now show a klipper device, similar to:

   ![](./Images/stm32f446_id.png)

(note: this test is not appicable if the firmware was compiled for UART, rather than USB)

## Configure the printer parameters
### Basic configuration
1. Refer to [klipper's official installation](https://www.klipper3d.org/Installation.html) to `Configuring OctoPrint to use Klipper`
2. Refer to [klipper's official installation](https://www.klipper3d.org/Installation.html) to `Configuring Klipper`. And use the configuration file [Octopus klipper.cfg](./Octopus%20klipper.cfg) as the underlying `printer.cfg`, which includes all the correct pinout for Octopus
3. Refer to [klipper's official Config_Reference](https://www.klipper3d.org/Config_Reference.html) to configure the features you want.
4. If you use USB to communicate with raspberry pi, run the `ls /dev/serial/by-id/*` command in raspberry pi to get the correct ID number of the motherboard, and set the correct ID number in `printer.cfg`. And wiring reference [here](#raspberry-pi-is-powered-by-an-external-5v-adapter-and-communicates-with-octopus-pro-via-usb)
    ```
    [mcu]
    serial: /dev/serial/by-id/usb-Klipper_stm32f446xx_0E002B00135053424E363620-if00
    ```
    <img src=Images/cfg_usb.png/><br/>
5. If you use USART2 to communicate with raspberry pi, you need to modify the following files by inserting the SD card into the computer or by SSH command. And wiring reference [Octopus V1.0/V1.1 here](#raspberry-pi-is-powered-by-the-motherboard-5v-and-communicates-with-the-octopus-v10v11-via-uart) or [Octopus Pro here](#raspberry-pi-is-powered-by-the-motherboard-5v-and-communicates-with-the-octopus-pro-via-uart)
   * Remove `console=serial0,115200` in `/boot/cmdline.txt`
   * Add `dtoverlay=pi3-miniuart-bt` at the end of file `/boot/config.txt`
   * Modify the configuration of `[mcu]` in `printer.cfg` to `serial: /dev/ttyAMA0` and enable `restart_method: command` by SSH
     ```
     [mcu]
     serial: /dev/ttyAMA0
     restart_method: command
     ```
     <img src=Images/cfg_uart.png/><br/>

### LCD12864 (RepRapDiscount 128x64 Full Graphic Smart Controller): Set the `display` in `printer.cfg` to the following parameters
   ```
   [display]
   lcd_type: st7920
   cs_pin: EXP1_4
   sclk_pin: EXP1_5
   sid_pin: EXP1_3
   encoder_pins: ^EXP2_5, ^EXP2_3
   click_pin: ^!EXP1_2
   kill_pin: ^!EXP2_8

   [output_pin beeper]
   pin: EXP1_1
   ```
   <img src=Images/cfg_lcd12864.png/><br/>

### LCD2004 (RepRapDiscount 2004 Smart Controller): Set the `display` in `printer.cfg` to the following parameters
   ```
   [display]
   lcd_type: hd44780
   rs_pin: EXP1_4
   e_pin: EXP1_3
   d4_pin: EXP1_5
   d5_pin: EXP1_6
   d6_pin: EXP1_7
   d7_pin: EXP1_8
   encoder_pins: ^EXP2_3, ^EXP2_5
   click_pin: ^!EXP1_2
   kill_pin: ^!EXP2_8

   [output_pin beeper]
   pin: EXP1_1
   ```
   <img src=Images/cfg_lcd2004.png/><br/>

### Mini12864 (Mini 12864Panel with neopixel backlight leds): Set the `display` in `printer.cfg` to the following parameters
   ```
   [display]
   lcd_type: uc1701
   cs_pin: EXP1_3
   a0_pin: EXP1_4
   rst_pin: EXP1_5
   encoder_pins: ^EXP2_5, ^EXP2_3
   click_pin: ^!EXP1_2
   ## Some micro-controller boards may require an spi bus to be specified:
   #spi_bus: spi
   ## Alternatively, some micro-controller boards may work with software spi:
   contrast: 63
   spi_software_mosi_pin: PA7
   spi_software_miso_pin: PA6
   spi_software_sclk_pin: PA5

   [output_pin beeper]
   pin: EXP1_1

   [neopixel btt_mini12864]
   pin: EXP1_6
   chain_count: 3
   color_order: RGB
   initial_RED: 0.4
   initial_GREEN: 0.4
   initial_BLUE: 0.4
   ```
   <img src=Images/cfg_mini12864.png/><br/>

### BigTreeTech TFT TouchScreen emulated 12864 mode: Set the `display` in `printer.cfg` to the following parameters
   ```
   [display]
   lcd_type: emulated_st7920
   spi_software_miso_pin: PA6
   spi_software_mosi_pin: EXP1_3
   spi_software_sclk_pin: EXP1_5
   en_pin: EXP1_4
   encoder_pins: ^EXP2_5, ^EXP2_3
   click_pin: ^!EXP1_2

   [output_pin beeper]
   pin: EXP1_1
   ```
   <img src=Images/cfg_tft_emulated_12864.png/><br/>
