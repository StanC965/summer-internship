#include "main.h"
#include "led.h"
#include "button.h"
#include "sos.h"
#include "delay.h"
#include <intrinsics.h>

extern volatile uint8_t button_event_detected[BUTTON_COUNT];
static uint8_t button_pressed[BUTTON_COUNT] = {0};
// volatile uint8_t sos_active = 0;

static const led_id_t button_to_led_map[BUTTON_COUNT] = {
    [BUTTON_ONBOARD] = LED_ONBOARD,
    [BUTTON_OLED1_1] = LED_OLED1_1,
    [BUTTON_OLED1_2] = LED_OLED1_2,
    [BUTTON_OLED1_3] = LED_OLED1_3};

void main(void)
{
  led_init();
  button_init();
  button_init_interrupt();

  __enable_interrupt();

  while (1)
  {
    for (uint8_t i = BUTTON_OLED1_1; i <= BUTTON_OLED1_3; i++)
    {
      if (button_event_detected[i])
      {
        button_event_detected[i] = 0;

        delay(10 * MILISECOND);

        if (!button_read(i) && !button_pressed[i])
        {
          button_pressed[i] = 1;
          led_power_on(button_to_led_map[i]);
        }
        else if (button_read(i) && button_pressed[i])
        {
          button_pressed[i] = 0;
          led_power_off(button_to_led_map[i]);
        }
      }
    }
    delay(1 * MILISECOND);
  }
}
