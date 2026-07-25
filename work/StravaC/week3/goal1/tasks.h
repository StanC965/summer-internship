#ifndef TASKS_H
#define TASKS_H

/*
Autor: Strava Cosmin-Paul
Data: 2026

Interfata taskurilor executate de scheduler.

Fiecare task:
- este apelat periodic de dispatcher;
- trebuie sa fie scurt;
- nu trebuie sa contina delay-uri blocante;
- trebuie sa returneze controlul catre main.
*/

extern void tasks_init(void);

extern void tasks_10ms_execute(void);
extern void tasks_50ms_execute(void);
extern void tasks_100ms_execute(void);
extern void tasks_500ms_execute(void);
extern void tasks_1000ms_execute(void);

#endif