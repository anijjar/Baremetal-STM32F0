
#include "timer.h"

// Initializes timer to work as a counter
void TIMx_Counter_Init(sTIMx_t * obj, uint16_t arr, uint16_t psc){
    // Ensure the timer is turned off
    TIMx_Disable(obj);

    // Turn on the RCC clock
    SET_BIT(obj->rcc, obj->clk_bit);

    // Set the count direction
    SET_BIT(obj->TIMx->CR1, (obj->count_mode << 4));

    // One Pulse Mode?
    SET_BIT(obj->TIMx->CR1, (obj->one_pulse_mode << 3));

    // Set the Timer Prescaler/autoreload register
    SET_BIT(obj->TIMx->PSC, psc-1);
    SET_BIT(obj->TIMx->ARR, arr);

    // Reset the timer and apply the new settings
    SET_BIT(obj->TIMx->EGR, TIM_EGR_UG);

    // Enable Hardware Interrupt
    SET_BIT(obj->TIMx->DIER, TIM_DIER_UIE);

    TIMx_Enable(obj);

    NVIC_Enable_Interrupt(obj->IRQn, obj->nvic_priority);
}

void TIMx_Enable(sTIMx_t * obj){
    SET_BIT(obj->TIMx->CR1, TIM_CR1_CEN);
}

void TIMx_Disable(sTIMx_t * obj){
    CLEAR_BIT(obj->TIMx->CR1, TIM_CR1_CEN);
}

// void TIM3_IRQHandler(){
//     if(TIM3->SR & TIM_SR_UIF){

//     }
// }