#include "main.h"
#include "led.h"
#include "button.h"
#include "sos.h"
#include "delay.h"
#include <intrinsics.h>
#include "adc.h"
#include "timer.h"
#include "CarCrashDetection.h"
#include "scheduler.h"
#include "pwm.h"

void main(void)
{
  led_init();
  pwm_init();
  timer1_init_10ms();
  
  __enable_interrupt();
  
  pwm_start();

  scheduler_tasks_dispatcher();
  
}
