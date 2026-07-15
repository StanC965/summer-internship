#ifndef BUTTON_C
#define BUTTON_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"
#include "button.h"
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define BUTTON_DEBOUNCE_DELAY   (600U)

static void button_delay(void)
{
    volatile unsigned int i;
    for (i = 0; i < BUTTON_DEBOUNCE_DELAY; i++) { }
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void button_init(void)
{
    gpio_set_direction(SW0_PIN, GPIO_INPUT);
    gpio_enable_pullup(SW0_PIN);
}

unsigned char button_is_pressed(void)
{
    unsigned char first_read;
    unsigned char second_read;

    /* LOW on the pin means pressed */
    first_read = gpio_read_pin(SW0_PIN);

    button_delay();     

    second_read = gpio_read_pin(SW0_PIN);

    /* the state is accepted only if both readings agree */
    if ((first_read == GPIO_LOW) && (second_read == GPIO_LOW))
        return BUTTON_PRESSED;
    else
        return BUTTON_RELEASED;
}
#endif
