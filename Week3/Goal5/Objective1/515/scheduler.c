#include "scheduler.h"
#include "led.h"

volatile unsigned char scheduler_flag_50ms   = 0;
volatile unsigned char scheduler_flag_100ms  = 0;
volatile unsigned char scheduler_flag_500ms  = 0;
volatile unsigned char scheduler_flag_1000ms = 0;

void scheduler_init(void)
{
    scheduler_flag_50ms   = 0;
    scheduler_flag_100ms  = 0;
    scheduler_flag_500ms  = 0;
    scheduler_flag_1000ms = 0;
}

void scheduler_flags_management(void)
{
    static unsigned char scheduler_tick_counter = 0;

    scheduler_tick_counter++;

    if ((scheduler_tick_counter % 5) == 0)
    {
        scheduler_flag_50ms = 1;
    }

    if ((scheduler_tick_counter % 10) == 0)
    {
        scheduler_flag_100ms = 1;
    }

    if ((scheduler_tick_counter % 50) == 0)
    {
        scheduler_flag_500ms = 1;
    }

    if (scheduler_tick_counter >= 100)
    {
        scheduler_flag_1000ms = 1;
        scheduler_tick_counter = 0;
    }
}

void scheduler_tasks_dispatcher(void)
{
    while (1)
    {
        if (scheduler_flag_50ms)
        {
            scheduler_flag_50ms = 0; 
            scheduler_task_50ms();
        }

        if (scheduler_flag_100ms)
        {
            scheduler_flag_100ms = 0; 
            scheduler_task_100ms();
        }

        if (scheduler_flag_500ms)
        {
            scheduler_flag_500ms = 0; 
            scheduler_task_500ms();
        }

        if (scheduler_flag_1000ms)
        {
            scheduler_flag_1000ms = 0; 
            scheduler_task_1000ms();
        }
    }
}

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