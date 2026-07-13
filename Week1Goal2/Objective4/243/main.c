/* 243 - test the new led blink functionalities  */

#include "gpio.h"
#include "led.h"

void main( void )
{
    led_init();

    while(1)
    {
        led_blink_slow();   
    }
}
