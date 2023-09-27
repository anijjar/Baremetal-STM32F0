#ifndef _COMMON_H
#define _COMMON_H

#include <stdint.h>

// Linker Symbols
// extern int __boot_start__;
// extern int __boot_size__;
// extern int __app_start__;
// extern int __app_size__;
// extern int __ram_start__;
// extern int __ram_size__;

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define TOGGLE_BIT(REG, BIT)   ((REG) ^= (BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#endif