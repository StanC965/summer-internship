#include "iom324pb.h"

void main(void)
{
  
    DDRC_DDRC7 = 1;

    while (1)
    { 
        PORTC_PORTC7 = 0; 
        for (volatile long i = 0; i < 80000; i++);
        PORTC_PORTC7 = 1;  
        for (volatile long i = 0; i < 80000; i++);
    }
}