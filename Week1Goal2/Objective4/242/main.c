/* 242 - main module: uses the led module */

#include "gpio.h"
#include "led.h"

#define DELAY_HALF_SECOND 15000UL

void delay(void)
{
    volatile unsigned long i;
    for (i = 0; i < DELAY_HALF_SECOND; i++) { }
}

void main( void )
{
    led_init();

    while(1)
    {
        led_power_on();
        delay();
        led_power_off();
        delay();
    }
}
