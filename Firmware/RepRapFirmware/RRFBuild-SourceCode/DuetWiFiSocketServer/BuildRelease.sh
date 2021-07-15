#!/bin/sh

#extract firmware version from header file
VER=`awk 'sub(/.*VERSION_MAIN/,""){print $1}' src/Config.h  | awk 'gsub(/"/, "", $1)'`

OUTPUT=releases/${VER}

mkdir -p releases/${VER}

#Building LPC Firmware
make BUILD=relbuild clean
make -j2 BUILD=relbuild HOSTSYS=-DLPCRRF
if [ -f ./relbuild/DuetWiFiServer.bin ]; then
	mv ./relbuild/DuetWiFiServer.bin ${OUTPUT}/DuetWiFiServer-lpc.bin
fi 

#Building LPC Firmware with extended listen
make BUILD=relbuild clean
make -j2 BUILD=relbuild HOSTSYS="-DLPCRRF -DEXTENDED_LISTEN"
if [ -f ./relbuild/DuetWiFiServer.bin ]; then
	mv ./relbuild/DuetWiFiServer.bin ${OUTPUT}/DuetWiFiServer-lpc-el.bin
fi 

#Building STM32F4 Firmware
make BUILD=relbuild clean
make -j2 BUILD=relbuild HOSTSYS=-DSTM32F4
if [ -f ./relbuild/DuetWiFiServer.bin ]; then
	mv ./relbuild/DuetWiFiServer.bin ${OUTPUT}/DuetWiFiServer-stm32f4.bin
fi 

#Building Duet firmware
make BUILD=relbuild clean
make -j2 BUILD=relbuild HOSTSYS=
if [ -f ./relbuild/DuetWiFiServer.bin ]; then
	mv ./relbuild/DuetWiFiServer.bin ${OUTPUT}/DuetWiFiServer-duet.bin
fi 
make BUILD=relbuild clean


