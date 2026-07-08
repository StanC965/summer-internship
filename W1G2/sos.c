#ifndef SOS_C
#define SOS_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* include private types and definitions for the module mod */
#include "led.h"
#include "gpio.h"
#include "iom324pb.h"  

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Implementation      */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


static void morse_delay_units(float units)
{
    // 1 unitate = 0 .2 secunde
    gpio_Timer1_start(0.2 * units, 1024);
    
     
    while(TCNT1 < OCR1A);
    
    gpio_Timer1_stop();
}


static void morse_point(void)
{
    led_Set(LED_ZERO);
    morse_delay_units(1);    
    led_Reset(LED_ZERO);
    morse_delay_units(1);    
}


static void morse_line(void)
{
    led_Set(LED_ZERO);
    morse_delay_units(3);    
    led_Reset(LED_ZERO);
    morse_delay_units(2);    // Pauza intre elemente
}



void letter_S(void)
{
    morse_point();
    morse_point();
    morse_point();
 
    morse_delay_units(2); 
}

void letter_O(void)
{
    morse_line();
    morse_line();
      morse_line();
  
    morse_delay_units(2);
}

void SOS(void)
{
    letter_S();
    letter_O();
    letter_S();
    
    morse_delay_units(4); 
}
#endif