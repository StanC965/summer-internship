/* 231 - set_pin - write 1 any pin of PORTC */

#include "iom324pb.h"

#define DELAY_HALF_SECOND 15000UL

void delay(void)
{
    volatile unsigned long i;
    for (i = 0; i < DELAY_HALF_SECOND; i++) { }
}

void set_pin(unsigned char pin)
{
    PORTC |= (1 << pin);
}

void main( void )
{   /* i need to use a led connected to PORTC, LED0 on the main board is on PC7, but it is ACTIVE LOW
      that means set_pin it will turn it off */
    DDRC |= (1 << 7);      /* PC7 (LED0) */

    while(1)
    {
        set_pin(7);        
        delay();
    }
}
