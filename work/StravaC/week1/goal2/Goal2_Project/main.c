#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "sos.h"

void delay_between_sos(void)
{
    volatile unsigned long i;

    for (i = 0; i < 250000UL; i++)
    {

    }
}

void main(void)
{
    gpio_uint8_t button_state;
    gpio_uint8_t sos_started;

    sos_started = GPIO_FALSE;

    gpio_set_direction(&DDRC, 6, GPIO_INPUT);
    gpio_set_direction(&DDRC, 7, GPIO_OUTPUT);

    gpio_activate_pullup(&PORTC, 6);
    led_power_off(&PORTC, 7);

    while (1)
    {
        if (sos_started == GPIO_FALSE)
        {
            button_state = gpio_read_pin_debounced(&PINC, 6);

            if (button_state == GPIO_LOW)
            {
                sos_started = GPIO_TRUE;
            }
        }
        else
        {
            sos_play(&PORTC, 7);
            delay_between_sos();
        }
    }
}