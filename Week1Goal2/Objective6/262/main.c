/* 262 - the SOS signal starts when SW0 is pressed */

#include "button.h"
#include "led.h"
#include "sos.h"

void main( void )
{
    button_init();
    led_init();
    led_power_off();

    /* keep asking the button state until it is pressed */
    while (button_is_pressed() == BUTTON_RELEASED)
    {
    }

    /* once pressed, the SOS signaling runs forever */
    while(1)
    {
        sos_signal();
        sos_pause();
    }
}
