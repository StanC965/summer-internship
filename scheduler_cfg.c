#include "scheduler_cfg.h"


void task_10ms(void)
{
    
}

void task_50ms(void)
{
  Start_Conversion();
}

void task_100ms(void)
{
light_read();
}

void task_500ms(void)
{
 
    Toggle_Status_LED();
}
void task_1000ms(void)
{
 
    Toggle_Status_LED();
}
void Toggle_Status_LED(){
toggle_pin(&PORTC,PIN7);
}