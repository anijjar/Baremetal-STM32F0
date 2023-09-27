#ifndef LED_H
#define LED_H

#include "common.h"
#include "gpio.h"

typedef enum {
  LED_OFF = 0U,
  LED_ON,
  LED_TOGGLE
} eLedState_t;

typedef enum {
  LED_OK = 0U,
  LED_ERROR,
} eLedErrorCodes_t;

#define LED_BLUE_PIN PIN_8 //PC8
#define LED_BLUE_PORT GPIOC
#define LED_GREEN_PIN PIN_9 //PC9
#define LED_GREEN_PORT GPIOC

eLedErrorCodes_t LED_Init(GPIO_TypeDef * port, eGpioPin_t pin, eLedState_t state);

void LED_On(uint8_t led, GPIO_TypeDef * GPIOx);
void LED_Off(uint8_t led, GPIO_TypeDef * GPIOx);
void LED_Toggle(uint8_t led, GPIO_TypeDef * GPIOx);


#endif