#ifndef LED_C
#define LED_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"
#include "led.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void led_init(void)
{
    /* LED0 pin as output - uses the gpio module */
    gpio_set_direction(LED0_PIN, GPIO_OUTPUT);
}

void led_power_on(void)
{
    /* LED0 is active low: ON means writing 0 -> reset the pin */
    gpio_reset_pin(LED0_PIN);
}

void led_power_off(void)
{
    /* LED0 is active low: OFF means writing 1 -> set the pin */
    gpio_set_pin(LED0_PIN);
}

#endif
