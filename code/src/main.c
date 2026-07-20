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

  schedule_task_dispatcher();
}
