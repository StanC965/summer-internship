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

  airbag_timer_configure();

  __enable_interrupt();

  while (1)
  {
    unsigned char status = 1;
    if ( status == CRASH)
    {
      airbag_timer_start();
      break;
    }
  }

  while (1)
  {
  }
}
