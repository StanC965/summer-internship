//da , se poate vedea cu ochiul uman

#include <intrinsics.h>
#include "led.h"
#include "gpio.h"
#include "CarCrashDetection.h"

#define PC1 1
#define PC6 6
#define INPUT 0

#define PCINT22 6
#define PCIE2 2

#define COM0A0 6
#define WGM01 1
#define CS00 0
#define OCIE0A 1
#define PB3 3
#define PC7 7
#define led0 0
#define led2 2
#define pop 5
#define PCINT17 1
#define PD4 4

int state = 0;
int cnt = 0;

#pragma vector=PCINT2_vect
__interrupt void buttonInterrupt(void){
  if(!getPin(&PINC,PC6)){
    if(GetCarCrashDetectionStatus() == CRASH){
        ledPowerOn(led0);
        setPin(&TCCR0B,CS00);
    }
    
  }
  if(!getPin(&PINC,PC1)){
    ledPowerOff(led0);
    ledPowerOff(led2);
  }
}

#pragma vector=TIMER0_COMPA_vect
__interrupt void myInterrupt(void){
      cnt ++;
      if(cnt == pop){
      ledPowerOn(led2);
      ledPowerOff(led0);
      resetPin(&TCCR0B,CS00);
      cnt=0;
      TCNT0 = 0;
      }

   

    

}

void main(void){
    OCR0A = 100;
    ledInit(&DDRD,&PORTD,PD4);
    ledInit(&DDRC,&PORTC,PC7);
    setDirection(&DDRC,PC1,INPUT);
    setPin(&PORTC,PC1);
    srand(31);
    setPin(&TCCR0A,WGM01);
    setPin(&TIMSK0,OCIE0A);
    setDirection(&DDRC,PC6,INPUT);
    setPin(&PCMSK2,PCINT17);
    
    setPin(&PORTC,PC6);
    setPin(&PCMSK2,PCINT22);
    setPin(&PCICR,PCIE2);
 
    __enable_interrupt();
    while(1){
    }
}