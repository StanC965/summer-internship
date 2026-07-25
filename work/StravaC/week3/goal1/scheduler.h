#ifndef SCHEDULER_H
#define SCHEDULER_H

/*
Autor: Strava Cosmin-Paul
Data: 2026

Interfata publica a schedulerului cooperativ.

Provided interfaces:
- scheduler_init();
- scheduler_flags_management();
- scheduler_dispatcher();
*/

/* Module initialization */

extern void scheduler_init(void);

/*
Apelata din ISR-ul timerului la fiecare system tick de 10 ms.
*/

extern void scheduler_flags_management(void);

/*
Contine bucla infinita si apeleaza taskurile configurate.
*/

extern void scheduler_dispatcher(void);

#endif