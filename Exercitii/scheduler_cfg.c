#ifndef SCHEDULER_CONFIG_C
#define SCHEDULER_CONFIG_C

#include "gpio.h"        
#include "iom324pb.h"  
#include "timer.h"
#include "scheduler.h"
#include "led.h"
#include "button.h"
#include "usart.h"


volatile char sentence[20]={"SALUTARE_sii_ce_faci"};
volatile unsigned char i=0;
void task_10ms(void)
{
   unsigned char temp= sentence[i];

  USART_Transmit( temp);
  i++;
  if(i==21)
  i=0;    
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