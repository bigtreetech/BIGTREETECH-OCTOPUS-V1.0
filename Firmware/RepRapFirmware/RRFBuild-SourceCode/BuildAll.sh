#!/bin/sh
#./BuildRelease.sh Release STM32F4 SBC
#./BuildRelease.sh Release STM32F4 ESP8266WIFI
./BuildRelease.sh Debug STM32F4 SBC
./BuildRelease.sh Debug STM32F4 ESP8266WIFI
#./BuildRelease.sh Release LPC SBC
#./BuildRelease.sh Release LPC ESP8266WIFI
#./BuildRelease.sh Release LPC ETHERNET false
#./BuildRelease.sh Release LPC NONE
./BuildRelease.sh Debug LPC SBC
./BuildRelease.sh Debug LPC ESP8266WIFI
#./BuildRelease.sh Debug LPC ETHERNET
#./BuildRelease.sh Debug LPC NONE
