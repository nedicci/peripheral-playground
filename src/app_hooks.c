#include "FreeRTOS.h"
#include "task.h"

void vApplicationMallocFailedHook(void)
{
    /* Called if a malloc() fails. Halt so a debugger can catch it. */
    __asm volatile("bkpt #0");
    while (1);
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask;
    (void)pcTaskName;
    __asm volatile("bkpt #0");
    while (1);
}
