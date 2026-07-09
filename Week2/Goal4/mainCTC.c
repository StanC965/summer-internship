#include <intrinsics.h>
#include "iom324pb.h"
#include "gpio.h"

#define OCIE0A 1
#define WGM01 1
#define CS00 0
volatile unsigned char x;
#pragma vector=TIMER0_COMPA_vect
__interrupt void myInterrupt(void){
    
    x = TCNT0;
    
}

void main(void){
  TCNT0 = 0;
  OCR0A = 127;
  setPin(&TCCR0A,WGM01);
  setPin(&TIMSK0,OCIE0A);
  
  setPin(&TCCR0B,CS00);
  __enable_interrupt();
  
  while(1){
  }
}