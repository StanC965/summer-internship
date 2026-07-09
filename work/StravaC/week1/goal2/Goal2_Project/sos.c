#ifndef SOS_C
#define SOS_C

// Includes

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier contine implementarea modulului sos.

Modulul sos este un nivel de abstractizare mai inalt.
El nu lucreaza direct cu registrele microcontroller-ului,
ci foloseste functiile din modulul led.

POINT si LINE sunt comportamente construite peste LED on/off.
SOS este construit peste POINT si LINE.
*/

#include "sos.h"
#include "led.h"

// Static private functions declaration

static void sos_point(volatile gpio_uint8_t *port, gpio_uint8_t pin);
static void sos_line(volatile gpio_uint8_t *port, gpio_uint8_t pin);
static void sos_delay_point(void);
static void sos_delay_line(void);
static void sos_delay_pause(void);

// Public functions

void sos_play(volatile gpio_uint8_t *port, gpio_uint8_t pin)
{
    sos_point(port, pin);
    sos_point(port, pin);
    sos_point(port, pin);

    sos_line(port, pin);
    sos_line(port, pin);
    sos_line(port, pin);

    sos_point(port, pin);
    sos_point(port, pin);
    sos_point(port, pin);
}

// Static private functions

static void sos_point(volatile gpio_uint8_t *port, gpio_uint8_t pin)
{
    led_power_on(port, pin);
    sos_delay_point();

    led_power_off(port, pin);
    sos_delay_pause();
}

static void sos_line(volatile gpio_uint8_t *port, gpio_uint8_t pin)
{
    led_power_on(port, pin);
    sos_delay_line();

    led_power_off(port, pin);
    sos_delay_pause();
}

static void sos_delay_point(void)
{
    volatile unsigned long i;

    for (i = 0; i < 25000UL; i++)
    {

    }
}

static void sos_delay_line(void)
{
    volatile unsigned long i;

    for (i = 0; i < 75000UL; i++)
    {

    }
}

static void sos_delay_pause(void)
{
    volatile unsigned long i;

    for (i = 0; i < 25000UL; i++)
    {

    }
}

#endif