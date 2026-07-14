//441
#include "iom324.h"
#include "led.h"
#include "gpio.h"
#include "CarCrashDetection.h"
#include <intrinsics.h>

#define SW0_PIN 6 //pc6
#define AIRBAG_LED0_PIN 7 //pc7
#define OUTPUT 1
#define INPUT 0

void timer0_init(void){
  TCCR0A=0b00000010; //COM0A[1:0]=01, COM0B[1:0]- normal mode operation, 0x00 , WGM0[1:0]=10 -toggle OC0A on compare match
  OCR0A=87;// 700=(8*(OCR0A+1))/1M => OCR0A=88-1=87
  TIMSK0=0b00000010; //Overflow Interrupt Enable
  TCCR0B=0b00000000; //prescale 0 - timer oprit
  __enable_interrupt();
}

void airbag_init(void){
  Init_LED(&DDRC,AIRBAG_LED0_PIN,OUTPUT);
  set_pin(&PORTC,AIRBAG_LED0_PIN);
  set_direction(&DDRC, SW0_PIN, INPUT);
  set_pin(&PORTC, SW0_PIN);
}


#pragma vector=TIMER0_COMPA_vect
__interrupt void timer0_compa_interrupt(void){
  reset_pin(&PORTC, AIRBAG_LED0_PIN); //declansarea airbag-ului
  TCCR0B=0b00000000; //oprim timer ul
}
void main( void )
{
  airbag_init();
  timer0_init();
  unsigned char airbag=0;
  while(1){
    if(read_pin(&PINC, SW0_PIN)==0 && airbag==0){
      airbag=1;
      TCNT0=0; //incepe numaratoarea
      TCCR0B=0b00000010;
    }
  }
}