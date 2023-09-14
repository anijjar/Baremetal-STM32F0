#ifndef _UART_H
#define _UART_H

#include "main.h"
#include "_gpio.h"

/*
UART Driver
DMA version (not implemented)
- Pros: lower cpu overhead
- Cons: higher power consumption

Polling/Interrupt version
- Pros: quick and simple
- Cons: higher cpu overhead

Incomplete, but modify as we go
*/

typedef enum {
    TRANSMIT_PIN_1 = 0U,
    TRANSMIT_PIN_2,
    RECEIVE_PIN_1,
    RECEIVE_PIN_2,
    CK_PIN,
    CTS_PIN,
    RTS_PIN,
    TOTAL_USART_PINS,
} eUsartPins_t;

typedef enum {
    RECEIVE_BUFFER = 0U,
    TRANSMIT_BUFFER,
} eUsartBuffer_t;

typedef enum {
    USART1_PERIPHERAL = 0U,
    USART2_PERIPHERAL,
} eUsartPeriperal_t;

void USARTx_INIT(eUsartPeriperal_t periph, sGPIO_t sTx, sGPIO_t sRx);
sGPIO_t GET_USARTx_PIN(eUsartPeriperal_t periph, eUsartPins_t pin);

int USARTx_SEND_MESSAGE(USART_TypeDef * USARTx, uint8_t * message, int len);
void USARTx_SEND_CHAR(USART_TypeDef * USARTx, const uint8_t c);

uint8_t USARTx_RECEIVE_CHAR(USART_TypeDef * USARTx);
#endif