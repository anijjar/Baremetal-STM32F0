
#include "gpio.h"

eGpioError_t GPIO_CONFIG_PIN_INPUT_DEFAULT(GPIO_TypeDef * GPIOx, eGpioPin_t pin){
    GPIO_CONFIG_PIN(
        GPIOx,
        pin,
        GPIO_MODER_INPUT,
        GPIO_OTYPER_PP,
        GPIO_OSPEEDR_LOW,
        GPIO_PUPDR_NONE,
        GPIO_AF_0
    );
    return GPIO_OK;
}

eGpioError_t GPIO_CONFIG_PIN_OUTPUT_DEFAULT(GPIO_TypeDef * GPIOx, eGpioPin_t pin){
    GPIO_CONFIG_PIN(
        GPIOx,
        pin,
        GPIO_MODER_OUTPUT,
        GPIO_OTYPER_PP,
        GPIO_OSPEEDR_LOW,
        GPIO_PUPDR_NONE,
        GPIO_AF_0
    );
    return GPIO_OK;
}

eGpioError_t GPIO_CONFIG_PIN(GPIO_TypeDef * GPIOx, eGpioPin_t pin, eGpioModer_t moder, eGpioOtyper_t otyper, eGpioOspeedr_t ospeedr, eGpioPupdr_t pupdr, eGpioAf_t af){
    // Turn on clock
    if(GPIOx == GPIOA){
        SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOAEN);
    } else if(GPIOx == GPIOB) {
        SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOBEN);
    } else if(GPIOx == GPIOC) {
        SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOCEN);
    } else if(GPIOx == GPIOD) {
        SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIODEN);
    } else if(GPIOx == GPIOF) {
        SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOFEN);
    } else {
        return GPIO_ERROR;
    }
     
    // Configure basic registers
    SET_BIT(GPIOx->MODER, moder << (pin*2));
    SET_BIT(GPIOx->OSPEEDR, ospeedr << (pin*2));
    SET_BIT(GPIOx->PUPDR, pupdr << (pin*2));
    SET_BIT(GPIOx->AFR[pin / 8], af << (pin*2));
    SET_BIT(GPIOx->OTYPER, otyper << pin);

    return GPIO_OK;
}

eGpioError_t GPIO_DECONFIG_PIN(GPIO_TypeDef * GPIOx, eGpioPin_t pin, eGpioModer_t moder, eGpioOtyper_t otyper, eGpioOspeedr_t ospeedr, eGpioPupdr_t pupdr, eGpioAf_t af ){
     
    // Configure basic registers
    CLEAR_BIT(GPIOx->MODER, moder << (pin*2));
    CLEAR_BIT(GPIOx->OSPEEDR, ospeedr << (pin*2));
    CLEAR_BIT(GPIOx->PUPDR, pupdr << (pin*2));
    CLEAR_BIT(GPIOx->AFR[pin / 8], af << (pin*2));
    CLEAR_BIT(GPIOx->OTYPER, otyper << pin);
    return GPIO_OK;
}

eGpioError_t GPIO_CONFIG_IT(GPIO_TypeDef * GPIOx, eGpioPin_t pin, eGpioItPriority_t pri, eGpioItTrig_t trig, eGpioPort_t port) {
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGCOMPEN);
    SET_BIT(SYSCFG->EXTICR[pin / 4], ( port << ( pin % 4 ) ) );
    SET_BIT(EXTI->IMR, 1 << pin);
    SET_BIT(EXTI->RTSR, (trig & 0x1) << pin); //rising edge
    SET_BIT(EXTI->FTSR, (trig & 0x2) << pin); // falling edge
    if(pin == PIN_0 || pin == PIN_1) {
        GPIO_ENABLE_INTERRUPT(EXTI0_1_IRQn, pri);
    } else if(pin == PIN_2 || pin == PIN_3){
        GPIO_ENABLE_INTERRUPT(EXTI2_3_IRQn, pri);
    } else {
        GPIO_ENABLE_INTERRUPT(EXTI4_15_IRQn, pri);
    }
    return GPIO_OK;
}

eGpioError_t GPIO_ENABLE_INTERRUPT( IRQn_Type IRQn, eGpioItPriority_t priority ) {
    NVIC_SetPriority(IRQn, priority);
    NVIC_EnableIRQ(IRQn);
    return GPIO_OK;
}

eGpioError_t GPIO_DISABLE_INTERRUPT( IRQn_Type IRQn) {
    NVIC_DisableIRQ(IRQn);
    return GPIO_OK;
}


eGpioError_t GPIO_OUTPUT_SET(GPIO_TypeDef * GPIOx, eGpioPin_t pin){
    SET_BIT(GPIOx->ODR, 1 << pin);
    return GPIO_OK;
}

eGpioError_t GPIO_OUTPUT_RESET(GPIO_TypeDef * GPIOx, eGpioPin_t pin){
    CLEAR_BIT(GPIOx->ODR, 1 << pin);
    return GPIO_OK;
}

eGpioError_t GPIO_OUTPUT_TOGGLE(GPIO_TypeDef * GPIOx, eGpioPin_t pin){
    TOGGLE_BIT(GPIOx->ODR, 1 << pin);
    return GPIO_OK;
}

eGpioError_t GPIO_CONFIG_LOCK(GPIO_TypeDef * GPIOx, eGpioPin_t pin){
    SET_BIT(GPIOx->LCKR, 1 << pin);
    return GPIO_OK;
}

eGpioError_t GPIO_CONFIG_UNLOCK(GPIO_TypeDef * GPIOx, eGpioPin_t pin){
    CLEAR_BIT(GPIOx->LCKR, 1 << pin);
    return GPIO_OK;
}