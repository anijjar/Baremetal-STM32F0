
#include "rcc.h"

eRccErrorCodes_t RCC_SPEEDUP_SYSTEM_CLK(){
    if(CORE_CLOCK_HZ > 8000000U){
        // Set the speed of the flash memory
        if(CORE_CLOCK_HZ >= 24000000U){
            // Zero wait states for <24MHz, 1 for >=24MHz
            SET_BIT(FLASH->ACR, FLASH_ACR_LATENCY);
            // Enable Prefetch (fetch several instructions)
            SET_BIT(FLASH->ACR, FLASH_ACR_PRFTBE);
        }

        // Define PLL speed
        CLEAR_BIT(RCC->CFGR, RCC_CFGR_PLLSRC);
        SET_BIT(RCC->CFGR, PLL_MULT);

        // Turn PLL on and wait for it to be ready
        SET_BIT(RCC->CR, RCC_CR_PLLON);
        while(!(RCC->CR & RCC_CR_PLLRDY)){
            // Do nothing till done.
        }

        // PLL selected as system clock
        SET_BIT(RCC->CFGR, RCC_CFGR_SW_1);
        while(!(RCC->CFGR & RCC_CFGR_SWS_PLL)){
            // Do nothing till done.
        }
    } else {
        return RCC_ERROR;
    }
    return RCC_OK;
}

uint8_t RCC_PREFETCH_BUFFER_STATUS(){
    return READ_BIT(FLASH->ACR, FLASH_ACR_PRFTBS);
}

eRccErrorCodes_t RCC_ENABLE_MCO_PIN(){
    // Turn on the GPIOA Clock
    SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOAEN);
    // MCO is located at AF0
    SET_BIT(GPIOA->MODER, GPIO_MODER_MODER8_1);

    #ifdef MICROCONTROLLER_CLOCK_OUTPUT_HSI14
        SET_BIT(RCC->CFGR, RCC_CFGR_MCO_HSI14);
    #endif
    #ifdef MICROCONTROLLER_CLOCK_OUTPUT_LSI
        SET_BIT(RCC->CFGR, RCC_CFGR_MCO_LSI);
    #endif
    #ifdef MICROCONTROLLER_CLOCK_OUTPUT_LSE
        SET_BIT(RCC->CFGR, RCC_CFGR_MCO_LSE);
    #endif
    #ifdef MICROCONTROLLER_CLOCK_OUTPUT_SCLK
        SET_BIT(RCC->CFGR, RCC_CFGR_MCO_SYSCLK);
    #endif
    #ifdef MICROCONTROLLER_CLOCK_OUTPUT_HSI8
        SET_BIT(RCC->CFGR, RCC_CFGR_MCO_HSI);
    #endif
    #ifdef MICROCONTROLLER_CLOCK_OUTPUT_HSE32
        SET_BIT(RCC->CFGR, RCC_CFGR_MCO_HSE);
    #endif
    #ifdef MICROCONTROLLER_CLOCK_OUTPUT_PLL
        SET_BIT(RCC->CFGR, RCC_CFGR_MCO_PLL);
    #endif
    return RCC_OK;
}