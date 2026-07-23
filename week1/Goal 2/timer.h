#include "button.h"
#include <iom324pb.h>

#pragma once
static volatile int i=0;
extern volatile int sec;

void PWM_TC1_Init();
void Timer1_Scheduler_Init();
void timer_init();
void change_prescale();
void prescale_init();
void change_led();
void airbag_dus(unsigned char airbag_status);
void PWM_TC1_SetDutyCycle(unsigned int duty);
