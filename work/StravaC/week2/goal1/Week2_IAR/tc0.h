#ifndef TC0_H
#define TC0_H

/*
Autor: Strava Cosmin-Paul
Data: 2026

Interfata modulului Timer/Counter0.

Configuratie:
- Normal Mode;
- sistem clock = 1 MHz;
- prescaler = 64;
- interrupt la overflow;
- eveniment periodic dupa 61 overflow-uri.
*/

#define TC0_FALSE                       (0U)
#define TC0_TRUE                        (1U)

#define TC0_PERIOD_NOT_ELAPSED          (TC0_FALSE)
#define TC0_PERIOD_ELAPSED              (TC0_TRUE)

typedef unsigned char tc0_uint8_t;

/* Module initialization */

extern void tc0_init(void);

/* Atomic actions */

extern void tc0_start(void);

extern void tc0_stop(void);

extern tc0_uint8_t tc0_is_period_elapsed(void);

extern void tc0_clear_period_status(void);

#endif