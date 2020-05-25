#include "chip.h"

const uint32_t OscRateIn = 12000000;
const uint32_t RTCOscRateIn = 32768;

int main(void) {
  // Set LED pin as high
  Chip_GPIO_Init(LPC_GPIO);
  Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 29);
  Chip_GPIO_WritePortBit(LPC_GPIO, 0, 29, false);
  volatile int i;
  while(1) {
    for(i = 0; i < 3500000; i++);
    Chip_GPIO_WritePortBit(LPC_GPIO, 0, 29, true);
    for(i = 0; i < 3500000; i++);
    Chip_GPIO_WritePortBit(LPC_GPIO, 0, 29, false);
  }
  return 0;
}
