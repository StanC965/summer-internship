// 241 - CORE
#include <iom324pb.h>
#include "gpio.h"
void delay(unsigned long count){
  volatile unsigned long i;

  for (i = 0; i < count; i++){
      // Software delay
  }
}

void main( void )
{
  gpio_set_direction(&DDRD,5,GPIO_OUTPUT);
  gpio_set_direction(&DDRD,4,GPIO_OUTPUT);
  gpio_set_direction(&DDRA,3,GPIO_OUTPUT);
  
  gpio_set_direction(&DDRC,7,GPIO_OUTPUT);
  
  while(1){
    
    gpio_toggle_pin(&PORTC,7);
    
    gpio_set_pin(&PORTD,5);
    gpio_set_pin(&PORTD,4);
    gpio_set_pin(&PORTA,3);
    delay(250000UL);
    
    gpio_reset_pin(&PORTD,5);
    gpio_reset_pin(&PORTD,4);
    gpio_set_pin(&PORTA,3);
    delay(250000UL);

    gpio_set_pin(&PORTD,5);
    gpio_reset_pin(&PORTD,4);
    gpio_reset_pin(&PORTA,3);
    delay(250000UL);
    
    gpio_reset_pin(&PORTD,5);
    gpio_set_pin(&PORTD,4);
    gpio_reset_pin(&PORTA,3);
    delay(250000UL);

  }
}
