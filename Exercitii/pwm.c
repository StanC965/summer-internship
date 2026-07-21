#ifndef PWM_C
#define PWM_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"
#include "iom324pb.h" 
#include "pwm.h"

static volatile short sequence[5] = {0, 64, 128, 192, 255};
static volatile unsigned char index = 0;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Implementation                                                           */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#pragma vector=TIMER1_COMPA_vect
__interrupt void ONE_SECOND()
{
    index++;
    if(index > 4)
        index = 0;
    
    OCR0A = sequence[index]; 
}

void pwm_init_LED()
{
  
    gpio_set_direction(&DDRB, 3, 0); //output
  

    gpio_set_pin(&TCCR0A, 7); // COM0A1 = 1
  
    gpio_set_pin(&TCCR0A, 0);// (Fast PWM)
    gpio_set_pin(&TCCR0A, 1); 
    TCCR0B = 0;
  
 
    gpio_set_pin(&TCCR0B, 1); //64
    gpio_set_pin(&TCCR0B, 0); 
}

void pwm_test_led()
{
    pwm_init_LED();
    
    
    gpio_Timer1_start(1.0f, 64);
    
 //   gpio_set_pin(&TIMSK1, 1); 
    gpio_set_pin(&SREG, 7);   
    
    OCR0A = sequence[0];       
}

void pwm_dc(int param)
{
  
if(param < 0) param = 0;
    if(param > 100) param = 100;
    
    
    OCR0A = (unsigned char)((param * 255) / 100);
}


#endif