#include <intrinsics.h>
#include "iom324pb.h"
#include "gpio.h"
#include "led.h"

#define TOIE0 0
#define CS00 0
#define CS01 1
#define CS02 2
#define SecVarP1 3905
#define SecVarP2 500
#define SecVarP3 61
#define SecVarP4 15
#define SecVarP5 4
#define PC7 7
#define led0 0
#define PC6 6
#define INPUT 0
#define PCINT22 6
#define PCIE2 2 
int secV = SecVarP5;
int led0Status = 0;
int cnt = 0;
int sel = 0;
#pragma vector=PCINT2_vect
__interrupt void butInterrupt(void){
  if(!getPin(&PINC,PC6)){
    sel = (sel+1)%5;
    if(sel == 0){
      
      setPin(&TCCR0B,CS00);
      resetPin(&TCCR0B,CS01);
      resetPin(&TCCR0B,CS02);
      cnt = 0;
    }
    else
      if(sel == 1){
        
        resetPin(&TCCR0B,CS00);
      setPin(&TCCR0B,CS01);
      resetPin(&TCCR0B,CS02);
      cnt = 0;
      }
        else
          if(sel == 2){
           
            setPin(&TCCR0B,CS00);
            setPin(&TCCR0B,CS01);
            resetPin(&TCCR0B,CS02);
            cnt = 0;
          }
          else
            if(sel == 3){
              
              resetPin(&TCCR0B,CS00);
              resetPin(&TCCR0B,CS01);
              setPin(&TCCR0B,CS02);
              cnt = 0;
              
            }
            else
              if(sel == 4){
                
                setPin(&TCCR0B,CS00);
                resetPin(&TCCR0B,CS01);
                setPin(&TCCR0B,CS02);
                cnt = 0;
              }
  }
}

#pragma vector=TIMER0_OVF_vect
__interrupt void myInterrupt(void){
  cnt++;
  if(cnt == secV){
  led0Status ^= 1;
    if(led0Status == 1)
        ledPowerOn(led0);
    else
        ledPowerOff(led0);
    cnt = 0;
  }

}



int main( void )
{
  setDirection(&DDRC,PC6,INPUT);
  setPin(&PORTC,PC6);
  setPin(&PCMSK2,PCINT22);
  setPin(&PCICR,PCIE2);

  ledInit(&DDRC,&PORTC,PC7);
  setPin(&TIMSK0,TOIE0);

  setPin(&TCCR0B,CS00);
  __enable_interrupt();
  while(1){
  }
}
