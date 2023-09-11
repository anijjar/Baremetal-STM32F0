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

uint8_t gRx_array_1[USART_1_BUFFER_SIZE];
uint8_t gRx_array_2[USART_1_BUFFER_SIZE];

uint8_t gTx_array_1[USART_2_BUFFER_SIZE];
uint8_t gTx_array_2[USART_2_BUFFER_SIZE];

sCircBuff8bit_t gbuff_rx1;
sCircBuff8bit_t gbuff_rx2;
sCircBuff8bit_t gbuff_tx1;
sCircBuff8bit_t gbuff_tx2;

sGPIO_t GET_USART1_PIN(eUsartPins_t pin){
    return gUsart1_pins[pin];
}

void USART1_INIT(sGPIO_t sTx, sGPIO_t sRx) {

    // Initialize the Buffers
    Init_8BitCircularBuffer(&gbuff_rx1, gRx_array_1, USART_1_BUFFER_SIZE);
    Init_8BitCircularBuffer(&gbuff_tx1, gTx_array_1, USART_1_BUFFER_SIZE);

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
    uint16_t usartdiv =  CORE_CLOCK_HZ / USART_1_BAUD;
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

    //Enable DMA (Not Implemented)
    #ifdef USART_1_DMA_RX
        // SET_BIT(USART1->CR3, USART_CR3_DMAR);
    #endif
    #ifdef USART_1_DMA_RX
        // SET_BIT(USART1->CR3, USART_CR3_DMAT);
    #endif

    NVIC_ENABLE_INTERRUPT(USART1_IRQn, USART_1_PRIORITY);
}


// void _Send_Char(uint8_t c){
//     USART1->TDR = c;
// }