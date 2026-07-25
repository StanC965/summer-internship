#include "iom324pb.h"
#include <intrinsics.h>
#include "gpio.h"
#include "led.h"
#include "timer.h"

void main(void)
{
    gpio_init();
    led_init(LED0_DDR, LED0_PIN);     

    timer_systick_init();              
    __enable_interrupt();

    while(1)
    {
    }
}
