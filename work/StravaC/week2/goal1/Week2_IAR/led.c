#ifndef LED_C
#define LED_C

/*
Autor: Strava Cosmin-Paul
Data: 2026

Implementarea modulului LED.
*/

/* Fast blink timing */

#define LED_FAST_DELAY_COUNT               (15000UL)
#define LED_DELAY_COUNTER_INITIAL_VALUE    (0UL)

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

void led_toggle(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin
)
{
    gpio_toggle_pin(
        led_port,
        led_pin
    );
}

void led_delay_fast(void)
{
    volatile unsigned long led_delay_counter;

    for (
        led_delay_counter = LED_DELAY_COUNTER_INITIAL_VALUE;
        led_delay_counter < LED_FAST_DELAY_COUNT;
        led_delay_counter++
    )
    {
        /*
        Intarziere software pentru blink rapid.
        */
    }
}

#endif