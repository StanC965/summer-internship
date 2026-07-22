#ifndef UART_C
#define UART_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "uart.h"
#include <iom324pb.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void uart_init(void)
{
    UBRR2H = (uint8_t)(UART_UBRR_VALUE >> 8);
    UBRR2L = (uint8_t)(UART_UBRR_VALUE);

    UCSR2A |= (1 << U2X2);

    UCSR2B = (1 << TXEN2) | (1 << RXEN2);

    UCSR2C = (1 << UCSZ21) | (1 << UCSZ20);   
}

void uart_send_byte(uint8_t data)
{
    while (!(UCSR2A & (1 << UDRE2)))          
    {
    }
    UDR2 = data;
}

uint8_t uart_receive_byte(void)
{
    while (!(UCSR2A & (1 << RXC2)))          
    {
    }
    return UDR2;
}

void uart_send_string(const char *str)
{
    while (*str != '\0')
    {
        uart_send_byte((uint8_t)*str);
        str++;
    }
}

void uart_receive_string(char *buffer, uint8_t max_length)
{
    uint8_t index = 0;
    char received_byte;

    do
    {
        received_byte = (char)uart_receive_byte();

        if (index < (max_length - 1U))
        {
            buffer[index] = received_byte;
            index++;
        }
    } while (received_byte != '\n');

    buffer[index] = '\0';
}

#endif /* UART_C */
