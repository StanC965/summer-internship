#include <intrinsics.h>
#include "iom324pb.h"
#include "gpio.h"
#include "led.h"

#define TOIE0 0
#define CS00 0
#define CS02 2
#define SecVar 3905
#define PC7 7
#define led0 0

int led0Status = 0;
int cnt = 0;
#pragma vector=TIMER0_OVF_vect
__interrupt void myInterrupt(void){
  cnt++;
  if(cnt == SecVar){
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
  TCCR0A = 0;
TCCR0B = 0;
TCNT0 = 0;
  ledInit(&DDRC,&PORTC,PC7);
  setPin(&TIMSK0,TOIE0);

  setPin(&TCCR0B,CS00);
  __enable_interrupt();
  while(1){
  }
}
