#include "main.h"
// #include "sensors.h"
#include "hc05.h"
#include "onboardPeriph.h"

sHc_t hc05 = {
  .UART_Periph = USART1_PERIPHERAL,
  .baud = 9600,
};

void init_hardware(){
  onboard_led_blue_init();
  onboard_led_green_init();
  led_off(ONBOARD_BLUE_LED_PIN, ONBOARD_BLUE_LED_PORT);
  hc05.sTx = GET_USARTx_PIN(USART1_PERIPHERAL, TRANSMIT_PIN_1);
  hc05.sRx = GET_USARTx_PIN(USART1_PERIPHERAL, RECEIVE_PIN_1);
  HC05_INIT(&hc05);
}

int main(void) {
  init_hardware();
  led_on(ONBOARD_BLUE_LED_PIN, ONBOARD_BLUE_LED_PORT);

  for(;;){
    HC05_SEND_MESSAGE(&hc05, "IM HERE\r\n");
  }
  return 0;
}