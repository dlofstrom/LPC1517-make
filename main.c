#include "led.h"

int main(void) {
  led_init();
  volatile int i;
  while(1) {
    for(i = 0; i < 3500000; i++);
    led_toggle();
  }
  return 0;
}
