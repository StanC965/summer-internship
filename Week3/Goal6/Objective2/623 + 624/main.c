#include "timer.h"
#include "led.h"
#include "button.h"
#include "scheduler.h"
#include "adc.h"
#include "pwm.h"
#include "intrinsics.h"

void init_system(void)
{
    gpio_init();
    led_init();
    button_init();
    pwm_init();
    scheduler_init();
            
    __enable_interrupt();
}

void main(void)
{
    init_system();
    
    timer_t3_init_system_tick();
    
    scheduler_tasks_dispatcher();
}