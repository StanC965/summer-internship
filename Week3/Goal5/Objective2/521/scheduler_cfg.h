#ifndef SCHEDULER_CFG_H
#define SCHEDULER_CFG_H

/** \fn     void scheduler_task_50ms(void)
    \brief  Required hook. Executed once every 50ms.
*/
void scheduler_task_50ms(void);

/** \fn     void scheduler_task_100ms(void)
    \brief  Required hook. Executed once every 100ms.
*/
void scheduler_task_100ms(void);

/** \fn     void scheduler_task_500ms(void)
    \brief  Required hook. Executed once every 500ms.
*/
void scheduler_task_500ms(void);

/** \fn     void scheduler_task_1000ms(void)
    \brief  Required hook. Executed once every 1000ms.
*/
void scheduler_task_1000ms(void);

#endif