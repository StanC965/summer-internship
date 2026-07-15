#ifndef LED_H
#define LED_H

/*
Autor: Strava Cosmin-Paul
Data: 2026

Interfata modulului LED.

LED-urile folosite sunt active-low:
LOW  -> ON
HIGH -> OFF
*/

#include "gpio.h"

extern void led_power_on(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin
);

extern void led_power_off(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin
);

extern void led_toggle(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin
);

extern void led_delay_fast(void);

#endif