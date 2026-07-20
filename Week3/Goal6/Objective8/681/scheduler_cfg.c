#include "scheduler_cfg.h"
#include "pwm.h"
#include "button.h"
#include "adc.h"
#include "led.h"

#define MAX_BLINK_TOGGLES   8

static void state_panel_unlocked(unsigned char sw0_edge, unsigned char oled_edge, unsigned char curr_oled1, unsigned char curr_oled2, unsigned char curr_oled3);
static void state_panel_blocked(unsigned char sw0_edge, unsigned char oled_edge, unsigned char curr_oled1, unsigned char curr_oled2, unsigned char curr_oled3);
static void state_panel_blinking(unsigned char sw0_edge, unsigned char oled_edge, unsigned char curr_oled1, unsigned char curr_oled2, unsigned char curr_oled3);

static void (*current_panel_state)(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char) = state_panel_unlocked;
static unsigned char blink_toggle_count = 0;

static unsigned char prev_sw0   = 0;
static unsigned char prev_oled1 = 0;
static unsigned char prev_oled2 = 0;
static unsigned char prev_oled3 = 0;

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
    
    unsigned char sw0_edge  = (curr_sw0 == 1 && prev_sw0 == 0);
    unsigned char oled_edge = ((curr_oled1 == 1 && prev_oled1 == 0) || 
                               (curr_oled2 == 1 && prev_oled2 == 0) || 
                               (curr_oled3 == 1 && prev_oled3 == 0));

    if (current_panel_state != 0)
    {
        current_panel_state(sw0_edge, oled_edge, curr_oled1, curr_oled2, curr_oled3);
    }
    
    prev_sw0   = curr_sw0;
    prev_oled1 = curr_oled1;
    prev_oled2 = curr_oled2;
    prev_oled3 = curr_oled3;
}

void scheduler_task_500ms(void)
{
    if (current_panel_state == state_panel_blinking)
    {
        led_toggle(LED_LED0_PORT, LED_LED0_PIN);
        blink_toggle_count++;
        
        if (blink_toggle_count >= MAX_BLINK_TOGGLES)
        {
            led_power_on(LED_LED0_PORT, LED_LED0_PIN);
            current_panel_state = state_panel_blocked;
        }
    }
}

void scheduler_task_1000ms(void)
{
    
}

static void state_panel_unlocked(unsigned char sw0_edge, unsigned char oled_edge, unsigned char curr_oled1, unsigned char curr_oled2, unsigned char curr_oled3)
{
    if (sw0_edge)
    {
        led_power_off(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
        led_power_off(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
        led_power_off(LED_OLED_3_PORT, LED_OLED_3_PIN);
        led_power_off(LED_IO_LED_PORT, LED_IO_LED_PIN);
        
        led_power_on(LED_LED0_PORT, LED_LED0_PIN);
        current_panel_state = state_panel_blocked;
    }
    else
    {
        if (curr_oled1 == 1 && prev_oled1 == 0) led_toggle(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
        if (curr_oled2 == 1 && prev_oled2 == 0) led_toggle(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
        if (curr_oled3 == 1 && prev_oled3 == 0) led_toggle(LED_OLED_3_PORT, LED_OLED_3_PIN);
    }
}

static void state_panel_blocked(unsigned char sw0_edge, unsigned char oled_edge, unsigned char curr_oled1, unsigned char curr_oled2, unsigned char curr_oled3)
{
    if (sw0_edge)
    {
        led_power_off(LED_LED0_PORT, LED_LED0_PIN);
        current_panel_state = state_panel_unlocked;
    }
    else if (oled_edge)
    {
        blink_toggle_count = 0;
        current_panel_state = state_panel_blinking;
    }
}

static void state_panel_blinking(unsigned char sw0_edge, unsigned char oled_edge, unsigned char curr_oled1, unsigned char curr_oled2, unsigned char curr_oled3)
{
    if (sw0_edge)
    {
        led_power_off(LED_LED0_PORT, LED_LED0_PIN);
        current_panel_state = state_panel_unlocked;
    }
}
