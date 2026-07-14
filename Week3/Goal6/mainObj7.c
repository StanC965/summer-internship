#include "scheduler.h"
#include "led.h"

#define PC7 7
//avantajul principal pe care il vad eu in a folosii poiteri la functii este faptul ca fiecare stare are o functie proprie , iar astfel codul este modular


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
