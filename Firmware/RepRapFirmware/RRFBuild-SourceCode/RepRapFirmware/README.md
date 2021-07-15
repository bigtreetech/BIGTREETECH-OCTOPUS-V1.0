# LPC/STM32F4 Port of RepRapFirmware v3

This is aport of [RepRapFirmware](https://github.com/Duet3D/RepRapFirmware) for LPC1768/LPC1769 and STM32F4 based boards.  

# What is it?
It is a port of the [RepRapFirmware](https://github.com/Duet3D/RepRapFirmware) version 3 (RRF3) used on the Duet family of controllers.  
The firmware can be used to control 3D printers, CNC machines, laser cutters and more.  
There are a couple of features which sets it aside from Marlin, Smoothieware etc
  - All settings for the firmware are configurable dynamically. No recompiling required
  - Although it supports USB control through software such as Pronterface or Octoprint, the Duet Web Control (DWC) is the best way to control and configure the software
  - Native network control through Wifi, Ethernet or an SBC

The boards which are currently supported are detailed in the wiki [here](https://teamgloomy.github.io/supported_boards.html)

### Main Differences to the Duet RRF
The main differences for the LPC Port are detailed within the wiki [here](https://teamgloomy.github.io/lpc_differences.html)
The main differences for the STM32F4 Port are detailed within the wiki [here](https://teamgloomy.github.io/stm32_differences.html)

## Getting Started
Information to support using this firmware can be found on the [wiki](https://teamgloomy.github.io/getting_started.html)  
The wiki also details different methods of connecting for different boards.

## Support
For LPC/STM specific questions (and general questions too), please get in touch over at the [RepRap Forum](https://reprap.org/forum/read.php?147,874661)  
There is also a [Discord Channel](https://discord.gg/uS97Qs7) where LPC/STM support can also be found.  
For generic RepRapFirmware questions, please use the [Duet Forum](forum.duet.com)  

**The LPC/STM port is experimental and is likely to contain bugs - Use at your own risk**

# Licence
The source files in this project are licensed under GPLv3, see http://www.gnu.org/licenses/gpl-3.0.en.html. 

# Documentation
All documentation has been moved to the [RepRapFirmware GitHub Wiki](https://github.com/Duet3D/RepRapFirmware/wiki).

