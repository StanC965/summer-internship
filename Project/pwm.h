/**
 * @file pwm.h
 * @brief Header file for Pulse Width Modulation (PWM) peripheral driver[cite: 12].
 * @details Controls Timer0 Fast PWM hardware modes and duty cycle generation[cite: 11, 12].
 */

#ifndef PWM_H
#define PWM_H

#include <iom324pb.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public Provided Interfaces
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/**
 * @brief Initializes Timer0 in 8-bit Fast PWM Mode on OC0A (PB3)[cite: 11, 12].
 * @details Sets up hardware registers while leaving the timer clock stopped initially[cite: 11, 12].
 */
void pwm_init(void);

/**
 * @brief Sets the output duty cycle percentage[cite: 11, 12].
 * @param duty_percentage Target duty cycle value (0 to 100%)[cite: 11, 12].
 */
void pwm_set_duty_cycle(unsigned char duty_percentage);

/**
 * @brief Configures duty cycle resolution with 1% step sizes[cite: 11, 12].
 * @param param Target duty cycle percentage (0 to 100%)[cite: 11, 12].
 */
void pwm_dc(unsigned char param);

#endif