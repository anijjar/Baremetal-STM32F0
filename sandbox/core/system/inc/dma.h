#ifndef DMA_H
#define DMA_H

/*

DMA Driver

*/

#include "common.h"
#include "gpio.h"

typedef enum {
    DMA_OK = 0U,
    DMA_ERROR
} eDmaErrorCodes_t; 

eDmaErrorCodes_t DMA_INIT();

#endif