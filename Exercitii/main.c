#include <iom324pb.h>

#pragma vector = PCINT2_vect

/*
__interrupt void my_routine(void)
 the amazing routine for serving the interrupt caused by my button press 
{
    //din document
}
*/

__interrupt void PinChangePortC_ISR(void)
{
    
    if ( !(PINC & (1 << 6)) )  
    {
        
    }
}

void setup(void)
{
    
    DDRC  &= ~(1 << 6); 
  
    PORTC |=  (1 << 6); 
    
    
    PCICR |= (1 << 2);   //activare port c
    
    PCMSK2 |= (1 << 6); //activare pin PCINT22 apare in register summary
    
    
    __enable_interrupt();
}

int main(void)
{
    setup();
    
    while(1)
    {
        
    }
}