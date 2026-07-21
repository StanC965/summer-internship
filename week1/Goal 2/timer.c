#include "timer.h"


volatile unsigned int prescale=0;
static volatile int sec=0;
volatile unsigned int btn0=0;


__interrupt void led(){
  led0_set_state(ON);
  
}
void timer_init(){
  TCCR0A=0x42;
  OCR0A=0x5a;
  TIMSK0=0x02;
  SREG_I=1;
}
void change_prescale(){  
  prescale%=5;
  TCCR0B=prescale+1;
}
void prescale_init(){
  TCCR0B=0x02;
}
void change_led(){
 
 LedOn(&PORTB,PIN3);
    LedOn(&PORTC,PIN7);
    LedOn(&PORTD,PIN5);
    LedOn(&PORTD,PIN4);
    LedOn(&PORTA,PIN3);
 while(btn0==1){
   prescale_init();
  if(sec>0){
    LedOff(&PORTB,PIN3);
    if(sec>1)
    LedOff(&PORTA,PIN3);
    if(sec>2)
     LedOff(&PORTD,PIN4);
    if(sec>3)
    LedOff(&PORTD,PIN5);
    if(sec>4){
     LedOff(&PORTC,PIN7);
    }
    if(sec>5){
      sec=0;
    btn0=0;
    TCCR0B=0x00;}
    if(sec==0){
    LedOn(&PORTB,PIN1);
    LedOn(&PORTC,PIN7);
    LedOn(&PORTD,PIN5);
    LedOn(&PORTD,PIN4);
    LedOn(&PORTA,PIN3);
    
    }
    
  }
 }
 
 

 }


void airbag_dus(unsigned char airbag_status){
  if(airbag_status){
  prescale_init();
  }
}