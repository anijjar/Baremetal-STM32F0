#ifndef GPIO_H
#define GPIO_H

#include "common.h"
/*
TODO: Implement a buffer to track enabled pins and ports.
Turn off the RCC clock of deinit pins
*/


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
} eGpioPin_t;

typedef enum {
    GPIO_MODER_INPUT = 0U,
    GPIO_MODER_OUTPUT,
    GPIO_MODER_AF,
    GPIO_MODER_ANALOG,
    GPIO_MODER_TOTAL
} eGpioModer_t;

typedef enum {
    GPIO_OTYPER_PP = 0U,
    GPIO_OTYPER_DRAIN,
    GPIO_OTYPER_TOTAL
} eGpioOtyper_t;

typedef enum {
    GPIO_OSPEEDR_LOW = 0U,
    GPIO_OSPEEDR_MED,
    GPIO_OSPEEDR_RESERVED,
    GPIO_OSPEEDR_HIGH,
    GPIO_OSPEEDR_TOTAL
} eGpioOspeedr_t;

typedef enum {
    GPIO_PUPDR_NONE = 0U,
    GPIO_PUPDR_PU,
    GPIO_PUPDR_PD,
    GPIO_PUPDR_RESERVED,
    GPIO_PUPDR_TOTAL
} eGpioPupdr_t;

typedef enum {
    GPIO_AF_0 = 0U,
    GPIO_AF_1,
    GPIO_AF_2,
    GPIO_AF_3,
    GPIO_AF_4,
    GPIO_AF_5,
    GPIO_AF_6,
    GPIO_AF_7,
    GPIO_AF_TOTAL
} eGpioAf_t;

typedef enum {
    GPIO_IT_PRIORITY_HIGHEST = 0U,
    GPIO_IT_PRIORITY_HIGH,
    GPIO_IT_PRIORITY_MED,
    GPIO_IT_PRIORITY_LOW,
} eGpioItPriority_t; 

typedef enum {
    GPIO_IT_TRIGGER_RISING = 1U, 
    GPIO_IT_TRIGGER_FALLING, 
    GPIO_IT_TRIGGER_BOTH,
} eGpioItTrig_t; 

typedef enum {
    GPIO_PORT_GPIOA = 0U,
    GPIO_PORT_GPIOB,
    GPIO_PORT_GPIOC,
    GPIO_PORT_GPIOD,
    GPIO_PORT_RESERVED, // Do not use
    GPIO_PORT_GPIOF,
} eGpioPort_t;

typedef enum {
    GPIO_OK = 0U,
    GPIO_ERROR
} eGpioError_t;


eGpioError_t GPIO_CONFIG_PIN_INPUT_DEFAULT(GPIO_TypeDef * GPIOx, eGpioPin_t pin);
eGpioError_t GPIO_CONFIG_PIN_OUTPUT_DEFAULT(GPIO_TypeDef * GPIOx, eGpioPin_t pin);
eGpioError_t GPIO_CONFIG_PIN(GPIO_TypeDef * GPIOx,
    eGpioPin_t pin,
    eGpioModer_t moder,
    eGpioOtyper_t otyper,
    eGpioOspeedr_t ospeedr,
    eGpioPupdr_t pupdr,
    eGpioAf_t af
);

eGpioError_t GPIO_DECONFIG_PIN(GPIO_TypeDef * GPIOx,
    eGpioPin_t pin,
    eGpioModer_t moder,
    eGpioOtyper_t otyper,
    eGpioOspeedr_t ospeedr,
    eGpioPupdr_t pupdr,
    eGpioAf_t af
);

/* See vector table for interrupt handler symbols */
eGpioError_t GPIO_CONFIG_IT(
    GPIO_TypeDef * GPIOx,
    eGpioPin_t pin,
    eGpioItPriority_t pri,
    eGpioItTrig_t trig,
    eGpioPort_t port
);

eGpioError_t GPIO_OUTPUT_SET(GPIO_TypeDef * GPIOx, eGpioPin_t pin);
eGpioError_t GPIO_OUTPUT_RESET(GPIO_TypeDef * GPIOx, eGpioPin_t pin);
eGpioError_t GPIO_OUTPUT_TOGGLE(GPIO_TypeDef * GPIOx, eGpioPin_t pin);
eGpioError_t GPIO_CONFIG_LOCK(GPIO_TypeDef * GPIOx, eGpioPin_t pin);
eGpioError_t GPIO_CONFIG_UNLOCK(GPIO_TypeDef * GPIOx, eGpioPin_t pin);
eGpioError_t GPIO_ENABLE_INTERRUPT(IRQn_Type IRQn, eGpioItPriority_t priority);
eGpioError_t GPIO_DISABLE_INTERRUPT(IRQn_Type IRQn);
#endif