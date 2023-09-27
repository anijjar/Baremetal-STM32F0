#include "common.h"
#include "led.h"
#include "uart.h"

const uint8_t * message = "Hi my name is";

void USART1_IRQHandler(){
  
  // Example 1: Echo back message
  if(USART1->ISR & USART_ISR_RXNE){
    USART1->TDR = USART1->RDR;
  }
}

void config_uart1(void){
  UART1_DEINIT();
  UART_CONFIG_ENABLE_TRANSMIT_PIN(UART1_CONFIG);
  UART_CONFIG_ENABLE_RECEIVER_PIN(UART1_CONFIG);
  UART_CONFIG_ENABLE_RXNE_IE(UART1_CONFIG);
  UART_CONFIG_ENABLE_NVIC_IE(UART1_CONFIG);
  UART_CONFIG_NVIC_PRIORITY_HIGH(UART1_CONFIG);
  UART_CONFIG_SET_BAUDRATE_9600(UART1_CONFIG);
  UART1_INIT();
}

void init_hardware(void){
  // LED_Init(LED_BLUE_PORT, LED_BLUE_PIN, LED_ON);
  LED_Init(LED_GREEN_PORT, LED_GREEN_PIN, LED_ON);
}

void init_system_clock(void) {
  // update CORE_CLOCK_HZ before running app
  CORE_CLOCK_HZ = DEFAULT_SYSTEM_CLOCK; /* up to 48MHz*/
  // TODO: Implement updating features
}

/*
Entry point to access apps
*/
int main(void) {
  init_system_clock();
  init_hardware();
  config_uart1();
  LED_Init(LED_BLUE_PORT, LED_BLUE_PIN, LED_ON);
  for(;;){
    // USARTx_SEND_CHAR(USART1, 'H');
  }
  return 0;
}