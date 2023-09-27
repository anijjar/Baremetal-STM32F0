
#include "rcc.h"

eRccErrorCodes_t RCC_MCO_PIN_INIT(eRccMcoClkSrc_t src){
    GPIO_CONFIG_PIN(
        GPIOA,
        PIN_8,
        GPIO_MODER_AF,
        GPIO_OTYPER_PP,
        GPIO_OSPEEDR_LOW,
        GPIO_PUPDR_NONE,
        GPIO_AF_0
    );
    switch(src){
        case RCC_MCO_CLK_SRC_HSI14:
            SET_BIT(RCC->CFGR, RCC_CFGR_MCO_HSI14);
            return RCC_OK;
        case RCC_MCO_CLK_SRC_LSI:
            SET_BIT(RCC->CFGR, RCC_CFGR_MCO_LSI);
            return RCC_OK;
        case RCC_MCO_CLK_SRC_LSE:
            SET_BIT(RCC->CFGR, RCC_CFGR_MCO_LSE);
            return RCC_OK;
        case RCC_MCO_CLK_SRC_SCLK:
            SET_BIT(RCC->CFGR, RCC_CFGR_MCO_SYSCLK);
            return RCC_OK;
        case RCC_MCO_CLK_SRC_HSI8:
            SET_BIT(RCC->CFGR, RCC_CFGR_MCO_HSI);
            return RCC_OK;
        case RCC_MCO_CLK_SRC_PLL:
            SET_BIT(RCC->CFGR, RCC_CFGR_MCO_PLL);
            return RCC_OK;
        case RCC_MCO_CLK_SRC_HSE32:
            SET_BIT(RCC->CFGR, RCC_CFGR_MCO_HSE);
            return RCC_OK;
        default:
            break;
    }
    return RCC_ERROR;
}
eRccErrorCodes_t RCC_MCO_PIN_DEINIT(){
    GPIO_DECONFIG_PIN(
        GPIOA,
        PIN_8,
        GPIO_MODER_AF,
        GPIO_OTYPER_PP,
        GPIO_OSPEEDR_LOW,
        GPIO_PUPDR_NONE,
        GPIO_AF_0
    );
    return RCC_OK;
}