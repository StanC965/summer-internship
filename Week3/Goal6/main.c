#include "scheduler.h"
#include "led.h"

#define PC7 7


#pragma vector = TIMER1_COMPA_vect
__interrupt void myInterrupt(void){
    schedulerFlasgsManagement();

}

void main( void )
{
  ledInit(&DDRC,&PORTC,PC7);
  SREG |= 1<<7;
  scheduleTaskDispatcher();
}
