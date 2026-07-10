#include <intrinsics.h>
#include "iom324pb.h"
#include "gpio.h"

#define TOIE0 0
#define CS00 0
//423
//MIN = 0.000256
//MAX = 0.262144

//424
//Nu se creeaza o deviatie a timpului asa mare incat se poate calcula timpul exact
#pragma vector=TIMER0_OVF_vect
__interrupt void myInterrupt(void){
  unsigned int a = 0;

}



int main( void )
{
  setPin(&TIMSK0,TOIE0);
  setPin(&TCCR0B,CS00);
  __enable_interrupt();
  while(1){
  }
}
