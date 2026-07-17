/* 321, 323 - code redesigned: gpio generalized to any port, module name prefixes,
   no magic numbers */

#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "button.h"

void main( void )
{
    led_init(LED0_DDR, LED0_PIN);
    led_power_off(LED0_PORT, LED0_PIN);

    button_init(SW0_DDR, SW0_PORT, SW0_PIN);

    while(1)
    {
        if (button_is_pressed(SW0_PIN_REG, SW0_PIN) == BUTTON_PRESSED)
        {
            led_power_on(LED0_PORT, LED0_PIN);
        }
        else
        {
            led_power_off(LED0_PORT, LED0_PIN);
        }
    }
}
