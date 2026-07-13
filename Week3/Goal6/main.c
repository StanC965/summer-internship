#include "pwm.h"
#include "iom324pb.h"

void main( void )
{
  initializePwm();
  startPwm(1);
  SREG |= 1<<7;
  while(1){
    pwmSetDutyCycle(100);

    for(long i=0;i<500000;i++);

    pwmSetDutyCycle(75);

    for(long i=0;i<500000;i++);

    pwmSetDutyCycle(50);

    for(long i=0;i<500000;i++);

    pwmSetDutyCycle(25);

    for(long i=0;i<500000;i++);

    pwmSetDutyCycle(0);

    for(long i=0;i<500000;i++);
}
    
  
}
