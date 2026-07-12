// 225 - CORE
#include <iom324pb.h>

void delay(unsigned long count)
{
    volatile unsigned long i;

    for (i = 0; i < count; i++)
    {
        // Software delay
    }
}
void main( void )
{
  DDRD_DDRD5 = 1;
  DDRD_DDRD4 = 1;
  DDRA_DDRA3 = 1;
  
  PORTD_PORTD5 = 1;
  PORTD_PORTD4 = 1;
  PORTA_PORTA3 = 1;
  
  while(1){
    
    PORTD_PORTD5 = 0;
    PORTA_PORTA3 = 0;
    PORTD_PORTD4 = 1;
    delay(250000UL);

    PORTD_PORTD5 = 1;
    PORTA_PORTA3 = 1;
    PORTD_PORTD4 = 0;
    delay(250000UL);

  }
}
