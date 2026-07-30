#ifndef UART_H
#define UART_H

typedef unsigned char uart_uint8_t;

#define UART_DATA_NOT_AVAILABLE    (0U)
#define UART_DATA_AVAILABLE        (1U)

extern void uart_init(void);
extern void uart_send_byte(uart_uint8_t uart_data);
extern uart_uint8_t uart_is_data_available(void);
extern uart_uint8_t uart_receive_byte(void);
extern void uart_send_string(const char *uart_text);

#endif
