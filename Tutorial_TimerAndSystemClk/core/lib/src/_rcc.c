
#include "_rcc.h"

void _SYSTEM_CORE_CLOCK_SETUP(){

    #ifdef _ENABLE_PLL_SYSTEM_CLOCK
        // Set the speed of the flash memory
        if(CORE_CLOCK_HZ > 24000000U){
            // Zero wait states for <=24MHz, 1 for >24MHz
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
        
    #else
        // keep default clock (8MHz HSI)
    #endif
}

uint8_t _PREFETCH_BUFFER_STATUS(){
    return READ_BIT(FLASH->ACR, FLASH_ACR_PRFTBS);
}

void _SET_MICROCONTROLLER_CLOCK_OUTPUT(){
    #ifdef _MICROCONTROLLER_CLOCK_OUTPUT_OFF
        SET_BIT(RCC->CFGR, RCC_CFGR_MCO_NOCLOCK);
    #elif _MICROCONTROLLER_CLOCK_OUTPUT_HSI14
        SET_BIT(RCC->CFGR, RCC_CFGR_MCO_HSI14);
    #elif _MICROCONTROLLER_CLOCK_OUTPUT_LSI
        SET_BIT(RCC->CFGR, RCC_CFGR_MCO_LSI);
    #elif _MICROCONTROLLER_CLOCK_OUTPUT_LSE
        SET_BIT(RCC->CFGR, RCC_CFGR_MCO_LSE);
    #elif _MICROCONTROLLER_CLOCK_OUTPUT_SCLK
        SET_BIT(RCC->CFGR, RCC_CFGR_MCO_SYSCLK);
    #elif _MICROCONTROLLER_CLOCK_OUTPUT_HSI8
        SET_BIT(RCC->CFGR, RCC_CFGR_MCO_HSI);
    #elif _MICROCONTROLLER_CLOCK_OUTPUT_HSE32
        SET_BIT(RCC->CFGR, RCC_CFGR_MCO_HSE);
    #elif _MICROCONTROLLER_CLOCK_OUTPUT_PLL
        SET_BIT(RCC->CFGR, RCC_CFGR_MCO_PLL);
    #endif
}