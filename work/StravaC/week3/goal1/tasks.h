#ifndef TASKS_H
#define TASKS_H

/*
Autor: Strava Cosmin-Paul
Data: 2026

Interfata taskurilor aplicatiei.

Schedulerul lucreaza numai cu functii generice:
- task_10ms();
- task_50ms();
- task_100ms();
- task_500ms();
- task_1000ms();

Functionalitatea concreta a aplicatiei este amplasata
in interiorul acestor taskuri.
*/

extern void tasks_init(void);

extern void task_10ms(void);
extern void task_50ms(void);
extern void task_100ms(void);
extern void task_500ms(void);
extern void task_1000ms(void);

#endif