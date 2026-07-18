#include "main.h"
#include "led.h"
#include "button.h"
#include "sos.h"
#include "delay.h"
#include <intrinsics.h>
#include "adc.h"

extern volatile uint8_t light_sensor_value;

#define LIGHT_SENSOR_FULL_DARK    (255U)
#define LIGHT_SENSOR_SEMI_DARK    (170U)
#define LIGHT_SENSOR_SEMI_LIGHT   (85U)
#define LIGHT_SENSOR_FULL_LIGHT   (0U)

void main(void)
{
  led_init();
  adc_init();

  __enable_interrupt();

  while (1)
  {
    adc_start_conversion();
    if (light_sensor_value < LIGHT_SENSOR_SEMI_LIGHT)
    {
      led_power_on(LED_OLED1_1);
      led_power_on(LED_OLED1_2);
      led_power_on(LED_OLED1_3);
    }
    else if (light_sensor_value >= LIGHT_SENSOR_SEMI_LIGHT && light_sensor_value < LIGHT_SENSOR_SEMI_DARK)
    {
      led_power_on(LED_OLED1_1);
      led_power_on(LED_OLED1_2);
    }
     else if (light_sensor_value >= LIGHT_SENSOR_SEMI_DARK && light_sensor_value < LIGHT_SENSOR_FULL_DARK)
    {
      led_power_on(LED_OLED1_1);
    }
    else 
    {
      led_power_off(LED_OLED1_1);
      led_power_off(LED_OLED1_2);
      led_power_off(LED_OLED1_3);
    }
    // delay(1 * MILISECOND);
  }
}
