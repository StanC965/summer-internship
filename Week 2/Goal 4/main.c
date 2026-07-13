//431-432
//Ambele leduri clipesc sincron prin resetarea pinilor la initializare
//(1024*128)/1M=0.131072 s
// putem folosi alti factori de prescalare, si inlocuim in formula 1024 cu 256,64,8 sau 1
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
  OCR0A=127;
  TIMSK0=0b00000010; //Overflow Interrupt Enable
  TCCR0B=0b00000101;
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
