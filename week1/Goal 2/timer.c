#include "timer.h"

volatile unsigned int prescale=0;
__interrupt void led(){
  i++;
  if(i==4){
    toggle_pin(&PORTC,PIN7);
    i=0;
  }
}
void timer_init(){
  TCCR0A=0x00;
  OCR0A=0xff;
  TIMSK0=0x01;
  SREG_I=1;
}
void change_prescale(){  
  prescale%=5;
  TCCR0B=prescale+1;
  
  
}