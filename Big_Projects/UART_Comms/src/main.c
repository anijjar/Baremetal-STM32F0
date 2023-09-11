#include "main.h"
#include "onboardPeriph.h"
#include "_uart.h"
// #include "_uart.h"


void USART1_IRQHandler(){
  // if(USART1->ISR & ){

  // }
}

void Initialize_Hardware(){
  onboard_led_blue_init();
  USART1_INIT(GET_USART1_PIN(TRANSMIT_PIN_1), GET_USART1_PIN(RECEIVE_PIN_1));
}

/*
This example echos back messages
*/
int main(void) {
  Initialize_Hardware();
  // Blue LED signals that HW was initialized correctly
  led_on(ONBOARD_BLUE_LED_PIN, ONBOARD_BLUE_LED_PORT);
    USART1->TDR = 'a';
  for(;;){
    // _Send_Char(rxb);
  }
  return 0;
}