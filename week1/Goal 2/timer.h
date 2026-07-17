#include "button.h"
#include <iom324pb.h>

#pragma once
static volatile int i=0;

#pragma vector= TIMER0_COMPA_vect 
__interrupt void led();
void timer_init();
void change_prescale();
void prescale_init();
void change_led();