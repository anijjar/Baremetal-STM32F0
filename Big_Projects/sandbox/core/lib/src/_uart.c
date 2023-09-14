#include "_uart.h"

const sGPIO_t gUsart1_pins[TOTAL_USART_PINS] = {
	{PIN_6, GPIOB},
	{PIN_9, GPIOA},
	{PIN_7, GPIOB},
	{PIN_10, GPIOA},
	{PIN_8, GPIOA},
	{PIN_11, GPIOA},
	{PIN_12, GPIOA},
};

const sGPIO_t gUsart2_pins[TOTAL_USART_PINS] = {
	{PIN_2, GPIOA},
	{PIN_14, GPIOA},
	{PIN_3, GPIOA},
	{PIN_15, GPIOA},
	{PIN_4, GPIOA},
	{PIN_0, GPIOA},
	{PIN_1, GPIOA}
};


void USARTx_INIT(eUsartPeriperal_t periph, sGPIO_t sTx, sGPIO_t sRx, uint32_t baud) {
    uint16_t usartdiv = 0;
    if(periph == USART1_PERIPHERAL){

        // Turn on GPIO Clock
        if(sTx.GPIOx == GPIOB || sRx.GPIOx == GPIOB){
            SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOBEN);
        }
        if(sTx.GPIOx == GPIOA || sRx.GPIOx == GPIOA){
            SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOAEN);
            // Also configure alternate function selection for GPIOA
            SET_BIT(sTx.GPIOx->AFR[sTx.pin / 8], 1 << (4 * (sTx.pin % 8)));
            SET_BIT(sRx.GPIOx->AFR[sRx.pin / 8], 1 << (4 * (sRx.pin % 8)));
        }

        // Configure GPIO as AF
        SET_BIT(sTx.GPIOx->MODER, 2 << (2 * sTx.pin));
        SET_BIT(sRx.GPIOx->MODER, 2 << (2 * sRx.pin));

        // Optional: Enable other pins
        #if USART_1_EXTRA_PINS_EN
            // Turn on the clock
            SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOAEN);
            // CK pin
            SET_BIT(gUsart1_pins[CK_PIN].GPIOx->MODER, GPIO_MODER_MODER8_1);
            SET_BIT(USART1->CR2, USART_CR2_CLKEN);
            // CTS Pin
            SET_BIT(gUsart1_pins[CTS_PIN].GPIOx->MODER, GPIO_MODER_MODER11_1);
            SET_BIT(USART1->CR3, USART_CR3_CTSE);
            // RTS Pin
            SET_BIT(gUsart1_pins[RTS_PIN].GPIOx->MODER, GPIO_MODER_MODER12_1);
            SET_BIT(USART1->CR3, USART_CR3_RTSE);
        #endif

        //Turn on USART 1 Clock
        SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);
        
        //Swap the transmit and receive pins 
        #ifdef USART_1_PIN_SWAP
            SET_BIT(USART1->CR2, USART_CR2_SWAP);
        #endif
        
        //Set the Parity
        #ifdef USART_1_PARITY_ODD
            SET_BIT(USART1->CR1, USART_CR1_PS);
        #endif

        //Set the oversampling and baudrate
        usartdiv =  CORE_CLOCK_HZ / baud;
        #ifdef USART_1_OVER8
            SET_BIT(USART1->CR1, USART_CR1_OVER8);
            WRITE_REG(USART1->BRR, (uint16_t)(usartdiv & 0xFFF0) | (uint16_t)((usartdiv & 0x000F) >> 1));
        #else
            WRITE_REG(USART1->BRR, usartdiv);
        #endif

        //Enable the USART 1 Peripheral, Receiver, and Transceiver
        SET_BIT(USART1->CR1, USART_CR1_UE | USART_CR1_RE | USART_CR1_TE);

        //Enable the interrupts
        #ifdef USART_1_TC_IT // Transmission Complete
            SET_BIT(USART1->CR1, USART_CR1_TCIE);
        #endif
        #ifdef USART_1_TXE_IT // Transfer Buffer not empty
            SET_BIT(USART1->CR1, USART_CR1_TXEIE);
        #endif
        #ifdef USART_1_RXNE_IT // Receive Buffer not empty
            SET_BIT(USART1->CR1, USART_CR1_RXNEIE);
        #endif

        //Enable DMA
        #ifdef USART_1_DMA_RX
            SET_BIT(USART1->CR3, USART_CR3_DMAR);  
        #endif
        #ifdef USART_1_DMA_TX
            SET_BIT(USART1->CR3, USART_CR3_DMAT);
            USART1->ICR |= USART_ICR_TCCF; /* Clear TC flag */
            USART1->CR1 |= USART_CR1_TCIE; /* Enable TC interrupt */
        #endif

        #ifdef USART_1_IT
            NVIC_ENABLE_INTERRUPT(USART1_IRQn, USART_1_PRIORITY);
        #endif
    } else if(periph == USART2_PERIPHERAL){

        // Turn on GPIO Clock
        SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOAEN);
        // Also configure alternate function selection for GPIOA
        SET_BIT(sTx.GPIOx->AFR[sTx.pin / 8], 1 << (4 * (sTx.pin % 8)));
        SET_BIT(sRx.GPIOx->AFR[sRx.pin / 8], 1 << (4 * (sRx.pin % 8)));

        // Configure GPIO as AF
        SET_BIT(sTx.GPIOx->MODER, 2 << (2 * sTx.pin));
        SET_BIT(sRx.GPIOx->MODER, 2 << (2 * sRx.pin));

        // Optional: Enable other pins
        #if USART_2_EXTRA_PINS_EN
            // Turn on the clock
            SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOAEN);
            // CK pin
            SET_BIT(gUsart2_pins[CK_PIN].GPIOx->MODER, GPIO_MODER_MODER8_1);
            SET_BIT(USART2->CR2, USART_CR2_CLKEN);
            // CTS Pin
            SET_BIT(gUsart2_pins[CTS_PIN].GPIOx->MODER, GPIO_MODER_MODER11_1);
            SET_BIT(USART2->CR3, USART_CR3_CTSE);
            // RTS Pin
            SET_BIT(gUsart2_pins[RTS_PIN].GPIOx->MODER, GPIO_MODER_MODER12_1);
            SET_BIT(USART2->CR3, USART_CR3_RTSE);
        #endif

        //Turn on USART 2 Clock
        SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN);
        
        //Swap the transmit and receive pins 
        #ifdef USART_2_PIN_SWAP
            SET_BIT(USART2->CR2, USART_CR2_SWAP);
        #endif
        
        //Set the Parity
        #ifdef USART_2_PARITY_ODD
            SET_BIT(USART2->CR1, USART_CR1_PS);
        #endif

        //Set the oversampling and baudrate
        usartdiv =  CORE_CLOCK_HZ / baud;
        #ifdef USART_2_OVER8
            SET_BIT(USART2->CR1, USART_CR1_OVER8);
            WRITE_REG(USART2->BRR, (uint16_t)(usartdiv & 0xFFF0) | (uint16_t)((usartdiv & 0x000F) >> 1));
        #else
            WRITE_REG(USART2->BRR, usartdiv);
        #endif

        //Enable the USART 1 Peripheral, Receiver, and Transceiver
        SET_BIT(USART2->CR1, USART_CR1_UE | USART_CR1_RE | USART_CR1_TE);

        //Enable the interrupts
        #ifdef USART_2_TC_IT // Transmission Complete
            SET_BIT(USART2->CR1, USART_CR1_TCIE);
        #endif
        #ifdef USART_2_TXE_IT // Transfer Buffer not empty
            SET_BIT(USART2->CR1, USART_CR1_TXEIE);
        #endif
        #ifdef USART_2_RXNE_IT // Receive Buffer not empty
            SET_BIT(USART2->CR1, USART_CR1_RXNEIE);
        #endif

        //Enable DMA (Not Implemented)
        #ifdef USART_2_DMA_RX
            SET_BIT(USART2->CR3, USART_CR3_DMAR);  
        #endif
        #ifdef USART_2_DMA_TX
            SET_BIT(USART1->CR3, USART_CR3_DMAT);
            USART2->ICR |= USART_ICR_TCCF; /* Clear TC flag */
            USART2->CR1 |= USART_CR1_TCIE; /* Enable TC interrupt */
        #endif

        #ifdef USART_2_IT
            NVIC_ENABLE_INTERRUPT(USART2_IRQn, USART_2_PRIORITY);
        #endif
    }
}

sGPIO_t GET_USARTx_PIN(eUsartPeriperal_t periph, eUsartPins_t pin){
    return (periph == USART1_PERIPHERAL) ? gUsart1_pins[pin] : gUsart2_pins[pin];
}

// For one-off messages not using the circular buffer
// Poor performance because it uses CPU and requires to wait
// For best performance, use the buffer and let the DMA do the work
int USARTx_SEND_MESSAGE(USART_TypeDef * USARTx, uint8_t * message, int len){
    for(int i = 0; i < len; i++){
        USARTx_SEND_CHAR(USARTx, message[i]);
        while((USARTx->ISR & USART_ISR_TXE) != USART_ISR_TXE);
    }
    return 0;
}

void USARTx_SEND_CHAR(USART_TypeDef * USARTx, const uint8_t c){
    USARTx->TDR = c;
}

uint8_t USARTx_RECEIVE_CHAR(USART_TypeDef * USARTx){
    return (uint8_t)USARTx->RDR;
}