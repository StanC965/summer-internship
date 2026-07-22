//731
#include "iom324pb.h"
#include "uart.h"

void main( void )
{
  uart_init(103); //pentru 9600 baud
  
  unsigned char caracter;
  while(1){
    uart_transmit_string("Salut!");
    caracter=uart_receive();
  }
  
}
