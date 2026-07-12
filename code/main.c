#include <iom324pb.h>
#include "main.h" 

void main (void){
  
  gpio_set_direction(&DDRD, OUTPUT, 5);
  gpio_set_direction(&DDRD, OUTPUT, 4);
  gpio_set_direction(&DDRA, OUTPUT, 3);
  gpio_set_direction(&DDRC, OUTPUT, 7);
  gpio_set_direction(&DDRB, OUTPUT, 3);
  
  while(1){
    // INITIAL STATE:
    gpio_set_pin(&PORTD, 5);
    gpio_set_pin(&PORTD, 4);
    gpio_set_pin(&PORTA, 3);
    gpio_set_pin(&PORTC, 7);
    gpio_set_pin(&PORTB, 3);

    delay(50000);

    // STATE 1
    gpio_reset_pin(&PORTD, 5);

    delay(50000);

    // STATE 2
    gpio_set_pin(&PORTD, 5);
    gpio_reset_pin(&PORTD, 4);

    delay(50000);

    // STATE 3
    gpio_set_pin(&PORTD, 4);
    gpio_reset_pin(&PORTA, 3);

    delay(50000);

    // STATE 4
    gpio_set_pin(&PORTA, 3);
    gpio_reset_pin(&PORTC, 7);

    delay(50000);

    // STATE 5
    gpio_set_pin(&PORTC, 7);
    gpio_reset_pin(&PORTB, 3);

    delay(50000);
    
    // STATE 6
    gpio_set_pin(&PORTB, 3);
    gpio_toggle_pin(&PORTC, 7);
    
    delay(50000);
  }
  
}