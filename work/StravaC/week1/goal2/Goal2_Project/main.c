#include "iom324pb.h"
#include "gpio.h"
#include "led.h"

void delay_half_second(void)
{
    volatile unsigned long i;

    for (i = 0; i < 50000UL; i++)
    {

    }
}

void main(void)
{
    gpio_set_direction(&DDRC, 7, GPIO_OUTPUT);

    while (1)
    {
        led_power_on(&PORTC, 7);
        delay_half_second();

        led_power_off(&PORTC, 7);
        delay_half_second();
    }
}