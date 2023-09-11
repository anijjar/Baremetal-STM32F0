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



void TIMx_Init(TIM_TypeDef * TIMx, uint16_t cr1, NVIC_Priority_t priority);

void Counter_Init(TIM_TypeDef * TIMx, uint16_t arr, uint16_t psc);

void TIMx_Enable(TIM_TypeDef * TIMx);

void TIMx_Disable(TIM_TypeDef * TIMx);

#endif