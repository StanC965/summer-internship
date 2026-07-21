/**
 * @file scheduler_cfg.h
 * @brief Configuration interface declaring recurring task hooks for the task dispatcher[cite: 16].
 */

#ifndef SCHEDULER_CFG_H
#define SCHEDULER_CFG_H

/**
 * @brief Hook executed periodically every 50 ms[cite: 16].
 */
void scheduler_task_50ms(void);

/**
 * @brief Hook executed periodically every 100 ms[cite: 16].
 */
void scheduler_task_100ms(void);

/**
 * @brief Hook executed periodically every 500 ms[cite: 16].
 */
void scheduler_task_500ms(void);

/**
 * @brief Hook executed periodically every 1000 ms (1 second)[cite: 16].
 */
void scheduler_task_1000ms(void);

#endif