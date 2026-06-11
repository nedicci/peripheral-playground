#include <stdint.h>
#include "btn_mgr.h"
#include "led_mgr.h"
#include "uart_mgr.h"
#include "bsp.h"

void btn_mgr_thread(void *arg)
{
    (void)arg;
    for (;;)
    {
        if (btn_mgr_is_pressed())
        {
            /* Notify LED task */
            xTaskNotifyGive(led_mgr_thread_handle);

            /* Send message to UART task */
            const char *msg = "Button pressed!\r\n";
            xQueueSend(uart_mgr_queue, &msg, 0);

            /* Wait for release before re-arming */
            while (btn_mgr_is_pressed())
            {
                vTaskDelay(pdMS_TO_TICKS(10));
            }
        }
        vTaskDelay(pdMS_TO_TICKS(20));  /* poll at 50 Hz */
    }
}

void btn_mgr_init(void)
{
    BUTTON_CLK_ENABLE();

    /* Set PC13 as input: clear bits [27:26] in MODER */
    BUTTON_GPIO_MODER &= ~(0x3U << (BUTTON_PIN * 2U));
}

int btn_mgr_is_pressed(void)
{
    return BTN_PRESSED();
}