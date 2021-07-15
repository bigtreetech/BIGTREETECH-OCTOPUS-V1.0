#!/bin/sh
echo "RRFBuild"
git checkout $1
cd CoreN2G
echo "CoreN2G"
git checkout $1
cd ../RepRapFirmware
echo "RepRapFirmware"
git checkout $1
cd ../RRFLibraries
echo "RRFLibraries"
git checkout $1
cd ../FreeRTOS
echo "FreeRTOS"
git checkout $1
cd ..
