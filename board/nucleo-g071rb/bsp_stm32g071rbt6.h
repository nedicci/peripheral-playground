#ifndef BSP_STM32G071RBT6_H
#define BSP_STM32G071RBT6_H

#include <stdint.h>

#define RCC_BASE_ADDR           (0x40021000UL)
#define GPIOA_BASE_ADDR         (0x50000000UL)
#define GPIOC_BASE_ADDR         (0x50000800UL)
#define USART2_BASE_ADDR        (0x40004400UL)

#define RCC_IOPENR_OFFSET       (0x034U)
#define RCC_APBENR1_OFFSET      (0x03CU)
#define GPIO_MODER_OFFSET       (0x000U)
#define GPIO_IDR_OFFSET         (0x010U)
#define GPIO_BSRR_OFFSET        (0x018U)
#define USART_CR1_OFFSET        (0x00U)
#define USART_BRR_OFFSET        (0x0CU)
#define USART_ISR_OFFSET        (0x1CU)
#define USART_TDR_OFFSET        (0x28U)
#define GPIO_AFRL_OFFSET        (0x020U)

/* LED - PA5 */
#define LED_CLK_ENABLE()        (*(volatile uint32_t *)(RCC_BASE_ADDR + RCC_IOPENR_OFFSET)) |= (1U << 0)
#define LED_GPIO_MODER          (*(volatile uint32_t *)(GPIOA_BASE_ADDR + GPIO_MODER_OFFSET))
#define LED_GPIO_BSRR           (*(volatile uint32_t *)(GPIOA_BASE_ADDR + GPIO_BSRR_OFFSET))
#define LED_PIN                 (5U)

/* Button - PC13 */
#define BUTTON_CLK_ENABLE()     (*(volatile uint32_t *)(RCC_BASE_ADDR + RCC_IOPENR_OFFSET)) |= (1U << 2)
#define BUTTON_GPIO_MODER       (*(volatile uint32_t *)(GPIOC_BASE_ADDR + GPIO_MODER_OFFSET))
#define BUTTON_GPIO_IDR         (*(volatile uint32_t *)(GPIOC_BASE_ADDR + GPIO_IDR_OFFSET))
#define BUTTON_PIN              (13U)
#define BTN_PRESSED()           (!(BUTTON_GPIO_IDR & (1U << BUTTON_PIN)))  /* active-low */

/* USART2 - PA2 (TX), PA3 (RX) */
#define USART2_GPIO_CLK_ENABLE() (*(volatile uint32_t *)(RCC_BASE_ADDR + RCC_IOPENR_OFFSET)) |= (1U << 0)
#define USART2_GPIO_MODER       (*(volatile uint32_t *)(GPIOA_BASE_ADDR + GPIO_MODER_OFFSET))
#define USART2_CLK_ENABLE()     (*(volatile uint32_t *)(RCC_BASE_ADDR + RCC_APBENR1_OFFSET)) |= (1U << 17)
#define USART2_CR1              (*(volatile uint32_t *)(USART2_BASE_ADDR + USART_CR1_OFFSET))
#define USART2_BRR              (*(volatile uint32_t *)(USART2_BASE_ADDR + USART_BRR_OFFSET))
#define USART2_ISR              (*(volatile uint32_t *)(USART2_BASE_ADDR + USART_ISR_OFFSET))
#define USART2_TDR              (*(volatile uint32_t *)(USART2_BASE_ADDR + USART_TDR_OFFSET))
#define GPIOA_AFRL              (*(volatile uint32_t *)(GPIOA_BASE_ADDR + GPIO_AFRL_OFFSET))
#define USART2_TX_PIN           (2U)
#define USART2_RX_PIN           (3U)
#define USART2_AF               (1U)    /* AF1 on G071 */
#define USART2_CR1_ENABLE_MASK  ((1U << 0) | (1U << 3)) /* UE=bit0, TE=bit3 on G0 */

#endif /* BSP_STM32G071RBT6_H */
