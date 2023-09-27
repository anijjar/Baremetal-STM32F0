#include "led.h"



eLedErrorCodes_t LED_Init(GPIO_TypeDef * port, eGpioPin_t pin, eLedState_t state){
    
    GPIO_CONFIG_PIN(port, 
        pin, 
        GPIO_MODER_OUTPUT, 
        GPIO_OTYPER_PP,
        GPIO_OSPEEDR_LOW,
        GPIO_PUPDR_NONE,
        GPIO_AF_0
    );

    // Switch statement is ok because the cases are 
    // not disjointed (1, 3435, 34, 23, etc), so the 
    // compiler will not perform a goto, but rather 
    // if-else branching.
    switch(state){
        case LED_OFF:
            LED_Off(pin, port);
            return LED_OK;
        case LED_ON:
            LED_On(pin, port);
            return LED_OK;
        case LED_TOGGLE:
            LED_Toggle(pin, port);
            return LED_OK;
        default:
            break;
    }
    return LED_ERROR;
}

void LED_On(uint8_t led, GPIO_TypeDef * GPIOx){
    GPIO_OUTPUT_SET(GPIOx, led);
}
void LED_Off(uint8_t led, GPIO_TypeDef * GPIOx){
    GPIO_OUTPUT_RESET(GPIOx, led);
}
void LED_Toggle(uint8_t led, GPIO_TypeDef * GPIOx){
    GPIO_OUTPUT_TOGGLE(GPIOx, led);
}