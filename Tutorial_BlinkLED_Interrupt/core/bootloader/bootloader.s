

// Bootloader

/* Define chip attributes and assembly language */
.syntax unified
.cpu cortex-m0
.fpu softvfp
.thumb

// Global values.
.global Reset_Handler


/*
 * The Reset handler. Called on reset.
 * We want to copy the initialized data into the .data Ram section,
 * Set the .bss RAM section to all 0s,
 * and jump into the main method.
 */
.type Reset_Handler, %function
Reset_Handler:

  // Set SP to end of RAM from linker file
  LDR  r0, =_estack
  MOV  sp, r0
  
  // Copy data from flash to RAM data init section
  // R2 will store our progress along the sidata section
  MOVS r0, #0
  // Load the start/end address of the data section and data init section.
  LDR r1, = _sdata
  LDR r2, = _edata
  LDR r3, = _sidata
  B copy_sidata_loop

  copy_sidata:
    //offset the data init section by the progress
    LDR r4, [r3, r0]
    // Copy the word into data and incrememt
    STR r4, [r1, r0]
    ADDS r0, r0, #4
  //
  copy_sidata_loop:
    // Copy the next word from sidata->data until done
    ADDS r4, r0, r1
    CMP r4, r2
    BCC copy_sidata
  //
  // Once the data is done copying into ram, move onto BSS with 0s.
  MOVS r0, #0
  LDR r1, =_sbss
  LDR r2, = _ebss
  B reset_bss_loop

  reset_bss:
    // Store a 0 and increment by a word
    STR r0, [r1]
    ADDS r1, r1, #4
  //
  reset_bss_loop:
    // Use r1 to count the progress. increment if we are not done
    CMP r1, r2
    BCC reset_bss
  //


  // jump into 'main' method after done intitializing.
  B main
.size Reset_Handler, .-Reset_Handler
