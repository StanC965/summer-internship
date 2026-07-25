#include "iom324pb.h"
#include <intrinsics.h>
#include "gpio.h"
#include "led.h"
#include "timer.h"
#include "scheduler.h"

void main(void)
{
    gpio_init();
    led_init(LED0_DDR, LED0_PIN);     

    timer_systick_init();       
    scheduler_init();
    __enable_interrupt();

    while(1)
    {
        if (scheduler_flag_500ms())
        {
            led_toggle(LED0_PORT, LED0_PIN);   
        }
    }
}
