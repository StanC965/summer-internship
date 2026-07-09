#ifndef LED_C
#define LED_C

// Includes

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier contine implementarea modulului led.
Modulul led foloseste functiile de baza din modulul gpio.
*/

#include "led.h"

// Static private objects

// Momentan nu avem variabile private in acest modul.

// Static private functions declaration

// Momentan nu avem functii private in acest modul.

// Public functions implementation 

void led_power_on(volatile gpio_uint8_t *port, gpio_uint8_t pin)
{
    gpio_reset_pin(port, pin);
}

void led_power_off(volatile gpio_uint8_t *port, gpio_uint8_t pin)
{
    gpio_set_pin(port, pin);
}

// Static private functions implementation

// Momentan nu avem functii private de implementat.

#endif