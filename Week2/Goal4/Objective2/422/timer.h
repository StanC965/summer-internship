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

/** \fn     void timer_start_t0(void)
    \brief  Starts Timer0 using the pre-configured clock speed.
*/
void timer_start_t0(void);

/** \fn     void timer_stop_t0(void)
    \brief  Stops Timer0 by disconnecting its clock source.
*/
void timer_stop_t0(void);

#endif