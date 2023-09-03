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

int main(void) {
  _SYSTEM_CORE_CLOCK_SETUP();
  onboard_led_blue_init();

  sTIMx_t * ptr_tim = &timer_3;
  ptr_tim->TIMx = TIM3;
  ptr_tim->rcc = RCC->APB1ENR;
  ptr_tim->clk_bit = RCC_APB1ENR_TIM3EN;
  ptr_tim->IRQn = TIM3_IRQn;
  ptr_tim->nvic_priority = NVIC_PRIORITY_2;
  ptr_tim->count_mode = TIMER_COUNT_UP;
  ptr_tim->one_pulse_mode = TIMER_ONE_PULSE_MODE_OFF;
  TIMx_Counter_Init(ptr_tim, 1000, CORE_CLOCK_HZ/1000);


  for(;;);
  return 0;
}