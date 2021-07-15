Fork of the Duet WiFi Socket Server for LPC/RRF and updated ESP SDK/Framework
===========================================

# Duet WiFi Socket Server for LPC1768 & STM32F4 versions of RRF
This fork of the Duet WiFi Socket Server is intended for use with the LPC1768 & STM32F4 version of RRF.
The LPC version supports a smaller number of active connections than the standard server (to match the LPC
RRF port). It is also built using a more recent ESP8266 toolkit and framework.
 
# Build Instructions

Checkout and build the ESP8266 framework from here:
    https://github.com/gloomyandy/Arduino.git

Checkout the this branch on your computer

    git clone https://github.com/gloomyandy/DuetWiFiSocketServer.git
    cd DuetWiFiSocketServer
    git checkout newsdk-lpc

Build the firmware

    make

Upload to an ESP8266 connect via USB (replace \<Com Port\> by the actual port)

    esptools.py --port <COM Port> write_flash 0x00000 duetwifi.bin


