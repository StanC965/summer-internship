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

Pentru task-ul 263, SOS-ul poate fi oprit prin apasarea butonului SW0.
Butonul este verificat dupa fiecare punct sau linie.
*/

#include "sos.h"
#include "led.h"

// Static private functions declaration

static void sos_point(volatile gpio_uint8_t *port, gpio_uint8_t pin);
static void sos_line(volatile gpio_uint8_t *port, gpio_uint8_t pin);

static gpio_uint8_t sos_button_is_pressed(volatile gpio_uint8_t *button_pin_register,
                                          gpio_uint8_t button_pin);

static void sos_wait_button_release(volatile gpio_uint8_t *button_pin_register,
                                    gpio_uint8_t button_pin);

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

gpio_uint8_t sos_play_interruptible(volatile gpio_uint8_t *led_port,
                                    gpio_uint8_t led_pin,
                                    volatile gpio_uint8_t *button_pin_register,
                                    gpio_uint8_t button_pin)
{
    sos_point(led_port, led_pin);

    if (sos_button_is_pressed(button_pin_register, button_pin) == GPIO_TRUE)
    {
        led_power_off(led_port, led_pin);
        sos_wait_button_release(button_pin_register, button_pin);
        return GPIO_FALSE;
    }

    sos_point(led_port, led_pin);

    if (sos_button_is_pressed(button_pin_register, button_pin) == GPIO_TRUE)
    {
        led_power_off(led_port, led_pin);
        sos_wait_button_release(button_pin_register, button_pin);
        return GPIO_FALSE;
    }

    sos_point(led_port, led_pin);

    if (sos_button_is_pressed(button_pin_register, button_pin) == GPIO_TRUE)
    {
        led_power_off(led_port, led_pin);
        sos_wait_button_release(button_pin_register, button_pin);
        return GPIO_FALSE;
    }

    sos_line(led_port, led_pin);

    if (sos_button_is_pressed(button_pin_register, button_pin) == GPIO_TRUE)
    {
        led_power_off(led_port, led_pin);
        sos_wait_button_release(button_pin_register, button_pin);
        return GPIO_FALSE;
    }

    sos_line(led_port, led_pin);

    if (sos_button_is_pressed(button_pin_register, button_pin) == GPIO_TRUE)
    {
        led_power_off(led_port, led_pin);
        sos_wait_button_release(button_pin_register, button_pin);
        return GPIO_FALSE;
    }

    sos_line(led_port, led_pin);

    if (sos_button_is_pressed(button_pin_register, button_pin) == GPIO_TRUE)
    {
        led_power_off(led_port, led_pin);
        sos_wait_button_release(button_pin_register, button_pin);
        return GPIO_FALSE;
    }

    sos_point(led_port, led_pin);

    if (sos_button_is_pressed(button_pin_register, button_pin) == GPIO_TRUE)
    {
        led_power_off(led_port, led_pin);
        sos_wait_button_release(button_pin_register, button_pin);
        return GPIO_FALSE;
    }

    sos_point(led_port, led_pin);

    if (sos_button_is_pressed(button_pin_register, button_pin) == GPIO_TRUE)
    {
        led_power_off(led_port, led_pin);
        sos_wait_button_release(button_pin_register, button_pin);
        return GPIO_FALSE;
    }

    sos_point(led_port, led_pin);

    if (sos_button_is_pressed(button_pin_register, button_pin) == GPIO_TRUE)
    {
        led_power_off(led_port, led_pin);
        sos_wait_button_release(button_pin_register, button_pin);
        return GPIO_FALSE;
    }

    return GPIO_TRUE;
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

static gpio_uint8_t sos_button_is_pressed(volatile gpio_uint8_t *button_pin_register,
                                          gpio_uint8_t button_pin)
{
    if (gpio_read_pin_debounced(button_pin_register, button_pin) == GPIO_LOW)
    {
        return GPIO_TRUE;
    }

    return GPIO_FALSE;
}

static void sos_wait_button_release(volatile gpio_uint8_t *button_pin_register,
                                    gpio_uint8_t button_pin)
{
    while (gpio_read_pin_debounced(button_pin_register, button_pin) == GPIO_LOW)
    {

    }
}

static void sos_delay_point(void)
{
    volatile unsigned long i;

    for (i = 0; i < 30000UL; i++)
    {

    }
}

static void sos_delay_line(void)
{
    volatile unsigned long i;

    for (i = 0; i < 120000UL; i++)
    {

    }
}

static void sos_delay_pause(void)
{
    volatile unsigned long i;

    for (i = 0; i < 30000UL; i++)
    {

    }
}

#endif