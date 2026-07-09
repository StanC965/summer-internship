#ifndef LED_C
#define LED_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "led.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Implementation                                                            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void Init_LED(volatile unsigned char *ddr_reg, unsigned char pin_number)
{
    set_direction(ddr_reg, pin_number, OUTPUT);
}

void PowerOn_LED(volatile unsigned char *port_reg, unsigned char pin_number)
{
    reset_pin(port_reg, pin_number);
}

void PowerOff_LED(volatile unsigned char *port_reg, unsigned char pin_number)
{
    set_pin(port_reg, pin_number);
}

void Toggle_LED(volatile unsigned char *port_reg, unsigned char pin_number)
{
    toggle_pin(port_reg, pin_number);
}

#endif