#ifndef _TIMER_H
#define _TIMER_H

//STM32F03 has 5 general purpose, 2 basic, and one advanced

// Input Capture -- sample every period
// Output Capture -- trigger outut every period
// PWM generation -- generate a PWM waveform
// One-Pulse Mode Output

#include "main.h"
#include "_exti.h"
#include "_rcc.h"

typedef enum {
    TIMER_ONE_PULSE_MODE_OFF = 0U,
    TIMER_ONE_PULSE_MODE_ON,
} timer_one_pulse_mode_t;

typedef enum {
    TIMER_COUNT_UP = 0U,
    TIMER_COUNT_DOWN,
} timer_count_type_t;

typedef struct {
    TIM_TypeDef * TIMx;
    uint32_t rcc; // RCC->APB1ENR or RCC->APB2ENR
    uint32_t clk_bit; // RCC_APB1ENR_TIM3EN
    IRQn_Type IRQn;
    NVIC_Priority_t nvic_priority; // _exti.h
    timer_count_type_t count_mode;
    timer_one_pulse_mode_t one_pulse_mode;
} sTIMx_t;

// User pointers to populate these variables
// We dont need to add volatile because we assign pointers to them
// in compile time
sTIMx_t timer_1;
sTIMx_t timer_3;
sTIMx_t timer_14;
sTIMx_t timer_15;
sTIMx_t timer_16;
sTIMx_t timer_17;
sTIMx_t timer_6;
sTIMx_t timer_7;

void TIMx_Counter_Init(sTIMx_t * obj, uint16_t arr, uint16_t psc);

void TIMx_Enable(sTIMx_t * obj);

void TIMx_Disable(sTIMx_t * obj);

#endif