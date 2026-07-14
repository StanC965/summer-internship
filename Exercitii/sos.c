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

volatile _Bool sos_stop = 0;
static void sos_morse_delay_units(float units)
{
    if (sos_stop) return;

    gpio_Timer1_start(0.2 * units, 1024);
    
    while(TCNT1 < OCR1A)
    {
        // Cautam GPIO_FALSE  pentru a detecta apasareea de oprire
        if (gpio_read_pin(&PINC, 6) == GPIO_FALSE) 
        {
            for(volatile unsigned int i = 0; i < 5000; i++);  //asta are rol de debounce,nu putem sa folosim timer-ul deoarece acela e ocupat in operatiile SOS curente
            if (gpio_read_pin(&PINC, 6) == GPIO_FALSE)
            {
                sos_stop = 1; 
                break;             
            }
        }
    }
    
    gpio_Timer1_stop();
}

static void sos_morse_point(void)
{
    if (sos_stop) return;
    led_Set(LED_ZERO);
    sos_morse_delay_units(1);    
    led_Reset(LED_ZERO);
    sos_morse_delay_units(1);    
}

static void sos_morse_line(void)
{
    if (sos_stop) return;
    led_Set(LED_ZERO);
    sos_morse_delay_units(3);    
    led_Reset(LED_ZERO);
    sos_morse_delay_units(1);    
}

void sos_letter_S(void)
{
    sos_morse_point();
    sos_morse_point(); 
    sos_morse_point(); 
    sos_morse_delay_units(2); 
}

void sos_letter_O(void)
{
    sos_morse_line(); 
    sos_morse_line(); 
    sos_morse_line(); 
    sos_morse_delay_units(2);
}

void sos_pattern(void)
{
    
    while(gpio_read_pin(&PINC, 6) == GPIO_FALSE);
    
    sos_letter_S();
    sos_letter_O(); 
    sos_letter_S(); 
    
    sos_morse_delay_units(4); 
}
#endif