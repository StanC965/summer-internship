#include "scheduler_cfg.h"
#include "adc.h"
#include "led.h"
#include "button.h"

#define THRESHOLD_SEMI_DARK      (ADC_MAX_VAL / 4)  
#define THRESHOLD_SEMI_LIGHT     (ADC_MAX_VAL / 2)     
#define THRESHOLD_FULL_LIGHT     ((ADC_MAX_VAL * 3) / 4)

void scheduler_task_50ms(void)
{
    button_debounce_update();
}

void scheduler_task_100ms(void)
{
    if (button_get_debounced_state() == 1)
    {
        led_toggle(LED_LED0_PORT, LED_LED0_PIN);
    }
}

void scheduler_task_500ms(void)
{
    
}

void scheduler_task_1000ms(void)
{
    
}