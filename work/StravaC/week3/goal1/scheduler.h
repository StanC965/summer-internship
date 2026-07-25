#ifndef SCHEDULER_H
#define SCHEDULER_H

/*
Autor: Strava Cosmin-Paul
Data: 2026

Modul pentru administrarea flagurilor schedulerului.

System tick:
- perioada de baza = 10 ms

Perioade construite:
- 10 ms;
- 50 ms;
- 100 ms;
- 500 ms;
- 1000 ms.

scheduler_flags_management() este apelata din ISR-ul TC1.
Taskurile sunt executate ulterior de dispatcher, in main.
*/

#define SCHEDULER_FALSE                  (0U)
#define SCHEDULER_TRUE                   (1U)

#define SCHEDULER_FLAG_NOT_ACTIVE        (SCHEDULER_FALSE)
#define SCHEDULER_FLAG_ACTIVE            (SCHEDULER_TRUE)

typedef unsigned char scheduler_uint8_t;

/* Module initialization */

extern void scheduler_init(void);

/*
Apelata numai din ISR-ul system tick.
*/

extern void scheduler_flags_management(void);

/* Flag state functions */

extern scheduler_uint8_t scheduler_is_10ms_flag_active(void);
extern scheduler_uint8_t scheduler_is_50ms_flag_active(void);
extern scheduler_uint8_t scheduler_is_100ms_flag_active(void);
extern scheduler_uint8_t scheduler_is_500ms_flag_active(void);
extern scheduler_uint8_t scheduler_is_1000ms_flag_active(void);

/* Flag clear functions */

extern void scheduler_clear_10ms_flag(void);
extern void scheduler_clear_50ms_flag(void);
extern void scheduler_clear_100ms_flag(void);
extern void scheduler_clear_500ms_flag(void);
extern void scheduler_clear_1000ms_flag(void);

#endif