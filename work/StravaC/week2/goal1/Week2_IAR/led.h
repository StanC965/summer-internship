#ifndef LED_H
#define LED_H

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier reprezinta interfata modulului led.

Modulul led se ocupa de functionalitati generale pentru LED-uri:
aprindere, stingere, blink rapid si blink lent.

Comportamentele mai complexe, cum ar fi secventa SOS,
nu sunt tinute aici, ci intr-un modul separat.

Conventie de numire:
Toate functiile si variabilele acestui modul folosesc prefixul led_.
*/

#include "gpio.h"

/* Public functions */

extern void led_power_on(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin
);

extern void led_power_off(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin
);

extern void led_blink_fast(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin
);

extern void led_blink_slow(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin
);

#endif