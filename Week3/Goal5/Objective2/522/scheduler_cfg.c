#include "scheduler_cfg.h"
#include "adc.h"
#include "led.h"

#define THRESHOLD_SEMI_DARK      (ADC_MAX_VAL / 4)  
#define THRESHOLD_SEMI_LIGHT     (ADC_MAX_VAL / 2)     
#define THRESHOLD_FULL_LIGHT     ((ADC_MAX_VAL * 3) / 4)

void scheduler_task_50ms(void)
{
    adc_start_conversion();
}

void scheduler_task_100ms(void)
{
    adc_result_t current_light_level = adc_get_data();

    if (current_light_level >= THRESHOLD_FULL_LIGHT)
    {
        led_power_on(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
        led_power_on(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
        led_power_on(LED_OLED_3_PORT, LED_OLED_3_PIN); 
    }
    else if (current_light_level >= THRESHOLD_SEMI_LIGHT)
    {
        led_power_on(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
        led_power_on(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
        led_power_off(LED_OLED_3_PORT, LED_OLED_3_PIN);
    }
    else if (current_light_level >= THRESHOLD_SEMI_DARK)
    {
        led_power_on(LED_OLED_1_2_PORT, LED_OLED_1_PIN); 
        led_power_off(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
        led_power_off(LED_OLED_3_PORT, LED_OLED_3_PIN); 
    }
    else
    {
        led_power_off(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
        led_power_off(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
        led_power_off(LED_OLED_3_PORT, LED_OLED_3_PIN);
    }
}

void scheduler_task_500ms(void)
{
    
}

void scheduler_task_1000ms(void)
{
    
}