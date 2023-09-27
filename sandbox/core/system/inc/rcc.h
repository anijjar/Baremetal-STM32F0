#ifndef RCC_H
#define RCC_H

#include "common.h"
#include "gpio.h"

typedef enum {
    RCC_OK = 0U,
    RCC_ERROR,
} eRccErrorCodes_t;

typedef enum {
    RCC_MCO_CLK_SRC_HSI14 = 0U,
    RCC_MCO_CLK_SRC_LSI,
    RCC_MCO_CLK_SRC_LSE,
    RCC_MCO_CLK_SRC_SCLK,
    RCC_MCO_CLK_SRC_HSI8,
    RCC_MCO_CLK_SRC_PLL,
    RCC_MCO_CLK_SRC_HSE32,
    RCC_MCO_CLK_SRC_TOTAL
} eRccMcoClkSrc_t;

eRccErrorCodes_t RCC_MCO_PIN_INIT(eRccMcoClkSrc_t src);
eRccErrorCodes_t RCC_MCO_PIN_DEINIT();
#endif