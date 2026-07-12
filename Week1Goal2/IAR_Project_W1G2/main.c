// 234 - CORE
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

//Function tu set direction for DDRC register
void set_direction(unsigned char pin, unsigned char direction){
  
  if (direction){
    DDRC |= (1 << pin);      // Output
  }
  else{
    DDRC &= ~(1 << pin);     // Input
  }
}

//Function to toggle pin from PORTC
void toggle_pin(unsigned char pin){
  PORTC ^= (1 << pin);
}

void main( void )
{
  DDRD_DDRD5 = 1;
  DDRD_DDRD4 = 1;
  DDRA_DDRA3 = 1;
  
  set_direction(7,OUTPUT);
  
  while(1){
    
    toggle_pin(7);
    
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
