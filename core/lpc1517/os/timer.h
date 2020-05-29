#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void timer_init(void);
uint32_t timer_get(void);
uint32_t timer_get_us(void);
uint32_t timer_get_ms(void);

#endif
