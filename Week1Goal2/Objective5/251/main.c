/* 251  */

#include "iom324pb.h"

#define SW0_PIN 6

void main( void )
{
    volatile unsigned char pinc_value;   
    volatile unsigned char button_pressed;

    DDRC &= ~(1 << SW0_PIN);    /* PC6 as input  */
    PORTC |= (1 << SW0_PIN);    /* enable the internal pull-up on PC6 */

    while(1)
    {
        pinc_value = PINC;                          /* read the whole PINC register */
        button_pressed = !(pinc_value & (1 << SW0_PIN));  /* 0 on the pin means pressed */
    }
}
