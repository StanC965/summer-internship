#include "iom324pb.h"
#include <intrinsics.h>
#include "gpio.h"
#include "led.h"
#include "timer.h"

#define TIMER_OVF_PER_SECOND    (4U)   /* 4 x 262.144ms ~= 1.049s */

static volatile unsigned char timer_ovf_count = 0;

#pragma vector=TIMER0_OVF_vect
__interrupt void timer0_ovf_isr(void)
{
    timer_ovf_count++;

    if (timer_ovf_count >= TIMER_OVF_PER_SECOND)
    {
        timer_ovf_count = 0;
        led_toggle(LED0_PORT, LED0_PIN);
    }
}

void main( void )
{
    gpio_init();
    led_init(LED0_DDR, LED0_PIN);
    led_power_off(LED0_PORT, LED0_PIN);

    timer_init();
    __enable_interrupt();
    timer_start(TIMER_PRESCALER_1024);

    while(1)
    {
    }
}
