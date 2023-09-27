/* mem.ld */
/* Entry Point */
ENTRY(Reset_Handler)

_estack = 0x20002000; /* end of RAM */
_min_heap_size = 0x200; /* required amount of heap  */
_min_stack_size = 0x400; /* required amount of stack */

MEMORY {
  BOOT    (rx)    : ORIGIN = 0x8000000,   LENGTH = 64K 
  RAM    (xrw)    : ORIGIN = 0x20000000,   LENGTH = 8K
}

__boot_start__ = ORIGIN(BOOT);
__boot_size__ = LENGTH(BOOT);
__app_start__ = ORIGIN(APP);
__app_size__ = LENGTH(APP);
__ram_start__ = ORIGIN(RAM);
__ram_size__ = LENGTH(RAM);

SECTIONS {
  .isr_table : {
    . = ALIGN(4);
    KEEP(*(.isr_table))
    . = ALIGN(4);
  } > BOOT

  .text : {
    . = ALIGN(4);
    *(.text)
    . = ALIGN(4);
    _etext = .;
  } > BOOT
  
  .rodata : {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } > BOOT

  .data : {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >RAM AT> BOOTLOADER

  
  /* Uninitialized data section into RAM memory */
  . = ALIGN(4);
  .bss :
  {
    
    _sbss = .;         
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >RAM


  .heap_stack : {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } > RAM
}