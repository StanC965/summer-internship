#ifndef LED_H
#define LED_H

/*
Autor: Strava Cosmin-Paul
Data: 2026

Interfata modulului LED.

LED-urile utilizate sunt active-low:
- nivel LOW  -> LED aprins;
- nivel HIGH -> LED stins.

Actiunile atomice ale modulului sunt:
- aprindere;
- stingere;
- toggle.
*/

#include "gpio.h"

/* Module initialization */

extern void led_init(
    volatile gpio_uint8_t *led_ddr_register,
    volatile gpio_uint8_t *led_port_register,
    gpio_uint8_t led_pin_number
);

/* Atomic LED actions */

extern void led_power_on(
    volatile gpio_uint8_t *led_port_register,
    gpio_uint8_t led_pin_number
);

extern void led_power_off(
    volatile gpio_uint8_t *led_port_register,
    gpio_uint8_t led_pin_number
);

extern void led_toggle(
    volatile gpio_uint8_t *led_port_register,
    gpio_uint8_t led_pin_number
);

#endif