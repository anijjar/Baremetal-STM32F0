/* Linker Script for STM32F030x8*/

/* Define the end of RAM and stack memory */
/* 8k of SRAM starting @ 0x20000000*/
_estack = 0x20001FFF;

/* Define memory to tell linker how much memory we have */
MEMORY
{
  FLASH    (rx)    : ORIGIN = 0x8000000,   LENGTH = 64K
  RAM    (xrw)    : ORIGIN = 0x20000000,   LENGTH = 8K
}

