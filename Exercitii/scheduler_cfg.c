#ifndef SCHEDULER_CONFIG_C
#define SCHEDULER_CONFIG_C

#include "gpio.h"        
#include "iom324pb.h"  
#include "timer.h"
#include "scheduler.h"
#include "led.h"


volatile short sequence[5] = {0, 64, 128, 192, 255};
volatile unsigned char index = 0;

void task_10ms(void)
{
   
}

void task_50ms(void)
{
   
   
}

void task_100ms(void) {}
void task_500ms(void) {}
void task_1000ms(void) {

 index++;
    if(index > 4)
        index = 0;
    
    OCR0A = sequence[index]; }

#endif