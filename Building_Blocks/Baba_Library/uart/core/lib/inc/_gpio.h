#ifndef _GPIO_H
#define _GPIO_H
// See vector_tables for callback names to redefine.

#include "main.h"

typedef enum {
    PIN_0 = 0U,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7,
    PIN_8,
    PIN_9,
    PIN_10,
    PIN_11,
    PIN_12,
    PIN_13,
    PIN_14,
    PIN_15,
} ePin_t;

// Level 0 is highest priority, level 3 is lowest.
typedef enum {
    NVIC_PRIORITY_0 = 0U,
    NVIC_PRIORITY_1,
    NVIC_PRIORITY_2,
    NVIC_PRIORITY_3,
} eNVICPriority_t; 

typedef enum {
    EXTI_TRIGGER_RISING = 1U, 
    EXTI_TRIGGER_FALLING, 
    EXTI_TRIGGER_BOTH,
} eExtiTrigger_t; 

typedef enum {
    SYSCFG_EXTICR_GPIOA = 0U,
    SYSCFG_EXTICR_GPIOB,
    SYSCFG_EXTICR_GPIOC,
    SYSCFG_EXTICR_GPIOD,
    SYSCFG_EXTICR_RESERVED, // Do not use
    SYSCFG_EXTICR_GPIOF,
} eSyscfgExticr_t;

typedef struct {
    ePin_t pin;
    GPIO_TypeDef * GPIOx;
} sGPIO_t;

typedef struct {
    ePin_t pin;
    eNVICPriority_t pri;
    eExtiTrigger_t trig;
    eSyscfgExticr_t port;
    IRQn_Type IRQn;
} sEXTI_t;

// @brief configure EXTI Lines for GPIO only.
void EXTI_GPIO_INIT(sEXTI_t * packet);

void NVIC_ENABLE_INTERRUPT(IRQn_Type IRQn, eNVICPriority_t priority);

#endif