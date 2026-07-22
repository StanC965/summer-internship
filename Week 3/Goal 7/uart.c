#include "iom324pb.h"
#include "uart.h"

void uart_init(unsigned int ubrr){
  UBRR2H=(unsigned char)(ubrr>>8);
  UBRR2L=(unsigned char)ubrr;
  UCSR2B=0b00011000; //activam USART Receiver si Trransmitter
  UCSR2C=0b00000110; //8 biti, 1 bit stop
  
}

void uart_transmit_char(unsigned char data){
  while((UCSR2A&0x20)!=0x20);
  UDR2=data;
}

void uart_transmit_string(char sir[]){
  int i=0;
  while(sir[i]!='\0'){
    uart_transmit_char(sir[i]);
    i++;
  }
}

unsigned char uart_receive(void){
  while((UCSR2A&0x80)!=0x80);
  return UDR2;
}