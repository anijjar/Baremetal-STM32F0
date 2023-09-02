#ifndef _LED_H
#define _LED_H

#include "main.h"
#include "_exti.h"

typedef enum {
  LED_OFF = 0U,
  LED_ON,
} led_state_t;

#define ONBOARD_PUSH_BUTTON_PIN 0 //PA0
#define ONBOARD_BLUE_LED_PIN 8 //PC8
#define ONBOARD_GREEN_LED_PIN 9 //PC9

const GPIO_TypeDef * ONBOARD_BLUE_LED_PORT = GPIOC;
const GPIO_TypeDef * ONBOARD_GREEN_LED_PORT = GPIOC;

#define ONBOARD_LED_BLUE_DEFAULT_STATE LED_OFF
#define ONBOARD_LED_GREEN_DEFAULT_STATE LED_OFF

volatile led_state_t onboard_blue_led_state = ONBOARD_LED_BLUE_DEFAULT_STATE;
volatile led_state_t onboard_green_led_state = ONBOARD_LED_GREEN_DEFAULT_STATE;


void onboard_led_blue_init();
void onboard_led_green_init();
void onboard_pushButton_init();

void led_on(uint8_t led, GPIO_TypeDef * GPIOx);
void led_off(uint8_t led, GPIO_TypeDef * GPIOx);
void led_toggle(uint8_t led, GPIO_TypeDef * GPIOx);

void onboard_pushbutton_interrupt(FunctionalState state);
// Uncomment if using pushbutton
// void EXTI0_1_IRQHandler(void);

#endif