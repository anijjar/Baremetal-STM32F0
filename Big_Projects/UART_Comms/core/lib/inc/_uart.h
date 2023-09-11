#ifndef _UART_H
#define _UART_H

#include "main.h"
#include "_gpio.h"
#include "circularBuffer.h"

/*
UART Setup
*/

// #define USART_1_EXTRA_PINS_EN
// #define USART_2_EXTRA_PINS_EN

// #define USART_1_PIN_SWAP 
// #define USART_2_PIN_SWAP 

// #define USART_1_DMA_RX
// #define USART_2_DMA_RX

// #define USART_1_DMA_TX
// #define USART_2_DMA_TX

// #define USART_1_OVER8
// #define USART_2_OVER8

// #define USART_1_PARITY_ODD
// #define USART_2_PARITY_ODD

// #define USART_1_TC_IT // Transmission Complete Interrupt
// #define USART_2_TC_IT // Transmission Complete Interrupt

// #define USART_1_TXE_IT // Transmit DR Empty Interrupt
// #define USART_2_TXE_IT // Transmit DR Empty Interrupt

#define USART_1_RXNE_IT // Receive DR Empty Interrupt
#define USART_2_RXNE_IT // Receive DR Empty Interrupt


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

void USART1_INIT(sGPIO_t sTx, sGPIO_t sRx);
sGPIO_t GET_USART1_PIN(eUsartPins_t pin);

#endif