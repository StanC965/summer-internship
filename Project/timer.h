/**
 * @file timer.h
 * @brief Header file for Timer hardware module management[cite: 20].
 * @details Provides interface definitions and constants for Timer0, Timer1, and Timer3 operation modes[cite: 20].
 */

#ifndef TIMER_H
#define TIMER_H

#include <iom324pb.h>

/** @name Timer0 Control Bit Definitions */
/**@{*/
#define TIMER_T0_STOPPED             0x00  
#define TIMER_T0_NO_PRESCALE         0x01  

#define TIMER_T0_A_COMP_INT          1
#define TIMER_T0_OVERFLOW_INT        0    

#define TIMER_T0_CTC_MODE            1
#define TIMER_T0_TOGGLE_OC0A         6
/**@}*/

/** @name Timer1 Control Bit Definitions */
/**@{*/
#define TIMER_T1_CAPT_INT            5

#define TIMER_ICNC1                  7   
#define TIMER_ICES1                  6   
#define TIMER_ICIE1                  5   
#define TIMER_ICF1                   3
/**@}*/

/**
 * @brief Initializes the Timer module by configuring Timer0 in Normal Mode and setting default interrupts[cite: 20].
 */
void timer_init(void);

/**
 * @brief Initializes Timer0 in Clear Timer on Compare Match (CTC) mode[cite: 20].
 * @param compare_value Ceiling target value (OCR0A) to trigger compare match interrupts[cite: 20].
 */
void timer_init_ctc_t0(unsigned char compare_value);

/**
 * @brief Starts Timer0 with a specified prescaler division factor[cite: 20].
 * @param division_value Physical clock divider ratio (1, 8, 64, 256, or 1024)[cite: 20].
 */
void timer_start_t0(unsigned int division_value);

/**
 * @brief Stops Timer0 by disconnecting its clock source[cite: 20].
 */
void timer_stop_t0(void);

/**
 * @brief Starts Timer1 with a specified prescaler division factor[cite: 20].
 * @param division_value Physical clock divider ratio (1, 8, 64, 256, or 1024)[cite: 20].
 */
void timer_start_t1(unsigned int division_value);

/**
 * @brief Stops Timer1 by disconnecting its clock source[cite: 20].
 */
void timer_stop_t1(void);

/**
 * @brief Initializes Timer1 for Input Capture Unit (ICU) operation on falling edges[cite: 20].
 */
void timer_t1_init_icu(void);

/**
 * @brief Initializes Timer3 in CTC Mode with a prescaler of 8 to generate precise 10ms System Ticks[cite: 20].
 */
void timer_t3_init_system_tick(void);

#endif