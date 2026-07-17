#ifndef SCHEDULER_H
#define SCHEDULER_H

extern volatile unsigned char scheduler_flags;

/** \fn     void scheduler_init(void)
    \brief  Provided interface. Resets scheduler variables and flags.
*/
void scheduler_init(void);

/** \fn     void scheduler_flags_management(void)
    \brief  Provided interface. Evaluates timing counters on every tick.
*/
void scheduler_flags_management(void);

/** \fn     void scheduler_tasks_dispatcher(void)
    \brief  Provided interface. Main processing loop executing pending tasks.
*/
void scheduler_tasks_dispatcher(void);

#endif