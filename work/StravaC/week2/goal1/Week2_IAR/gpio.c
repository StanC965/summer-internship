#ifndef GPIO_C
#define GPIO_C

// Includes

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier contine implementarea modulului gpio.

Modulul gpio se ocupa doar de operatii de baza pe pini:
set, reset, toggle, configurarea directiei,
activarea rezistentei pull-up si citirea unui pin.

Pentru situatiile in care este necesara verificarea unui buton
prin polling, modulul pastreaza si functia de citire cu debounce.
*/

/* Debounce configuration */

#define GPIO_DEBOUNCE_DELAY_COUNT          (20000UL)
#define GPIO_DELAY_COUNTER_INITIAL_VALUE   (0UL)

#include "gpio.h"

/* Static private functions declaration */

static void gpio_debounce_delay(void);

/* Public functions implementation */

void gpio_set_pin(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
)
{
    *port |= (GPIO_ONE << pin);
}

void gpio_reset_pin(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
)
{
    *port &= ~(GPIO_ONE << pin);
}

void gpio_toggle_pin(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
)
{
    *port ^= (GPIO_ONE << pin);
}

void gpio_set_direction(
    volatile gpio_uint8_t *ddr,
    gpio_uint8_t pin,
    gpio_uint8_t direction
)
{
    if (direction == GPIO_OUTPUT)
    {
        *ddr |= (GPIO_ONE << pin);
    }
    else
    {
        *ddr &= ~(GPIO_ONE << pin);
    }
}

void gpio_activate_pullup(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
)
{
    gpio_set_pin(port, pin);
}

gpio_uint8_t gpio_read_pin(
    volatile gpio_uint8_t *pin_register,
    gpio_uint8_t pin
)
{
    gpio_uint8_t pin_state;

    pin_state = (
        (*pin_register & (GPIO_ONE << pin)) != GPIO_ZERO
    );

    return pin_state;
}

gpio_uint8_t gpio_read_pin_debounced(
    volatile gpio_uint8_t *pin_register,
    gpio_uint8_t pin
)
{
    gpio_uint8_t first_read;
    gpio_uint8_t second_read;

    first_read = gpio_read_pin(
        pin_register,
        pin
    );

    gpio_debounce_delay();

    second_read = gpio_read_pin(
        pin_register,
        pin
    );

    if (first_read == second_read)
    {
        return second_read;
    }

    /*
    Daca cele doua citiri sunt diferite,
    butonul este considerat eliberat.
    */
    return GPIO_HIGH;
}

/* Static private functions implementation */

static void gpio_debounce_delay(void)
{
    volatile unsigned long delay_counter;

    for (
        delay_counter = GPIO_DELAY_COUNTER_INITIAL_VALUE;
        delay_counter < GPIO_DEBOUNCE_DELAY_COUNT;
        delay_counter++
    )
    {
        /*
        Bucla este folosita pentru realizarea
        unei intarzieri software.
        */
    }
}

#endif