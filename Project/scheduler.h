/**
 * @file scheduler.h
 * @brief Header file for the cooperative task scheduler module[cite: 9].
 * @details Declares flag definitions and public dispatching interfaces[cite: 9].
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

/**
 * @brief Global volatile status flags tracking pending scheduler tasks[cite: 9].
 */
extern volatile unsigned char scheduler_flags;

/**
 * @brief Resets scheduler internal variables and flag registers[cite: 9].
 */
void scheduler_init(void);

/**
 * @brief Evaluates time counters on every system tick to update task flags[cite: 9].
 * @details Call this function inside the primary system timer interrupt tick routine[cite: 9, 10].
 */
void scheduler_flags_management(void);

/**
 * @brief Main execution loop that dispatches pending scheduled tasks[cite: 9].
 * @details Executes in an infinite loop, evaluating and clearing flag bits as tasks run[cite: 9, 13].
 */
void scheduler_tasks_dispatcher(void);

#endif