#!/bin/sh
git tag $1
cd CoreN2G
git tag $1
cd ../RepRapFirmware
git tag $1
cd ../RRFLibraries
git tag $1
cd ../FreeRTOS
git tag $1
cd ..
