#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "sos.h"

void main(void)
{
    set_direction(7, 1);   
    set_direction(6, 0);  
    set_pin(6);     

    while (1)
    {
        if (debounce(6))
        {
            sos();
            delay(1000000);  
        }
    }
}