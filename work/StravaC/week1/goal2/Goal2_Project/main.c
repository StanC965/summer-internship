#include "iom324pb.h"

void delay_half_second(void)
{
    volatile unsigned long i;

    for (i = 0; i < 50000UL; i++)
    {

    }
}

void set_pin(volatile unsigned char *port, unsigned char pin)
{
    *port |= (1 << pin);
}

void reset_pin(volatile unsigned char *port, unsigned char pin)
{
    *port &= ~(1 << pin);
}

void toggle_pin(volatile unsigned char *port, unsigned char pin)
{
    *port ^= (1 << pin);
}

void set_direction(volatile unsigned char *ddr, unsigned char pin, unsigned char direction)
{
    direction ? (*ddr |= (1 << pin)) : (*ddr &= ~(1 << pin));
}

void main(void)
{
    set_direction(&DDRC, 7, 1);
    set_direction(&DDRD, 5, 1);
    set_direction(&DDRD, 4, 1);
    set_direction(&DDRA, 3, 1);

    set_pin(&PORTC, 7);
    set_pin(&PORTD, 5);
    set_pin(&PORTD, 4);
    set_pin(&PORTA, 3);

    while (1)
    {
        toggle_pin(&PORTC, 7);
        toggle_pin(&PORTD, 5);
        toggle_pin(&PORTD, 4);
        toggle_pin(&PORTA, 3);

        delay_half_second();
    }
}