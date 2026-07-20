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
  pwm_start();

  __enable_interrupt();

  while (1)
  {
    pwm_set_duty_cycle(100);
    delay(3 * SECOND);

    pwm_set_duty_cycle(75);
    delay(3 * SECOND);

    pwm_set_duty_cycle(50);
    delay(3 * SECOND);

    pwm_set_duty_cycle(25);
    delay(3 * SECOND);

    pwm_set_duty_cycle(0);
    delay(3 * SECOND);
  }
}
