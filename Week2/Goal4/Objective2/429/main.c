#include "timer.h"
#include "led.h"
#include "button.h"
#include "intrinsics.h"

#define TIMER_T0_BLINK_INTERVAL      5    
#define TIMER_T0_MAX_BLINK_TOGGLES   8     

volatile unsigned char bmw_panel_blocked = 0;

volatile unsigned char timer_blink_active = 0;
volatile unsigned char timer_blink_tick_count = 0;
volatile unsigned char timer_blink_toggle_count = 0;

void start_blink(void);

#pragma vector = TIMER0_OVF_vect
__interrupt void timer_t0_overflow_isr(void)
{
    if (timer_blink_active)
    {
        timer_blink_tick_count++;
        
        if (timer_blink_tick_count >= TIMER_T0_BLINK_INTERVAL)
        {
            timer_blink_tick_count = 0;
            
            led_toggle(LED_LED0_PORT, LED_LED0_PIN);
            timer_blink_toggle_count++;
            
            if (timer_blink_toggle_count >= TIMER_T0_MAX_BLINK_TOGGLES)
            {
                timer_blink_active = 0;
                timer_stop_t0();
                
                led_power_on(LED_LED0_PORT, LED_LED0_PIN);
            }
        }
    }
}

#pragma vector = PCINT2_vect
__interrupt void button_sw0_pcint_isr(void)
{
    if (button_is_pressed(BUTTON_SW0_PINR, BUTTON_SW0_PIN))
    {
        bmw_panel_blocked = !bmw_panel_blocked;
        
        if (bmw_panel_blocked)
        {
            led_power_off(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
            led_power_off(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
            led_power_off(LED_OLED_3_PORT, LED_OLED_3_PIN);
            led_power_off(LED_IO_LED_PORT, LED_IO_LED_PIN);
            
            led_power_on(LED_LED0_PORT, LED_LED0_PIN);
        }
        else
        {
            led_power_off(LED_LED0_PORT, LED_LED0_PIN);
        }
        return;
    }
    
    // OLED Button 1 
    if (button_is_pressed(BUTTON_OLED_1_PINR, BUTTON_OLED_1_PIN))
    {
        if (bmw_panel_blocked)
        {
            start_blink();
        }
        else
        {
            led_toggle(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
        }
    }
}

#pragma vector = PCINT0_vect
__interrupt void oled_port_a_isr(void)
{
    if (button_is_pressed(BUTTON_OLED_2_3_PINR, BUTTON_OLED_2_PIN))
    {
        if (bmw_panel_blocked)
        {
            start_blink();
        }
        else
        {
            led_toggle(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
        }
    }

    if (button_is_pressed(BUTTON_OLED_2_3_PINR, BUTTON_OLED_3_PIN))
    {
        if (bmw_panel_blocked)
        {
            start_blink();
        }
        else
        {
            led_toggle(LED_OLED_3_PORT, LED_OLED_3_PIN);
        }
    }
}

void start_blink(void)
{
    if (!timer_blink_active)
    {
        timer_blink_tick_count = 0;
        timer_blink_toggle_count = 0;
        timer_blink_active = 1;
        
        timer_start_t0(256);
    }
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