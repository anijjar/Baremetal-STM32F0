#include "common.h"
#include "memory_map.h"
#include "register_map.h"

#define GREEN_LED_PIN (9)

void LED_Init(void);
void LED_On(uint8_t led);

int main(void){

    LED_Init();
    LED_On(GREEN_LED_PIN);
    for(;;);
    return 0;
}

void LED_Init(void){
    SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOCEN);
    // Green LED
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODER9_0);
}
void LED_On(uint8_t led){
    SET_BIT(GPIOC->ODR, 1 << led);
}