#ifndef SCHEDULER_H
#define SCHEDULER_H

/*
Autor: Strava Cosmin-Paul
Data: 2026

Interfata schedulerului cooperativ.

Componente:
- flags management;
- tasks dispatcher;
- perioade construite pe baza system tick-ului de 10 ms.
*/

#define SCHEDULER_FALSE                  (0U)
#define SCHEDULER_TRUE                   (1U)

#define SCHEDULER_FLAG_NOT_ACTIVE        (SCHEDULER_FALSE)
#define SCHEDULER_FLAG_ACTIVE            (SCHEDULER_TRUE)

typedef unsigned char scheduler_uint8_t;

/* Module initialization */

extern void scheduler_init(void);

/*
Apelata la fiecare 10 ms din ISR-ul TC1.
Administreaza contoarele si flagurile.
*/

extern void scheduler_flags_management(void);

/*
Contine bucla infinita a aplicatiei si executa
taskurile ale caror flaguri sunt active.
*/

extern void scheduler_tasks_dispatcher(void);

#endif