/* 241 - main module: integrates the gpio module to blink LED0 (PC7) */

#include "iom324pb.h"
#include "gpio.h"

#define LED0_PIN 7
#define DELAY_HALF_SECOND 15000UL

void delay(void)
{
    volatile unsigned long i;
    for (i = 0; i < DELAY_HALF_SECOND; i++) { }
}

void main( void )
{
    gpio_set_direction(LED0_PIN, GPIO_OUTPUT);

    while(1)
    {
        gpio_toggle_pin(LED0_PIN);   /* LED0 blinks (active low, but toggle just flips it) */
        delay();
    }
}
