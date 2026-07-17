#include "scheduler_cfg.h"
#include "led.h" 

void scheduler_task_50ms(void)
{
    led_power_on(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
}

void scheduler_task_100ms(void)
{
    led_power_on(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
}

void scheduler_task_500ms(void)
{
    led_power_on(LED_OLED_3_PORT, LED_OLED_3_PIN);
}

void scheduler_task_1000ms(void)
{
    led_power_off(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
    led_power_off(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
    led_power_off(LED_OLED_3_PORT, LED_OLED_3_PIN);
}