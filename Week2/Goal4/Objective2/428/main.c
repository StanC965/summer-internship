#include "timer.h"
#include "led.h"
#include "button.h"
#include "intrinsics.h"

#define TIMER_T0_TARGET_OVERFLOWS    16

volatile unsigned long timer_t0_overflow_count = 0;

volatile unsigned char countdown_active = 0;
volatile unsigned char seconds_remaining = 5;

void update_countdown_leds(unsigned char seconds);

#pragma vector = TIMER0_OVF_vect
__interrupt void timer_t0_overflow_isr(void)
{
    if (countdown_active)
    {
        timer_t0_overflow_count++;
        
        if (timer_t0_overflow_count >= TIMER_T0_TARGET_OVERFLOWS)
        {
            timer_t0_overflow_count = 0;
            
            if (seconds_remaining > 0)
            {
                seconds_remaining--;
                update_countdown_leds(seconds_remaining);
            }
            else
            {
                countdown_active = 0;
                timer_stop_t0();
            }
        }
    }
}

#pragma vector = PCINT2_vect
__interrupt void button_sw0_pcint_isr(void)
{
    if (button_is_pressed(BUTTON_SW0_PINR, BUTTON_SW0_PIN))
    {
        seconds_remaining = 5;
        timer_t0_overflow_count = 0;
        countdown_active = 1;
        
        update_countdown_leds(seconds_remaining);
        
        timer_start_t0(256);
    }
}

void update_countdown_leds(unsigned char seconds)
{
    led_power_off(LED_LED0_PORT, LED_LED0_PIN);
    led_power_off(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
    led_power_off(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
    led_power_off(LED_OLED_3_PORT, LED_OLED_3_PIN);
    led_power_off(LED_IO_LED_PORT, LED_IO_LED_PIN);

    if (seconds >= 1) led_power_on(LED_LED0_PORT, LED_LED0_PIN);
    if (seconds >= 2) led_power_on(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
    if (seconds >= 3) led_power_on(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
    if (seconds >= 4) led_power_on(LED_OLED_3_PORT, LED_OLED_3_PIN);
    if (seconds >= 5) led_power_on(LED_IO_LED_PORT, LED_IO_LED_PIN);
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
    init_system();
  
    
    while (1)
    {
        
    }
}