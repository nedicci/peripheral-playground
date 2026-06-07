    .syntax unified
    .cpu cortex-m0plus
    .thumb

    .global Reset_Handler

/* --------------------------------------------------------------------------
 * Interrupt vector table
 * First entry: initial stack pointer (address, not a function)
 * All others:  THUMB function addresses (bit 0 set by the linker)
 * -------------------------------------------------------------------------- */
    .section .isr_vector, "a", %progbits
    .type g_pfnVectors, %object
g_pfnVectors:
    /* Cortex-M0+ core */
    .word _estack
    .word Reset_Handler
    .word NMI_Handler
    .word HardFault_Handler
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word SVC_Handler
    .word 0
    .word 0
    .word PendSV_Handler
    .word SysTick_Handler
    /* STM32G071xx external interrupts (32 total) */
    .word WWDG_IRQHandler
    .word PVD_IRQHandler
    .word RTC_TAMP_IRQHandler
    .word FLASH_IRQHandler
    .word RCC_IRQHandler
    .word EXTI0_1_IRQHandler
    .word EXTI2_3_IRQHandler
    .word EXTI4_15_IRQHandler
    .word UCPD1_2_IRQHandler
    .word DMA1_Channel1_IRQHandler
    .word DMA1_Channel2_3_IRQHandler
    .word DMA1_Ch4_7_DMAMUX1_OVR_IRQHandler
    .word ADC1_COMP_IRQHandler
    .word TIM1_BRK_UP_TRG_COM_IRQHandler
    .word TIM1_CC_IRQHandler
    .word TIM2_IRQHandler
    .word TIM3_TIM4_IRQHandler
    .word TIM6_DAC_LPTIM1_IRQHandler
    .word TIM7_LPTIM2_IRQHandler
    .word TIM14_IRQHandler
    .word TIM15_IRQHandler
    .word TIM16_FDCAN_IT0_IRQHandler
    .word TIM17_FDCAN_IT1_IRQHandler
    .word I2C1_IRQHandler
    .word I2C2_3_IRQHandler
    .word SPI1_IRQHandler
    .word SPI2_3_IRQHandler
    .word USART1_IRQHandler
    .word USART2_LPUART2_IRQHandler
    .word USART3_4_5_6_LPUART1_IRQHandler
    .word CEC_IRQHandler
    .word AES_RNG_IRQHandler
    .size g_pfnVectors, .-g_pfnVectors

/* --------------------------------------------------------------------------
 * Reset handler
 * 1. Copy .data from flash (LMA) to SRAM (VMA)
 * 2. Zero-initialise .bss
 * 3. Jump to main()
 * -------------------------------------------------------------------------- */
    .section .text.Reset_Handler, "ax", %progbits
    .thumb_func
    .type Reset_Handler, %function
Reset_Handler:
    /* Copy .data --------------------------------------------------------- */
    ldr     r0, =_sdata      /* destination start (SRAM) */
    ldr     r1, =_edata      /* destination end   (SRAM) */
    ldr     r2, =_sidata     /* source start      (Flash) */
    movs    r3, #0
    b       DataCopyCond

DataCopyLoop:
    ldr     r4, [r2, r3]
    str     r4, [r0, r3]
    adds    r3, r3, #4

DataCopyCond:
    adds    r4, r0, r3
    cmp     r4, r1
    bcc     DataCopyLoop

    /* Zero .bss ---------------------------------------------------------- */
    ldr     r2, =_sbss
    ldr     r3, =_ebss
    movs    r4, #0
    b       BssZeroCond

BssZeroLoop:
    str     r4, [r2]
    adds    r2, r2, #4

BssZeroCond:
    cmp     r2, r3
    bcc     BssZeroLoop

    /* Branch to application ---------------------------------------------- */
    bl      main
    /* If main() returns, spin forever */
    b       .
    .size Reset_Handler, .-Reset_Handler

/* --------------------------------------------------------------------------
 * Default handler — any unhandled exception/interrupt spins here
 * -------------------------------------------------------------------------- */
    .section .text.Default_Handler, "ax", %progbits
    .thumb_func
    .type Default_Handler, %function
Default_Handler:
    b       .
    .size Default_Handler, .-Default_Handler

/* --------------------------------------------------------------------------
 * Weak aliases — override any of these in your application code
 * -------------------------------------------------------------------------- */
    .weak NMI_Handler
    .thumb_set NMI_Handler, Default_Handler

    .weak HardFault_Handler
    .thumb_set HardFault_Handler, Default_Handler

    .weak SVC_Handler
    .thumb_set SVC_Handler, Default_Handler

    .weak PendSV_Handler
    .thumb_set PendSV_Handler, Default_Handler

    .weak SysTick_Handler
    .thumb_set SysTick_Handler, Default_Handler

    .weak WWDG_IRQHandler
    .thumb_set WWDG_IRQHandler, Default_Handler

    .weak PVD_IRQHandler
    .thumb_set PVD_IRQHandler, Default_Handler

    .weak RTC_TAMP_IRQHandler
    .thumb_set RTC_TAMP_IRQHandler, Default_Handler

    .weak FLASH_IRQHandler
    .thumb_set FLASH_IRQHandler, Default_Handler

    .weak RCC_IRQHandler
    .thumb_set RCC_IRQHandler, Default_Handler

    .weak EXTI0_1_IRQHandler
    .thumb_set EXTI0_1_IRQHandler, Default_Handler

    .weak EXTI2_3_IRQHandler
    .thumb_set EXTI2_3_IRQHandler, Default_Handler

    .weak EXTI4_15_IRQHandler
    .thumb_set EXTI4_15_IRQHandler, Default_Handler

    .weak UCPD1_2_IRQHandler
    .thumb_set UCPD1_2_IRQHandler, Default_Handler

    .weak DMA1_Channel1_IRQHandler
    .thumb_set DMA1_Channel1_IRQHandler, Default_Handler

    .weak DMA1_Channel2_3_IRQHandler
    .thumb_set DMA1_Channel2_3_IRQHandler, Default_Handler

    .weak DMA1_Ch4_7_DMAMUX1_OVR_IRQHandler
    .thumb_set DMA1_Ch4_7_DMAMUX1_OVR_IRQHandler, Default_Handler

    .weak ADC1_COMP_IRQHandler
    .thumb_set ADC1_COMP_IRQHandler, Default_Handler

    .weak TIM1_BRK_UP_TRG_COM_IRQHandler
    .thumb_set TIM1_BRK_UP_TRG_COM_IRQHandler, Default_Handler

    .weak TIM1_CC_IRQHandler
    .thumb_set TIM1_CC_IRQHandler, Default_Handler

    .weak TIM2_IRQHandler
    .thumb_set TIM2_IRQHandler, Default_Handler

    .weak TIM3_TIM4_IRQHandler
    .thumb_set TIM3_TIM4_IRQHandler, Default_Handler

    .weak TIM6_DAC_LPTIM1_IRQHandler
    .thumb_set TIM6_DAC_LPTIM1_IRQHandler, Default_Handler

    .weak TIM7_LPTIM2_IRQHandler
    .thumb_set TIM7_LPTIM2_IRQHandler, Default_Handler

    .weak TIM14_IRQHandler
    .thumb_set TIM14_IRQHandler, Default_Handler

    .weak TIM15_IRQHandler
    .thumb_set TIM15_IRQHandler, Default_Handler

    .weak TIM16_FDCAN_IT0_IRQHandler
    .thumb_set TIM16_FDCAN_IT0_IRQHandler, Default_Handler

    .weak TIM17_FDCAN_IT1_IRQHandler
    .thumb_set TIM17_FDCAN_IT1_IRQHandler, Default_Handler

    .weak I2C1_IRQHandler
    .thumb_set I2C1_IRQHandler, Default_Handler

    .weak I2C2_3_IRQHandler
    .thumb_set I2C2_3_IRQHandler, Default_Handler

    .weak SPI1_IRQHandler
    .thumb_set SPI1_IRQHandler, Default_Handler

    .weak SPI2_3_IRQHandler
    .thumb_set SPI2_3_IRQHandler, Default_Handler

    .weak USART1_IRQHandler
    .thumb_set USART1_IRQHandler, Default_Handler

    .weak USART2_LPUART2_IRQHandler
    .thumb_set USART2_LPUART2_IRQHandler, Default_Handler

    .weak USART3_4_5_6_LPUART1_IRQHandler
    .thumb_set USART3_4_5_6_LPUART1_IRQHandler, Default_Handler

    .weak CEC_IRQHandler
    .thumb_set CEC_IRQHandler, Default_Handler

    .weak AES_RNG_IRQHandler
    .thumb_set AES_RNG_IRQHandler, Default_Handler
