#ifndef SCHEDULER_CONFIG_C
#define SCHEDULER_CONFIG_C

#include "gpio.h"        
#include "iom324pb.h"  
#include "timer.h"
#include "scheduler.h"
#include "led.h"
#include "button.h"
#include "usart.h"



void task_10ms(void)
{
 
}

void task_50ms(void)
{

   
}

void task_100ms(void) {}
void task_500ms(void) {}
void task_1000ms(void) {
  USART_Transmit( 89);}

#endif