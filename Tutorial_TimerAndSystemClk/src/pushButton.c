
#include "onboardPeriph.h"

void onboard_pushButton_init() {
    // Turn on the GPIOA Clock
    SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOAEN);
    // Make the Button pull down by default
    SET_BIT(GPIOA->PUPDR, GPIO_PUPDR_PUPDR0_1);
}

void onboard_pushbutton_interrupt(FunctionalState state) {
    if(state == ENABLE){
        EXTI_GPIO_Init(PUSH_BUTTON_PIN, SYSCFG_EXTICR_GPIOA, EXTI_TRIGGER_RISING, EXTI0_1_IRQn, NVIC_PRIORITY_3);
    } else {
        // TODO: Create exti function to disable interrupt
    }
}

// Uncomment this to get 
// Toggling this way reduces the bounce
// void EXTI0_1_IRQHandler(void){
//   if(EXTI->PR & (1 << PUSH_BUTTON_PIN)) {
       // Add code here
//     // Clear Status Flag
//     SET_BIT(EXTI->PR, EXTI_PR_PR0);
//   }
// }