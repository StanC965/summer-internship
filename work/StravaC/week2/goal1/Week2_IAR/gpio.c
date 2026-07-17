#ifndef GPIO_C
#define GPIO_C

/*
Autor: Strava Cosmin-Paul
Data: 2026

Implementarea modulului GPIO.

Modulul este independent de placa folosita.
El nu configureaza automat un anumit port sau pin.
Configurarea concreta este realizata de modulele care folosesc GPIO.
*/

#include "gpio.h"

void gpio_init(void)
{
    /*
    Modulul GPIO nu necesita configurarea unui periferic global.

    Registrele DDRx, PORTx si PINx sunt configurate punctual
    prin functiile atomice ale modulului.
    */
}

void gpio_set_direction(
    volatile gpio_uint8_t *gpio_ddr_register,
    gpio_uint8_t gpio_pin_number,
    gpio_uint8_t gpio_direction
)
{
    if (gpio_direction == GPIO_OUTPUT)
    {
        *gpio_ddr_register |= (
            GPIO_ONE << gpio_pin_number
        );
    }
    else
    {
        *gpio_ddr_register &= ~(
            GPIO_ONE << gpio_pin_number
        );
    }
}

void gpio_set_pin(
    volatile gpio_uint8_t *gpio_port_register,
    gpio_uint8_t gpio_pin_number
)
{
    *gpio_port_register |= (
        GPIO_ONE << gpio_pin_number
    );
}

void gpio_reset_pin(
    volatile gpio_uint8_t *gpio_port_register,
    gpio_uint8_t gpio_pin_number
)
{
    *gpio_port_register &= ~(
        GPIO_ONE << gpio_pin_number
    );
}

void gpio_toggle_pin(
    volatile gpio_uint8_t *gpio_port_register,
    gpio_uint8_t gpio_pin_number
)
{
    *gpio_port_register ^= (
        GPIO_ONE << gpio_pin_number
    );
}

gpio_uint8_t gpio_read_pin(
    volatile gpio_uint8_t *gpio_pin_register,
    gpio_uint8_t gpio_pin_number
)
{
    gpio_uint8_t gpio_pin_state;

    gpio_pin_state = (
        (*gpio_pin_register &
         (GPIO_ONE << gpio_pin_number)) != GPIO_ZERO
    );

    return gpio_pin_state;
}

#endif