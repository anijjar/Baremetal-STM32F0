/*

Define the interrupt table for the STM32F03xx Chipset

 */

 /* Define chip attributes and assembly language */
.syntax unified
.cpu cortex-m0
.fpu softvfp
.thumb

// Global memory locations
.global vtable
.global default_interrupt_handler

// Vector Table
.type vtable, %object
.section .vector_table, "a", %progbits
vtable:
  // 0-15
  .word  _estack
  .word  Reset_Handler
  .word  NMI_Handler
  .word  HardFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  0
  .word  0
  .word  PendSV_Handler
  .word  SysTick_Handler
  // 16-31
  .word  WWDG_IRQHandler                   /* Window WatchDog              */
  .word  0                                 /* Reserved                     */
  .word  RTC_IRQHandler                    /* RTC through the EXTI line    */
  .word  FLASH_IRQHandler                  /* FLASH                        */
  .word  RCC_IRQHandler                    /* RCC                          */
  .word  EXTI0_1_IRQHandler                /* EXTI Line 0 and 1            */
  .word  EXTI2_3_IRQHandler                /* EXTI Line 2 and 3            */
  .word  EXTI4_15_IRQHandler               /* EXTI Line 4 to 15            */
  .word  0                                 /* Reserved                     */
  .word  DMA1_Channel1_IRQHandler          /* DMA1 Channel 1               */
  .word  DMA1_Channel2_3_IRQHandler        /* DMA1 Channel 2 and Channel 3 */
  .word  DMA1_Channel4_5_IRQHandler        /* DMA1 Channel 4 and Channel 5 */
  .word  ADC1_IRQHandler                   /* ADC1                         */
  .word  TIM1_BRK_UP_TRG_COM_IRQHandler    /* TIM1 Break, Update, Trigger and Commutation */
  .word  TIM1_CC_IRQHandler                /* TIM1 Capture Compare         */
  // 32-47
  .word  0                                 /* Reserved                     */
  .word  TIM3_IRQHandler                   /* TIM3                         */
  .word  TIM6_IRQHandler                   /* TIM6                         */
  .word  0                                 /* Reserved                     */
  .word  TIM14_IRQHandler                  /* TIM14                        */
  .word  TIM15_IRQHandler                  /* TIM15                        */
  .word  TIM16_IRQHandler                  /* TIM16                        */
  .word  TIM17_IRQHandler                  /* TIM17                        */
  .word  I2C1_IRQHandler                   /* I2C1                         */
  .word  I2C2_IRQHandler                   /* I2C2                         */
  .word  SPI1_IRQHandler                   /* SPI1                         */
  .word  SPI2_IRQHandler                   /* SPI2                         */
  .word  USART1_IRQHandler                 /* USART1                       */
  .word  USART2_IRQHandler                 /* USART2                       */
  .word  0                                 /* Reserved                     */
  .word  0                                 /* Reserved                     */
  // 48
  .word  0                                 /* Reserved                     */
  
  // Setup weak aliases for each handler for the default handler to call.  The are overwritten automatically since they are weak. 
  .weak      NMI_Handler
  .thumb_set NMI_Handler,default_interrupt_handler

  .weak      HardFault_Handler
  .thumb_set HardFault_Handler,default_interrupt_handler

  .weak      SVC_Handler
  .thumb_set SVC_Handler,default_interrupt_handler

  .weak      PendSV_Handler
  .thumb_set PendSV_Handler,default_interrupt_handler

  .weak      SysTick_Handler
  .thumb_set SysTick_Handler,default_interrupt_handler

  .weak      WWDG_IRQHandler
  .thumb_set WWDG_IRQHandler,default_interrupt_handler

  .weak      RTC_IRQHandler
  .thumb_set RTC_IRQHandler,default_interrupt_handler

  .weak      FLASH_IRQHandler
  .thumb_set FLASH_IRQHandler,default_interrupt_handler

  .weak      RCC_IRQHandler
  .thumb_set RCC_IRQHandler,default_interrupt_handler

  .weak      EXTI0_1_IRQHandler
  .thumb_set EXTI0_1_IRQHandler,default_interrupt_handler

  .weak      EXTI2_3_IRQHandler
  .thumb_set EXTI2_3_IRQHandler,default_interrupt_handler

  .weak      EXTI4_15_IRQHandler
  .thumb_set EXTI4_15_IRQHandler,default_interrupt_handler

  .weak      DMA1_Channel1_IRQHandler
  .thumb_set DMA1_Channel1_IRQHandler,default_interrupt_handler

  .weak      DMA1_Channel2_3_IRQHandler
  .thumb_set DMA1_Channel2_3_IRQHandler,default_interrupt_handler

  .weak      DMA1_Channel4_5_IRQHandler
  .thumb_set DMA1_Channel4_5_IRQHandler,default_interrupt_handler

  .weak      ADC1_IRQHandler
  .thumb_set ADC1_IRQHandler,default_interrupt_handler

  .weak      TIM1_BRK_UP_TRG_COM_IRQHandler
  .thumb_set TIM1_BRK_UP_TRG_COM_IRQHandler,default_interrupt_handler

  .weak      TIM1_CC_IRQHandler
  .thumb_set TIM1_CC_IRQHandler,default_interrupt_handler

  .weak      TIM3_IRQHandler
  .thumb_set TIM3_IRQHandler,default_interrupt_handler

  .weak      TIM6_IRQHandler
  .thumb_set TIM6_IRQHandler,default_interrupt_handler

  .weak      TIM14_IRQHandler
  .thumb_set TIM14_IRQHandler,default_interrupt_handler

  .weak      TIM15_IRQHandler
  .thumb_set TIM15_IRQHandler,default_interrupt_handler

  .weak      TIM16_IRQHandler
  .thumb_set TIM16_IRQHandler,default_interrupt_handler

  .weak      TIM17_IRQHandler
  .thumb_set TIM17_IRQHandler,default_interrupt_handler

  .weak      I2C1_IRQHandler
  .thumb_set I2C1_IRQHandler,default_interrupt_handler

  .weak      I2C2_IRQHandler
  .thumb_set I2C2_IRQHandler,default_interrupt_handler

  .weak      SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler,default_interrupt_handler

  .weak      SPI2_IRQHandler
  .thumb_set SPI2_IRQHandler,default_interrupt_handler

  .weak      USART1_IRQHandler
  .thumb_set USART1_IRQHandler,default_interrupt_handler

  .weak      USART2_IRQHandler
  .thumb_set USART2_IRQHandler,default_interrupt_handler
.size vtable, .-vtable

// Default interrupt handler. 
// Unconfigured interrupts go to the infinite void here.
.section .text.default_interrupt_handler, "ax", %progbits
default_interrupt_handler:
  default_interrupt_loop:
    /* Add stuff here for debugging if needed */
    /* TODO: it would be cool to blink an LED or something*/
    B default_interrupt_loop
.size default_interrupt_handler, .-default_interrupt_handler
