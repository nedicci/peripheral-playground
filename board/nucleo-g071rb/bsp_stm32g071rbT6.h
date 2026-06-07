#ifndef BSP_STM32G071RBT6_H
#define BSP_STM32G071RBT6_H

#include <stdint.h>

/*
 * Board-specific LED definitions for NUCLEO-G071RB
 * LED: LD4, green, connected to PA5
 */

/* Enable GPIOA clock via RCC_IOPENR bit 0 */
#define LED_CLK_ENABLE()  \
    (*(volatile uint32_t *)(0x40021000UL + 0x034U)) |= (1U << 0)

/* GPIOA MODER and BSRR registers */
#define LED_GPIO_MODER    (*(volatile uint32_t *)(0x50000000UL + 0x000U))
#define LED_GPIO_BSRR     (*(volatile uint32_t *)(0x50000000UL + 0x018U))

/* PA5 */
#define LED_PIN           (5U)

#endif /* BSP_STM32G071RBT6_H */
