#include <iom324pb.h>
#include <stdint.h>

#define INPUT 0
#define OUTPUT 1

void portc_set_pin(uint8_t pin){
  PORTC |= (1 << pin);
}

void portc_reset_pin(uint8_t pin){
  PORTC &= ~(1 << pin);
}

void ddrc_set_direction(uint8_t direction, uint8_t pin){
  DDRC = (direction == OUTPUT) ? (DDRC | (1 << pin)) : (DDRC & ~(1 << pin)); 
}

void portc_toggle_pin(uint8_t pin){
  PORTC ^= (1 << pin);
}

void delay(long count){
  for(long i = 0; i < count; i++);
}

void main (void){
  
  DDRD |= 1 << 5;
  DDRD |= 1 << 4;
  DDRA |= 1 << 3;
  ddrc_set_direction(OUTPUT, 7);
  DDRB |= 1 << 3;
  
  while(1){
    // INITIAL STATE:
    PORTD |= 1 << 5;
    PORTD |= 1 << 4;
    PORTA |= 1 << 3;
    portc_set_pin(7);
    PORTB |= 1 << 3;

    delay(50000);

    // STATE 1
    PORTD &= ~(1 << 5);

    delay(50000);

    // STATE 2
    PORTD |= 1 << 5;
    PORTD &= ~(1 << 4);

    delay(50000);

    // STATE 3
    PORTD |= 1 << 4;
    PORTA &= ~(1 << 3);

    delay(50000);

    // STATE 4
    PORTA |= 1 << 3;
    portc_reset_pin(7);

    delay(50000);

    // STATE 5
    portc_set_pin(7);
    PORTB &= ~(1 << 3);

    delay(50000);
    
    // STATE 6
    PORTB |= (1 << 3);
    portc_toggle_pin(7);
    
    delay(50000);
  }
  
}