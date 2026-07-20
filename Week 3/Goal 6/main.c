#include "iom324pb.h"
#include "pwm.h"

void main( void )
{
  pwm_init();
  //pwm_set_duty_cycle(100);
  pwm_set_duty_cycle(75);
  //pwm_set_duty_cycle(50);
  //pwm_set_duty_cycle(25);
  //pwm_set_duty_cycle(0);
}
