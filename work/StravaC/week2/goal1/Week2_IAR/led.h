#ifndef LED_H
#define LED_H

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier reprezinta interfata modulului led.
LED-urile extensiei OLED1 sunt active-low.
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

#endif