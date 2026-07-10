

#include <intrinsics.h>
#include "led.h"
#define Var 1560
#define VarH 780
#define COM0A0 6
#define WGM01 1
#define CS00 0
#define OCIE0A 1
#define PB3 3
#define PC7 7
#define led0 0
int state = 0;
int cnt = 0;
int state = 0;
#pragma vector= TIMER0_COMPA_vect
__interrupt void myInterrupt(void){
    
   cnt++;
   if(cnt <= VarH){
     ledPowerOn(led0);
   }
   else
      ledPowerOff(led0);
   if(cnt == Var){
     
      
      
      cnt=0;
   
   }

    

}

void main(void){
    OCR0A = 127;
    
    ledInit(&DDRC,&PORTC,PC7);
    
    setPin(&TCCR0A,WGM01);
    setPin(&TIMSK0,OCIE0A);
    setPin(&TCCR0B,CS00);
 
    __enable_interrupt();
    while(1){
    }
}