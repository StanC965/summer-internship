#ifndef UART_H
#define UART_H

void uart_init(unsigned int ubrr);
void uart_transmit_char(unsigned char data);
void uart_transmit_string(char sir[]);
unsigned char uart_receive(void);

#endif