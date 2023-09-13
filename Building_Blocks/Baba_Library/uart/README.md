

# Getting Started with Debugging
- Run "st-util" on power shell if using GDB
- clean up the directory with "make clean"
- compile and assemble files using "make"
- launch GDB using "make gdb"
- Type "target extended-remote :4242" in GDB (4242 is from st-util)
- Type "run" to start code
- See commands below

This will only work on the stm32f0308-Discovery board. The linker and core files need to be rewritten otherwise.

## Commands for GDB:
- continue ~ runs the program until it encounters breakpoint
- step ~ walk line by line in the program
- load ~ upload code to stm
- run ~ run the program
- info <> ~ typing b gives info on breakpoints\
- kill ~ kill the program
- /x ~ print contents of an address
- print <var_name> ~ gets variable value
- ptype <var_name> ~ gets variable type (does not work for uints)
- whatis <var_name> ~ gets variable type (works for uints)
- explore  <var_name> ~ gets variable type (works for uints)
- br <line of code to stop at> | br filename:line
- Bt ~ prints summary of how the program got to where it is. 

# STM Clock
Using the PLL, we can raise the 8MHz clock into 48MHz. This increases current consumption.

Using an external Clock would increase accuracy. PLL takes time to stabalize, so applications requiring quick switches from sleep are unideal.

# Flash Memory Latency
The flash memory locations have a max speed of 24MHz. Therefore, when using clock speeds >24MHz, we need to include wait states to ensure the data is read completly. Ie, add NOP instructions to the assembly.

| Speed | Wait States |
| ----- | ----------- |
| <=24MHz  | 0  |
| 24-48MHz | 1 |

We can improve performance by using the "Flash Prefetch Buffer" to fetch a few more instructions.

# UART
Drop in files to any empty project to get running. Removed other files to reduce redundancy