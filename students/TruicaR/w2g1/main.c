#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "sos.h"
#include <intrinsics.h>
#pragma vector = PCINT2_vect
__interrupt void pcint2_isr(void)
{
    
}
void main(void)
{
    
DDRC_DDRC6 = 0;       
PORTC_PORTC6 = 1;     

PCMSK2_PCINT22 = 1;  
PCICR_PCIE2 = 1;      

__enable_interrupt();

while(1){}
}