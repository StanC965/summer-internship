// 233 - CORE
#include <iom324pb.h>

#define INPUT   0
#define OUTPUT  1

void delay(unsigned long count){
  volatile unsigned long i;

  for (i = 0; i < count; i++){
      // Software delay
  }
}

//Function tu set any pin from PORTC
void set_pin(unsigned char pin){
  PORTC |= (1 << pin);
}

//Function tu reset any pin from PORTC
void reset_pin(unsigned char pin){
  PORTC &= ~(1 << pin);
}

void set_direction(unsigned char pin, unsigned char direction){
  
  if (direction){
    DDRC |= (1 << pin);      // Output
  }
  else{
    DDRC &= ~(1 << pin);     // Input
  }
}

void main( void )
{
  DDRD_DDRD5 = 1;
  DDRD_DDRD4 = 1;
  DDRA_DDRA3 = 1;
  
  set_direction(7,OUTPUT);
  
  while(1){
    
    set_pin(7); //LEDO OFF
    
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
    reset_pin(7); //LED0 ON
    delay(250000UL);

  }
}
