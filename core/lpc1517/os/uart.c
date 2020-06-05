#include "uart.h"
#include "chip.h"

#define UART_TX_PORT 0
#define UART_TX_PIN 22
#define UART_RX_PORT 0
#define UART_RX_PIN 23
// The fixed pins on the chosen uart pins have to be disabled
#define UART_TX_FIXED_PIN SWM_FIXED_I2C0_SCL
#define UART_RX_FIXED_PIN SWM_FIXED_I2C0_SDA
#define UART_BAUD 9600

#define RINGBUFF_SIZE 128
static RINGBUFF_T txring;
static uint8_t tx_buff[RINGBUFF_SIZE];
static RINGBUFF_T rxring;
static uint8_t rx_buff[RINGBUFF_SIZE];

//Uart interrupt handler
void UART0_IRQHandler(void)
{
  //Use default ringbuffer
  Chip_UART_IRQRBHandler(LPC_USART0, &rxring, &txring);
}

void uart_init(void) {
  // Configure pins
  Chip_IOCON_PinMuxSet(LPC_IOCON, UART_TX_PORT, UART_TX_PIN, (IOCON_FUNC0 | IOCON_MODE_INACT | IOCON_DIGMODE_EN));
  Chip_IOCON_PinMuxSet(LPC_IOCON, UART_RX_PORT, UART_RX_PIN, (IOCON_FUNC0 | IOCON_MODE_INACT | IOCON_DIGMODE_EN));
  Chip_SWM_Init();
  if(Chip_SWM_IsFixedPinEnabled(UART_TX_FIXED_PIN)) {
    Chip_SWM_DisableFixedPin(UART_TX_FIXED_PIN);
  }
  Chip_SWM_MovablePortPinAssign(SWM_UART0_TXD_O, UART_TX_PORT, UART_TX_PIN);
  if(Chip_SWM_IsFixedPinEnabled(UART_RX_FIXED_PIN)) {
    Chip_SWM_DisableFixedPin(UART_RX_FIXED_PIN);
  }
  Chip_SWM_MovablePortPinAssign(SWM_UART0_RXD_I, UART_RX_PORT, UART_RX_PIN);

  //Uart clock
  Chip_Clock_SetUARTBaseClockRate((UART_BAUD * 128), true);
  Chip_UART_Init(LPC_USART0);
  Chip_UART_ConfigData(LPC_USART0, UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1);
  Chip_UART_SetBaud(LPC_USART0, UART_BAUD);
  Chip_UART_Enable(LPC_USART0);
  Chip_UART_TXEnable(LPC_USART0);

  //Init ring buffers
  RingBuffer_Init(&rxring, rx_buff, 1, RINGBUFF_SIZE);
  RingBuffer_Init(&txring, tx_buff, 1, RINGBUFF_SIZE);

  //Enable interrupt
  Chip_UART_IntEnable(LPC_USART0, UART_INTEN_RXRDY);
  Chip_UART_IntDisable(LPC_USART0, UART_INTEN_TXRDY);
  NVIC_EnableIRQ(UART0_IRQn);
}

uint8_t uart_available(void) {
  return !RingBuffer_IsEmpty(&rxring);
}

uint8_t uart_read(void) {
  uint8_t data;
  RingBuffer_Pop(&rxring, &data);
  return data;
}

void uart_write(uint8_t c) {
  Chip_UART_SendRB(LPC_USART0, &txring, &c, 1);
}
