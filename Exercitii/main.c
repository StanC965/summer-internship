#include "iom324pb.h"


#pragma vector = TIMER0_OVF_vect
__interrupt void Overflow_IR(void)
{
  //am ajuns in intrerupere
}

void setup()
{
    
    PRR0 &= ~(1 << PRR0_PRTIM0); 
    
    TCCR0A = 0;
    
    
    TCCR0B = 2; 
    

    TIMSK0 |= 1 << TIMSK0_TOIE0;
    
    TCNT0 = 0; 
    
   SREG|=1<<7; 
}

void main( void )
{
    setup();
    while(1)
    {
       
    }
}