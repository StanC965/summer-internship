#ifndef GPIO_C
#define GPIO_C

// Includes

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier contine implementarea modulului gpio.
Modulul gpio se ocupa doar de operatii de baza pe pini:
set, reset, toggle si configurarea directiei.
*/

#include "gpio.h"

// Static private objects

// Momentan nu avem variabile private in acest modul.

// Static private functions declaration

// Momentan nu avem functii private in acest modul.

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

// Static private functions implementation

// Momentan nu avem functii private de implementat.

#endif