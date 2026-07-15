#ifndef GPIO_C
#define GPIO_C

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier contine implementarea modulului gpio.
*/

#include "gpio.h"

void gpio_set_pin(
    volatile gpio_uint8_t *gpio_port,
    gpio_uint8_t gpio_pin
)
{
    *gpio_port |= (GPIO_ONE << gpio_pin);
}

void gpio_reset_pin(
    volatile gpio_uint8_t *gpio_port,
    gpio_uint8_t gpio_pin
)
{
    *gpio_port &= ~(GPIO_ONE << gpio_pin);
}

void gpio_toggle_pin(
    volatile gpio_uint8_t *gpio_port,
    gpio_uint8_t gpio_pin
)
{
    *gpio_port ^= (GPIO_ONE << gpio_pin);
}

void gpio_set_direction(
    volatile gpio_uint8_t *gpio_ddr,
    gpio_uint8_t gpio_pin,
    gpio_uint8_t gpio_direction
)
{
    if (gpio_direction == GPIO_OUTPUT)
    {
        *gpio_ddr |= (GPIO_ONE << gpio_pin);
    }
    else
    {
        *gpio_ddr &= ~(GPIO_ONE << gpio_pin);
    }
}

void gpio_activate_pullup(
    volatile gpio_uint8_t *gpio_port,
    gpio_uint8_t gpio_pin
)
{
    gpio_set_pin(
        gpio_port,
        gpio_pin
    );
}

gpio_uint8_t gpio_read_pin(
    volatile gpio_uint8_t *gpio_pin_register,
    gpio_uint8_t gpio_pin
)
{
    gpio_uint8_t gpio_pin_state;

    gpio_pin_state = (
        (*gpio_pin_register & (GPIO_ONE << gpio_pin)) != GPIO_ZERO
    );

    return gpio_pin_state;
}

#endif