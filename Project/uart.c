/**
 * @file uart.c
 * @brief Implementation of USART2 hardware communication routines[cite: 18, 21].
 */

#ifndef UART_C
#define UART_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "uart.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Implementation                                                            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void uart_init(void)
{
    unsigned int ubrr_value = (unsigned int)((UART_SYSTEM_CLOCK_FREQ / (16UL * UART_DEFAULT_BAUD)) - 1);

    // Baud rate high and low registers
    UBRR2H = (unsigned char)(ubrr_value >> 8);
    UBRR2L = (unsigned char)(ubrr_value);

    // Enable Receiver and Transmitter
    UCSR2B = (1 << 4) | (1 << 3);

    // Select 8-bit character data size.
    UCSR2C = (1 << 2) | (1 << 1);
}

unsigned char uart_is_tx_ready(void)
{
    return (UCSR2A & (1 << 5)) ? 1 : 0;
}

void uart_send_byte(unsigned char data)
{
    UDR2 = data;
}

unsigned char uart_is_rx_available(void)
{
    return (UCSR2A & (1 << 7)) ? 1 : 0;
}

unsigned char uart_read_byte(void)
{
    return UDR2;
}

void uart_send_string(const char *str)
{
    while (*str != '\0')
    {
        while (!uart_is_tx_ready());
        uart_send_byte((unsigned char)(*str));
        str++;
    }
}

#endif