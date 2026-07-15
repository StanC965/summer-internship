/* 253 - same behavior as 252, but using the extended gpio module */
#include "gpio.h"
#include "led.h"

#define SW0_PIN 6

void main( void )
{
    /* button init */
    gpio_set_direction(SW0_PIN, GPIO_INPUT);
    gpio_enable_pullup(SW0_PIN);

    /* led init */
    led_init();
    led_power_off();

    while(1)
    {
        if (gpio_read_pin(SW0_PIN) == GPIO_LOW)   /* LOW means button pressed */
        {
            led_power_on();
        }
        else
        {
            led_power_off();
        }
    }
}
