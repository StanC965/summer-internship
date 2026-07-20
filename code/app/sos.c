#ifndef SOS_C
#define SOS_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "sos.h"
#include "led.h"
#include "delay.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects & functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

static const step_t sos_sequence[] = {
    {1, 1},
    {0, 1},
    {1, 1},
    {0, 1},
    {1, 1},
    {0, 2},

    {1, 3},
    {0, 1},
    {1, 3},
    {0, 1},
    {1, 3},
    {0, 2},

    {1, 1},
    {0, 1},
    {1, 1},
    {0, 1},
    {1, 1},
    {0, 7},
};

static void sos_point(led_id_t led_id)
{
  led_blink_custom(led_id, 1, TIME_UNIT, TIME_UNIT);
}

static void sos_line(led_id_t led_id)
{
  led_blink_custom(led_id, 1, 3 * TIME_UNIT, TIME_UNIT);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void sos_update(led_id_t led_id)
{
  static uint8_t current_step = 0;
  static uint32_t state_timer_ms = 0;

  step_t step = sos_sequence[current_step];

  if (step.led_state)
  {
    led_power_on(led_id);
  }
  else
  {
    led_power_off(led_id);
  }

  state_timer_ms += MILISECOND;

  uint32_t target_duration = step.duration_units * TIME_UNIT;
  if (state_timer_ms >= target_duration)
  {
    state_timer_ms = 0;
    current_step++;

    if (current_step >= SOS_TOTAL_STEPS)
    {
      current_step = 0;
    }
  }
}

void sos_play(led_id_t led_id)
{
  sos_point(led_id);
  sos_point(led_id);
  sos_point(led_id);

  delay(2 * TIME_UNIT);

  sos_line(led_id);
  sos_line(led_id);
  sos_line(led_id);

  delay(2 * TIME_UNIT);

  sos_point(led_id);
  sos_point(led_id);
  sos_point(led_id);
}

#endif /* SOS_C */
