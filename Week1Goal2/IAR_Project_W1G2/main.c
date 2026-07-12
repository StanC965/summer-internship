// 231 - CORE
#include <iom324pb.h>

void delay(unsigned long count)
{
    volatile unsigned long i;

    for (i = 0; i < count; i++)
    {
        // Software delay
    }
}

//Function tu set any pin from PORTC
void set_pin(unsigned char pin)
{
    PORTC |= (1 << pin);
}

void main( void )
{
  DDRD_DDRD5 = 1;
  DDRD_DDRD4 = 1;
  DDRA_DDRA3 = 1;
  
  DDRC_DDRC7 = 1;
  set_pin(7); //LEDO 
  
  while(1){
    
    PORTD_PORTD5 = 1;
    PORTD_PORTD4 = 1;
    PORTA_PORTA3 = 1;
    delay(250000UL);
    
    PORTD_PORTD5 = 0;
    PORTD_PORTD4 = 0;
    PORTA_PORTA3 = 1;
    delay(250000UL);

    PORTD_PORTD5 = 1;
    PORTD_PORTD4 = 0;
    PORTA_PORTA3 = 0;
    delay(250000UL);
    
    PORTD_PORTD5 = 0;
    PORTD_PORTD4 = 1;
    PORTA_PORTA3 = 0;
    delay(250000UL);

  }
}
