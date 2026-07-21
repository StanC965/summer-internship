#include "scheduler_cfg.h"
#include "adc.h"
#include "led.h"
#include "button.h"

#define MAX_BLINK_TOGGLES   8

static unsigned char bmw_panel_blocked = 0;
static unsigned char blink_active = 0;
static unsigned char blink_toggle_count = 0;

static unsigned char prev_sw0   = 0;
static unsigned char prev_oled1 = 0;
static unsigned char prev_oled2 = 0;
static unsigned char prev_oled3 = 0;

static void start_blink(void)
{
    if (!blink_active)
    {
        blink_toggle_count = 0;
        blink_active = 1;
    }
}

void scheduler_task_50ms(void)
{
    button_debounce_update();
}

void scheduler_task_100ms(void)
{
    unsigned char curr_sw0   = button_get_sw0_state();
    unsigned char curr_oled1 = button_get_oled1_state();
    unsigned char curr_oled2 = button_get_oled2_state();
    unsigned char curr_oled3 = button_get_oled3_state();
    
    if (curr_sw0 == 1 && prev_sw0 == 0)
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
            blink_active = 0; 
        }
    }
    
    if (curr_oled1 == 1 && prev_oled1 == 0)
    {
        if (bmw_panel_blocked)  start_blink();
        else                    led_toggle(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
    }
    
    if (curr_oled2 == 1 && prev_oled2 == 0)
    {
        if (bmw_panel_blocked)  start_blink();
        else                    led_toggle(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
    }
    
    if (curr_oled3 == 1 && prev_oled3 == 0)
    {
        if (bmw_panel_blocked)  start_blink();
        else                    led_toggle(LED_OLED_3_PORT, LED_OLED_3_PIN);
    }
    
    prev_sw0   = curr_sw0;
    prev_oled1 = curr_oled1;
    prev_oled2 = curr_oled2;
    prev_oled3 = curr_oled3;
}

void scheduler_task_500ms(void)
{
    if (blink_active)
    {
        led_toggle(LED_LED0_PORT, LED_LED0_PIN);
        blink_toggle_count++;
        
        if (blink_toggle_count >= MAX_BLINK_TOGGLES)
        {
            blink_active = 0;
            led_power_on(LED_LED0_PORT, LED_LED0_PIN); 
        }
    }
}

void scheduler_task_1000ms(void)
{
    
}