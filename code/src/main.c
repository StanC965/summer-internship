#include "main.h"
#include "led.h"
#include "button.h"
#include "sos.h"
#include "delay.h"
#include <intrinsics.h>
#include "adc.h"
#include "timer.h"
#include "CarCrashDetection.h"

void main(void)
{
  led_init();

  timer1_();

  __enable_interrupt();

  while (1)
  {
    if (scheduler_flag_10ms)
    {
      scheduler_flag_10ms = 0;
    }

    if (scheduler_flag_50ms)
    {
      scheduler_flag_50ms = 0;
    }

    if (scheduler_flag_100ms)
    {
      scheduler_flag_100ms = 0;
    }

    if (scheduler_flag_500ms)
    {
      scheduler_flag_500ms = 0;
    }

    if (scheduler_flag_1000ms)
    {
      scheduler_flag_1000ms = 0;
    }
  }
}
