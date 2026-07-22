#ifndef USART_C
#define USART_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


#include "gpio.h"       
#include "iom324pb.h"
#include "adc.h"
#include "usart.h"



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Implementation      */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


  void USART_Init( unsigned int ubrr)
{
/*Set baud rate */
UBRR2H = (unsigned char)(ubrr>>8);
UBRR2L = (unsigned char)ubrr;
/*Enable receiver and transmitter */
UCSR2B = (1<<4)|(1<<3);
/* Set frame format: 8data, 2stop bit */
UCSR2C = (1<<3)|(1<<1)|(1<<2);
  
}

void USART_Transmit( unsigned char data )
{
/* Wait for empty transmit buffer */
while ( !( UCSR2A & (1<<5)) )
;
/* Put data into buffer, sends the data */
UDR2 = data;
}


#endif