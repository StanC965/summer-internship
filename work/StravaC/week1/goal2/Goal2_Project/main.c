#include "iom324pb.h"
#include "gpio.h"
#include "led.h"

void main(void)
{
    gpio_set_direction(&DDRC, 7, GPIO_OUTPUT);

    while (1)
    {
      led_blink_slow(&PORTC, 7);
    }
}