#ifndef _RCC_H
#define _RCC_H

#include "main.h"

// MCO Pin Source
// #define MICROCONTROLLER_CLOCK_OUTPUT_HSI14
// #define MICROCONTROLLER_CLOCK_OUTPUT_LSI
// #define MICROCONTROLLER_CLOCK_OUTPUT_LSE
// #define MICROCONTROLLER_CLOCK_OUTPUT_SCLK
// #define MICROCONTROLLER_CLOCK_OUTPUT_HSI8
// #define MICROCONTROLLER_CLOCK_OUTPUT_HSE32
// #define MICROCONTROLLER_CLOCK_OUTPUT_PLL


typedef enum {
    RCC_OK = 0U,
    RCC_ERROR,
} eRccErrorCodes_t;


eRccErrorCodes_t RCC_SPEEDUP_SYSTEM_CLK();

uint8_t RCC_PREFETCH_BUFFER_STATUS();

eRccErrorCodes_t RCC_ENABLE_MCO_PIN();
#endif