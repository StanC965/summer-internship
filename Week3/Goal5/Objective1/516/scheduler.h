#ifndef SCHEDULER_H
#define SCHEDULER_H

extern volatile unsigned char scheduler_flags;

#define SCHEDULER_BIT_50MS     0  
#define SCHEDULER_BIT_100MS    1  
#define SCHEDULER_BIT_500MS    2  
#define SCHEDULER_BIT_1000MS   3

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