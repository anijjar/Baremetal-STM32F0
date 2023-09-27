#include "common.h"
#include "memory_map.h"
#include "register_map.h"

#define PUSH_BUTTON_PIN (0)
#define PUSH_BUTTON_PRIORITY (1) // higher [0,1,2,3] lower

uint8_t key = 0U;

void PushButton_Init(void){
    // Turn on the GPIOA Clock
    SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOAEN);

    // Make the Button pull down by default
    SET_BIT(GPIOA->PUPDR, GPIO_PUPDR_PUPDR0_1);

    // Turn on the Syscfg clock
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGCOMPEN);

    // Setup EXTI Line as an interrupt (bits 16:31 are for other functions)
    SET_BIT(EXTI->IMR, 1 << PUSH_BUTTON_PIN);

    // Trigger on rising edge
    SET_BIT(EXTI->RTSR, 1 << PUSH_BUTTON_PIN);

    // Set interrupt priority (0 is highest, 3 is lowest)
    SET_BIT(NVIC->IP[0U], PUSH_BUTTON_PRIORITY << 6);

    // Enable Interrupt
    SET_BIT(NVIC->ISER[0U], 1 << (uint32_t)EXTI0_1_IRQn);
}

void PushButton_Deinit() {
    // Turn everything off
    CLEAR_BIT(RCC->AHBENR, RCC_AHBENR_GPIOAEN);
    CLEAR_BIT(GPIOA->PUPDR, GPIO_PUPDR_PUPDR0_1);
    CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGCOMPEN);
    CLEAR_BIT(EXTI->IMR, 1 << PUSH_BUTTON_PIN);
    CLEAR_BIT(EXTI->RTSR, 1 << PUSH_BUTTON_PIN);
    CLEAR_BIT(NVIC->IP[0U], PUSH_BUTTON_PRIORITY << 6);
    CLEAR_BIT(NVIC->ISER[0U], 1 << (uint32_t)EXTI0_1_IRQn);
}

void EXTI0_1_IRQHandler(void){
  if(EXTI->PR & (1 << PUSH_BUTTON_PIN)) {
    key = 1U;
    // Clear Status Flag
    SET_BIT(EXTI->PR, EXTI_PR_PR0);
  }
}

void start_app(uint32_t pc, uint32_t sp) __attribute__((naked)) {
    __asm("           \n\
          msr msp, r1 /* load r1 into MSP */\n\
          bx r0       /* branch to the address at r0 */\n\
    ");
}

int bootloader(void){
    key = 0U;
    uint32_t *app_code = (uint32_t *)__app_start__;
    uint32_t app_sp = app_code[0];
    uint32_t app_start = app_code[1];
    PushButton_Init();

    for(;;) {
        if(key) {
            key = 0U;
            PushButton_Deinit();
            start_app(app_start, app_sp);
        }
    }
    return 0;
}
