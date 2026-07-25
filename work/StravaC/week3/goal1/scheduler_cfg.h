#ifndef SCHEDULER_CFG_H
#define SCHEDULER_CFG_H

/*
Autor: Strava Cosmin-Paul
Data: 2026

Configuratia aplicatiei pentru scheduler.

Required interfaces:
taskurile apelate de scheduler.

Provided application interface:
scheduler_cfg_init().
*/

extern void scheduler_cfg_init(void);

extern void scheduler_task_10ms(void);
extern void scheduler_task_50ms(void);
extern void scheduler_task_100ms(void);
extern void scheduler_task_500ms(void);
extern void scheduler_task_1000ms(void);

#endif