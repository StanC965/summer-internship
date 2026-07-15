#ifndef LED_C
#define LED_C

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier contine implementarea modulului led.

LED-urile sunt active-low:
- LOW aprinde LED-ul;
- HIGH stinge LED-ul.
*/

#include "led.h"

void led_power_on(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin
)
{
    gpio_reset_pin(
        led_port,
        led_pin
    );
}

void led_power_off(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin
)
{
    gpio_set_pin(
        led_port,
        led_pin
    );
}

#endif