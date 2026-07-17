#include "scheduler.h"
#include "led.h"

volatile unsigned char scheduler_flags = 0x00;

void scheduler_init(void)
{
    scheduler_flags = 0x00;
}

void scheduler_flags_management(void)
{
    static unsigned char scheduler_tick_counter = 0;

    scheduler_tick_counter++;

    if ((scheduler_tick_counter % 5) == 0)
    {
        scheduler_flags |= (1 << SCHEDULER_BIT_50MS);
    }

    if ((scheduler_tick_counter % 10) == 0)
    {
        scheduler_flags |= (1 << SCHEDULER_BIT_100MS);
    }

    if ((scheduler_tick_counter % 50) == 0)
    {
        scheduler_flags |= (1 << SCHEDULER_BIT_500MS);
    }

    if (scheduler_tick_counter >= 100)
    {
        scheduler_flags |= (1 << SCHEDULER_BIT_1000MS); 
        scheduler_tick_counter = 0;
    }
}

void scheduler_tasks_dispatcher(void)
{
    while (1)
    {
        if (scheduler_flags & (1 << SCHEDULER_BIT_50MS))
        {
            scheduler_flags &= ~(1 << SCHEDULER_BIT_50MS);
            scheduler_task_50ms();
        }

        if (scheduler_flags & (1 << SCHEDULER_BIT_100MS))
        {
            scheduler_flags &= ~(1 << SCHEDULER_BIT_100MS);
            scheduler_task_100ms();
        }

        if (scheduler_flags & (1 << SCHEDULER_BIT_500MS))
        {
            scheduler_flags &= ~(1 << SCHEDULER_BIT_500MS);
            scheduler_task_500ms();
        }

        if (scheduler_flags & (1 << SCHEDULER_BIT_1000MS))
        {
            scheduler_flags &= ~(1 << SCHEDULER_BIT_1000MS);
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