#ifndef LED_C
#define LED_C

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier contine implementarea modulului led.

Modulul led foloseste functiile de baza din modulul gpio.

Pentru ca LED-urile sunt active-low:
aprinderea se face prin resetarea pinului;
stingerea se face prin setarea pinului.

Modulul led contine doar comportamente specifice LED-urilor:
power on, power off, blink fast si blink slow.

Conventie de numire:
Toate functiile si variabilele acestui modul folosesc prefixul led_.
*/

/* LED delay configuration */

#define LED_FAST_DELAY_COUNT               (15000UL)
#define LED_SLOW_DELAY_COUNT               (50000UL)
#define LED_DELAY_COUNTER_INITIAL_VALUE    (0UL)

#include "led.h"

/* Static private functions declaration */

static void led_delay_fast(void);

static void led_delay_slow(void);

/* Public functions */

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

void led_blink_fast(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin
)
{
    led_power_on(
        led_port,
        led_pin
    );

    led_delay_fast();

    led_power_off(
        led_port,
        led_pin
    );

    led_delay_fast();
}

void led_blink_slow(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin
)
{
    led_power_on(
        led_port,
        led_pin
    );

    led_delay_slow();

    led_power_off(
        led_port,
        led_pin
    );

    led_delay_slow();
}

/* Static private functions */

static void led_delay_fast(void)
{
    volatile unsigned long led_delay_counter;

    for (
        led_delay_counter = LED_DELAY_COUNTER_INITIAL_VALUE;
        led_delay_counter < LED_FAST_DELAY_COUNT;
        led_delay_counter++
    )
    {
        /*
        Bucla este folosita pentru realizarea
        unei intarzieri software.
        */
    }
}

static void led_delay_slow(void)
{
    volatile unsigned long led_delay_counter;

    for (
        led_delay_counter = LED_DELAY_COUNTER_INITIAL_VALUE;
        led_delay_counter < LED_SLOW_DELAY_COUNT;
        led_delay_counter++
    )
    {
        /*
        Bucla este folosita pentru realizarea
        unei intarzieri software.
        */
    }
}

#endif