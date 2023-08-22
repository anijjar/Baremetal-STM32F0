/* Main program. */
#include "main.h"

void SimpleIncrementExample(){
  uint32_t var1 = 2;
  int val = 0;
  while (1) {
    val += var1;
  }
}

int main(void) {
  
  // Works
  // SimpleIncrementExample();

  // Turn on the GPIOC Clock
  SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOCEN);
  // Set PC8 to output mode
  SET_BIT(GPIOC->MODER, GPIO_MODER_MODER8_0);
  // Set PC8 to High using ODR register;
  SET_BIT(GPIOC->ODR, GPIO_ODR_8);

  for(;;);
  return 0;
}