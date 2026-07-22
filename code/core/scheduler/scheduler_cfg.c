#ifndef SCHEDULER_CFG_C
#define SCHEDULER_CFG_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "scheduler_cfg.h"
#include "adc.h"
#include "led.h"
#include "button.h"
#include "hvac_control.h"
#include "pwm.h"
#include "lighting.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects & functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void task_10ms(void)
{
  button_debounce_update();
  
  if(button_was_pressed(BUTTON_ONBOARD))
  {
    lighting_trigger_entry_phase();
  }
}

void task_50ms(void)
{
}

void task_100ms(void)
{
    pwm_sequence_update();
}

void task_200ms(void)
{
    lighting_entry_phase_update();
}

void task_500ms(void)
{
}

void task_1000ms(void)
{
}

#endif /* SCHEDULER_CFG_C */
