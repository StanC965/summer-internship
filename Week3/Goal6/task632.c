#include "pwm.h"
#include "iom324pb.h"
#include "scheduler.h"

#pragma vector = TIMER1_COMPA_vect
__interrupt void myInterrupt(void){
  schedulerFlasgsManagement();
}

void main( void )
{
  initializePwm();
  startPwm(1);
  setPwmDc(0);
  SREG |= 1<<7;
  scheduleTaskDispatcher();
}