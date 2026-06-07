#include <stdint.h>
#include "led_mgr.h"

int main(void)
{
    led_mgr_init();

    while (1) {
        led_mgr_on();
        // led_mgr_delay(800000U);

        // led_mgr_off();
        // led_mgr_delay(800000U);
    }
}
