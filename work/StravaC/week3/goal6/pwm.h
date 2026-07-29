#ifndef PWM_H
#define PWM_H

typedef unsigned char pwm_uint8_t;
typedef unsigned int pwm_uint16_t;

typedef enum
{
    PWM_DUTY_CYCLE_0_PERCENT = 0,
    PWM_DUTY_CYCLE_25_PERCENT,
    PWM_DUTY_CYCLE_50_PERCENT,
    PWM_DUTY_CYCLE_75_PERCENT,
    PWM_DUTY_CYCLE_100_PERCENT
} pwm_duty_cycle_t;

extern void pwm_init(void);

extern void pwm_start(void);

extern void pwm_stop(void);

extern void pwm_set_duty_cycle(
    pwm_duty_cycle_t pwm_duty_cycle
);

/*
Exercise 626 - STRETCH

Sets the LED duty cycle using a value from 0% to 100%.
The duty cycle can be changed with a 1% step size.
*/

extern void pwm_set_duty_cycle_percent(
    pwm_uint8_t pwm_duty_cycle_percent
);

#endif