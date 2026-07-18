#include "main.h"
#include "led.h"
#include "button.h"
#include "sos.h"
#include "delay.h"
#include <intrinsics.h>
#include "adc.h"

void main(void)
{
  adc_init();
  
  __enable_interrupt();

  while (1)
  {
    adc_trigger_conversion();
    delay(1 * MILISECOND);
  }
}
