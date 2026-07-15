#include <iom324pb.h>
#include "button.h"
#include "led.h"

#pragma vector = PCINT2_vect
__interrupt void button_press_routine(void)
{
    if (!button_read(BUTTON_ONBOARD))
    {
        led_power_on(LED_ONBOARD);
    }
    else
    {
        led_power_off(LED_ONBOARD);
    }
}
