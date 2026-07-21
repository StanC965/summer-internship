#include "tc1.h"
#include "scheduler.h"
#include <intrinsics.h>

void main(void)
{
    tc1_systick_init();
    __enable_interrupt();
    while (1) {}
}