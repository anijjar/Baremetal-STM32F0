#ifndef _MAIN_H
#define _MAIN_H

// C Libraries here
#include <stdint.h>
#include "stm32f0xx.h"

#define DEVICE_TAG  "PROJECT: UART\r\n"
#define TOGGLE_BIT(REG, BIT)   ((REG) ^= (BIT))

/*
SYSTEM CLOCK SETUP: 
- To use default clock, comment out _ENABLE_PLL..
    and update CORE_CLOCK_HZ to 8000000U.
- Next, call the function in _rcc.h
*/
// #define _ENABLE_PLL_SYSTEM_CLOCK // _rcc.c
#define CORE_CLOCK_HZ 8000000U //48MHz max
#define PLL_MULT RCC_CFGR_PLLMUL8
/* END OF SYSTEM CLOCK SETUP */



/*
OUTPUT CLOCK SIGNAL SETUP
- Configure the output clock pin.
- Located in _rcc.c
- Uncomment one to use
*/
// #define _MICROCONTROLLER_CLOCK_OUTPUT_HSI14
// #define _MICROCONTROLLER_CLOCK_OUTPUT_LSI
// #define _MICROCONTROLLER_CLOCK_OUTPUT_LSE
// #define _MICROCONTROLLER_CLOCK_OUTPUT_SCLK 
// #define _MICROCONTROLLER_CLOCK_OUTPUT_HSI8 
// #define _MICROCONTROLLER_CLOCK_OUTPUT_HSE32
// #define _MICROCONTROLLER_CLOCK_OUTPUT_PLL 
/* END OF OUTPUT CLOCK SIGNAL SETUP */

/*
USART HIGH-LEVEL SETUP
- See the _uart.h file for other defines.
*/
#define USART_1_BUFFER_SIZE 8U
#define USART_1_PRIORITY NVIC_PRIORITY_1
#define USART_1_BAUD 9600U
// #define USART_1_EXTRA_PINS_EN
// #define USART_1_PIN_SWAP 
// #define USART_1_DMA_RX
// #define USART_1_DMA_TX
// #define USART_1_OVER8
// #define USART_1_PARITY_ODD
#define USART_1_IT // Enable NVIC Interrupt handle
// #define USART_1_TC_IT // Transmission Complete Interrupt
// #define USART_1_TXE_IT // Transmit DR Empty Interrupt
#define USART_1_RXNE_IT // Receive DR Empty Interrupt

#define USART_2_BUFFER_SIZE 8U
#define USART_2_PRIORITY NVIC_PRIORITY_1
#define USART_2_BAUD 115200U
// #define USART_2_EXTRA_PINS_EN
// #define USART_2_PIN_SWAP 
// #define USART_2_DMA_RX
// #define USART_2_DMA_TX
// #define USART_2_OVER8
// #define USART_2_PARITY_ODD
#define USART_2_IT // Enable NVIC Interrupt handle
// #define USART_2_TC_IT // Transmission Complete Interrupt
// #define USART_2_TXE_IT // Transmit DR Empty Interrupt
#define USART_2_RXNE_IT // Receive DR Empty Interrupt
/* END OF USART HIGH-LEVEL SETUP */

#endif