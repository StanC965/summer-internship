#include "timer.h"
#include "led.h"
#include "button.h"
#include "scheduler.h"
#include "intrinsics.h"

void clear_oled_leds(void)
{
    led_power_off(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
    led_power_off(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
    led_power_off(LED_OLED_3_PORT, LED_OLED_3_PIN);
}

void init_system(void)
{
    gpio_init();
    timer_init();   
    led_init();
    button_init();
    scheduler_init();
        
    __enable_interrupt();
}

void main(void)
{
    init_system();
    
    timer_t3_init_system_tick();

    
    while (1)
    {
        if (scheduler_flag_50ms)
        {
            scheduler_flag_50ms = 0; 
            
            led_power_on(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
        }

        if (scheduler_flag_100ms)
        {
            scheduler_flag_100ms = 0; 
            
            led_power_on(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
        }

        if (scheduler_flag_500ms)
        {
            scheduler_flag_500ms = 0; 
            
            led_power_on(LED_OLED_3_PORT, LED_OLED_3_PIN);
        }

        if (scheduler_flag_1000ms)
        {
            scheduler_flag_1000ms = 0; 
            
            clear_oled_leds();
        }
    }
}