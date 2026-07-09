/* 216 - blink LED0: 1 second ON, 1 second OFF, repeat */
#include "iom324pb.h"

#define DELAY_1_SECOND 30000UL /* found the number while testing  */

void main( void )
{
    volatile unsigned long i;     

    DDRC_DDRC7 = 1;               

    while(1)
    {
        PORTC_PORTC7 = 0;         /* LED0 ON */
        for (i = 0; i < DELAY_1_SECOND; i++) { }

        PORTC_PORTC7 = 1;         /* LED0 OFF */
        for (i = 0; i < DELAY_1_SECOND; i++) { }
    }
}