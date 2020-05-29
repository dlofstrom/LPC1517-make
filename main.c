#include "led.h"
#include "timer.h"

int main(void) {
  led_init();
  timer_init();
  uint32_t tic = timer_get_ms();
  uint32_t toc = tic;
  while(1) {
    toc = timer_get_ms();
    if(toc - tic > 1000) {
      led_toggle();
      tic = toc;
    }
  }
  return 0;
}
