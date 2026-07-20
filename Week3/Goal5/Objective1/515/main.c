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
    
    scheduler_tasks_dispatcher();
}