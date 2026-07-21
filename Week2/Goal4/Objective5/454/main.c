#include "timer.h"
#include "led.h"
#include "button.h"
#include "CarCrashDetection.h"
#include "intrinsics.h"

volatile unsigned char button_push_count = 0;

void clear_oled_leds(void);

#pragma vector = PCINT2_vect
__interrupt void pin_change_port_c_isr(void)
{
    if (button_is_pressed(BUTTON_SW0_PINR, BUTTON_SW0_PIN)) 
    {
        PORTD &= ~(1 << 6); 
    }
    else
    {
        PORTD |= (1 << 6);
    }
}

#pragma vector = TIMER1_CAPT_vect
__interrupt void timer1_input_capture_isr(void)
{
    button_push_count++;

    if (button_push_count == 4)
    {
        led_power_on(LED_OLED_1_2_PORT, LED_OLED_1_PIN);  
    }
    else if (button_push_count == 5)
    {
        led_power_on(LED_OLED_1_2_PORT, LED_OLED_2_PIN);  
    }
    else if (button_push_count == 6)
    {
        led_power_on(LED_OLED_3_PORT, LED_OLED_3_PIN);    
        button_push_count = 0;
    }
    else
    {
      clear_oled_leds();
    }
}

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
    init_system();
    
    timer_t1_init_icu();
    timer_start_t1(64);
    
    while (1)
    {
        
    }
}