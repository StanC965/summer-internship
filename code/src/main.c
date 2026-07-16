#include "main.h"
#include "led.h"
#include "button.h"
#include "sos.h"
#include "delay.h"
#include <intrinsics.h>
#include <hvac_control.h>

void main(void)
{
  hvac_control_init();

  __enable_interrupt();

  while (1)
  {
    hvac_control_process();

    delay(1 * MILISECOND);
  }
}
