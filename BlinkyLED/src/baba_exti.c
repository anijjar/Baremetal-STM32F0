
#include "baba_exti.h"

void EXTI_GPIO_Init(Handler_Pin_t p, Handler_Port_t x, Handler_Trigger_Rising_t r, Handler_Trigger_Falling_t f, IRQn_Type IRQn){
  // Turn on the Syscfg clock
  SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGCOMPEN);

  // Assign a EXTI line to a Pin. All ports share a line with a pin (PA1=PB1 PA1!=PA2)
  // Another implementation can be with if statements and macros, but that adds unecessary instructions.
  // Shifting is quicker to perform than conditionals.
  SET_BIT(SYSCFG->EXTICR[p / 4], ( x << ( p % 4 ) ) ); // Port = x | pin mod 4 loops every 4

  // Setup EXTI Line as an interrupt (bits 16:31 are for other functions)
  SET_BIT(EXTI->IMR, 1 << p);

  // Setup Trigger (Branching Way - slow) 
  // if(t == Handler_Trigger_Falling){
  //   CLEAR_BIT(EXTI->RTSR, 1 << p);
  //   SET_BIT(EXTI->FTSR, 1 << p);
  // } else if(t == Handler_Trigger_Rising) {
  //   CLEAR_BIT(EXTI->FTSR, 1 << p);
  //   SET_BIT(EXTI->RTSR, 1 << p);
  // } else { // Set Both
  //   SET_BIT(EXTI->RTSR, 1 << p);
  //   SET_BIT(EXTI->FTSR, 1 << p);
  // }
  
  // Setup Trigger (Using Pointer arithmetic - fast)
  SET_BIT( EXTI->RTSR, r << p);
  SET_BIT( EXTI->FTSR, f << p);

  NVIC_SetPriority(IRQn, 0x04);
  NVIC_EnableIRQ(IRQn);

}
