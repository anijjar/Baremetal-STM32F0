
#include "baba_exti.h"

void EXTI_GPIO_Init(uint8_t pin, Syscfg_exticr_t port, Exti_trigger_t trigger){
  
  assert( pin >= 0 && pin < 16 );

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

  NVIC_SetPriority(IRQn, 0x04);
  NVIC_EnableIRQ(IRQn);
}