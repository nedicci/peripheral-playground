#ifndef LED_MGR_H
#define LED_MGR_H

/* Configure the LED pin as output and enable its GPIO clock. */
void led_mgr_init(void);

/* Turn the LED on. */
void led_mgr_on(void);

/* Turn the LED off. */
void led_mgr_off(void);

/* Simple busy-wait delay (≈500 ms @ 16 MHz HSI per 800 000 ticks). */
void led_mgr_delay(volatile uint32_t ticks);

#endif /* LED_MGR_H */
