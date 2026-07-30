#include "iom324pb.h"
#include "uart.h"

/*
IO1 on EXT4 exposes USART2:
RX = PE2 / EXT4 pin 13
TX = PE3 / EXT4 pin 14

9600 baud, 8N1, asynchronous, normal speed, F_CPU = 16 MHz.
UBRR = 16000000 / (16 * 9600) - 1 = 103.
*/
#define UART_ZERO                       (0U)
#define UART_ONE                        (1U)
#define UART_UBRR_VALUE                 (103U)
#define UART_RXC_BIT                    (7U)
#define UART_UDRE_BIT                   (5U)
#define UART_U2X_BIT                    (1U)
#define UART_RXEN_BIT                   (4U)
#define UART_TXEN_BIT                   (3U)
#define UART_UCSZ21_BIT                 (2U)
#define UART_UCSZ20_BIT                 (1U)

void uart_init(void)
{
    UCSR2A &= (uart_uint8_t)(~(UART_ONE << UART_U2X_BIT));
    UBRR2H = (uart_uint8_t)(UART_UBRR_VALUE >> 8U);
    UBRR2L = (uart_uint8_t)UART_UBRR_VALUE;
    UCSR2B = (uart_uint8_t)((UART_ONE << UART_RXEN_BIT) | (UART_ONE << UART_TXEN_BIT));
    UCSR2C = (uart_uint8_t)((UART_ONE << UART_UCSZ21_BIT) | (UART_ONE << UART_UCSZ20_BIT));
}

void uart_send_byte(uart_uint8_t uart_data)
{
    while ((UCSR2A & (UART_ONE << UART_UDRE_BIT)) == UART_ZERO)
    {
    }
    UDR2 = uart_data;
}

uart_uint8_t uart_is_data_available(void)
{
    if ((UCSR2A & (UART_ONE << UART_RXC_BIT)) != UART_ZERO)
    {
        return UART_DATA_AVAILABLE;
    }
    return UART_DATA_NOT_AVAILABLE;
}

uart_uint8_t uart_receive_byte(void)
{
    while (uart_is_data_available() == UART_DATA_NOT_AVAILABLE)
    {
    }
    return UDR2;
}

void uart_send_string(const char *uart_text)
{
    while (*uart_text != '\0')
    {
        uart_send_byte((uart_uint8_t)(*uart_text));
        uart_text++;
    }
}
