// 236 - CORE
#include <iom324pb.h>

#define INPUT   0
#define OUTPUT  1

void delay(unsigned long count){
  volatile unsigned long i;

  for (i = 0; i < count; i++){
      // Software delay
  }
}

//Function tu set any pin from any PORT
void set_pin(volatile unsigned char *port, unsigned char pin){
  *port |= (1 << pin);
}

//Function tu reset any pin from any PORT
void reset_pin(volatile unsigned char *port, unsigned char pin){
  *port &= ~(1 << pin);
}

//Function tu set direction for DDRx
void set_direction(volatile unsigned char *ddr, unsigned char pin, unsigned char direction){
  direction ? (*ddr |= (1 << pin)) : (*ddr &= ~(1 << pin));
}

//Function to toggle pin from any PORT
void toggle_pin(volatile unsigned char *port, unsigned char pin){
  *port ^= (1 << pin);
}

void main( void )
{
  set_direction(&DDRD,5,OUTPUT);
  set_direction(&DDRD,4,OUTPUT);
  set_direction(&DDRA,3,OUTPUT);
  
  set_direction(&DDRC,7,OUTPUT);
  
  while(1){
    
    toggle_pin(&PORTC,7);
    
    set_pin(&PORTD,5);
    set_pin(&PORTD,4);
    set_pin(&PORTA,3);
    delay(250000UL);
    
    reset_pin(&PORTD,5);
    reset_pin(&PORTD,4);
    set_pin(&PORTA,3);
    delay(250000UL);

    set_pin(&PORTD,5);
    reset_pin(&PORTD,4);
    reset_pin(&PORTA,3);
    delay(250000UL);
    
    reset_pin(&PORTD,5);
    set_pin(&PORTD,4);
    reset_pin(&PORTA,3);
    delay(250000UL);

  }
}
