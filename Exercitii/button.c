#ifndef BUTTON_C
#define BUTTON_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"       
#include "iom324pb.h"  
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Implementation      */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

static volatile unsigned char debounce_buffer = 0x1F; 
static unsigned char stable_state = 0;

void configure_SW0()
{
  
 gpio_set_direction(&PORTC,6,GPIO_INPUT);
 gpio_set_pin(&PORTC,6);

}
unsigned char button_read_sw0_safe(void)
{
    unsigned char current_sample = 0;
    

    
    if ((PINC & 0x40) == 0)
    {
        current_sample = 1; // Apasat
    }
    else
    {
        current_sample = 0; // Eliberat
    }
    

    debounce_buffer <<= 1;
    
    // 2. Adaugam noul bit
    debounce_buffer |= current_sample;
    

    debounce_buffer &= 0x1F;
    
 
    if (debounce_buffer == 0x1F)
    {
       
        stable_state = 1;
    }
    else if (debounce_buffer == 0x00)
    {
   
        stable_state = 0;
    }
    

    return stable_state;  
}

#endif