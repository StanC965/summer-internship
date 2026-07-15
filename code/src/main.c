#include "main.h"
#include "led.h"
#include "button.h"
#include "sos.h"
#include "delay.h"
#include <intrinsics.h>

extern volatile uint8_t button_event_detected;
volatile uint8_t sos_active = 0;

void main(void)
{
  led_init();
  button_init();
  button_enable_pullup(BUTTON_ONBOARD);
  button_onboard_init_interrupt();
  __enable_interrupt(); 

  while (1)
  {
    if (button_event_detected)
    {
      button_event_detected = 0;

      delay(10 * MILISECOND);

      if (!button_read(BUTTON_ONBOARD))
      {
        sos_active = !sos_active;

        if (!sos_active)
        {
          led_power_off(LED_ONBOARD);
        }
        while (!button_read(BUTTON_ONBOARD))
        {
          delay(10 * MILISECOND);
        }
      }
    }
    if (sos_active)
    {
      sos_update(LED_ONBOARD);
    }
    delay(1 * MILISECOND);
  }
}
