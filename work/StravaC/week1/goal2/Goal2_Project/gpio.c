#ifndef GPIO_C
#define GPIO_C

// Includes

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier contine implementarea modulului gpio.

Modulul gpio se ocupa doar de operatii de baza pe pini:
set, reset, toggle, configurarea directiei, activare pull-up si citire pin.

Pentru butoane am adaugat si citire cu debounce.
*/

#include "gpio.h"

// Static private functions declaration

static void gpio_debounce_delay(void);

// Public functions implementation

void gpio_set_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin)
{
    *port |= (GPIO_ONE << pin);
}

void gpio_reset_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin)
{
    *port &= ~(GPIO_ONE << pin);
}

void gpio_toggle_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin)
{
    *port ^= (GPIO_ONE << pin);
}

void gpio_set_direction(volatile gpio_uint8_t *ddr, gpio_uint8_t pin, gpio_uint8_t direction)
{
    direction ? (*ddr |= (GPIO_ONE << pin)) : (*ddr &= ~(GPIO_ONE << pin));
}

void gpio_activate_pullup(volatile gpio_uint8_t *port, gpio_uint8_t pin)
{
    gpio_set_pin(port, pin);
}

gpio_uint8_t gpio_read_pin(volatile gpio_uint8_t *pin_register, gpio_uint8_t pin)
{
    return ((*pin_register & (GPIO_ONE << pin)) != GPIO_ZERO);
}

gpio_uint8_t gpio_read_pin_debounced(volatile gpio_uint8_t *pin_register, gpio_uint8_t pin)
{
    gpio_uint8_t first_read;
    gpio_uint8_t second_read;

    first_read = gpio_read_pin(pin_register, pin);

    gpio_debounce_delay();

    second_read = gpio_read_pin(pin_register, pin);

    if (first_read == second_read)
    {
        return second_read;
    }

    return GPIO_HIGH;
}

// Static private functions implementation

static void gpio_debounce_delay(void)
{
    volatile unsigned long i;

    for (i = 0; i < 5000UL; i++)
    {

    }
}

#endif