#ifndef LED_MGR_H
#define LED_MGR_H

#include "FreeRTOS.h"
#include "task.h"

extern TaskHandle_t led_mgr_thread_handle;

void led_mgr_thread(void *arg);

/* Configure the LED pin as output and enable its GPIO clock. */
void led_mgr_init(void);

/* Turn the LED on. */
void led_mgr_on(void);

/* Turn the LED off. */
void led_mgr_off(void);

/* Simple busy-wait delay (≈500 ms @ 16 MHz HSI per 800 000 ticks). */
void led_mgr_delay(volatile uint32_t ticks);

/* Blink the LED a given number of times. */
void led_mgr_blink(uint32_t times);

#endif /* LED_MGR_H */
