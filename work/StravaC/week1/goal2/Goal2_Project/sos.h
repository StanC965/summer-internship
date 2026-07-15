#ifndef SOS_H
#define SOS_H

// Exported types and values

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier reprezinta interfata modulului sos.

Modulul sos contine comportamentul SOS in cod Morse.
SOS este format din 3 puncte, 3 linii si 3 puncte.

Pentru task-ul 263 am adaugat o functie care poate opri SOS-ul
daca SW0 este apasat in timpul secventei.
*/

#include "gpio.h"

// Public functions

extern void sos_play(volatile gpio_uint8_t *port, gpio_uint8_t pin);

extern gpio_uint8_t sos_play_interruptible(volatile gpio_uint8_t *led_port,
                                           gpio_uint8_t led_pin,
                                           volatile gpio_uint8_t *button_pin_register,
                                           gpio_uint8_t button_pin);

#endif