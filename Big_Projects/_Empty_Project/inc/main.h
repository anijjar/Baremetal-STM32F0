#ifndef _MAIN_H
#define _MAIN_H
// C Libraries here
#include <stdint.h>
#include "stm32f0xx.h"

#define DEVICE_TAG  "PROJECT NAME HERE"
#define TOGGLE_BIT(REG, BIT)   ((REG) ^= (BIT))

/*
SYSTEM CLOCK SETUP 
*/
#define DEFAULT_HSI_CLOCK_HZ 8000000U
// Getting started:
// If you want to use default clock, comment out _ENABLE_PLL...
// and update the CORE_CLOCK_HZ to DEFAULT_HSI_CLOCK_HZ.
// Also, comment out PLL_DIV and PLL_MULT, but not neccessary.
// #define _ENABLE_PLL_SYSTEM_CLOCK // _rcc.c
#define _MICROCONTROLLER_CLOCK_OUTPUT_OFF // _rcc.c

#define CORE_CLOCK_HZ 8000000U //48MHz max

// Math to get desired CORE_CLOCK_HZ
// PLL_freq = (HSI / 2) * PLL_MULT
#define PLL_MULT RCC_CFGR_PLLMUL8

/*

END OF SYSTEM CLOCK SETUP 

*/
#endif