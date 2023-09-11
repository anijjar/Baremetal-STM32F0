
#include "onboardPeriph.h"

void onboard_led_blue_init() {
    // Turn on the GPIOC Clock
    SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOCEN);
    // Set PC8 to output mode
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODER8_0);
    SET_BIT(GPIOC->ODR, ONBOARD_LED_BLUE_DEFAULT_STATE << ONBOARD_BLUE_LED_PIN);
}

void onboard_led_green_init() {
    // Turn on the GPIOC Clock
    SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOCEN);
    // Set PC9 to output mode
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODER9_0);
    SET_BIT(GPIOC->ODR, ONBOARD_LED_GREEN_DEFAULT_STATE << ONBOARD_GREEN_LED_PIN);
}

void led_on(uint8_t led, GPIO_TypeDef * GPIOx){
    SET_BIT(GPIOx->ODR, 1 << led);
}
void led_off(uint8_t led, GPIO_TypeDef * GPIOx){
    CLEAR_BIT(GPIOx->ODR, 1 << led);
}
void led_toggle(uint8_t led, GPIO_TypeDef * GPIOx){
    TOGGLE_BIT(GPIOx->ODR, 1 << led);
}
