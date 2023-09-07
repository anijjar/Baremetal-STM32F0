#include "main.h"
#include "_rcc.h"
#include "onboardPeriph.h"
#include "timer.h"

void TIM3_IRQHandler(){
  if(TIM3->SR & TIM_SR_UIF){
    CLEAR_BIT(TIM3->SR, TIM_SR_UIF);
    led_toggle(ONBOARD_BLUE_LED_PIN, ONBOARD_BLUE_LED_PORT);
  }
}

// Toggling this way reduces the bounce
void EXTI0_1_IRQHandler(void){
  if(EXTI->PR & (1 << ONBOARD_PUSH_BUTTON_PIN)) {
    led_toggle(ONBOARD_GREEN_LED_PIN, ONBOARD_GREEN_LED_PORT);
    SET_BIT(EXTI->PR, EXTI_PR_PR0);
  }
}

int main(void) {
  _SYSTEM_CORE_CLOCK_SETUP();
  onboard_led_green_init();
  onboard_led_blue_init();
  onboard_pushButton_init();
  onboard_pushbutton_interrupt(ENABLE);

  TIMx_Init(TIM3, 0x0000, NVIC_PRIORITY_3);
  Counter_Init(TIM3, 1000, CORE_CLOCK_HZ/100000);


  for(;;);
  return 0;
}