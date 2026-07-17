#ifndef BUTTON_C
#define BUTTON_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "iom324pb.h"
#include "gpio.h"
#include "button.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* debounce time */
#define BUTTON_DEBOUNCE_DELAY   (600U)

static void button_delay(void)
{
    volatile unsigned int i;
    for (i = 0; i < BUTTON_DEBOUNCE_DELAY; i++) { }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void button_init(gpio_reg_t ddr, gpio_reg_t port, unsigned char pin)
{
    gpio_set_direction(ddr, pin, GPIO_INPUT);
    gpio_enable_pullup(port, pin);
}

unsigned char button_is_pressed(gpio_reg_t pinx, unsigned char pin)
{
    unsigned char first_read;
    unsigned char second_read;

    /* the buttons are active low: LOW on the pin means pressed */
    first_read = gpio_read_pin(pinx, pin);

    button_delay();          

    second_read = gpio_read_pin(pinx, pin);

    if ((first_read == GPIO_LOW) && (second_read == GPIO_LOW))
        return BUTTON_PRESSED;
    else
        return BUTTON_RELEASED;
}

#endif
