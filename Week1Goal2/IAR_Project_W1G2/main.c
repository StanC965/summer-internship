// 223 - CORE
#include <iom324pb.h>

void main( void )
{
  
  //Turn on LED1
  DDRD_DDRD5 = 1;
  PORTD_PORTD5 = 0;
  
  //Turn on LED2
  DDRD_DDRD4 = 1;
  PORTD_PORTD4 = 0;
  
  //Turn on LED3
  DDRA_DDRA3 = 1;
  PORTA_PORTA3 = 0;
  
  while(1){
    

  }
}
