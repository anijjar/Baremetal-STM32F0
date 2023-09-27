#ifndef UART_H
#define UART_H

#include "common.h"
#include "dma.h"
#include "gpio.h"

/*
UART Driver
DMA version (not implemented)
- Pros: lower cpu overhead
- Cons: higher power consumption

Polling/Interrupt version
- Pros: quick and simple
- Cons: higher cpu overhead

UART1 Pins:
- Transmit Pin : PB6 and PA9
- Receive Pin : PB7 and PA10
- CK Pin : PA8
- CTS Pin : PA11
- RTS Pin : PA12

UART2 Pins:
- Transmit Pin : PA2 and PA14
- Receive Pin : PA3 and PA15
- CK Pin : PA4
- CTS Pin : PA0
- RTS Pin : PA1
*/

#define UART_BAUDRATE_2400                                     (2400U)
#define UART_BAUDRATE_9600                                     (9600U)
#define UART_BAUDRATE_19200                                    (19200U)
#define UART_BAUDRATE_38400                                    (38400U)
#define UART_BAUDRATE_57600                                    (57600U)
#define UART_BAUDRATE_115200                                   (115200U)
#define UART_BAUDRATE_230400                                   (230400U)
#define UART_BAUDRATE_460800                                   (460800U)
#define UART_BAUDRATE_921600                                   (921600U)
#define UART_BAUDRATE_2000000                                  (2000000U)
#define UART_BAUDRATE_3000000                                  (3000000U)
#define UART_BAUDRATE_4000000                                  (4000000U)
#define UART_BAUDRATE_5000000                                  (5000000U)
#define UART_BAUDRATE_6000000                                  (6000000U)

#define UART_CONFIG_ENABLE_TRANSMIT_PIN(field)                 (SET_BIT(field, 1 << 0))
#define UART_CONFIG_ENABLE_RECEIVER_PIN(field)                 (SET_BIT(field, 1 << 1))
#define UART_CONFIG_ENABLE_CK_PIN(field)                       (SET_BIT(field, 1 << 2))
#define UART_CONFIG_ENABLE_CTS_PIN(field)                      (SET_BIT(field, 1 << 3))
#define UART_CONFIG_ENABLE_RTS_PIN(field)                      (SET_BIT(field, 1 << 4))
#define UART_CONFIG_SWAP_PINS(field)                           (SET_BIT(field, 1 << 5))
#define UART_CONFIG_9_DATA_BITS(field)                         (SET_BIT(field, 1 << 6))
#define UART_CONFIG_2_STOP_BITS(field)                         (SET_BIT(field, 1 << 7))
#define UART_CONFIG_PARITY_ODD(field)                          (SET_BIT(field, 1 << 9))
#define UART_CONFIG_8_BIT_OVERSAMPLE(field)                    (SET_BIT(field, 1 << 10))
#define UART_CONFIG_ENABLE_DMA(field)                          (SET_BIT(field, 1 << 11))
#define UART_CONFIG_ENABLE_TC_IE(field)                        (SET_BIT(field, 1 << 12))
#define UART_CONFIG_ENABLE_TXE_IE(field)                       (SET_BIT(field, 1 << 13))
#define UART_CONFIG_ENABLE_RXNE_IE(field)                      (SET_BIT(field, 1 << 14))
#define UART_CONFIG_ENABLE_NVIC_IE(field)                      (SET_BIT(field, 1 << 15))
#define UART_CONFIG_NVIC_PRIORITY_LOW(field)                   (SET_BIT(field, GPIO_IT_PRIORITY_LOW << 16))
#define UART_CONFIG_NVIC_PRIORITY_MED(field)                   (SET_BIT(field, GPIO_IT_PRIORITY_MED << 16))
#define UART_CONFIG_NVIC_PRIORITY_HIGH(field)                  (SET_BIT(field, GPIO_IT_PRIORITY_HIGH << 16))
#define UART_CONFIG_NVIC_PRIORITY_HIGHEST(field)               (SET_BIT(field, GPIO_IT_PRIORITY_HIGHEST << 16))
#define UART_CONFIG_SET_BAUDRATE_2400(field)                   (SET_BIT(field, 0 << 18))
#define UART_CONFIG_SET_BAUDRATE_9600(field)                   (SET_BIT(field, 1 << 18))
#define UART_CONFIG_SET_BAUDRATE_19200(field)                  (SET_BIT(field, 2 << 18))
#define UART_CONFIG_SET_BAUDRATE_38400(field)                  (SET_BIT(field, 3 << 18))
#define UART_CONFIG_SET_BAUDRATE_57600(field)                  (SET_BIT(field, 4 << 18))
#define UART_CONFIG_SET_BAUDRATE_115200(field)                 (SET_BIT(field, 5 << 18))
#define UART_CONFIG_SET_BAUDRATE_230400(field)                 (SET_BIT(field, 6 << 18))
#define UART_CONFIG_SET_BAUDRATE_460800(field)                 (SET_BIT(field, 7 << 18))
#define UART_CONFIG_SET_BAUDRATE_921600(field)                 (SET_BIT(field, 8 << 18))
#define UART_CONFIG_SET_BAUDRATE_2000000(field)                (SET_BIT(field, 9 << 18))
#define UART_CONFIG_SET_BAUDRATE_3000000(field)                (SET_BIT(field, 10 << 18))
#define UART_CONFIG_SET_BAUDRATE_4000000(field)                (SET_BIT(field, 11 << 18))
#define UART_CONFIG_SET_BAUDRATE_5000000(field)                (SET_BIT(field, 12 << 18))
#define UART_CONFIG_SET_BAUDRATE_6000000(field)                (SET_BIT(field, 13 << 18))
#define UART_CONFIG_SELECT_TRANSMIT_PIN_2(field)               (SET_BIT(field, 1 << 22))
#define UART_CONFIG_SELECT_RECEIVER_PIN_2(field)               (SET_BIT(field, 1 << 23))

#define UART_CONFIG_READ_ENABLE_TRANSMIT_PIN(field)            (READ_BIT(field, 1 << 0))
#define UART_CONFIG_READ_ENABLE_RECEIVER_PIN(field)            (READ_BIT(field, 1 << 1))
#define UART_CONFIG_READ_ENABLE_CK_PIN(field)                  (READ_BIT(field, 1 << 2))
#define UART_CONFIG_READ_ENABLE_CTS_PIN(field)                 (READ_BIT(field, 1 << 3))
#define UART_CONFIG_READ_ENABLE_RTS_PIN(field)                 (READ_BIT(field, 1 << 4))
#define UART_CONFIG_READ_SWAP_PINS(field)                      (READ_BIT(field, 1 << 5))
#define UART_CONFIG_READ_9_DATA_BITS(field)                    (READ_BIT(field, 1 << 6))
#define UART_CONFIG_READ_2_STOP_BITS(field)                    (READ_BIT(field, 1 << 7))
#define UART_CONFIG_READ_PARITY_ODD(field)                     (READ_BIT(field, 1 << 9))
#define UART_CONFIG_READ_8_BIT_OVERSAMPLE(field)               (READ_BIT(field, 1 << 10))
#define UART_CONFIG_READ_ENABLE_DMA(field)                     (READ_BIT(field, 1 << 11))
#define UART_CONFIG_READ_ENABLE_TC_IE(field)                   (READ_BIT(field, 1 << 12))
#define UART_CONFIG_READ_ENABLE_TXE_IE(field)                  (READ_BIT(field, 1 << 13))
#define UART_CONFIG_READ_ENABLE_RXNE_IE(field)                 (READ_BIT(field, 1 << 14))
#define UART_CONFIG_READ_ENABLE_NVIC_IE(field)                 (READ_BIT(field, 1 << 15))
#define UART_CONFIG_READ_NVIC_PRIORITY(field)                  (READ_BIT(field, 0x3 << 16))
#define UART_CONFIG_READ_SET_BAUDRATE(field)                   (READ_BIT(field, 0xF << 18))
#define UART_CONFIG_READ_SELECT_TRANSMIT_PIN_2(field)          (READ_BIT(field, 1 << 22))
#define UART_CONFIG_READ_SELECT_RECEIVER_PIN_2(field)          (READ_BIT(field, 1 << 23))

volatile uint32_t UART1_CONFIG;
volatile uint32_t UART2_CONFIG;

typedef enum {
    UART_OK = 0U,
    UART_ERROR
} eUartErrorCodes_t; 

eUartErrorCodes_t UART1_INIT();
eUartErrorCodes_t UART2_INIT();

eUartErrorCodes_t UART1_DEINIT();
eUartErrorCodes_t UART2_DEINIT();

eUartErrorCodes_t USARTx_SEND_CHAR(USART_TypeDef * USARTx, const uint8_t c);


#endif