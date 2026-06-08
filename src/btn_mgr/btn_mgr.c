#include <stdint.h>
#include "btn_mgr.h"
#include "bsp.h"

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