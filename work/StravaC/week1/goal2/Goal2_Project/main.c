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

void wait_button_release(void)
{
    while (gpio_read_pin_debounced(&PINC, 6) == GPIO_LOW)
    {

    }
}

void main(void)
{
    gpio_uint8_t sos_enabled;
    gpio_uint8_t button_state;

    sos_enabled = GPIO_FALSE;

    gpio_set_direction(&DDRC, 6, GPIO_INPUT);
    gpio_set_direction(&DDRC, 7, GPIO_OUTPUT);

    gpio_activate_pullup(&PORTC, 6);
    led_power_off(&PORTC, 7);

    while (1)
    {
        if (sos_enabled == GPIO_FALSE)
        {
            button_state = gpio_read_pin_debounced(&PINC, 6);

            if (button_state == GPIO_LOW)
            {
                sos_enabled = GPIO_TRUE;
                wait_button_release();
            }
        }
        else
        {
            sos_enabled = sos_play_interruptible(&PORTC, 7, &PINC, 6);

            if (sos_enabled == GPIO_TRUE)
            {
                delay_between_sos();
            }
        }
    }
}