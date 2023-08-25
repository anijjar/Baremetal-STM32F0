#ifndef _BABA_EXTI_H
#define _BABA_EXTI_H

#include "baba.h"

typedef enum {
    Handler_Pin_P0 = 0U,
    Handler_Pin_P1,
    Handler_Pin_P2,
    Handler_Pin_P3,
    Handler_Pin_P4,
    Handler_Pin_P5,
    Handler_Pin_P6,
    Handler_Pin_P7,
    Handler_Pin_P8,
    Handler_Pin_P9,
    Handler_Pin_P10,
    Handler_Pin_P11,
    Handler_Pin_P12,
    Handler_Pin_P13,
    Handler_Pin_P14,
    Handler_Pin_P15,
} Handler_Pin_t;

typedef enum {
    Handler_Port_A = 0U,
    Handler_Port_B,
    Handler_Port_C,
    Handler_Port_D,
    Handler_Port_Reserved,
    Handler_Port_F,
} Handler_Port_t;

typedef enum {
    Handler_Trigger_Rising_Off = 0U,
    Handler_Trigger_Rising_On,
} Handler_Trigger_Rising_t;

typedef enum {
    Handler_Trigger_Falling_Off = 0U,
    Handler_Trigger_Falling_On,
} Handler_Trigger_Falling_t;

// Rather than by pin, rely on the macros in stm32f0.h
void EXTI_GPIO_Init(Handler_Pin_t p, Handler_Port_t x, Handler_Trigger_Rising_t r, Handler_Trigger_Falling_t f, IRQn_Type IRQn);


#endif