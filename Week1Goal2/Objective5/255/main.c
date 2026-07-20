/* 255 - read the SW0 button with debounce and control LED0 */

#include "button.h"
#include "led.h"

void main( void )
{
    button_init();
    led_init();
    led_power_off();

    while(1)
    {
        if (button_is_pressed() == BUTTON_PRESSED)
        {
            led_power_on();
        }
        else
        {
            led_power_off();
        }
    }
}
