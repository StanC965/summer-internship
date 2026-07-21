#ifndef PWM_H
#define PWM_H

#include <iom324pb.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public Provided Interfaces
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void pwm_init(void)
    \brief  Initializes Timer0 in 8-bit Fast PWM Mode on OC0A (PB3),
            configures the pin direction, and leaves the clock stopped.
*/
void pwm_init(void);

/** \fn     void pwm_set_duty_cycle(unsigned char duty_percentage)
    \brief  Atomic action function that calculates and writes the appropriate 
            OCR0A value to hit 0%, 25%, 50%, 75%, or 100% duty cycles.
    \param  duty_percentage The target value (e.g., 0, 25, 50, 75, 100).
*/
void pwm_set_duty_cycle(unsigned char duty_percentage);

#endif