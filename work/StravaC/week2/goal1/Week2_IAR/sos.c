#ifndef SOS_C
#define SOS_C

// Includes

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier contine implementarea modulului sos.

Modulul sos este un nivel de abstractizare mai inalt.
El nu lucreaza direct cu registrele microcontroller-ului pentru LED,
ci foloseste functiile din modulul led.

POINT si LINE sunt comportamente construite peste LED on/off.
SOS este construit peste POINT si LINE.

Pentru task-ul 316, oprirea SOS-ului este solicitata printr-un flag
setat de rutina de intrerupere asociata butonului SW0.

Modulul sos nu trebuie sa cunoasca pinul sau vectorul intreruperii.
El verifica doar daca exista o cerere de oprire.
*/

#include "sos.h"
#include "led.h"

// Static private functions declaration

static void sos_point(volatile gpio_uint8_t *port,
                      gpio_uint8_t pin);

static void sos_line(volatile gpio_uint8_t *port,
                     gpio_uint8_t pin);

static gpio_uint8_t sos_stop_is_requested(
    volatile gpio_uint8_t *interrupt_request);

static void sos_delay_point(
    volatile gpio_uint8_t *interrupt_request);

static void sos_delay_line(
    volatile gpio_uint8_t *interrupt_request);

static void sos_delay_pause(
    volatile gpio_uint8_t *interrupt_request);

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

gpio_uint8_t sos_play_interruptible(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin,
    volatile gpio_uint8_t *interrupt_request)
{
    gpio_uint8_t symbol_index;

    /*
    Litera S: trei puncte.
    */
    for (symbol_index = 0U; symbol_index < 3U; symbol_index++)
    {
        led_power_on(led_port, led_pin);
        sos_delay_point(interrupt_request);
        led_power_off(led_port, led_pin);

        if (sos_stop_is_requested(interrupt_request) == GPIO_TRUE)
        {
            return GPIO_FALSE;
        }

        sos_delay_pause(interrupt_request);

        if (sos_stop_is_requested(interrupt_request) == GPIO_TRUE)
        {
            return GPIO_FALSE;
        }
    }

    /*
    Litera O: trei linii.
    */
    for (symbol_index = 0U; symbol_index < 3U; symbol_index++)
    {
        led_power_on(led_port, led_pin);
        sos_delay_line(interrupt_request);
        led_power_off(led_port, led_pin);

        if (sos_stop_is_requested(interrupt_request) == GPIO_TRUE)
        {
            return GPIO_FALSE;
        }

        sos_delay_pause(interrupt_request);

        if (sos_stop_is_requested(interrupt_request) == GPIO_TRUE)
        {
            return GPIO_FALSE;
        }
    }

    /*
    Litera S: trei puncte.
    */
    for (symbol_index = 0U; symbol_index < 3U; symbol_index++)
    {
        led_power_on(led_port, led_pin);
        sos_delay_point(interrupt_request);
        led_power_off(led_port, led_pin);

        if (sos_stop_is_requested(interrupt_request) == GPIO_TRUE)
        {
            return GPIO_FALSE;
        }

        sos_delay_pause(interrupt_request);

        if (sos_stop_is_requested(interrupt_request) == GPIO_TRUE)
        {
            return GPIO_FALSE;
        }
    }

    return GPIO_TRUE;
}

// Static private functions implementation

static void sos_point(volatile gpio_uint8_t *port,
                      gpio_uint8_t pin)
{
    led_power_on(port, pin);
    sos_delay_point(GPIO_NULL);

    led_power_off(port, pin);
    sos_delay_pause(GPIO_NULL);
}

static void sos_line(volatile gpio_uint8_t *port,
                     gpio_uint8_t pin)
{
    led_power_on(port, pin);
    sos_delay_line(GPIO_NULL);

    led_power_off(port, pin);
    sos_delay_pause(GPIO_NULL);
}

static gpio_uint8_t sos_stop_is_requested(
    volatile gpio_uint8_t *interrupt_request)
{
    if (interrupt_request == GPIO_NULL)
    {
        return GPIO_FALSE;
    }

    if (*interrupt_request == GPIO_TRUE)
    {
        /*
        Cererea este consumata aici, astfel incat apasarea care opreste
        mesajul curent sa nu porneasca imediat un mesaj nou in main.
        */
        *interrupt_request = GPIO_FALSE;
        return GPIO_TRUE;
    }

    return GPIO_FALSE;
}

static void sos_delay_point(
    volatile gpio_uint8_t *interrupt_request)
{
    volatile unsigned long i;

    for (i = 0; i < 30000UL; i++)
    {
        if ((interrupt_request != GPIO_NULL) &&
            (*interrupt_request == GPIO_TRUE))
        {
            break;
        }
    }
}

static void sos_delay_line(
    volatile gpio_uint8_t *interrupt_request)
{
    volatile unsigned long i;

    for (i = 0; i < 120000UL; i++)
    {
        if ((interrupt_request != GPIO_NULL) &&
            (*interrupt_request == GPIO_TRUE))
        {
            break;
        }
    }
}

static void sos_delay_pause(
    volatile gpio_uint8_t *interrupt_request)
{
    volatile unsigned long i;

    for (i = 0; i < 30000UL; i++)
    {
        if ((interrupt_request != GPIO_NULL) &&
            (*interrupt_request == GPIO_TRUE))
        {
            break;
        }
    }
}

#endif