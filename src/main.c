#include <stdint.h>
#include "led_mgr.h"
#include "btn_mgr.h"
#include "uart_mgr.h"

int main(void)
{
    led_mgr_init();
    btn_mgr_init();
    uart_mgr_init();

    uart_mgr_send("System ready!\r\n");

    while (1)
    {
        if (btn_mgr_is_pressed())
        {
            uart_mgr_send("Button pressed!\r\n");
            led_mgr_blink(5);

            /* Wait for release to avoid multiple triggers */
            while (btn_mgr_is_pressed())
            {
                /* Do nothing */
            }
        }
    }
}
