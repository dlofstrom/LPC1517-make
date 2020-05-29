#ifndef UART_H
#define UART_H

#include <stdint.h>

void uart_init(void);
uint8_t uart_available(void);
uint8_t uart_read(void);
void uart_write(uint8_t c);

#endif
