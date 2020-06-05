// Provide stubs for system calls
#include "chip.h"
#include "uart.h"
#include <sys/stat.h>

extern int _pvHeapStart;

void *_sbrk(int incr) {
  static unsigned char *heap = NULL;
  unsigned char *prev_heap;
  if (heap == NULL) {
    heap = (unsigned char *)&_pvHeapStart;
  }
  prev_heap = heap;
  heap += incr;
  return prev_heap;
}

int _close(int file) {
  return -1;
}

int _fstat(int file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}

int _isatty(int file) {
  return 1;
}

int _lseek(int file, int ptr, int dir) {
  return 0;
}

void _exit(int status) {
  while(1);
}

void _kill(int pid, int sig) {
  return;
}

int _getpid(void) {
  return -1;
}

int _write (int file, char * ptr, int len) {
  if((file != 1) && (file != 2) && (file != 3)) {
    return -1;
  }
  for(size_t i = 0; i < len; i++) {
    uart_write((uint8_t)*ptr++);
  }
  return len;
}

int _read (int file, char * ptr, int len) {
  if (file != 0) {
    return -1;
  }

  for(size_t i = 0; i < len; i++) {
    *(uint8_t *)ptr++ = uart_read();
  }
  return len;
}
