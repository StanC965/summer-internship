#include <iom324pb.h>



extern volatile unsigned char flag_task_10ms;
extern volatile unsigned char flag_task_50ms;
extern volatile unsigned char flag_task_100ms;
extern volatile unsigned char flag_task_500ms;
extern volatile unsigned char flag_task_1000ms;

#pragma vector= TIMER0_COMPA_vect 
__interrupt void flags();

void task_init();
void scheduler_flags_management();
