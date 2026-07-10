//voi alege prescale 8 si OCR1A = 9999 pentru a avea exact 10 ms
#include <intrinsics.h>
#include "gpio.h"
#include "led.h"

#define WGM12 3
#define CS12 2
#define CS11 1
#define CS10 0

#pragma vector=TIMER1_COMPA_vect
__interrupt void myInterrupt(void){
}

int main( void )
{
  TCNT1 = 0;
  OCR1A = 9999;
  
  setPin(&TCCR1B,WGM12);
  
  __enable_interrupt();
  
  
  while(1){
  
  }
}
