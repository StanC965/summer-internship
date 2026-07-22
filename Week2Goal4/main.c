#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "timer.h"

#define WAVE_TOP    (195U)   /* (195+1)*256us = 50.176ms per toggle -> ~100ms period */

void main( void )
{
    gpio_init();
    led_init(LED4_DDR, LED4_PIN);        

    timer_init_ctc(WAVE_TOP);
    timer_ctc_enable_oc0a_toggle();
    timer_start(TIMER_PRESCALER_256);

    while(1)
    {
    }
}
