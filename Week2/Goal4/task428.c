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
#define led1 1
#define led2 2
#define led3 3
#define led4 4
#define PC6 6
#define PD4 4
#define PD5 5

#define PA3 3

#define PB3 3


#define INPUT 0
#define PCINT22 6
#define PCIE2 2 
int secV = SecVarP1;
int ledStatus = 0;
int cnt = 0;
int sel = 0;
#pragma vector=PCINT2_vect
__interrupt void butInterrupt(void){
  if(!getPin(&PINC,PC6)){
      setPin(&TCCR0B,CS00);
      ledPowerOn(led0);
      ledStatus = 0;
      ledPowerOff(led1);
      ledPowerOff(led2);ledPowerOff(led3);
      ledPowerOff(led4);
      cnt = 0;
  }
}

#pragma vector=TIMER0_OVF_vect
__interrupt void myInterrupt(void){
  cnt++;
  if(cnt == secV){
  ledStatus = ledStatus+1;
  if(ledStatus == 0){
      ledPowerOn(led0);
    }
    else
      if(ledStatus == 1){
        
        ledPowerOff(led0);
        ledPowerOn(led1);
      }
        else
          if(ledStatus == 2){
            ledPowerOff(led1);
          ledPowerOn(led2);
          }
          else
              if(ledStatus == 3){
            ledPowerOff(led2);
          ledPowerOn(led3);
          }
              else
                  if(ledStatus == 4){
            ledPowerOff(led3);
          ledPowerOn(led4);
          }
                  else{
                      ledPowerOff(led4);
                      resetPin(&TCCR0B,CS00);
                    }
    cnt = 0;
  }

}



int main( void )
{
  setDirection(&DDRC,PC6,INPUT);
  setPin(&PORTC,PC6);
  setPin(&PCMSK2,PCINT22);
  setPin(&PCICR,PCIE2);
  ledInit(&DDRA,&PORTA,PA3);
  ledInit(&DDRB,&PORTB,PB3);
  ledInit(&DDRD,&PORTD,PD5);
  ledInit(&DDRD,&PORTD,PD4);
  ledInit(&DDRC,&PORTC,PC7);
  setPin(&TIMSK0,TOIE0);


  __enable_interrupt();
  while(1){
  }
}
