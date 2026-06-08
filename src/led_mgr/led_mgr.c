#include <stdint.h>
#include "led_mgr.h"
#include "bsp.h"

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

void led_mgr_blink(uint32_t times)
{
    for (uint32_t i = 0; i < times; i++) {
        led_mgr_on();
        led_mgr_delay(800000U); /* ≈500 ms @ 16 MHz HSI */
        led_mgr_off();
        led_mgr_delay(800000U); /* ≈500 ms @ 16 MHz HSI */
    }
}
