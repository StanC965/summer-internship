//626
#include "iom324pb.h"
#include <intrinsics.h>
#include "pwm.h"
#include "scheduler.h"

void timer1_init(void){
  TCCR1A=0X00;
  TCCR1B=0b00001001;
  OCR1A=9999;
  TIMSK1=0b00000010;
  __enable_interrupt();
}

#pragma vector=TIMER1_COMPA_vect
__interrupt void timer1_ISR(void){
  scheduler_flags_management();
}


void main( void )
{
  pwm_init();
  timer1_init();
  schedule_tasks_dispatcher();
}
