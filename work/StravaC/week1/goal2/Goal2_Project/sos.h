#ifndef SOS_H
#define SOS_H

// Exported types and values

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier reprezinta interfata modulului sos.

Modulul sos contine comportamentul SOS in cod Morse.
SOS este format din 3 puncte, 3 linii si 3 puncte.
*/

#include "gpio.h"

// Public functions

extern void sos_play(volatile gpio_uint8_t *port, gpio_uint8_t pin);

#endif