#include "hc05.h"

eHc05ErrorCodes_t HC05_INIT(sHc_t * const sensor){
    // Initialize a UART peripheral
    USARTx_INIT(sensor->UART_Periph, 
        sensor->sTx, 
        sensor->sRx, 
        sensor->baud
    );

    return HC05_OK;
} 

eHc05ErrorCodes_t HC05_SEND_MESSAGE(sHc_t * const sensor, char * message){
    if(sensor->UART_Periph == USART1_PERIPHERAL){
        return (eHc05ErrorCodes_t)USARTx_SEND_MESSAGE(USART1, message, sizeof(message)/sizeof(message[0]));
    } else if(sensor->UART_Periph == USART2_PERIPHERAL){
        return (eHc05ErrorCodes_t)USARTx_SEND_MESSAGE(USART2, message, sizeof(message)/sizeof(message[0]));
    }
}