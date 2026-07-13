//433
// 100ms/2=50ms
// 50ms= prescaler*(OCR0A+1)/1M, cea mai buna varianta e prescaler=256 si OCR0A=50000/256 -1=194.31 (impartita la 2 este aprox 100ms)
#include "iom324.h"
#include "led.h"
#include "gpio.h"
#include <intrinsics.h>

#define OC0A_PIN 3 //pb3 - LED-ul de pe placa IO1
#define LED0_PIN 7 //pc7
#define SW0_PIN 6 //pc6
#define OUTPUT 1
#define INPUT 0

void timer0_init(void){
  TCCR0A=0b01000010; //COM0A[1:0]=01, COM0B[1:0]- normal mode operation, 0x00 , WGM0[1:0]=10 -toggle OC0A on compare match
  OCR0A=194;
  TIMSK0=0b00000010; //Overflow Interrupt Enable
  TCCR0B=0b00000100; //prescale 256
  __enable_interrupt();
}

void leds_init(void){
  Init_LED(&DDRC,LED0_PIN,OUTPUT);
  reset_pin(&PORTC,LED0_PIN);
  set_direction(&DDRB,OC0A_PIN,OUTPUT);
  reset_pin(&PORTB,OC0A_PIN);
  
}


#pragma vector=TIMER0_COMPA_vect
__interrupt void timer0_compa_interrupt(void){
    Toggle_LED(&PORTC,LED0_PIN);

}
void main( void )
{
  leds_init();
  timer0_init();
  while(1);
}
