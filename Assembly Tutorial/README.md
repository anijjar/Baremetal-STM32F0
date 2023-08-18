
https://vivonomicon.com/2018/04/02/bare-metal-stm32-programming-part-1-hello-arm/

This project walks through how to make an assembly file and running the GDB debugging tool and st-link tool to flash and debug the program.


The linker script maps different memory sections to global variables.

The Assembly file (startup) contains the vector table which points to hardware interrupt addresses, used by the chip.

The linker uses the script to map variables to variables in the assembly file and builds it into an elf file.

GDB is a debugging tool that is used to step through the elf file and to check if it all works as expected.

ST-util can upload the code to a microcontroller.