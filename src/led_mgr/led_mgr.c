#include <stdint.h>
#include "led_mgr.h"
#include "bsp_stm32g071rbT6.h"

void led_mgr_init(void)
{
    LED_CLK_ENABLE();

    LED_GPIO_MODER &= ~(0x3U << (LED_PIN * 2U));
    LED_GPIO_MODER |=  (0x1U << (LED_PIN * 2U));
}

void led_mgr_on(void)
{
    LED_GPIO_BSRR = (1U << LED_PIN);
}

void led_mgr_off(void)
{
    LED_GPIO_BSRR = (1U << (LED_PIN + 16U));
}

void led_mgr_delay(volatile uint32_t ticks)
{
    while (ticks--) {
        __asm__ volatile ("nop");
    }
}
