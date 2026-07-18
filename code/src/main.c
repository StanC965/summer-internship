#include "main.h"
#include "led.h"
#include "button.h"
#include "sos.h"
#include "delay.h"
#include <intrinsics.h>
#include "adc.h"

extern volatile uint8_t light_sensor_value;

#define LIGHT_SENSOR_MIDPOINT (127U)

void main(void)
{
  led_init();
  adc_init();

  __enable_interrupt();

  while (1)
  {
    adc_start_conversion();
    if (light_sensor_value < LIGHT_SENSOR_MIDPOINT)
    {
      led_power_on(LED_ONBOARD);
    }
    else
    {
      led_power_off(LED_ONBOARD);
    }
    // delay(1 * MILISECOND);
  }
}
