#include "gpio.h"
#include "led.h"


void PowerOn_LED(unsigned char pin)
{
    reset_pin(pin);
}

void PowerOff_LED(unsigned char pin)
{
    set_pin(pin);
}