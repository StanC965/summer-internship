//425
#include "iom324.h"
#include "led.h"
#include "gpio.h"
#include <intrinsics.h>

#define LED0_PIN 7 //pc7
#define OUTPUT 1

volatile unsigned char contor=0;

void timer0_init(void){
  TCCR0A=0b00000000; //COM0A[1:0]- no compare mode, COM0B[1:0]- normal mode operation, 0x00 , WGM0[1:0]-normal mode operation
  TIMSK0=0b00000001; //Overflow Interrupt Enable
  TCCR0B=0b00000101; //FOC0A[1:0]- normal mode, 0x00, WGM0[2], CS0[2:0]=101- prescale cu 1024
  __enable_interrupt();
}

void led0_init(void){
  Init_LED(&DDRC,LED0_PIN,OUTPUT);
  set_pin(&PORTC,LED0_PIN);
}

#pragma vector=TIMER0_OVF_vect
__interrupt void timer0_ovf_interrupt(void){
  contor++;
  if(contor==4){ //262ms*4 = 1048 ms, adica aproximativ 1 secunda
    contor=0;
    Toggle_LED(&PORTC,LED0_PIN);
    
  }
}
void main( void )
{
  led0_init();
  timer0_init();
  while(1);
}
