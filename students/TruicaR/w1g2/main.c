#include "iom324pb.h"
#include "gpio.h"
#include "led.h"

void main(void)
{
    set_direction(7, 1);   

    while (1)
    {
        PowerOn_LED(7);
        for (volatile long i = 0; i < 800000; i++);

        PowerOff_LED(7);
        for (volatile long i = 0; i < 800000; i++);
    }
}