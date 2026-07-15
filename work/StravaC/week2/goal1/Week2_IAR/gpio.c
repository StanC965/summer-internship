#ifndef GPIO_C
#define GPIO_C

/*
Autor: Strava Cosmin-Paul
Data: 2026

Implementarea modulului GPIO.
*/

/* Debounce configuration */

#define GPIO_DEBOUNCE_DELAY_COUNT          (20000UL)
#define GPIO_DELAY_COUNTER_INITIAL_VALUE   (0UL)

#include "gpio.h"

/* Static private function */

static void gpio_debounce_delay(void);

void gpio_set_pin(
    volatile gpio_uint8_t *gpio_port,
    gpio_uint8_t gpio_pin
)
{
    *gpio_port |= (GPIO_ONE << gpio_pin);
}

void gpio_reset_pin(
    volatile gpio_uint8_t *gpio_port,
    gpio_uint8_t gpio_pin
)
{
    *gpio_port &= ~(GPIO_ONE << gpio_pin);
}

void gpio_toggle_pin(
    volatile gpio_uint8_t *gpio_port,
    gpio_uint8_t gpio_pin
)
{
    *gpio_port ^= (GPIO_ONE << gpio_pin);
}

void gpio_set_direction(
    volatile gpio_uint8_t *gpio_ddr,
    gpio_uint8_t gpio_pin,
    gpio_uint8_t gpio_direction
)
{
    if (gpio_direction == GPIO_OUTPUT)
    {
        *gpio_ddr |= (GPIO_ONE << gpio_pin);
    }
    else
    {
        *gpio_ddr &= ~(GPIO_ONE << gpio_pin);
    }
}

void gpio_activate_pullup(
    volatile gpio_uint8_t *gpio_port,
    gpio_uint8_t gpio_pin
)
{
    gpio_set_pin(
        gpio_port,
        gpio_pin
    );
}

gpio_uint8_t gpio_read_pin(
    volatile gpio_uint8_t *gpio_pin_register,
    gpio_uint8_t gpio_pin
)
{
    gpio_uint8_t gpio_pin_state;

    gpio_pin_state = (
        (*gpio_pin_register & (GPIO_ONE << gpio_pin)) != GPIO_ZERO
    );

    return gpio_pin_state;
}

gpio_uint8_t gpio_read_pin_debounced(
    volatile gpio_uint8_t *gpio_pin_register,
    gpio_uint8_t gpio_pin
)
{
    gpio_uint8_t gpio_first_read;
    gpio_uint8_t gpio_second_read;

    gpio_first_read = gpio_read_pin(
        gpio_pin_register,
        gpio_pin
    );

    gpio_debounce_delay();

    gpio_second_read = gpio_read_pin(
        gpio_pin_register,
        gpio_pin
    );

    if (gpio_first_read == gpio_second_read)
    {
        return gpio_second_read;
    }

    /*
    Daca cele doua citiri nu coincid, valoarea este considerata
    instabila si butonul este tratat ca eliberat.
    */

    return GPIO_HIGH;
}

static void gpio_debounce_delay(void)
{
    volatile unsigned long gpio_delay_counter;

    for (
        gpio_delay_counter = GPIO_DELAY_COUNTER_INITIAL_VALUE;
        gpio_delay_counter < GPIO_DEBOUNCE_DELAY_COUNT;
        gpio_delay_counter++
    )
    {
        /*
        Intarziere software pentru debounce.
        */
    }
}

#endif