
#include "_exti.h"

static void _Config_EXTI_GPIO( uint8_t pin, Syscfg_exticr_t port, Exti_trigger_t trigger, IRQn_Type IRQn ){
    // assert( pin >= 0 && pin < 16 );
    // assert(IRQn == EXTI0_1_IRQn || IRQn == EXTI2_3_IRQn || IRQn == EXTI4_15_IRQn);

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

void NVIC_Enable_Interrupt( IRQn_Type IRQn, NVIC_Priority_t priority ) {
    NVIC_SetPriority(IRQn, priority);
    NVIC_EnableIRQ(IRQn);
}

void EXTI_GPIO_Init( uint8_t pin, Syscfg_exticr_t port, Exti_trigger_t trigger, IRQn_Type IRQn, NVIC_Priority_t priority ){
    _Config_EXTI_GPIO(pin, port, trigger, IRQn);
    NVIC_Enable_Interrupt(IRQn, priority);
}

