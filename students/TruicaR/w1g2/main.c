#include "iom324pb.h"

void main(void)
{
  
    DDRD_DDRD5 = 1;
    DDRD_DDRD4 = 1;
    DDRA_DDRA3 = 1;
    while (1)
    { 
         PORTD_PORTD5=0;
         PORTD_PORTD4=0;
         PORTA_PORTA3=0;
    }
}