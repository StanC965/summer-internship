#include "iom324pb.h"
#include "gpio.h"
#include "led.h"

void main(void)
{
    unsigned char button_state;

    gpio_set_direction(&DDRC, 6, GPIO_INPUT);
    gpio_set_direction(&DDRC, 7, GPIO_OUTPUT);

    gpio_set_pin(&PORTC, 6);
    led_power_off(&PORTC, 7);

    while (1)
    {
        button_state = PINC;

        if ((button_state & (1 << 6)) == 0)
        {
            led_power_on(&PORTC, 7);
        }
        else
        {
            led_power_off(&PORTC, 7);
        }
    }
}