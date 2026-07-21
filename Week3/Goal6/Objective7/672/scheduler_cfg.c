#include "scheduler_cfg.h"
#include "pwm.h"
#include "button.h"
#include "adc.h"
#include "led.h"

typedef enum {
    STATE_BLINK_OFF,
    STATE_BLINK_ON
} blink_state_t;

static blink_state_t led0_blink_state = STATE_BLINK_OFF;

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
    switch (led0_blink_state)
    {
        case STATE_BLINK_OFF:
            led_power_on(LED_LED0_PORT, LED_LED0_PIN);
            
            led0_blink_state = STATE_BLINK_ON;
            break;

        case STATE_BLINK_ON:
            led_power_off(LED_LED0_PORT, LED_LED0_PIN);
            
            led0_blink_state = STATE_BLINK_OFF;
            break;

        default:
            led_power_off(LED_LED0_PORT, LED_LED0_PIN);
            led0_blink_state = STATE_BLINK_OFF;
            break;
    }
}