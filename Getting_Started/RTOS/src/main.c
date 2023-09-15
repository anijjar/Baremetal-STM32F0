#include "main.h"
#include "onboardPeriph.h"

uint32_t led_blue_delay = 0U;
uint32_t led_green_delay = 0U;

void init_hardware(){
  onboard_led_blue_init();
  onboard_led_green_init();
  // led_off(ONBOARD_BLUE_LED_PIN, ONBOARD_BLUE_LED_PORT);
}

static void task_led(void *args);

/**
 * RTOS Example:
 * This example will use RTOS tasks to toggle the two LEDs by
 * sampling an ADC input.
 * 
*/
int main(void) {
  // _SYSTEM_CORE_CLOCK_SETUP(); // Setup clock frequency in main.h
  init_hardware();
  led_blue_delay = 3;
  led_green_delay = led_blue_delay * 1.5;

  xTaskCreate(task_led,
    "LED_BLUE",
    128,
    (void*)&led_blue_delay, 
    configMAX_PRIORITIES-1, 
    NULL
  );
  
  xTaskCreate(task_led,
    "LED_GREEN",
    128,
    (void*)&led_blue_delay, 
    configMAX_PRIORITIES-1, 
    NULL
  );

  // Start the scheduler.
  vTaskStartScheduler();

  // Should never reach here
  for(;;);
  return 0;
}

static void task_led(void *args){
  int delay_ms = *(int*)args;

  for(;;){
    // Toggle the LED
    led_toggle(ONBOARD_BLUE_LED_PIN, ONBOARD_BLUE_LED_PORT);
    vTaskDelay(pdMS_TO_TICKS(delay_ms));
    
  }
}


void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If the application makes use of the
	vTaskDelete() API function (as this demo application does) then it is also
	important that vApplicationIdleHook() is permitted to return to its calling
	function, because it is the responsibility of the idle task to clean up
	memory allocated by the kernel to any task that has since been deleted. */
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This function will be called by each tick interrupt if
	configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
	added here, but the tick hook is called from an interrupt context, so
	code must not attempt to block, and only the interrupt safe FreeRTOS API
	functions can be used (those that end in FromISR()). */
}
/*-----------------------------------------------------------*/
