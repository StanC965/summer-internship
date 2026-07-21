/**
 * @file uart.h
 * @brief Header file for USART2 communication interface[cite: 18].
 * @details Contains baud rate macros and public function prototypes for asynchronous serial communications[cite: 18].
 */

#ifndef UART_H
#define UART_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <iom324pb.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported Macros and Definitions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** @name Default Serial Parameters */
/**@{*/
#define UART_DEFAULT_BAUD       9600UL      /**< Default target baud rate[cite: 18] */
#define UART_SYSTEM_CLOCK_FREQ  1000000UL   /**< System clock frequency for UBRR calculation[cite: 18] */
/**@}*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Public Functions                                                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/**
 * @brief Initializes the USART2 module on EXT4 (PE0 RX, PE1 TX) for 9600 8N1 asynchronous operation[cite: 18].
 */
void uart_init(void);

/**
 * @brief Checks if the USART2 Data Register (UDR2) is empty and ready for transmit[cite: 18].
 * @return 1 if buffer is ready, 0 if busy[cite: 18].
 */
unsigned char uart_is_tx_ready(void);

/**
 * @brief Writes a single byte to the transmit register UDR2[cite: 18].
 * @param data Character byte to send[cite: 18].
 */
void uart_send_byte(unsigned char data);

/**
 * @brief Checks if an unread character is waiting in UDR2[cite: 18].
 * @return 1 if character is ready, 0 otherwise[cite: 18].
 */
unsigned char uart_is_rx_available(void);

/**
 * @brief Reads incoming byte from UDR2 register[cite: 18].
 * @return Received character byte[cite: 18].
 */
unsigned char uart_read_byte(void);

/**
 * @brief Transmits a null-terminated string over USART2[cite: 18].
 * @param str Pointer to source null-terminated string[cite: 18].
 */
void uart_send_string(const char *str);

#endif