#include "gpio.h"
#include "led.h"

void led_on(volatile unsigned char *port, unsigned char pin)
{
    gpio_reset_pin(port, pin);
}

void led_off(volatile unsigned char *port, unsigned char pin)
{
    gpio_set_pin(port, pin);
}