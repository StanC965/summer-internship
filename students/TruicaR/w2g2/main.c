#include "iom324pb.h"
#include "tc0.h"
#include <intrinsics.h>

#pragma vector = TIMER0_OVF_vect
__interrupt void tc0_ovf_isr(void)
{
    
}

void main(void)
{
    tc0_normal_init();
    __enable_interrupt();
    while (1) {}
}