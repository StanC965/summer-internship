#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "tc1.h"
#include "scheduler.h"
#include <intrinsics.h>

void main(void)
{
    gpio_set_direction(&DDRC, 7, 1);
    led_off(&PORTC, 7);

    tc1_systick_init();
    __enable_interrupt();

    schedule_tasks_dispatcher();   
}