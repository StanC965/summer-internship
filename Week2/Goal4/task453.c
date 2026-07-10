//da , se poate vedea cu ochiul uman

#include <intrinsics.h>
#include "led.h"
#include "gpio.h"


#define PC1 1
#define PC6 6
#define INPUT 0

#define PA3 3
#define PD4 4
#define PD5 5

#define PCINT22 6
#define PCIE2 2

#define TOIE1 0

#define COM0A0 6
#define WGM01 1
#define CS00 0
#define OCIE0A 1
#define PB3 3
#define PC7 7
#define led0 0
#define led1 1
#define led3 3
#define led2 2
#define pop 5
#define PCINT17 1
#define PD4 4
#define ovf 15
#define prag1 1
#define prag2 5

int cntSec = 0;
int cnt = 0;

#pragma vector=PCINT2_vect
__interrupt void butInterrupt(void){
  if(!getPin(&PINC,PC6)){
    ledPowerOn(led1);
    setPin(&TCCR1B,CS00);
  }
  else{
    resetPin(&TCCR1B,CS00);
    ledPowerOff(led3);
            ledPowerOff(led1);
            ledPowerOff(led2);
            cntSec=0;
            TCNT1 = 0;
            
  }

}

#pragma vector=TIMER1_OVF_vect
__interrupt void myInterrupt(void){
    cnt++;
    if(cnt == ovf){
      cntSec++;
      if(cntSec >= prag1){
          if(cntSec <= prag2)
          {
            ledPowerOff(led1);
            ledPowerOn(led2);
          }
          else  {
            ledPowerOff(led2);
            ledPowerOn(led3);
          }
      }
      cnt=0;
    }

}


void main(void){
    setDirection(&DDRC,PC6,INPUT);
    setPin(&PORTC,PC6);
    setPin(&PCMSK2,PCINT22);
    setPin(&PCICR,PCIE2);
    ledInit(&DDRA,&PORTA,PA3);
    ledInit(&DDRD,&PORTD,PD4);
    ledInit(&DDRD,&PORTD,PD5);
    setPin(&TIMSK1,TOIE1);
    
    
    
    __enable_interrupt();
    while(1){
    }
}