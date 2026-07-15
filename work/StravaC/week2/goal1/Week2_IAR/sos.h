#ifndef SOS_H
#define SOS_H

// Exported types and values

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier reprezinta interfata modulului sos.

Modulul sos contine comportamentul SOS in cod Morse.
SOS este format din 3 puncte, 3 linii si 3 puncte.

Pentru task-ul 316, oprirea secventei nu mai este realizata
prin citirea periodica a pinului SW0.

Apasarea butonului este detectata de o rutina de intrerupere,
iar modulul sos verifica doar flagul setat de ISR.
*/

#include "gpio.h"

// Public functions

extern void sos_play(volatile gpio_uint8_t *port,
                     gpio_uint8_t pin);

extern gpio_uint8_t sos_play_interruptible(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin,
    volatile gpio_uint8_t *interrupt_request);

#endif