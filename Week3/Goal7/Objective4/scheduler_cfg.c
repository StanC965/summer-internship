#include "scheduler_cfg.h"
#include "pwm.h"
#include "button.h"
#include "adc.h"
#include "led.h"
#include "uart.h"

#define MAX_BLINK_TOGGLES 8

typedef enum {
    STATE_PANEL_UNLOCKED,
    STATE_PANEL_BLOCKED,
    STATE_PANEL_BLINKING
} panel_state_t;

static panel_state_t current_state = STATE_PANEL_UNLOCKED;
static unsigned char blink_toggle_count = 0;

static unsigned char mcu1_target_leds = 0x00;

static unsigned char prev_sw0   = 0;
static unsigned char prev_oled1 = 0;
static unsigned char prev_oled2 = 0;
static unsigned char prev_oled3 = 0;

static void v_mcu1_master_process_inputs(void);
static void v_mcu1_master_send_command(void);
static void v_mcu2_slave_process_and_drive(void);

void scheduler_task_50ms(void)
{    
    button_debounce_update();
    
    v_mcu2_slave_process_and_drive();
}

void scheduler_task_100ms(void)
{
    v_mcu1_master_process_inputs();
    
    v_mcu1_master_send_command();
}

void scheduler_task_500ms(void)
{
    if (current_state == STATE_PANEL_BLINKING)
    {
        mcu1_target_leds ^= (1 << 3);
        blink_toggle_count++;

        if (blink_toggle_count >= MAX_BLINK_TOGGLES)
        {
            mcu1_target_leds = (1 << 3);
            current_state = STATE_PANEL_BLOCKED;
        }
    }
}

void scheduler_task_1000ms(void)
{
    
}

static void v_mcu1_master_process_inputs(void)
{
    unsigned char curr_sw0   = button_get_sw0_state();
    unsigned char curr_oled1 = button_get_oled1_state();
    unsigned char curr_oled2 = button_get_oled2_state();
    unsigned char curr_oled3 = button_get_oled3_state();

    unsigned char sw0_edge  = (curr_sw0 == 1 && prev_sw0 == 0);
    unsigned char oled_edge = ((curr_oled1 == 1 && prev_oled1 == 0) ||
                               (curr_oled2 == 1 && prev_oled2 == 0) ||
                               (curr_oled3 == 1 && prev_oled3 == 0));

    switch (current_state)
    {
        case STATE_PANEL_UNLOCKED:
            if (sw0_edge)
            {
                mcu1_target_leds = (1 << 3);
                current_state = STATE_PANEL_BLOCKED;
            }
            else
            {
                if (curr_oled1 == 1 && prev_oled1 == 0) mcu1_target_leds ^= (1 << 0);
                if (curr_oled2 == 1 && prev_oled2 == 0) mcu1_target_leds ^= (1 << 1);
                if (curr_oled3 == 1 && prev_oled3 == 0) mcu1_target_leds ^= (1 << 2);
            }
            break;

        case STATE_PANEL_BLOCKED:
            if (sw0_edge)
            {
                mcu1_target_leds = 0x00;
                current_state = STATE_PANEL_UNLOCKED;
            }
            else if (oled_edge)
            {
                blink_toggle_count = 0;
                current_state = STATE_PANEL_BLINKING;
            }
            break;

        case STATE_PANEL_BLINKING:
            if (sw0_edge)
            {
                mcu1_target_leds = 0x00;
                current_state = STATE_PANEL_UNLOCKED;
            }
            break;

        default:
            current_state = STATE_PANEL_UNLOCKED;
            break;
    }

    prev_sw0   = curr_sw0;
    prev_oled1 = curr_oled1;
    prev_oled2 = curr_oled2;
    prev_oled3 = curr_oled3;
}

static void v_mcu1_master_send_command(void)
{
    if (uart_is_tx_ready())
    {
        uart_send_byte(mcu1_target_leds);
    }
}

static void v_mcu2_slave_process_and_drive(void)
{
    if (uart_is_rx_available())
    {
        unsigned char rx_cmd = uart_read_byte();

        
        if (rx_cmd & (1 << 0)) led_power_on(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
        else                   led_power_off(LED_OLED_1_2_PORT, LED_OLED_1_PIN);

        if (rx_cmd & (1 << 1)) led_power_on(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
        else                   led_power_off(LED_OLED_1_2_PORT, LED_OLED_2_PIN);

        if (rx_cmd & (1 << 2)) led_power_on(LED_OLED_3_PORT, LED_OLED_3_PIN);
        else                   led_power_off(LED_OLED_3_PORT, LED_OLED_3_PIN);

        if (rx_cmd & (1 << 3)) led_power_on(LED_LED0_PORT, LED_LED0_PIN);
        else                   led_power_off(LED_LED0_PORT, LED_LED0_PIN);
    }
}