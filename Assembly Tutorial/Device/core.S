/* Startup file for STM32F030x8 */

/* Define chip attributes and assembly language */
.syntax unified
.cpu cortex-m0
.fpu softvfp
.thumb

// Global memory locations
.global vtable
.global reset_handler

// Vector Table
.type vtable, %object
vtable:
    .word _estack
    .word reset_handler
.size vtable, .-vtable

/*
 * The Reset handler. Called on reset.
 */
.type reset_handler, %function
reset_handler:

  // Set SP to end of RAM from linker file
  LDR  r0, =_estack
  MOV  sp, r0

  LDR  r7, =0xDAED1234 // Dummy numbers for confirmation
  MOVS r0, #0
  
  main_loop:
    // Add 1 to register 'r0'.
    ADDS r0, r0, #1
    // Loop back.
    B    main_loop
.size reset_handler, .-reset_handler