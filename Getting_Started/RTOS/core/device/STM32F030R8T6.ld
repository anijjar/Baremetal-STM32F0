
ENTRY(Reset_Handler)

/* Define the end of RAM and stack memory */
/* 8k of SRAM starting @ 0x20000000*/
_estack = 0x20001FFF;

/* Throw an error if there is less than 256 Bytes left*/
/* RTOS Takes alot of memory*/
_Min_Heap_Size = 0x100; /* required amount of heap */
_Min_Stack_Size = 0x400; /* required amount of stack */

/* Define memory to tell linker how much memory we have */
MEMORY
{
  FLASH    (rx)    : ORIGIN = 0x8000000,   LENGTH = 64K
  RAM    (xrw)    : ORIGIN = 0x20000000,   LENGTH = 8K
}

/* Define several sectors for the Startup file 
  We will define sectors for the startup routine, main program code, read only data, dynamic data, bss, and heap/stack.
*/
SECTIONS
{
  /* The vector table is at the start and defines the hw interrupts */
  .vector_table :
  {
    /* Insert padding bytes until the current location becomes aligned on 4-byte boundary */
    . = ALIGN(4);
    /* Startup Code */
    KEEP (*(.vector_table))/* the '*' symbol is for any name */
    . = ALIGN(4);
  } >FLASH

  /* Text sector contains the main program code */
  .text :
  {
    . = ALIGN(4);
    *(.text) /* "all '.text' input sections in all input files" */
    *(.text*)
    . = ALIGN(4);
  } >FLASH

  /* read only data (variables declared 'static') */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } >FLASH

  /* dynamic variables */
  _sidata = .; /* set '_sidata' as the current stack pointer position */
  .data : AT(_sidata)
  {
    . = ALIGN(4);
    /* Mark the start/end locations for the 'data' section */
    _sdata = .;
    *(.data)
    *(.data*)
    _edata = .;
    . = ALIGN(4);
  } >RAM
  
  /* dynamic variables initialized to null */
  .bss :
  {
    . = ALIGN(4);
    /* Mark start and end of the sector */
    _sbss = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } >RAM
  
  /* Heap and Stack Space*/
  .heap_stack :
  {
    . = ALIGN(8);
    _sram = .;
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
    _eram = .;
  } >RAM
}
