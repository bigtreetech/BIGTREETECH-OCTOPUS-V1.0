# How to use Klipper on Octopus

## NOTE: 

* This motherboard comes with bootloader which allows firmware update through SD card. We recommend using SD card to update firmware instead of DFU. If you have ever used DFU to upload firmware, you can use the instructions [here](https://github.com/bigtreetech/BIGTREETECH-OCTOPUS-V1.0/tree/master/Firmware/DFU%20Update%20bootloader) to restore the bootloader of this motherboard.
* [BTT_OctoPus_Voron2_Config.cfg](https://github.com/bigtreetech/BIGTREETECH-OCTOPUS-V1.0/blob/master/Octopus%20works%20on%20Voron%20v2.4/Firmware/Klipper/BTT_OctoPus_Voron2_Config.cfg) is the reference configuration file of Voron2.4. you can modify your own configuration file based on this. (Note: there is no `position_max` of XYZ set in this file. We offer three sizes of 250/300/350mm. You must select one to uncomment or set your own custom size)

## Pinout
### Raspberry pi pinout
<img src=Images/rpi_pinout.jpg width="800" /><br/>

### Ocotpus pinout(Thanks [Thomas White](https://www.facebook.com/groups/505736576548648/user/100000740067128/) for the pinout of Octopus)
<img src=Images/octopus_pinout.png width="1600" /><br/>

## Wiring diagram
### Raspberry pi is powered by an external +5V adapter and communicates with the motherboard via USB
<img src=Images/wiring_usb.jpg width="1600" /><br/>

### Raspberry pi is powered by the motherboard +5V and communicates with the motherboard via UART
<img src=Images/wiring_uart.jpg width="1600" /><br/>

## Generate the firmware.bin

1. Precompiled firmware(The source code version used is [Commits on Jun 28, 2021](https://github.com/KevinOConnor/klipper/commit/430578957f37f42815ffea900cbc3459d6fd0888))
   * [firmware-USB.bin](https://github.com/bigtreetech/BIGTREETECH-OCTOPUS-V1.0/tree/master/Octopus%20works%20on%20Voron%20v2.4/Firmware/Klipper/firmware-USB.bin) Use USB to communicate with raspberry pi. Connect the type-A USB of raspberry pi with the type-C of motherboard directly to communicate normally.
   * [firmware-USART2.bin](https://github.com/bigtreetech/BIGTREETECH-OCTOPUS-V1.0/tree/master/Octopus%20works%20on%20Voron%20v2.4/Firmware/Klipper/firmware-USART2.bin) Use USART2 to communicate with raspberry pi. Connect the UART-TX of raspberry pi with the USART-RX2 of motherboard and connect the UART-RX of raspberry pi with the USART-TX2 of motherboard directly to communicate normally.

2. Build your own firmware
   1. Refer to [klipper's official installation](https://www.klipper3d.org/Installation.html) to download klipper source code to raspberry pi
   2. `Building the micro-controller` with the configuration shown below.
      * [*] Enable extra low-level configuration options
      * Micro-controller Architecture = `STMicroelectronics STM32`
      * Processor model = `STM32F446`
      * Bootloader offset = `32KiB bootloader`
      * Clock Reference = `12 MHz crystal`
      * IF USE USB
         * Communication interface = `USB (on PA11/PA12)`
      * ElSE IF USE USART2
         * Communication interface = `Serial (on USART2 PD6/PD5)`
      * ELSE              
         * Communication interface = `The port you want`
   
      <img src=Images/menuconfig.png width="800" /><br/>
    3. The `klipper.bin` file will be generated in the folder `home/pi/kliiper/out` after `make`. And you can use the windows computer under the same LAN as raspberry pi to copy `klipper.bin` from raspberry pi to the computer with `pscp` command in the CMD terminal. such as `pscp -C pi@192.168.0.101:/home/pi/klipper/out/klipper.bin c:\klipper.bin`(The terminal may prompt that `The server's host key is not cached` and ask `Store key in cache?((y/n)`, Please type `y` to store. And then it will ask for a password, please type the default password `raspberry` for raspberry pi)

## Update the firmware.bin

1. Renamed the `firmware-USB.bin`, `firmware-USART2.bin` or the `klipper.bin`(in folder `home/pi/kliiper/out` build by yourself) to `firmware.bin`
2. Copy the `firmware.bin` to the root directory of SD card (make sure SD card is in FAT32 format)
3. Insert the SD card into the card slot of the motherboard
4. Press the reset button or restart the power supply, the motherboard will automatically update the `firmware.bin`

## Configure the printer parameters
### Basic configuration
1. Refer to [klipper's official installation](https://www.klipper3d.org/Installation.html) to `Configuring OctoPrint to use Klipper`
2. Refer to [klipper's official installation](https://www.klipper3d.org/Installation.html) to `Configuring Klipper`. And use the configuration file [BTT_OctoPus_Voron2_Config.cfg](https://github.com/bigtreetech/BIGTREETECH-OCTOPUS-V1.0/blob/master/Octopus%20works%20on%20Voron%20v2.4/Firmware/Klipper/BTT_OctoPus_Voron2_Config.cfg) as the underlying `printer.cfg`, which includes all the correct pinout for Octopus
3. Refer to [klipper's official Config_Reference](https://www.klipper3d.org/Config_Reference.html) to configure the features you want.
4. If you use USB to communicate with raspberry pi, run the `ls /dev/serial/by-id/*` command in raspberry pi to get the correct ID number of the motherboard, and set the correct ID number in `printer.cfg`. And wiring reference [here](#raspberry-pi-is-powered-by-an-external-5v-adapter-and-communicates-with-the-motherboard-via-usb)
    ``` 
    [mcu]
    serial: /dev/serial/by-id/usb-Klipper_stm32f446xx_0E002B00135053424E363620-if00
    ```
    <img src=Images/cfg_usb.png/><br/>
5. If you use USART2 to communicate with raspberry pi, you need to modify the following files by inserting the SD card into the computer or by SSH command. And wiring reference [here](#raspberry-pi-is-powered-by-the-motherboard-5v-and-communicates-with-the-motherboard-via-uart)
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

### BigTreeTtech TFT TouchSCreen emulated 12864 mode: Set the `display` in `printer.cfg` to the following parameters
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
