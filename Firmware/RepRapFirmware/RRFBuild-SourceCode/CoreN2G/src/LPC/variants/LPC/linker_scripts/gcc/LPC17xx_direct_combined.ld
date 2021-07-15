/* Linker script for mbed LPC1768 */

/* Linker script to configure memory regions. */
MEMORY
{

  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = (512K - 32K) /*top most 32k (last sector) used for SoftwareResetData*/
  RAM (rwx) :  ORIGIN = 0x100000C8, LENGTH = (32K - 0xC8 - 32)  /* topmost 32 bytes used by IAP functions */
  AHB_RAM(rwx) : ORIGIN = 0x2007C000, LENGTH = (16K + 16K) /* AHB0 + AHB1*/

}

INCLUDE common.ld
