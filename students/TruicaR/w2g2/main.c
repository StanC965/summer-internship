#include "panel.h"
#include <intrinsics.h>

void main(void)
{
    panel_init();
    __enable_interrupt();

    while (1)
    {
        panel_update();
    }
}