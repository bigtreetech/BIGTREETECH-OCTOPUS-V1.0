#!/bin/sh
echo
echo "----------Flash Memory Usage----------"
echo "             Start     End       Size"
arm-none-eabi-nm -S -s $1.elf -t d| awk 'BEGIN {FS = " "; bootstart=134217728;vecstart=0;resetstart =0;etextstart=0;etextend=0;edata=0;} {if ($3 == "g_pfnVectors"){vecstart=$1};if($3 == "_etext"){etextend=$1};if ($3 == "__reset_data_start"){resetstart=$1};if ($3 == "__etext_start"){etextstart=$1};} END{printf("Bootloader %8x %8x %6x (%dKb)\n", bootstart, vecstart-1, vecstart-bootstart, (vecstart-bootstart)/1024);printf("Vectors    %8x %8x %6x (%dKb)\n", vecstart, resetstart-1, resetstart-vecstart, (resetstart-vecstart)/1024);printf("Reset data %8x %8x %6x (%dKb)\n", resetstart, etextstart-1, etextstart-resetstart, (etextstart-resetstart)/1024);printf("Text       %8x %8x %6x (%dKb)\n", etextstart, etextend, etextend-etextstart, (etextend-etextstart)/1024);}'
arm-none-eabi-nm -S -s $1.elf -t d| awk 'BEGIN {FS = " "; start=0;etext=0;edata=0;} {if ($3 == "g_pfnVectors"){start=$1};if($3 == "_etext"){etext=$1};if ($3 == "_sidata"){edata=$1};} END{printf("ROData     %8x %8x %6x (%dKb)\n", etext, edata, edata - etext, (edata-etext)/1024); printf("Total Flash%8x %8x %6x (%dKb)\n", 0x8000000, edata, edata - 134217728, (edata - 134217728)/1024);}'

echo ""
echo "------------ROData Detail-------------"
echo "                                 Size"
awk  < $1.map 'BEGIN {FS = " "; strline=0; strcnt=0; strsz=0} {if (strline==1){strline=0;strcnt++;strsz+=strtonum($2)};if(strline==0 && ($1 ~ /\.str1\.1/)){strline=1};} END{printf("Strings                      %6x (%dKb)\n", strsz, strsz/1024);}'
awk  < $1.map 'BEGIN {FS = " "; exidx=0; extab=0;fill=0;} {if ($1 == ".ARM"){exidx=strtonum($3)};if ($1 == "*fill*"){fill+=strtonum($3)};if ($1 == ".ARM.extab" && $4 == ""){extab=strtonum($3)};} END{printf("ARM.exidx                    %6x (%dKb)\n", exidx, exidx/1024); printf("ARM.extab                    %6x (%dKb)\n", extab, extab/1024);printf("Fill                         %6x (%dKb)\n", fill, fill/1024);}'
arm-none-eabi-nm -S --size-sort -s $1.elf -t d| grep " r \| R \| v \| V" | awk 'BEGIN {FS = " "; main=0;ram0=0;} {main+=$2;} END{printf("Const                          %x (%dKb)\n", main, main/1024);}'
