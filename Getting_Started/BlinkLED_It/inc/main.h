#ifndef _MAIN_H
#define _MAIN_H


// #include <assert.h>
#include <stdint.h>
#include "stm32f0xx.h"

#define PUSH_BUTTON_PIN 0 //PA0
#define BLUE_LED_PIN 8 //PC8
#define GREEN_LED_PIN 9 //PC9

#define TOGGLE_BIT(REG, BIT)   ((REG) ^= (BIT))

#endif