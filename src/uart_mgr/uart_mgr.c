#include <stdint.h>
#include "uart_mgr.h"
#include "bsp.h"

void uart_mgr_init(void)
{
    /* Enable clocks */
    USART2_GPIO_CLK_ENABLE();
    USART2_CLK_ENABLE();

    /* Set TX and RX pins to Alternate Function mode (MODER = 10) */
    USART2_GPIO_MODER &= ~((0x3U << (USART2_TX_PIN * 2U)) |
                           (0x3U << (USART2_RX_PIN * 2U)));
    USART2_GPIO_MODER |=   (0x2U << (USART2_TX_PIN * 2U)) |
                           (0x2U << (USART2_RX_PIN * 2U));

    /* Set AF1 for PA2 and PA3 in AFRL */
    GPIOA_AFRL &= ~((0xFU << (USART2_TX_PIN * 4U)) |
                    (0xFU << (USART2_RX_PIN * 4U)));
    GPIOA_AFRL |=   (USART2_AF << (USART2_TX_PIN * 4U)) |
                    (USART2_AF << (USART2_RX_PIN * 4U));

    /* BRR = 16000000 / 115200 = 139 */
    USART2_BRR = 139U;

    /* Enable TX and USART */
    USART2_CR1 |= USART2_CR1_ENABLE_MASK;
}

void uart_mgr_send(const char *str)
{
    while (*str) {
        /* Wait until TXE (bit 7 in ISR) is set */
        while (!(USART2_ISR & (1U << 7))) {}
        USART2_TDR = (uint32_t)(*str++);
    }
}