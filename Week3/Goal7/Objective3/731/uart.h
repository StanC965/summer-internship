#ifndef UART_H
#define UART_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <iom324pb.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported Macros and Definitions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define UART_DEFAULT_BAUD       9600UL
#define UART_SYSTEM_CLOCK_FREQ  1000000UL

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Public Functions                                                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void uart_init(void)
    \brief  Initializes the USART2 module on EXT4 (PE0 RX, PE1 TX) for 9600 8N1 asynchronous operation.
*/
void uart_init(void);

/** \fn     unsigned char uart_is_tx_ready(void)
    \brief  Checks if the USART2 Data Register (UDR2) is empty and ready for transmit.
    \return 1 if buffer is ready, 0 if busy.
*/
unsigned char uart_is_tx_ready(void);

/** \fn     void uart_send_byte(unsigned char data)
    \brief  Writes a single byte to the transmit register UDR2.
    \param  data Character byte to send.
*/
void uart_send_byte(unsigned char data);

/** \fn     unsigned char uart_is_rx_available(void)
    \brief  Checks if an unread character is waiting in UDR2.
    \return 1 if character is ready, 0 otherwise.
*/
unsigned char uart_is_rx_available(void);

/** \fn     unsigned char uart_read_byte(void)
    \brief  Reads incoming byte from UDR2 register.
    \return Received character byte.
*/
unsigned char uart_read_byte(void);

/** \fn     void uart_send_string(const char *str)
    \brief  Transmits a null-terminated string over USART2.
    \param  str Pointer to source string.
*/
void uart_send_string(const char *str);

#endif 