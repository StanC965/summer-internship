// 216 - CORE
#include <iom324pb.h>

void delay(void)
{
    volatile unsigned long i;

    for (i = 0; i < 200000UL; i++)
    {
      //Do nothing
    }
}

void main( void )
{
  
  DDRC_DDRC7 = 1; //Configure PC7 as an output:
  
  while(1){
    
    PORTC_PORTC7 = 0; //Turn the LED ON (active LOW)
    delay();
    
    PORTC_PORTC7 = 1;
    delay();
  }
}
