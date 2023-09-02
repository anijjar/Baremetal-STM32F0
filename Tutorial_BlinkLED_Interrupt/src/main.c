#include "main.h"
#include "exti.h"

typedef enum {
  LED_ON = 0U,
  LED_OFF,
} led_state_t;

#define LED_DEFAULT_STATE LED_OFF
volatile led_state_t blue_led_state = LED_DEFAULT_STATE;

void EXTI0_1_IRQHandler(void);

int main(void) {

  // Configure LD3 as default LED
  // Turn on the GPIOC Clock
  SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOCEN);
  // Set PC8 to output mode
  SET_BIT(GPIOC->MODER, GPIO_MODER_MODER9_0);
  SET_BIT(GPIOC->ODR, GPIO_ODR_9);

  // Configure Blue LED (PC8)
  // Turn on the GPIOC Clock
  SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOCEN);
  // Set PC8 to output mode
  SET_BIT(GPIOC->MODER, GPIO_MODER_MODER8_0);
  
  // Configure Button (PA0)
  // Turn on the GPIOA Clock
  SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOAEN);
  // Make the Button pull down by default
  SET_BIT(GPIOA->PUPDR, GPIO_PUPDR_PUPDR0_1);

  // Configure Push button Interrupt
  EXTI_GPIO_Init(PUSH_BUTTON_PIN, SYSCFG_EXTICR_GPIOA, EXTI_TRIGGER_RISING, EXTI0_1_IRQn, NVIC_PRIORITY_3);

  // This causes bouncing
  // while(1) {
  //   if(blue_led_state == LED_ON){
  //     SET_BIT(GPIOC->ODR, GPIO_ODR_8);
  //   } else {
  //     CLEAR_BIT(GPIOC->ODR, GPIO_ODR_8);
  //   }
  // }
  for(;;);
  return 0;
}

// This handler causes bounces
// void EXTI0_1_IRQHandler(void) {
//   if(EXTI->PR & (1 << PUSH_BUTTON_PIN)) {
//     // Clear Status Flag
//     SET_BIT(EXTI->PR, EXTI_PR_PR0);
//     // Toggle Blue LED
//     blue_led_state = !blue_led_state;
//   }
// }

// Toggling this way reduces the bounce
void EXTI0_1_IRQHandler(void){
  if(EXTI->PR & (1 << PUSH_BUTTON_PIN)) {
    // Toggle Blue LED
    blue_led_state = !blue_led_state;
    // an improvement would be to set the bit using shifts,
    // rather then using branching instructions.
    // if(blue_led_state){
    //   SET_BIT(GPIOC->ODR, GPIO_ODR_8);
    // } else {
    //   CLEAR_BIT(GPIOC->ODR, GPIO_ODR_8);
    // }
    GPIOC->ODR ^= (1 << BLUE_LED_PIN);
    // Clear Status Flag
    SET_BIT(EXTI->PR, EXTI_PR_PR0);
  }
}