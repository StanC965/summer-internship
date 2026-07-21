#ifndef TC0_H
#define TC0_H

/*
Autor: Strava Cosmin-Paul
Data: 2026

Driver TC0 pentru CTC Mode.

TCNT0 numara de la 0 pana la OCR0A.
La compare match:
- TCNT0 este resetat;
- poate fi comutat automat pinul OC0A;
- poate fi generata intreruperea Compare Match A.
*/

#define TC0_FALSE                    (0U)
#define TC0_TRUE                     (1U)

typedef unsigned char tc0_uint8_t;

typedef void (*tc0_callback_t)(void);

extern void tc0_init(
    tc0_uint8_t tc0_top_value,
    tc0_uint8_t tc0_toggle_oc0a,
    tc0_callback_t tc0_callback
);

extern void tc0_start_prescaler_1(void);
extern void tc0_start_prescaler_8(void);
extern void tc0_start_prescaler_64(void);
extern void tc0_start_prescaler_256(void);
extern void tc0_start_prescaler_1024(void);

extern void tc0_stop(void);

#endif