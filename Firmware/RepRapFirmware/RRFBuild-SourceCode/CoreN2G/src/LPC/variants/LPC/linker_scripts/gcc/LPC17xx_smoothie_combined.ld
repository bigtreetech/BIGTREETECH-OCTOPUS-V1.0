/* Linker script for LPC1768/LPC1769 with Smoothie Bootloader */

/* Linker script to configure memory regions. */
MEMORY
{
  /* Start at 16k to avoid Smoothie bootloader */
  FLASH (rx) : ORIGIN = 16K, LENGTH = (512K - 16K - 32K) /* topmost 32K (Last Sector) used for software reset data*/
  RAM (rwx) :  ORIGIN = 0x10000000, LENGTH = (32K - 32) /* topmost 32 bytes used by IAP functions */
  AHB_RAM(rwx) : ORIGIN = 0x2007C000, LENGTH = (16K + 16K)
}

INCLUDE common.ld
