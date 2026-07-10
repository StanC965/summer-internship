//voi alege prescale 8 si OCR1A = 9999 pentru a avea exact 10 ms
#include <intrinsics.h>
#include "gpio.h"
#include "led.h"

#define WGM12 3
#define CS12 2
#define CS11 1
#define CS10 0
#define OCIE1A 1

#define PD4 4
#define COM1A 6
#define PD5 5

int flag10ms = 0;
int flag50ms = 0;
int flag100ms = 0;
int flag500ms = 0;
int flag1000ms = 0;

void schedulerFlasgsManagement(void){
  static unsigned char cnt50 = 0;
  static unsigned char cnt100 = 0;
  static unsigned short int cnt500 = 0;
  static unsigned short int cnt1000 = 0;
  flag10ms = 1;
  cnt50++;
  cnt100++;
  cnt500++;
  cnt1000++;
  if(cnt50 == 5){
    cnt50 = 0;
    flag50ms = 1;
    
  }
   if(cnt100 == 10){
    cnt100 = 0;
    flag100ms = 0;
  }
  if(cnt500 ==50){
    cnt500 = 0;
    flag500ms = 1;
  }
  
  if(cnt1000 == 100){
    cnt1000 = 0;
    flag1000ms = 1;
  }
}

#pragma vector=TIMER1_COMPA_vect
__interrupt void myInterrupt(void){
  
  schedulerFlasgsManagement();
}

void programInit(){
  TCNT1 = 0;
  OCR1A = 9999;
  

  ledInit(&DDRD,&PORTD,PD4);
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
