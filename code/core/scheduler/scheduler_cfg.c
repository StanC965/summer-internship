#ifndef SCHEDULER_CFG_C
#define SCHEDULER_CFG_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "scheduler_cfg.h"
#include "adc.h"
#include "led.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects & functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void task_10ms(void)
{
}

void task_50ms(void)
{
}

void task_100ms(void)
{
    adc_result_t light_sensor_value = adc_get_data();

    if (light_sensor_value < LIGHT_SENSOR_SEMI_LIGHT)
    {
        led_power_on(LED_OLED1_1);
        led_power_on(LED_OLED1_2);
        led_power_on(LED_OLED1_3);
    }
    else if (light_sensor_value >= LIGHT_SENSOR_SEMI_LIGHT && light_sensor_value < LIGHT_SENSOR_SEMI_DARK)
    {
        led_power_on(LED_OLED1_1);
        led_power_on(LED_OLED1_2);
    }
    else if (light_sensor_value >= LIGHT_SENSOR_SEMI_DARK && light_sensor_value < LIGHT_SENSOR_FULL_DARK)
    {
        led_power_on(LED_OLED1_1);
    }
    else
    {
        led_power_off(LED_OLED1_1);
        led_power_off(LED_OLED1_2);
        led_power_off(LED_OLED1_3);
    }

    adc_start_conversion();
}

void task_500ms(void)
{
}

void task_1000ms(void)
{

}

#endif /* SCHEDULER_CFG_C */
