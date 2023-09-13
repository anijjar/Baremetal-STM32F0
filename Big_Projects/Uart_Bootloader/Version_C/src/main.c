#include "main.h"
#include "onboardPeriph.h"

void init_hardware(){
  onboard_led_blue_init();
  onboard_led_green_init();
  led_off(ONBOARD_BLUE_LED_PIN, ONBOARD_BLUE_LED_PORT);
}

int main(void) {
  // _SYSTEM_CORE_CLOCK_SETUP(); // Setup clock frequency in main.h
  init_hardware();

  for(;;);
  return 0;
}