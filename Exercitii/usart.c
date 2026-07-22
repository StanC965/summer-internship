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

UBRR2H = (unsigned char)(ubrr>>8);
UBRR2L = (unsigned char)ubrr;

UCSR2B = (1<<4)|(1<<3);

UCSR2C = (1<<3)|(1<<1)|(1<<2);
  
}

void USART_Transmit( unsigned char data )
{

while ( !( UCSR2A & (1<<5)) )
;

UDR2 = data;
}


#endif