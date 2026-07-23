#include "pwm.h"


void PWM_Init(void)
{
    DDRD |= 0x20;
   TCCR1A = 0x83;
    OCR1A = 512;
    TCNT1 = 0x0000;
    PWM_TC1_SetDutyCycle(512);
    TCCR1B = 0x0b;
}
void PWM_TC1_SetDutyCycle(unsigned int duty)
{
    
    if (duty > 1023) 
    {
        duty = 1023;
    }
    OCR1A = duty; 
}
void PWM_SetPresetDutyCycle(PWM_DutyCycle_t duty_case)
{
    switch (duty_case)
    {
        case PWM_DUTY_100_PERCENT:
            PWM_TC1_SetDutyCycle(1023); 
            break;

        case PWM_DUTY_75_PERCENT:
            PWM_TC1_SetDutyCycle(767);  
            break;

        case PWM_DUTY_50_PERCENT:
            PWM_TC1_SetDutyCycle(512);  
            break;

        case PWM_DUTY_25_PERCENT:
            PWM_TC1_SetDutyCycle(256);  
            break;

        case PWM_DUTY_0_PERCENT:
        default:
            PWM_TC1_SetDutyCycle(0);    
            break;
    }
}