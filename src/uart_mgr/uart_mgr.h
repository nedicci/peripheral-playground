#ifndef UART_MGR_H
#define UART_MGR_H

#include <stdint.h>

/* Configure USART2 at 115200, 8N1. */
void uart_mgr_init(void);

/* Transmit a null-terminated string. */
void uart_mgr_send(const char *str);

#endif /* UART_MGR_H */