/* Main program. */
#include "main.h"

void SimpleIncrementExample(){
  uint32_t var1 = 2;
  int val = 0;
  while (1) {
    val += var1;
  }
}

void SoftwareDebounce(){
  // Use a hardware timer to provide 20ms delay.  
}


/*
  @brief Pushing button will turn on the LED. Poorly albeit.

  TODO: add software debounce for 40ms. 

*/
void PushButtonExample(){

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

  // SET_BIT(GPIOC->ODR, GPIO_ODR_8);

  while(1) {
    // If push button is pressed, toggle LED 
    TOGGLE_BIT(GPIOC->ODR, READ_BIT(GPIOA->IDR, GPIO_IDR_0) << 8);
  }

}


int main(void) {
  
  // Works
  // SimpleIncrementExample();
  PushButtonExample();
 

  for(;;);
  return 0;
}