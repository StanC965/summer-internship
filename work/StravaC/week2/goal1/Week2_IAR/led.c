#ifndef LED_C
#define LED_C

// Includes

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier contine implementarea modulului led.

Modulul led foloseste functiile de baza din modulul gpio.
Pentru ca LED-urile sunt active-low, aprinderea se face cu reset pe pin,
iar stingerea se face cu set pe pin.

Modulul led contine doar comportamente specifice LED-urilor:
power on, power off, blink fast si blink slow.
*/

#include "led.h"

// Static private functions declaration

static void led_delay_fast(void);
static void led_delay_slow(void);

// Public functions

void led_power_on(volatile gpio_uint8_t *port, gpio_uint8_t pin)
{
    gpio_reset_pin(port, pin);
}

void led_power_off(volatile gpio_uint8_t *port, gpio_uint8_t pin)
{
    gpio_set_pin(port, pin);
}

void led_blink_fast(volatile gpio_uint8_t *port, gpio_uint8_t pin)
{
    led_power_on(port, pin);
    led_delay_fast();

    led_power_off(port, pin);
    led_delay_fast();
}

void led_blink_slow(volatile gpio_uint8_t *port, gpio_uint8_t pin)
{
    led_power_on(port, pin);
    led_delay_slow();

    led_power_off(port, pin);
    led_delay_slow();
}

// Static private functions

static void led_delay_fast(void)
{
    volatile unsigned long i;

    for (i = 0; i < 15000UL; i++)
    {

    }
}

static void led_delay_slow(void)
{
    volatile unsigned long i;

    for (i = 0; i < 50000UL; i++)
    {

    }
}

#endif