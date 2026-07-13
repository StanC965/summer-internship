#ifndef BUTTON_C
#define BUTTON_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "button.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Implementation                                                            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void button_init(volatile unsigned char *ddr_reg, volatile unsigned char *port_reg, unsigned char pin_number)
{
    gpio_set_direction(ddr_reg, pin_number, GPIO_INPUT);    
    gpio_set_pin(port_reg, pin_number);
}

unsigned char button_is_pressed(volatile unsigned char *pin_reg, unsigned char pin_number, int *pressed_conf, int *released_conf)
{
    unsigned char result = 0;

    if (gpio_read_pin(pin_reg, pin_number) == 0)
    {
        (*pressed_conf)++;
        *released_conf = 0;
        
        if (*pressed_conf > BUTTON_DEBOUNCE_THRESHOLD)
        {
            result = 1; 
            *pressed_conf = 0;
        }
    } 
    else 
    {
        (*released_conf)++;
        *pressed_conf = 0;
        
        if (*released_conf > BUTTON_DEBOUNCE_THRESHOLD)
        {
            *released_conf = 0;
        }
    }

    return result;
}

#endif