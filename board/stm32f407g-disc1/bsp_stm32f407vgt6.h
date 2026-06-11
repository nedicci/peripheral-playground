#ifndef BSP_STM32F407VGT6_H
#define BSP_STM32F407VGT6_H

#include <stdint.h>

#define RCC_BASE_ADDR           (0x40023800UL)
#define GPIOA_BASE_ADDR         (0x40020000UL)
#define GPIOD_BASE_ADDR         (0x40020C00UL)
#define USART2_BASE_ADDR        (0x40004400UL)

#define RCC_AHB1ENR_OFFSET      (0x030U)
#define RCC_APB1ENR_OFFSET      (0x040U)
#define GPIO_MODER_OFFSET       (0x000U)
#define GPIO_IDR_OFFSET         (0x010U)
#define GPIO_BSRR_OFFSET        (0x018U)
#define GPIO_AFRL_OFFSET        (0x020U)

/* F4 USART (old-style): SR/DR/BRR/CR1 */
#define USART_CR1_OFFSET        (0x00CU)
#define USART_BRR_OFFSET        (0x008U)
#define USART_SR_OFFSET         (0x000U)
#define USART_DR_OFFSET         (0x004U)

/* LED - LD4 green (PD12), LD3 orange (PD13), LD5 red (PD14), LD6 blue (PD15) */
#define LED_CLK_ENABLE()        (*(volatile uint32_t *)(RCC_BASE_ADDR + RCC_AHB1ENR_OFFSET)) |= (1U << 3)
#define LED_GPIO_MODER          (*(volatile uint32_t *)(GPIOD_BASE_ADDR + GPIO_MODER_OFFSET))
#define LED_GPIO_BSRR           (*(volatile uint32_t *)(GPIOD_BASE_ADDR + GPIO_BSRR_OFFSET))
#define LED_PIN                 (12U)   /* LD4 green — change to 13/14/15 for other LEDs */

/* Button - B1 blue, PA0 (active-high) */
#define BUTTON_CLK_ENABLE()     (*(volatile uint32_t *)(RCC_BASE_ADDR + RCC_AHB1ENR_OFFSET)) |= (1U << 0)
#define BUTTON_GPIO_MODER       (*(volatile uint32_t *)(GPIOA_BASE_ADDR + GPIO_MODER_OFFSET))
#define BUTTON_GPIO_IDR         (*(volatile uint32_t *)(GPIOA_BASE_ADDR + GPIO_IDR_OFFSET))
#define BUTTON_PIN              (0U)
#define BTN_PRESSED()           (!!(BUTTON_GPIO_IDR & (1U << BUTTON_PIN)))  /* active-high */

/* USART2 - PA2 (TX), PA3 (RX), AF7 */
#define USART2_CLK_ENABLE()     (*(volatile uint32_t *)(RCC_BASE_ADDR + RCC_APB1ENR_OFFSET)) |= (1U << 17)
#define USART2_CR1              (*(volatile uint32_t *)(USART2_BASE_ADDR + USART_CR1_OFFSET))
#define USART2_BRR              (*(volatile uint32_t *)(USART2_BASE_ADDR + USART_BRR_OFFSET))

/* Alias SR->ISR and DR->TDR so uart_mgr.c compiles unchanged */
#define USART2_ISR              (*(volatile uint32_t *)(USART2_BASE_ADDR + USART_SR_OFFSET))
#define USART2_TDR              (*(volatile uint32_t *)(USART2_BASE_ADDR + USART_DR_OFFSET))
#define GPIOA_AFRL              (*(volatile uint32_t *)(GPIOA_BASE_ADDR + GPIO_AFRL_OFFSET))
#define USART2_TX_PIN           (2U)
#define USART2_RX_PIN           (3U)
#define USART2_AF               (7U)    /* AF7 on F4 */
#define USART2_GPIO_CLK_ENABLE() (*(volatile uint32_t *)(RCC_BASE_ADDR + RCC_AHB1ENR_OFFSET)) |= (1U << 0)
#define USART2_GPIO_MODER       (*(volatile uint32_t *)(GPIOA_BASE_ADDR + GPIO_MODER_OFFSET))
#define USART2_CR1_ENABLE_MASK  ((1U << 13) | (1U << 3)) /* TE=bit3, UE=bit13 */

#endif /* BSP_STM32F407VGT6_H */
