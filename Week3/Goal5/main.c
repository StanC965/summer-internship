//voi alege prescale 8 si OCR1A = 9999 pentru a avea exact 10 ms
#include <intrinsics.h>
#include "gpio.h"
#include "led.h"

#define WGM12 3
#define CS12 2
#define CS11 1
#define CS10 0
#define OCIE1A 1

#define COM1A 6
#define PD5 5

#pragma vector=TIMER1_COMPA_vect
__interrupt void myInterrupt(void){
  
  int a = 5;
}

void programInit(){
  TCNT1 = 0;
  OCR1A = 9999;
  
  ledInit(&DDRD,&PORTD,PD5);
  
  setPin(&TCCR1B,WGM12);
  setPin(&TIMSK1,OCIE1A);
  setPin(&TCCR1B,CS11);
  
  setPin(&TCCR1A,COM1A);
}

int main( void )
{
  
  programInit();
  __enable_interrupt();
  
  
  while(1){
  
  }
}
