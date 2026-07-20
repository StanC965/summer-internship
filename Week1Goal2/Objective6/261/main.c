/* 261 - SOS signal on LED0 */

#include "led.h"
#include "sos.h"

void main( void )
{
    led_init();
    led_power_off();

    while(1)
    {
        sos_signal();
    }
}
