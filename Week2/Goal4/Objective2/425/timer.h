#ifndef TIMER_H
#define TIMER_H

#include <iom324pb.h>

#define TIMER_T0_STOPPED             0x00  
#define TIMER_T0_NO_PRESCALE         0x01  

#define TIMER_TO_OVERFLOW_INT        0    

/** \fn     void timer_init(void)
    \brief  Initializes the Timer module. Configures Timer0 in Normal Mode
            and prepares interrupts, leaving the clock in a stopped state.
*/
void timer_init(void);

/** \fn     void timer_start_t0(unsigned int division_value)
    \brief  Starts Timer0 with the specified clock division factor.
            If the value is invalid, it falls back to no prescaling (1).
    \param  division_value The physical clock divider (1, 8, 64, 256, or 1024).
*/
void timer_start_t0(unsigned int division_value);

/** \fn     void timer_stop_t0(void)
    \brief  Stops Timer0 by disconnecting its clock source.
*/
void timer_stop_t0(void);

#endif