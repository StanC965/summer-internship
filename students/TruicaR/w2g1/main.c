#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "sos.h"
#include <intrinsics.h>

#define GPIO_INPUT   0
#define GPIO_OUTPUT  1
#define PULLUP_ON    1
#define INTERRUPT_ENABLED  1

#pragma vector = PCINT2_vect
__interrupt void pcint2_isr(void)
{
    
}
void main(void)
{
    
DDRC_DDRC6 = GPIO_INPUT;
PORTC_PORTC6 = PULLUP_ON;
PCMSK2_PCINT22 = INTERRUPT_ENABLED;
PCICR_PCIE2 = INTERRUPT_ENABLED;     

__enable_interrupt();

while(1){}
}