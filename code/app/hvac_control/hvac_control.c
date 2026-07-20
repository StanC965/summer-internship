#ifndef HVAC_CONTROL_C
#define HVAC_CONTROL_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "hvac_control.h"
#include "led.h"
#include "button.h"
#include "delay.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects & functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
static hvac_state_t hvac_state = STATE_NORMAL;
static uint8_t button_pressed_toggle[BUTTON_COUNT] = {0};

static const led_id_t button_to_led_map[BUTTON_COUNT] = {
    [BUTTON_ONBOARD] = LED_ONBOARD,
    [BUTTON_OLED1_1] = LED_OLED1_1,
    [BUTTON_OLED1_2] = LED_OLED1_2,
    [BUTTON_OLED1_3] = LED_OLED1_3};

static void turn_off_all_vents(void)
{
    for (uint8_t i = BUTTON_OLED1_1; i <= BUTTON_OLED1_3; i++)
    {
        led_power_off(button_to_led_map[i]);
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void hvac_control_init(void)
{
    led_init();
    button_init();
    button_init_interrupt();

    hvac_state = STATE_NORMAL;
}

void hvac_control_process(void)
{
    if (button_was_pressed(BUTTON_ONBOARD))
    {
        button_pressed_toggle[BUTTON_ONBOARD] ^= 1;

        if (button_pressed_toggle[BUTTON_ONBOARD])
        {
            hvac_state = STATE_BLOCKED;
            led_power_on(button_to_led_map[BUTTON_ONBOARD]);
            turn_off_all_vents();
        }
        else
        {
            hvac_state = STATE_NORMAL;
            led_power_off(button_to_led_map[BUTTON_ONBOARD]);
        }
    }

    for (uint8_t i = BUTTON_OLED1_1; i <= BUTTON_OLED1_3; i++)
    {
        if (button_was_pressed((button_id_t)i))
        {
            if (hvac_state == STATE_BLOCKED)
            {
                led_blink_fast(button_to_led_map[BUTTON_ONBOARD]);
                led_power_on(button_to_led_map[BUTTON_ONBOARD]);
            }
            else if (hvac_state == STATE_NORMAL)
            {
                button_pressed_toggle[i] ^= 1;

                if (button_pressed_toggle[i])
                {
                    led_power_on(button_to_led_map[i]);
                }
                else
                {
                    led_power_off(button_to_led_map[i]);
                }
            }
        }
    }
}

#endif /* HVAC_CONTROL_C */
