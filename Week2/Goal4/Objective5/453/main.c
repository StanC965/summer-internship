#include "timer.h"
#include "led.h"
#include "button.h"
#include "CarCrashDetection.h"
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
    
    __enable_interrupt();
}

void main(void)
{
    unsigned char button_was_pressed = 0;
    unsigned int final_ticks = 0;
    
    init_system();
  
    
    while (1)
    {
        if (button_is_pressed(BUTTON_SW0_PINR, BUTTON_SW0_PIN))
        {
            if (!button_was_pressed)
            {
                button_was_pressed = 1;
                timer_start_t1(1024); 
            }
        }
        else
        {
            if (button_was_pressed)
            {
                timer_stop_t1();
                button_was_pressed = 0;
                
                final_ticks = TCNT1; 
                clear_oled_leds();
                
                if (final_ticks < 977) 
                {
                    led_power_on(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
                }
                else if (final_ticks >= 977 && final_ticks <= 4883) 
                {
                    led_power_on(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
                }
                else 
                {
                    led_power_on(LED_OLED_3_PORT, LED_OLED_3_PIN);
                }
            }
        }
    }
}