
#include "gpio.h"


static void EXTI_GPIO_CONFIG( ePin_t pin, eSyscfgExticr_t port, eExtiTrigger_t trigger){

    // Turn on the Syscfg clock
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGCOMPEN);

    // Assign a EXTI line to a Pin. All ports share a line with a pin (PA1=PB1 PA1!=PA2)
    // Another implementation can be with if statements and macros, but that adds unecessary instructions.
    // Shifting is quicker to perform than conditionals.
    SET_BIT(SYSCFG->EXTICR[pin / 4], ( port << ( pin % 4 ) ) );

    // Setup EXTI Line as an interrupt (bits 16:31 are for other functions)
    SET_BIT(EXTI->IMR, 1 << pin);

    // Setup Trigger (Using masking and shifting is quick. Not branching)
    SET_BIT( EXTI->RTSR, (trigger & 0x1) << pin);
    SET_BIT( EXTI->FTSR, (trigger & 0x2) << pin);
}

void NVIC_ENABLE_INTERRUPT( IRQn_Type IRQn, eNVICPriority_t priority ) {
    NVIC_SetPriority(IRQn, priority);
    NVIC_EnableIRQ(IRQn);
}

void EXTI_GPIO_INIT(sEXTI_t * packet){
    EXTI_GPIO_CONFIG(packet->pin, packet->port, packet->trig);
    NVIC_ENABLE_INTERRUPT(packet->IRQn, packet->pri);
}