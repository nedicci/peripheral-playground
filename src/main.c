#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "led_mgr.h"
#include "btn_mgr.h"
#include "uart_mgr.h"

int main(void)
{
    led_mgr_init();
    btn_mgr_init();
    uart_mgr_init();

    uart_mgr_send("System ready!\r\n");

    uart_mgr_queue = xQueueCreate(8, sizeof(const char *));

    xTaskCreate(led_mgr_thread,  "LED",  256, NULL, 2, &led_mgr_thread_handle);
    xTaskCreate(btn_mgr_thread,  "BTN",  256, NULL, 3, NULL);
    xTaskCreate(uart_mgr_thread, "UART", 256, NULL, 1, NULL);

    vTaskStartScheduler();

    /* Never reached */
    while (1);
}
