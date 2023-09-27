#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include "register_map.h"
#include "memory_map.h"

// Linker Symbols

// Register Functions
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define TOGGLE_BIT(REG, BIT)   ((REG) ^= (BIT))
#define READ_BIT(REG, BIT)    ((REG) & (BIT))
#define CLEAR_REG(REG)        ((REG) = (0x0))
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

// System Core Clock Frequency
#define DEFAULT_SYSTEM_CLOCK   (8000000U)/*HSI*/
volatile uint32_t CORE_CLOCK_HZ; 


#endif