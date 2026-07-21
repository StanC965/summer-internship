#ifndef GPIO_C
#define GPIO_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "gpio.h"
#include "iom324pb.h" 


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Implementation      */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


void gpio_set_pin(volatile unsigned char *PORT, gpio_uint8_t bit)
{
    *PORT |= (1 << bit);  
}

void gpio_reset_pin(volatile unsigned char *port, gpio_uint8_t bit)
{
    (*port) &= ~(1 << bit);                 
}

void gpio_toggle_pin(volatile unsigned char *PORT, gpio_uint8_t bit)
{
    *PORT ^= (1 << bit);              
}

void gpio_set_direction(volatile unsigned char *ddr, gpio_uint8_t bit, gpio_uint8_t intrare)
{
    if(intrare == GPIO_TRUE)
    {
        *ddr &= ~(1 << bit);                             
    }
    else                                  
    {
        *ddr |= (1 << bit);
    }
}

void gpio_Timer1_stop()
{
  TCCR1B=0;
  OCR1A=0;
  TCNT1=0;
  
}


void gpio_Timer1_start(float secunde, int prescale)
{
    unsigned char bits = 0;

    switch(prescale)
    {
        case 1:    bits = 1; break;
        case 8:    bits = 2; break;
        case 64:   bits = 3; break;
        case 256:  bits = 4; break;
        case 1024: bits = 5; break;
        default:   return;
    }


    TCCR1A = 0;
    
  
    TCCR1B = (1 << 3); 
    
 
    TCNT1 = 0;
    
    
    OCR1A = (unsigned int)((1000000 * secunde) / prescale) - 1; 

    
    TCCR1B &= ~0x07; 
    TCCR1B |= bits; 
}

  gpio_uint8_t gpio_read_pin(volatile unsigned char *PIN, gpio_uint8_t bit)
  {
    
    if ((*PIN) & (1 << bit))
    {
        return GPIO_TRUE;
    }
    return GPIO_FALSE;

  }
  
#endif