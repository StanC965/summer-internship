#include "timer.h"
#include <iom324pb.h>



volatile int sec=0;


void Timer1_Scheduler_Init(void)
{
    TCCR1A = 0x00; 
    TCCR1B = 0x08; 
    OCR1A = 1249; 
    TIMSK1 |= 0x02;
    TCCR1B |= 0x03;
    TCNT1 = 0;
}
void PWM_TC1_Init(void)
{
    DDRD |= 0x20;
   TCCR1A = 0x83;
    TCCR1B = 0x0b;
    OCR1A = 512;
    TCNT1 = 0x0000;
}
void PWM_TC1_SetDutyCycle(unsigned int duty)
{
    
    if (duty > 1023) 
    {
        duty = 1023;
    }
    OCR1A = duty; 
}

void timer_init(){
  TCCR0A=0x00;
  OCR0A=0x5a;
  TIMSK0=0x02;
  SREG_I=1;
}

void prescale_init(){
  TCCR0B=0x05;
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