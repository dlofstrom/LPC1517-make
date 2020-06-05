#ifndef PINS_H
#define PINS_H

// LED pins
#define LED_PORT 0
#define LED_PIN 29

// UART pins
#define UART_TX_PORT 0
#define UART_TX_PIN 22
#define UART_RX_PORT 0
#define UART_RX_PIN 23
// The fixed pins on the chosen uart pins have to be disabled
#define UART_TX_FIXED_PIN SWM_FIXED_I2C0_SCL
#define UART_RX_FIXED_PIN SWM_FIXED_I2C0_SDA


#endif
