#include "iom324pb.h"
#include "tc0.h"

void tc0_normal_init(void)
{
    TCCR0A_WGM01 = 0;
    TCCR0A_WGM00 = 0;
    TCCR0B_WGM02 = 0;   

    TIMSK0_TOIE0 = 1;   

    TCCR0B_CS02 = 0;
    TCCR0B_CS01 = 0;
    TCCR0B_CS00 = 1;   
}