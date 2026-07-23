#include "scheduler_cfg.h"
#include "pwm.h"

static unsigned char state_case = 0;


void task_10ms(void)
{
  switch (state_case)
        {
            case 0:
                PWM_SetPresetDutyCycle(PWM_DUTY_100_PERCENT);
                state_case = 1;
                break;
            case 1:
                PWM_SetPresetDutyCycle(PWM_DUTY_75_PERCENT);
                state_case = 2;
                break;
            case 2:
                PWM_SetPresetDutyCycle(PWM_DUTY_50_PERCENT);
                state_case = 3;
                break;
            case 3:
                PWM_SetPresetDutyCycle(PWM_DUTY_25_PERCENT);
                state_case = 4;
                break;
            case 4:
                PWM_SetPresetDutyCycle(PWM_DUTY_0_PERCENT);
                state_case = 0; 
                break;
        }
}

void task_50ms(void)
{
 
}

void task_100ms(void)
{
//unsigned int senzor_val = ADC_get_data();
//PWM_TC1_SetDutyCycle(senzor_val);
//Start_Conversion();
}
void task_500ms(void)
{
        
}
void task_1000ms(void)
{
 
    
}
void Toggle_Status_LED(){
toggle_pin(&PORTC,PIN7);
}