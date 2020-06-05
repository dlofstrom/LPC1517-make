#include "led.h"
#include "chip.h"
#include "pins.h"

void led_init(void) {
  Chip_GPIO_Init(LPC_GPIO);
  Chip_GPIO_SetPinDIROutput(LPC_GPIO, LED_PORT, LED_PIN);
  Chip_GPIO_WritePortBit(LPC_GPIO, LED_PORT, LED_PIN, false);
}

void led_set(void) {
  Chip_GPIO_WritePortBit(LPC_GPIO, LED_PORT, LED_PIN, true);
}

void led_clear(void) {
  Chip_GPIO_WritePortBit(LPC_GPIO, LED_PORT, LED_PIN, false);
}

void led_toggle(void) {
  Chip_GPIO_WritePortBit(LPC_GPIO, LED_PORT, LED_PIN, !Chip_GPIO_ReadPortBit(LPC_GPIO, LED_PORT, LED_PIN));
}
