#ifndef _BABA_EXTI_H
#define _BABA_EXTI_H

#include "baba.h"

typedef enum {
    SYSCFG_EXTICR_A = 0U,
    SYSCFG_EXTICR_B,
    SYSCFG_EXTICR_C,
    SYSCFG_EXTICR_D,
    SYSCFG_EXTICR_RESERVED, // Do not use
    SYSCFG_EXTICR_F,
} Syscfg_exticr_t;

typedef enum {
    EXTI_TRIGGER_RISING = 1U, 
    EXTI_TRIGGER_FALLING, 
    EXTI_TRIGGER_BOTH,
} Exti_trigger_t;

// @brief configure EXTI Lines for GPIO only.
// pin = 0 to 15
void EXTI_GPIO_Init(uint8_t pin, Syscfg_exticr_t port, Exti_trigger_t trigger);


#endif