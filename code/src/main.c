#include "main.h"
#include "led.h"
#include "button.h"
#include "sos.h"
#include "delay.h"
#include <intrinsics.h>
#include "adc.h"
#include "timer.h"

void main(void)
{
  led_init();
  timer_init_ctc();

  __enable_interrupt();

  timer_start_prescaler_64();

  while (1)
  {

  }
}
