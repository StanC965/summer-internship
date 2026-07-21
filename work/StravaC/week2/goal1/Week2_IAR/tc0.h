#ifndef TC0_H
#define TC0_H

/*
Autor: Strava Cosmin-Paul
Data: 2026

Interfata modulului Timer/Counter0.

Configuratie:
- Normal Mode;
- numarare 0x00 ... 0xFF;
- clock direct din sistem;
- fara prescaler;
- interrupt la overflow.
*/

#define TC0_FALSE                 (0U)
#define TC0_TRUE                  (1U)

#define TC0_OVERFLOW_NOT_OCCURRED (TC0_FALSE)
#define TC0_OVERFLOW_OCCURRED     (TC0_TRUE)

typedef unsigned char tc0_uint8_t;

/* Module initialization */

extern void tc0_init(void);

/* Atomic actions */

extern void tc0_start(void);

extern void tc0_stop(void);

extern tc0_uint8_t tc0_is_overflow_detected(void);

extern void tc0_clear_overflow_status(void);

#endif