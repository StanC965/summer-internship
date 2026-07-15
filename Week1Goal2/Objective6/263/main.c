/* 263 - SOS starts at the first SW0 press and stops at the second press, and so on.*/

#include "button.h"
#include "led.h"
#include "sos.h"

static void wait_for_release(void)
{
    while (button_is_pressed() == BUTTON_PRESSED)
    {
    }
}

void main( void )
{
    unsigned char sos_active = 0;    /* 0 = stopped, 1 = running */

    button_init();
    led_init();
    led_power_off();

    while(1)
    {
        if (sos_active == 0)
        {
            /* stopped: poll the button until a new press starts the SOS */
            if (button_is_pressed() == BUTTON_PRESSED)
            {
                wait_for_release();
                sos_active = 1;
            }
        }
        else
        {
            /* running: a press during the sequence stops it */
            if (sos_signal_interruptible() == SOS_STOPPED)
            {
                wait_for_release();
                led_power_off();
                sos_active = 0;
            }
            else
            {
                sos_pause();
            }
        }
    }
}
