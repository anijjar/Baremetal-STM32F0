#ifndef _EXTI_H
#define _EXTI_H

#include "main.h"

typedef enum {
    SYSCFG_EXTICR_GPIOA = 0U,
    SYSCFG_EXTICR_GPIOB,
    SYSCFG_EXTICR_GPIOC,
    SYSCFG_EXTICR_GPIOD,
    SYSCFG_EXTICR_RESERVED, // Do not use
    SYSCFG_EXTICR_GPIOF,
} Syscfg_exticr_t;

typedef enum {
    EXTI_TRIGGER_RISING = 1U, 
    EXTI_TRIGGER_FALLING, 
    EXTI_TRIGGER_BOTH,
} Exti_trigger_t;

typedef enum {
    NVIC_PRIORITY_0 = 0U,
    NVIC_PRIORITY_1,
    NVIC_PRIORITY_2,
    NVIC_PRIORITY_3,
} NVIC_Priority_t; // Level 0 is highest priority, level 3 is lowest.

// @brief configure EXTI Lines for GPIO only.
// pin = 0 to 15
void EXTI_GPIO_Init(uint8_t pin, Syscfg_exticr_t port, Exti_trigger_t trigger, IRQn_Type IRQn, NVIC_Priority_t priority);

void NVIC_Enable_Interrupt(IRQn_Type IRQn, NVIC_Priority_t priority);

// See vector_tables for callback names to redefine.

#endif