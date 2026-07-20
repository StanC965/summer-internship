/* 215 - turn on LED0 (connected to PC7, active low) */
#include "iom324pb.h"

void main( void )
{
  /*PC7 as output */
    DDRC_DDRC7 = 1;

    /*turn LED0 ON*/
    PORTC_PORTC7 = 0;
    
    while(1)
    {
      
    }
}