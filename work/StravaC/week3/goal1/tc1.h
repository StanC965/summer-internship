#ifndef TC1_H
#define TC1_H

/*
Autor: Strava Cosmin-Paul
Data: 2026

Timer/Counter1 dedicat system tick-ului schedulerului.

Configuratie:
- fCPU = 16 MHz;
- CTC Mode;
- prescaler = 8;
- OCR1A = 19999;
- interrupt periodic la fiecare 10 ms.
*/

extern void tc1_init(void);

extern void tc1_start(void);

extern void tc1_stop(void);

#endif