#include "timer.h"
#include "chip.h"

static uint32_t ticks_per_second;
static uint32_t ticks_per_ms;
static uint32_t ticks_per_us;

void timer_init(void) {
  Chip_RIT_Init(LPC_RITIMER);
  Chip_RIT_SetCompareValue(LPC_RITIMER, (uint32_t)0xFFFFFFFF);
  Chip_RIT_EnableCompClear(LPC_RITIMER);
  Chip_RIT_Enable(LPC_RITIMER);

  ticks_per_second = Chip_Clock_GetSystemClockRate();
  ticks_per_ms = ticks_per_second / 1000;
  ticks_per_us = ticks_per_second / 1000000;
}

uint32_t timer_get(void) {
  return (uint32_t)Chip_RIT_GetCounter(LPC_RITIMER);
}

uint32_t timer_get_us(void) {
  return (uint32_t)Chip_RIT_GetCounter(LPC_RITIMER) / ticks_per_us;
}

uint32_t timer_get_ms(void) {
  return (uint32_t)Chip_RIT_GetCounter(LPC_RITIMER) / ticks_per_ms;
}
