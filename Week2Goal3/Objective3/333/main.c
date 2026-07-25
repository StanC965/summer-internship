/* 333 - same as 332, plus: when SW0 is pressed, all the OLED1 LEDs are turned off
   and LED0 is turned on. */

#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "button.h"

void main( void )
{
    unsigned char button1_previous = BUTTON_RELEASED;
    unsigned char button2_previous = BUTTON_RELEASED;
    unsigned char button3_previous = BUTTON_RELEASED;
    unsigned char button1_current;
    unsigned char button2_current;
    unsigned char button3_current;

    led_init(LED0_DDR, LED0_PIN);
    led_init(LED1_DDR, LED1_PIN);
    led_init(LED2_DDR, LED2_PIN);
    led_init(LED3_DDR, LED3_PIN);

    led_power_off(LED0_PORT, LED0_PIN);
    led_power_off(LED1_PORT, LED1_PIN);
    led_power_off(LED2_PORT, LED2_PIN);
    led_power_off(LED3_PORT, LED3_PIN);

    button_init(SW0_DDR, SW0_PORT, SW0_PIN);
    button_init(BUTTON1_DDR, BUTTON1_PORT, BUTTON1_PIN);
    button_init(BUTTON2_DDR, BUTTON2_PORT, BUTTON2_PIN);
    button_init(BUTTON3_DDR, BUTTON3_PORT, BUTTON3_PIN);

    while(1)
    {
        if (button_is_pressed(SW0_PIN_REG, SW0_PIN) == BUTTON_PRESSED)
        {
            /* SW0 pressed: all OLED1 LEDs off, LED0 on */
            led_power_off(LED1_PORT, LED1_PIN);
            led_power_off(LED2_PORT, LED2_PIN);
            led_power_off(LED3_PORT, LED3_PIN);
            led_power_on(LED0_PORT, LED0_PIN);
        }
        else
        {
            led_power_off(LED0_PORT, LED0_PIN);

            button1_current = button_is_pressed(BUTTON1_PIN_REG, BUTTON1_PIN);
            button2_current = button_is_pressed(BUTTON2_PIN_REG, BUTTON2_PIN);
            button3_current = button_is_pressed(BUTTON3_PIN_REG, BUTTON3_PIN);

            if ((button1_current == BUTTON_PRESSED) && (button1_previous == BUTTON_RELEASED))
                led_toggle(LED1_PORT, LED1_PIN);

            if ((button2_current == BUTTON_PRESSED) && (button2_previous == BUTTON_RELEASED))
                led_toggle(LED2_PORT, LED2_PIN);

            if ((button3_current == BUTTON_PRESSED) && (button3_previous == BUTTON_RELEASED))
                led_toggle(LED3_PORT, LED3_PIN);

            button1_previous = button1_current;
            button2_previous = button2_current;
            button3_previous = button3_current;
        }
    }
}
