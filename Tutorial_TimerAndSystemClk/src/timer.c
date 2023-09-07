
#include "timer.h"

void TIMx_Init(TIM_TypeDef * TIMx, uint16_t cr1, NVIC_Priority_t priority) {
    // Ensure the timer is turned off
    TIMx_Disable(TIMx);
    // Turn on the RCC clock and setup nvic
    if(TIMx == TIM3){
        SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);
        NVIC_Enable_Interrupt(TIM3_IRQn, priority);
    } else if(TIMx == TIM1) {
        SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);
        NVIC_Enable_Interrupt(TIM1_CC_IRQn, priority);
    } else if(TIMx == TIM6) {
        SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM6EN);
        NVIC_Enable_Interrupt(TIM6_IRQn, priority);
    } else if(TIMx == TIM14) {
        SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM14EN);
        NVIC_Enable_Interrupt(TIM14_IRQn, priority);
    } else if(TIMx == TIM15) {
        SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM15EN);
        NVIC_Enable_Interrupt(TIM15_IRQn, priority);
    } else if(TIMx == TIM16) {
        SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM16EN);
        NVIC_Enable_Interrupt(TIM16_IRQn, priority);
    } else if(TIMx == TIM17) {
        SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM17EN);
        NVIC_Enable_Interrupt(TIM17_IRQn, priority);
    }
    
    // One Pulse Mode?
    SET_BIT(TIMx->CR1, (cr1 & TIM_CR1_OPM) << TIM_CR1_OPM_Pos);

    // Direction
    SET_BIT(TIMx->CR1, (cr1 & TIM_CR1_DIR) << TIM_CR1_DIR_Pos);

    //Center-Aligned Mode Selection
    SET_BIT(TIMx->CR1, (cr1 & TIM_CR1_CMS) << TIM_CR1_CMS_Pos);


    // Reset the timer and apply the new settings
    SET_BIT(TIMx->EGR, TIM_EGR_UG);

    // Enable Hardware Interrupt
    SET_BIT(TIMx->DIER, TIM_DIER_UIE);

    TIMx_Enable(TIMx);

}


// Initializes timer to work as a counter
void Counter_Init(TIM_TypeDef * TIMx, uint16_t arr, uint16_t psc){
    // Ensure the timer is turned off
    TIMx_Disable(TIMx);
    // Set the Timer Prescaler/autoreload register
    SET_BIT(TIMx->PSC, psc-1);
    SET_BIT(TIMx->ARR, arr);
    // Reset the timer and apply the new settings
    SET_BIT(TIMx->EGR, TIM_EGR_UG);
    TIMx_Enable(TIMx);
}

void TIMx_Enable(TIM_TypeDef * TIMx){
    SET_BIT(TIMx->CR1, TIM_CR1_CEN);
}

void TIMx_Disable(TIM_TypeDef * TIMx){
    CLEAR_BIT(TIMx->CR1, TIM_CR1_CEN);
}

// void TIM3_IRQHandler(){
//     if(TIM3->SR & TIM_SR_UIF){
//     }
// }