#include "scheduler_cfg.h"
#include "pwm.h"
#include "button.h"
#include "adc.h"
#include "led.h"

static void state_blink_off(void);
static void state_blink_on(void);

static void (*current_blink_state)(void) = state_blink_off;

void scheduler_task_50ms(void)
{
    
}

void scheduler_task_100ms(void)
{
    
}

void scheduler_task_500ms(void)
{
    
}

void scheduler_task_1000ms(void)
{
    if (current_blink_state != 0)
    {
        current_blink_state();
    }
}

static void state_blink_off(void)
{
    led_power_on(LED_LED0_PORT, LED_LED0_PIN);
    
    current_blink_state = state_blink_on;
}

static void state_blink_on(void)
{
    led_power_off(LED_LED0_PORT, LED_LED0_PIN);
    
    current_blink_state = state_blink_off;
}