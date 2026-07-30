#ifndef PWM_H
#define PWM_H

typedef unsigned char pwm_uint8_t;
typedef unsigned int pwm_uint16_t;

typedef enum
{
    PWM_CHANNEL_DAY_LED = 0,
    PWM_CHANNEL_NIGHT_LED
} pwm_channel_t;

extern void pwm_init(void);

extern void pwm_start(void);

extern void pwm_stop(void);

extern void pwm_set_duty_cycle_percent(
    pwm_channel_t channel,
    pwm_uint8_t duty_cycle_percent
);

#endif