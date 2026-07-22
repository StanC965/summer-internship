#ifndef UART_H
#define UART_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdint.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  */
#define UART_UBRR_VALUE   (12U)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn      void uart_init(void)
    \brief   [ Configures USART2 for 9600 8N1 asynchronous UART. ]
    \details [ Sets UBRR2, enables U2X2 for better baud accuracy at low
             F_CPU, enables the transmitter and receiver, and configures
             8 data bits / no parity / 1 stop bit. ]
*/
extern void uart_init(void);

/** \fn      void uart_send_byte(uint8_t data)
    \brief   [ Sends a single byte over USART2, blocking until ready. ]
*/
extern void uart_send_byte(uint8_t data);

/** \fn      uint8_t uart_receive_byte(void)
    \brief   [ Receives a single byte over USART2, blocking until available. ]
*/
extern uint8_t uart_receive_byte(void);

/** \fn      void uart_send_string(const char *str)
    \brief   [ Sends a null-terminated string, one byte at a time. ]
*/
extern void uart_send_string(const char *str);

/** \fn      void uart_receive_string(char *buffer, uint8_t max_length)
    \brief   [ Receives bytes until '\n' or max_length-1 bytes are stored,
             then null-terminates the buffer. ]
*/
extern void uart_receive_string(char *buffer, uint8_t max_length);

#endif /* UART_H */
