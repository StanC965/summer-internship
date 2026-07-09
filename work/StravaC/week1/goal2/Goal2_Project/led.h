#ifndef LED_H
#define LED_H

// Exported types and values

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier reprezinta interfata modulului led.
Modulul led se ocupa doar de starea LED-urilor: aprins sau stins.
*/

#include "gpio.h"

// Public functions

/** \fn         void led_power_on(volatile gpio_uint8_t *port, gpio_uint8_t pin)

    \brief      Aprinde un LED active-low.
    \param[in]  port - adresa registrului PORTx pe care este conectat LED-ul
    \param[in]  pin  - pinul pe care este conectat LED-ul
    \param[out] Nu exista.
    \return     Nu returneaza nimic.
    \details    Pentru LED-urile active-low, aprinderea se face prin scrierea valorii 0 pe pin.
*/
extern void led_power_on(volatile gpio_uint8_t *port, gpio_uint8_t pin);

/** \fn         void led_power_off(volatile gpio_uint8_t *port, gpio_uint8_t pin)

    \brief      Stinge un LED active-low.
    \param[in]  port - adresa registrului PORTx pe care este conectat LED-ul
    \param[in]  pin  - pinul pe care este conectat LED-ul
    \param[out] Nu exista.
    \return     Nu returneaza nimic.
    \details    Pentru LED-urile active-low, stingerea se face prin scrierea valorii 1 pe pin.
*/
extern void led_power_off(volatile gpio_uint8_t *port, gpio_uint8_t pin);

#endif