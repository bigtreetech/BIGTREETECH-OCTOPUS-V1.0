#!/bin/sh

arm-none-eabi-nm -S --size-sort -s $1 -t d| grep " b \| B " | awk 'BEGIN {FS = " "; main=0;ram0=0;} {if($1<537378816){main+=$2};if($1>=537378816 && $1<537395200){ram0+=$2;};if($1>=537395200){ram0+=$2}; } END{print "\n\n--------Static Memory Totals-------\n\nMemory  \t  Bytes (dec)\n\nMain      \t  ", main, " / 32768\nAHBRAM   \t  ", ram0, " / 32768"}'
