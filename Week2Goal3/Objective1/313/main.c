/* 313 */

#include "iom324pb.h"
#include "led.h"

#pragma vector=INT2_vect
__interrupt void my_routine(void)
/* the amazing routine for serving the interrupt caused by my button press */
{
    led_power_on();
}

void main( void )
{
    while(1)
    {
    }
}
