#include "gpio.h"
#include "led.h"

void led_on(unsigned char pin)
{
    gpio_reset_pin(pin);
}

void led_off(unsigned char pin)
{
    gpio_set_pin(pin);
}