#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "sos.h"

void delay_between_sos(void)
{
    volatile unsigned long i;

    for (i = 0; i < 150000UL; i++)
    {

    }
}

void main(void)
{
    gpio_set_direction(&DDRC, 7, GPIO_OUTPUT);

    led_power_off(&PORTC, 7);

    while (1)
    {
        sos_play(&PORTC, 7);
        delay_between_sos();
    }
}