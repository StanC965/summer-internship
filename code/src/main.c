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

  timer1_init_ctc_100ms();
  timer1_enable_compare_a_interrupt();

  __enable_interrupt();

  while (1)
  {
  }
}
