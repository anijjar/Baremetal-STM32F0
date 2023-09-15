#include "main.h"
#include "onboardPeriph.h"
#include "_uart.h"

// Example 2:
uint8_t * receiveBuffer = "";
int indx = 0U;
int bufferSize = 16U;
int fReady = 0U;
int fOverflow = 0U;

// Example 3: Use the circular buffer


void USART1_IRQHandler(){
  // Example 1: Echo back message (works)
  // if(USART1->ISR & USART_ISR_RXNE){
  //   // USART1->TDR = USART1->RDR;
  // }

  // Example 2: store it into global receiveBuffer and echo back in main
  if(USART1->ISR & USART_ISR_RXNE){
    receiveBuffer[indx] = USARTx_RECEIVE_CHAR(USART1);
    indx += 1;
    // When a new line or carrage return is received, message is good.
    if(receiveBuffer[indx] == '\r' || receiveBuffer[indx] == '\n'){
      fReady = 1;
    }
    // if index wraps around, we know its an overflow.
    if((indx == bufferSize) && fReady != 1){
      fOverflow = 1;
    }
  }


}

void Initialize_Hardware(){
  onboard_led_blue_init();
  USARTx_INIT(USART1_PERIPHERAL, 
    GET_USARTx_PIN(USART1_PERIPHERAL, TRANSMIT_PIN_1), 
    GET_USARTx_PIN(USART1_PERIPHERAL, RECEIVE_PIN_1),
    9600
    );
}

/*
This example echos back messages through regular polling, then interrupts, then DMA-based polling/interrupt.
*/
int main(void) {
  Initialize_Hardware();
  // Blue LED signals that HW was initialized correctly
  led_on(ONBOARD_BLUE_LED_PIN, ONBOARD_BLUE_LED_PORT);  


  // USARTx_SEND_CHAR(USART1, 'a'); // works
  // uint8_t * message = "Hi\r\n";
  USARTx_SEND_MESSAGE(USART1, DEVICE_TAG, sizeof(DEVICE_TAG) / sizeof(DEVICE_TAG[0])); // works
  // for(;;){
    // USARTx_SEND_CHAR(USART1, 'a'); // works
    // USARTx_SEND_MESSAGE(USART1, message, sizeof(message) / sizeof(message[0])); // works
  // }
  
  // Example 2:
  for(;;){
    if(fReady){
      USARTx_SEND_MESSAGE(USART1, receiveBuffer, sizeof(receiveBuffer)/sizeof(receiveBuffer[0]));
    }
    if(fOverflow){
      indx = 0;
      USARTx_SEND_MESSAGE(USART1, "OVERFLOW\r\n", 10);
    }
  }

  // Example 3:
  for(;;){

  }

  return 0;
}