#include <iom324pb.h>

void delay(long count){
  for(long i = 0; i < count; i++);
}

void main (void){
  DDRD |= 1 << 5;
  DDRD |= 1 << 4;
  DDRA |= 1 << 3;
  
  while(1){
    // INITIAL STATE:
    PORTD |= 1 << 5;
    PORTD |= 1 << 4;
    PORTA |= 1 << 3;

    delay(50000);

    // STATE 1
    PORTD &= ~(1 << 5);
    PORTD &= ~(1 << 4);
    PORTA |= 1 << 3;

    delay(50000);

    // STATE 2
    PORTD |= 1 << 5;
    PORTD &= ~(1 << 4);
    PORTA &= ~(1 << 3);

    delay(50000);

    // STATE 3
    PORTD &= ~(1 << 5);
    PORTD |= 1 << 4;
    PORTA &= ~(1 << 3);

    delay(50000);
  }
  
}