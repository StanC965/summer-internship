#ifndef SOS_H
#define SOS_H

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier reprezinta interfata modulului sos.

Modulul sos contine comportamentul SOS in cod Morse.
SOS este format din trei puncte, trei linii si trei puncte.

Pentru versiunea bazata pe intreruperi,
modulul nu mai citeste direct butonul SW0.

Apasarea butonului este detectata de ISR,
iar modulul SOS verifica flagul setat de aceasta.

Conventie de numire:
Toate functiile si variabilele acestui modul folosesc prefixul sos_.
*/

#include "gpio.h"

/* Public functions */

extern void sos_play(
    volatile gpio_uint8_t *sos_led_port,
    gpio_uint8_t sos_led_pin
);

extern gpio_uint8_t sos_play_interruptible(
    volatile gpio_uint8_t *sos_led_port,
    gpio_uint8_t sos_led_pin,
    volatile gpio_uint8_t *sos_interrupt_request
);

#endif