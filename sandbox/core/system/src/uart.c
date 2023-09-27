#include "uart.h"


uint32_t UART_GET_BAUDRATE(const uint8_t baud){
    switch(baud) {
        case 1:
            return UART_BAUDRATE_2400;
            break;
        case 2:
            return UART_BAUDRATE_9600;
            break;
        case 3:
            return UART_BAUDRATE_19200;
            break;
        case 4:
            return UART_BAUDRATE_38400;
            break;
        case 5:
            return UART_BAUDRATE_57600;
            break;
        case 6:
            return UART_BAUDRATE_115200;
            break;
        case 7:
            return UART_BAUDRATE_230400;
            break;
        case 8:
            return UART_BAUDRATE_460800;
            break;
        case 9:
            return UART_BAUDRATE_921600;
            break;
        case 10:
            return UART_BAUDRATE_2000000;
            break;
        case 11:
            return UART_BAUDRATE_3000000;
            break;
        case 12:
            return UART_BAUDRATE_4000000;
            break;
        case 13:
            return UART_BAUDRATE_5000000;
            break;
        case 14:
            return UART_BAUDRATE_6000000;
            break;
        default:
            break;
    }
    return UART_BAUDRATE_9600;
}

eUartErrorCodes_t UART1_INIT(){
    // Enable UART Clock
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);

    if(UART_CONFIG_READ_ENABLE_TRANSMIT_PIN(UART1_CONFIG)){
        if(UART_CONFIG_READ_SELECT_TRANSMIT_PIN_2(UART1_CONFIG) == 0){
            GPIO_CONFIG_PIN(GPIOB, PIN_6, GPIO_MODER_AF, GPIO_OTYPER_PP, GPIO_OSPEEDR_LOW, GPIO_PUPDR_NONE, GPIO_AF_0);
        } else {
            GPIO_CONFIG_PIN(GPIOA, PIN_9, GPIO_MODER_AF, GPIO_OTYPER_PP, GPIO_OSPEEDR_LOW, GPIO_PUPDR_NONE, GPIO_AF_1);
        }
        //Enable the Transceiver
        SET_BIT(USART1->CR1, USART_CR1_TE);
        /* Polling idle frame Transmission w/o clock */
        while ((USART1->ISR & USART_ISR_TC) != USART_ISR_TC);
        if(UART_CONFIG_READ_ENABLE_DMA(UART1_CONFIG)){ 
            SET_BIT(USART1->CR3, USART_CR3_DMAT);
            SET_BIT(USART1->ICR, USART_ICR_TCCF); /* Clear TC flag */
            SET_BIT(USART1->CR1, USART_CR1_TCIE); /* Enable TC interrupt */
        }
    }

    if(UART_CONFIG_READ_ENABLE_RECEIVER_PIN(UART1_CONFIG)){
        if(UART_CONFIG_READ_SELECT_RECEIVER_PIN_2(UART1_CONFIG) == 0){
            GPIO_CONFIG_PIN(GPIOB, PIN_7, GPIO_MODER_AF, GPIO_OTYPER_PP, GPIO_OSPEEDR_LOW, GPIO_PUPDR_NONE, GPIO_AF_0);
        } else {
            GPIO_CONFIG_PIN(GPIOA, PIN_10, GPIO_MODER_AF, GPIO_OTYPER_PP, GPIO_OSPEEDR_LOW, GPIO_PUPDR_NONE, GPIO_AF_1);
        }
        //Enable the Receiever
        SET_BIT(USART1->CR1, USART_CR1_RE);
        if(UART_CONFIG_READ_ENABLE_DMA(UART1_CONFIG)){
            SET_BIT(USART1->CR3, USART_CR3_DMAR);  
        }
    }

    if(UART_CONFIG_READ_ENABLE_CK_PIN(UART1_CONFIG)){
        GPIO_CONFIG_PIN(GPIOA, PIN_8, GPIO_MODER_AF, GPIO_OTYPER_PP, GPIO_OSPEEDR_LOW, GPIO_PUPDR_NONE, GPIO_AF_1);
        // CK pin
        SET_BIT(USART1->CR2, USART_CR2_CLKEN);
    }

    if(UART_CONFIG_READ_ENABLE_CTS_PIN(UART1_CONFIG)){
        GPIO_CONFIG_PIN(GPIOA, PIN_11, GPIO_MODER_AF, GPIO_OTYPER_PP, GPIO_OSPEEDR_LOW, GPIO_PUPDR_NONE, GPIO_AF_1);
        // CTS Pin
        SET_BIT(USART1->CR3, USART_CR3_CTSE);
    }

    if(UART_CONFIG_READ_ENABLE_RTS_PIN(UART1_CONFIG)){
        GPIO_CONFIG_PIN(GPIOA, PIN_12, GPIO_MODER_AF, GPIO_OTYPER_PP, GPIO_OSPEEDR_LOW, GPIO_PUPDR_NONE, GPIO_AF_1);
        // RTS Pin
        SET_BIT(USART1->CR3, USART_CR3_RTSE);
    }

    if(UART_CONFIG_READ_SWAP_PINS(UART1_CONFIG)){
        SET_BIT(USART1->CR2, USART_CR2_SWAP);
    }

    if(UART_CONFIG_READ_9_DATA_BITS(UART1_CONFIG)){
        SET_BIT(USART1->CR1, USART_CR1_M);
    }

    if(UART_CONFIG_READ_2_STOP_BITS(UART1_CONFIG)){
        SET_BIT(USART1->CR2, USART_CR2_STOP_1);
    }

    if(UART_CONFIG_READ_PARITY_ODD(UART1_CONFIG)){
        SET_BIT(USART1->CR1, USART_CR1_PS);
    }

    uint16_t usartdiv = CORE_CLOCK_HZ / UART_GET_BAUDRATE(UART_CONFIG_READ_SET_BAUDRATE(UART1_CONFIG));
    if(UART_CONFIG_READ_8_BIT_OVERSAMPLE(UART1_CONFIG) == 0){
        WRITE_REG(USART1->BRR, usartdiv);
    } else {
        SET_BIT(USART1->CR1, USART_CR1_OVER8);
        WRITE_REG(USART1->BRR, (uint16_t)(usartdiv & 0xFFF0) | (uint16_t)((usartdiv & 0x000F) >> 1));
    }

    //Enable the USART 1 Peripheral
    SET_BIT(USART1->CR1, USART_CR1_UE);

    if(UART_CONFIG_READ_ENABLE_TC_IE(UART1_CONFIG)){
        SET_BIT(USART1->CR1, USART_CR1_TCIE);
    }

    if(UART_CONFIG_READ_ENABLE_TXE_IE(UART1_CONFIG)){
        SET_BIT(USART1->CR1, USART_CR1_TXEIE);
    }

    if(UART_CONFIG_READ_ENABLE_RXNE_IE(UART1_CONFIG)){
        SET_BIT(USART1->CR1, USART_CR1_RXNEIE);  
    }

    if(UART_CONFIG_READ_ENABLE_NVIC_IE(UART1_CONFIG)){
        GPIO_ENABLE_INTERRUPT(USART1_IRQn, UART_CONFIG_READ_NVIC_PRIORITY(UART1_CONFIG));
    }

    return UART_OK;
}

eUartErrorCodes_t UART2_INIT(){
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN);

    if(UART_CONFIG_READ_ENABLE_TRANSMIT_PIN(UART2_CONFIG)){
        if(UART_CONFIG_READ_SELECT_TRANSMIT_PIN_2(UART2_CONFIG) == 0){
            GPIO_CONFIG_PIN(GPIOA, PIN_2, GPIO_MODER_AF, GPIO_OTYPER_PP, GPIO_OSPEEDR_LOW, GPIO_PUPDR_NONE, GPIO_AF_1);
        } else {
            GPIO_CONFIG_PIN(GPIOA, PIN_14, GPIO_MODER_AF, GPIO_OTYPER_PP, GPIO_OSPEEDR_LOW, GPIO_PUPDR_NONE, GPIO_AF_1);
        }
        //Enable the Transceiver
        SET_BIT(USART2->CR1, USART_CR1_TE);
        /* Polling idle frame Transmission w/o clock */
        while ((USART2->ISR & USART_ISR_TC) != USART_ISR_TC);
        if(UART_CONFIG_READ_ENABLE_DMA(UART2_CONFIG)){ 
            SET_BIT(USART2->CR3, USART_CR3_DMAT);
            SET_BIT(USART2->ICR, USART_ICR_TCCF); /* Clear TC flag */
            SET_BIT(USART2->CR1, USART_CR1_TCIE); /* Enable TC interrupt */
        }
    }

    if(UART_CONFIG_READ_ENABLE_RECEIVER_PIN(UART2_CONFIG)){
        if(UART_CONFIG_READ_SELECT_RECEIVER_PIN_2(UART2_CONFIG) == 0){
            GPIO_CONFIG_PIN(GPIOA, PIN_3, GPIO_MODER_AF, GPIO_OTYPER_PP, GPIO_OSPEEDR_LOW, GPIO_PUPDR_NONE, GPIO_AF_1);
        } else {
            GPIO_CONFIG_PIN(GPIOA, PIN_15, GPIO_MODER_AF, GPIO_OTYPER_PP, GPIO_OSPEEDR_LOW, GPIO_PUPDR_NONE, GPIO_AF_1);
        }
        //Enable the Receiever
        SET_BIT(USART2->CR1, USART_CR1_RE);
        if(UART_CONFIG_READ_ENABLE_DMA(UART2_CONFIG)){
            SET_BIT(USART2->CR3, USART_CR3_DMAR);  
        }
    }

    if(UART_CONFIG_READ_ENABLE_CK_PIN(UART2_CONFIG)){
        GPIO_CONFIG_PIN(GPIOA, PIN_4, GPIO_MODER_AF, GPIO_OTYPER_PP, GPIO_OSPEEDR_LOW, GPIO_PUPDR_NONE, GPIO_AF_1);
        // CK pin
        SET_BIT(USART2->CR2, USART_CR2_CLKEN);
    }

    if(UART_CONFIG_READ_ENABLE_CTS_PIN(UART2_CONFIG)){
        GPIO_CONFIG_PIN(GPIOA, PIN_0, GPIO_MODER_AF, GPIO_OTYPER_PP, GPIO_OSPEEDR_LOW, GPIO_PUPDR_NONE, GPIO_AF_1);
        // CTS Pin
        SET_BIT(USART2->CR3, USART_CR3_CTSE);
    }

    if(UART_CONFIG_READ_ENABLE_RTS_PIN(UART2_CONFIG)){
        GPIO_CONFIG_PIN(GPIOA, PIN_1, GPIO_MODER_AF, GPIO_OTYPER_PP, GPIO_OSPEEDR_LOW, GPIO_PUPDR_NONE, GPIO_AF_1);
        // RTS Pin
        SET_BIT(USART2->CR3, USART_CR3_RTSE);
    }

    if(UART_CONFIG_READ_SWAP_PINS(UART2_CONFIG)){
        SET_BIT(USART2->CR2, USART_CR2_SWAP);
    }

    if(UART_CONFIG_READ_9_DATA_BITS(UART2_CONFIG)){
        SET_BIT(USART2->CR1, USART_CR1_M);
    }

    if(UART_CONFIG_READ_2_STOP_BITS(UART2_CONFIG)){
        SET_BIT(USART2->CR2, USART_CR2_STOP_1);
    }

    if(UART_CONFIG_READ_PARITY_ODD(UART2_CONFIG)){
        SET_BIT(USART2->CR1, USART_CR1_PS);
    }

    uint16_t usartdiv = CORE_CLOCK_HZ / UART_GET_BAUDRATE(UART_CONFIG_READ_SET_BAUDRATE(UART2_CONFIG));
    if(UART_CONFIG_READ_8_BIT_OVERSAMPLE(UART2_CONFIG) == 0){
        WRITE_REG(USART2->BRR, usartdiv);
    } else {
        SET_BIT(USART2->CR1, USART_CR1_OVER8);
        WRITE_REG(USART2->BRR, (uint16_t)(usartdiv & 0xFFF0) | (uint16_t)((usartdiv & 0x000F) >> 1));
    }

    if(UART_CONFIG_READ_ENABLE_TC_IE(UART2_CONFIG)){
        SET_BIT(USART2->CR1, USART_CR1_TCIE);
    }

    if(UART_CONFIG_READ_ENABLE_TXE_IE(UART2_CONFIG)){
        SET_BIT(USART2->CR1, USART_CR1_TXEIE);
    }

    if(UART_CONFIG_READ_ENABLE_RXNE_IE(UART2_CONFIG)){
        SET_BIT(USART2->CR1, USART_CR1_RXNEIE);  
    }

    if(UART_CONFIG_READ_ENABLE_NVIC_IE(UART2_CONFIG)){
        GPIO_ENABLE_INTERRUPT(USART2_IRQn, UART_CONFIG_READ_NVIC_PRIORITY(UART2_CONFIG));
    }

    //Enable the USART 2 Peripheral
    SET_BIT(USART2->CR1, USART_CR1_UE);
    return UART_OK;
}

eUartErrorCodes_t UART1_DEINIT(){
    UART1_CONFIG = 0U;
    GPIO_DISABLE_INTERRUPT(USART1_IRQn);
    return UART_OK;
}

eUartErrorCodes_t UART2_DEINIT(){
    UART2_CONFIG = 0U;
    GPIO_DISABLE_INTERRUPT(USART2_IRQn);
    return UART_OK;
}

eUartErrorCodes_t USARTx_SEND_CHAR(USART_TypeDef * USARTx, const uint8_t c){
    USARTx->TDR = c;
    while((USARTx->ISR & USART_ISR_TC) != USART_ISR_TC);
    // Set break character
    SET_BIT(USARTx->RQR, USART_RQR_SBKRQ);
    return UART_OK;
}

