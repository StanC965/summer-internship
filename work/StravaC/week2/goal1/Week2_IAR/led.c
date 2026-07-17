#ifndef LED_C
#define LED_C

/*
Autor: Strava Cosmin-Paul
Data: 2026

Implementarea modulului LED.

Initializarea configureaza pinul LED-ului ca iesire
si stabileste starea initiala OFF.
*/

#include "led.h"

void led_init(
    volatile gpio_uint8_t *led_ddr_register,
    volatile gpio_uint8_t *led_port_register,
    gpio_uint8_t led_pin_number
)
{
    gpio_set_direction(
        led_ddr_register,
        led_pin_number,
        GPIO_OUTPUT
    );

    led_power_off(
        led_port_register,
        led_pin_number
    );
}

void led_power_on(
    volatile gpio_uint8_t *led_port_register,
    gpio_uint8_t led_pin_number
)
{
    /*
    LED active-low:
    resetarea pinului aprinde LED-ul.
    */

    gpio_reset_pin(
        led_port_register,
        led_pin_number
    );
}

void led_power_off(
    volatile gpio_uint8_t *led_port_register,
    gpio_uint8_t led_pin_number
)
{
    /*
    LED active-low:
    setarea pinului stinge LED-ul.
    */

    gpio_set_pin(
        led_port_register,
        led_pin_number
    );
}

void led_toggle(
    volatile gpio_uint8_t *led_port_register,
    gpio_uint8_t led_pin_number
)
{
    gpio_toggle_pin(
        led_port_register,
        led_pin_number
    );
}

#endif