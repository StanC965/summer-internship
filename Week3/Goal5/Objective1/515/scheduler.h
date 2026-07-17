#ifndef SCHEDULER_H
#define SCHEDULER_H

extern volatile unsigned char scheduler_flag_50ms;
extern volatile unsigned char scheduler_flag_100ms;
extern volatile unsigned char scheduler_flag_500ms;
extern volatile unsigned char scheduler_flag_1000ms;

/** \fn     void scheduler_init(void)
    \brief  Initializes the scheduler module by resetting all period flags to 0.
*/
void scheduler_init(void);

/** \fn     void scheduler_flags_management(void)
    \brief  Increments internal tick counters on every 10ms tick and 
            sets the corresponding period flags. Called inside the Timer3 ISR.
*/
void scheduler_flags_management(void);

/** \fn     void scheduler_tasks_dispatcher(void)
    \brief  Centralized loop running the cooperative scheduler task checks.
*/
void scheduler_tasks_dispatcher(void);

void scheduler_task_50ms(void);
void scheduler_task_100ms(void);
void scheduler_task_500ms(void);
void scheduler_task_1000ms(void);

#endif