#ifndef SCHEDULER_H
#define SCHEDULER_H

extern volatile unsigned char flag_10ms;
extern volatile unsigned char flag_50ms;
extern volatile unsigned char flag_100ms;
extern volatile unsigned char flag_500ms;
extern volatile unsigned char flag_1000ms;
void schedule_tasks_dispatcher(void);

void task_50ms(void);
void task_100ms(void);
void task_500ms(void);
void task_1000ms(void);
void scheduler_flags_management(void);

#endif