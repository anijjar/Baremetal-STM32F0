#ifndef _HC05_H
#define _HC05_H

#include "_uart.h"

typedef enum {
    HC05_OK = 0U,
    HC05_ERROR,
    HC05_ERROR_CODES_TOTAL,
} eHc05ErrorCodes_t;

typedef struct {
    eUsartPeriperal_t UART_Periph;
    sGPIO_t sTx; 
    sGPIO_t sRx;
    uint32_t baud;
} sHc_t;

eHc05ErrorCodes_t HC05_INIT(sHc_t * const sensor);

eHc05ErrorCodes_t HC05_SEND_MESSAGE(sHc_t * const sensor, char * message);


#endif