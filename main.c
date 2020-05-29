#include "led.h"
#include "timer.h"
#include "uart.h"

int main(void) {
  // Initialize LED
  led_init();

  // Initialize timer
  timer_init();
  uint32_t tic = timer_get_ms();
  uint32_t toc = tic;

  // Initialize UART
  uart_init();

  const char *hello_world = "Hello World\n";
  for(char *c = hello_world; *c != '\0'; c++) {
    uart_write(*c);
  }

  while(1) {
    toc = timer_get_ms();
    if(toc - tic > 1000) {
      led_toggle();
      tic = toc;
    }

    // Echo back
    if(uart_available()) {
      char c = uart_read();
      uart_write(c);
    }
  }
  return 0;
}
