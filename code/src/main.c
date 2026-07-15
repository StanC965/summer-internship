#include "main.h"
#include "led.h"
#include "button.h"
#include "sos.h"
#include "delay.h"
#include <intrinsics.h>

void main(void)
{
  led_init();
  button_init();
  button_enable_pullup(BUTTON_ONBOARD);

  button_onboard_init_interrupt();

  __enable_interrupt();

  while (1)
  {
  }
}