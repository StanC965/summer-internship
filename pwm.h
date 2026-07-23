#include <iom324pb.h>

#pragma once
typedef enum {
    PWM_DUTY_0_PERCENT   = 0,
    PWM_DUTY_25_PERCENT  = 25,
    PWM_DUTY_50_PERCENT  = 50,
    PWM_DUTY_75_PERCENT  = 75,
    PWM_DUTY_100_PERCENT = 100
} PWM_DutyCycle_t;

void PWM_Init(void);
void PWM_TC1_SetDutyCycle(unsigned int duty);
void PWM_SetPresetDutyCycle(PWM_DutyCycle_t duty_case);