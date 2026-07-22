#ifndef SCHEDULER_CONFIG_C
#define SCHEDULER_CONFIG_C

#include "gpio.h"        
#include "iom324pb.h"  
#include "timer.h"
#include "scheduler.h"
#include "led.h"
#include "button.h"
#include "usart.h"



volatile const char sentence[] = "Hello World!"; 


volatile const char *ptr = sentence; 

void task_10ms(void)
{

    if (*ptr == '\0') {
        ptr = sentence; 
    }

    USART_Transmit(*ptr);
    ptr++;
}



void task_50ms(void)
{

   
}

void task_100ms(void) {}
void task_500ms(void) {}
void task_1000ms(void)
{


}

#endif