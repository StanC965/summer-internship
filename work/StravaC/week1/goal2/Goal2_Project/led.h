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

/** \fn         void led_blink_fast(volatile gpio_uint8_t *port, gpio_uint8_t pin)

    \brief      Face LED-ul sa clipeasca rapid.
    \param[in]  port - adresa registrului PORTx pe care este conectat LED-ul
    \param[in]  pin  - pinul pe care este conectat LED-ul
    \param[out] Nu exista.
    \return     Nu returneaza nimic.
    \details    LED-ul este aprins si stins repetitiv cu aproximativ 6 on-uri si 6 off-uri pe secunda.
*/
extern void led_blink_fast(volatile gpio_uint8_t *port, gpio_uint8_t pin);

/** \fn         void led_blink_slow(volatile gpio_uint8_t *port, gpio_uint8_t pin)

    \brief      Face LED-ul sa clipeasca lent.
    \param[in]  port - adresa registrului PORTx pe care este conectat LED-ul
    \param[in]  pin  - pinul pe care este conectat LED-ul
    \param[out] Nu exista.
    \return     Nu returneaza nimic.
    \details    LED-ul este aprins si stins repetitiv cu aproximativ 2 on-uri si 2 off-uri pe secunda.
*/
extern void led_blink_slow(volatile gpio_uint8_t *port, gpio_uint8_t pin);

/** \fn         void led_point(volatile gpio_uint8_t *port, gpio_uint8_t pin)

    \brief      Genereaza un punct Morse cu LED-ul.
    \param[in]  port - adresa registrului PORTx pe care este conectat LED-ul
    \param[in]  pin  - pinul pe care este conectat LED-ul
    \param[out] Nu exista.
    \return     Nu returneaza nimic.
    \details    Aprinde LED-ul scurt, apoi il stinge scurt.
*/
extern void led_point(volatile gpio_uint8_t *port, gpio_uint8_t pin);

/** \fn         void led_line(volatile gpio_uint8_t *port, gpio_uint8_t pin)

    \brief      Genereaza o linie Morse cu LED-ul.
    \param[in]  port - adresa registrului PORTx pe care este conectat LED-ul
    \param[in]  pin  - pinul pe care este conectat LED-ul
    \param[out] Nu exista.
    \return     Nu returneaza nimic.
    \details    Aprinde LED-ul mai mult timp, apoi il stinge scurt.
*/
extern void led_line(volatile gpio_uint8_t *port, gpio_uint8_t pin);

/** \fn         void led_sos(volatile gpio_uint8_t *port, gpio_uint8_t pin)

    \brief      Genereaza secventa SOS in cod Morse.
    \param[in]  port - adresa registrului PORTx pe care este conectat LED-ul
    \param[in]  pin  - pinul pe care este conectat LED-ul
    \param[out] Nu exista.
    \return     Nu returneaza nimic.
    \details    SOS inseamna 3 puncte, 3 linii, 3 puncte.
*/
extern void led_sos(volatile gpio_uint8_t *port, gpio_uint8_t pin);

#endif