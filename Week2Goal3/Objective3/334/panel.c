#ifndef PANEL_C
#define PANEL_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "button.h"
#include "panel.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  How many fast blinks of LED0 confirm that the panel is blocked */
#define PANEL_BLOCKED_BLINKS    (3U)

static volatile unsigned char panel_state = PANEL_UNBLOCKED;

/* previous button states, used for edge detection */
static unsigned char panel_button1_previous = BUTTON_RELEASED;
static unsigned char panel_button2_previous = BUTTON_RELEASED;
static unsigned char panel_button3_previous = BUTTON_RELEASED;

/* turn all the vent indicators (OLED1 LEDs) off */
static void panel_all_vents_off(void)
{
    led_power_off(LED1_PORT, LED1_PIN);
    led_power_off(LED2_PORT, LED2_PIN);
    led_power_off(LED3_PORT, LED3_PIN);
}

/* fast blink of LED0, telling the driver that the panel is blocked */
static void panel_blocked_feedback(void)
{
    unsigned char i;

    for (i = 0; i < PANEL_BLOCKED_BLINKS; i++)
    {
        led_blink_fast(LED0_PORT, LED0_PIN);
    }

    led_power_on(LED0_PORT, LED0_PIN);   /* LED0 stays on while blocked */
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void panel_init(void)
{
    led_init(LED0_DDR, LED0_PIN);
    led_init(LED1_DDR, LED1_PIN);
    led_init(LED2_DDR, LED2_PIN);
    led_init(LED3_DDR, LED3_PIN);

    led_power_off(LED0_PORT, LED0_PIN);
    panel_all_vents_off();

    button_init(BUTTON1_DDR, BUTTON1_PORT, BUTTON1_PIN);
    button_init(BUTTON2_DDR, BUTTON2_PORT, BUTTON2_PIN);
    button_init(BUTTON3_DDR, BUTTON3_PORT, BUTTON3_PIN);

    panel_state = PANEL_UNBLOCKED;
}

void panel_toggle_blocked(void)
{
    if (panel_state == PANEL_UNBLOCKED)
        panel_state = PANEL_BLOCKED;
    else
        panel_state = PANEL_UNBLOCKED;
}

void panel_update(void)
{
    unsigned char button1_current;
    unsigned char button2_current;
    unsigned char button3_current;
    unsigned char any_button_pressed;

    button1_current = button_is_pressed(BUTTON1_PIN_REG, BUTTON1_PIN);
    button2_current = button_is_pressed(BUTTON2_PIN_REG, BUTTON2_PIN);
    button3_current = button_is_pressed(BUTTON3_PIN_REG, BUTTON3_PIN);

    if (panel_state == PANEL_BLOCKED)
    {
        /* blocked: vents stay off, LED0 on, and any button press blinks LED0 fast */
        panel_all_vents_off();
        led_power_on(LED0_PORT, LED0_PIN);

        any_button_pressed =
            ((button1_current == BUTTON_PRESSED) && (panel_button1_previous == BUTTON_RELEASED)) ||
            ((button2_current == BUTTON_PRESSED) && (panel_button2_previous == BUTTON_RELEASED)) ||
            ((button3_current == BUTTON_PRESSED) && (panel_button3_previous == BUTTON_RELEASED));

        if (any_button_pressed != 0)
        {
            panel_blocked_feedback();
        }
    }
    else
    {
        /* normal: each button toggles only its own vent indicator */
        led_power_off(LED0_PORT, LED0_PIN);

        if ((button1_current == BUTTON_PRESSED) && (panel_button1_previous == BUTTON_RELEASED))
            led_toggle(LED1_PORT, LED1_PIN);

        if ((button2_current == BUTTON_PRESSED) && (panel_button2_previous == BUTTON_RELEASED))
            led_toggle(LED2_PORT, LED2_PIN);

        if ((button3_current == BUTTON_PRESSED) && (panel_button3_previous == BUTTON_RELEASED))
            led_toggle(LED3_PORT, LED3_PIN);
    }

    panel_button1_previous = button1_current;
    panel_button2_previous = button2_current;
    panel_button3_previous = button3_current;
}

#endif
