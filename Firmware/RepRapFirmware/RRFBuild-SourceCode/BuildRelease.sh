#!/bin/sh
echo $1 $2 $3
BUILD=${1:-Debug}
CORE=${2:-STM32F4}
NETWORK=${3:-SBC}
TMC22XX=${4:-true}
STARTUP_DELAY=$5
#extract firmware version from header file
VER=`awk 'sub(/.*MAIN_VERSION/,""){print $1}' RepRapFirmware/src/Version.h  | awk 'gsub(/"/, "", $1)'`

OUTPUT=releases/${VER}/${BUILD}

mkdir -p ${OUTPUT}

make distclean
make -j2 firmware CORE=${CORE} NETWORK=${NETWORK} BUILD=${BUILD} TMC22XX=${TMC22XX} OUTPUT_NAME=firmware STARTUP_DELAY=${STARTUP_DELAY}
if [ -f ./build/firmware.bin ]; then
        mv ./build/firmware.bin ${OUTPUT}/firmware-${CORE,,}-${NETWORK,,}-${VER,,}.bin
        mv ./build/firmware.map ${OUTPUT}/firmware-${CORE,,}-${NETWORK,,}-${VER,,}.map
fi 
