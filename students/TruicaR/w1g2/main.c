#include "iom324pb.h"

void main(void)
{
    DDRC_DDRC7 = 1;     // seteaza pinul PC7 ca OUTPUT
    PORTC_PORTC7 = 0;   // aprinde LED0 (activ pe LOW)

    while(1)
    {
    }
}