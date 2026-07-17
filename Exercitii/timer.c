#ifndef TIMER_C
#define TIMER_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"       
#include "iom324pb.h"  
#include "timer.h"
#include "scheduler.h"
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Implementation      */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#pragma vector=TIMER1_COMPA_vect
__interrupt void Time_interval(void)
{
   scheduler_flags_management();
}

void Timer1_ales_aprox_8Mhz(float milisecunde)
{
    gpio_set_pin(&TIMSK1, 1);
    gpio_set_pin(&SREG, 7);
    
    TCNT1 = 0;
    
    TCCR1A |= FAST_PWM_FOR_A;
    TCCR1B |= FAST_PWM_FOR_B;
    
    timer_Prescale_0_TC1(); 
    
    int sequence[5] = {1, 8, 64, 256, 1024};
    float sequence_of_OCR1A_values[5];
    float difference_of_OCR1A_values[5];
    
    
    for(int i = 0; i < 5; i++)
    {
       
        float OCR1A_value = (((milisecunde / 1000.0) * 8000000.0) / sequence[i]) - 1.0;
        
        sequence_of_OCR1A_values[i] = OCR1A_value;
        
     
        if (OCR1A_value >= 0 && OCR1A_value <= 65535.0)
        {
          
            float fraction = OCR1A_value - (long)OCR1A_value;
            
            
            if (fraction < 0) {
                fraction = -fraction;
            }
            difference_of_OCR1A_values[i] = fraction;
        }
        else
        {
            
            difference_of_OCR1A_values[i] = 999999.0;
        }
    }
    
    
    float min_diff = 999999.0;
    int index_min = 0; 
    
    for(int i = 0; i < 5; i++)
    {
        if(difference_of_OCR1A_values[i] < min_diff)
        {
            min_diff = difference_of_OCR1A_values[i];
            index_min = i;
        }
    }
    
    
    OCR1A = (unsigned int)sequence_of_OCR1A_values[index_min]; 
    
    switch(index_min)
    {
        case 0: timer_Prescale_1_TC1(); break;
        case 1: timer_Prescale_8_TC1(); break;
        case 2: timer_Prescale_64_TC1(); break;
        case 3: timer_Prescale_256_TC1(); break;
        case 4: timer_Prescale_1024_TC1(); break;
    }
}

_Bool Timer1_ales_exact_8Mhz(float milisecunde)
{
    gpio_set_pin(&TIMSK1, 1);
    gpio_set_pin(&SREG, 7);
    
    TCNT1 = 0;
    
  
    TCCR1A |= FAST_PWM_FOR_A;
    TCCR1B |= FAST_PWM_FOR_B;
  
    timer_Prescale_0_TC1(); 
    
    int sequence[5] = {1, 8, 64, 256, 1024};
   
    for(int i = 0; i < 5; i++)
    {
       
        float OCR1A_value = (((milisecunde / 1000.0) * 8000000.0) / sequence[i]) - 1; 
        
        
       
        
        if (OCR1A_value > 0 && OCR1A_value <= 65535.0 && (OCR1A_value - (long)OCR1A_value) == 0.0)
        {
            OCR1A = (unsigned int)OCR1A_value; 
            
            switch(i)
            {
                case 0: timer_Prescale_1_TC1(); break;
                case 1: timer_Prescale_8_TC1(); break;
                case 2: timer_Prescale_64_TC1(); break;
                case 3: timer_Prescale_256_TC1(); break;
                case 4: timer_Prescale_1024_TC1(); break;
            }
            return 1; 
        }
    }
    
    return 0; 
}


void timer_Prescale_1024_TC1()
{
 
    timer_Prescale_0_TC1(); 
  TCCR1B|=TCCR1B_PRESCALE_1024;
  
}

void timer_Prescale_256_TC1()
{
 
    timer_Prescale_0_TC1(); 
  TCCR1B|=TCCR1B_PRESCALE_256;
  
}

void timer_Prescale_64_TC1()
{
 
  timer_Prescale_0_TC1(); 
  TCCR1B|=TCCR1B_PRESCALE_64;
  
}

void timer_Prescale_8_TC1()
{

  timer_Prescale_0_TC1(); 
  TCCR1B|=TCCR1B_PRESCALE_8;
  
}

void timer_Prescale_1_TC1()
{
  
  timer_Prescale_0_TC1(); 
  TCCR1B|=TCCR1B_PRESCALE_1;
 
}

void timer_Prescale_0_TC1()
{
  
   TCCR1B&=~((1<<2)|(1<<1)|(1<<0));

}

void TIMER1_INIT_10ms()
{
 gpio_set_pin(&TCCR1B,1);
    gpio_set_pin(&TCCR1A,0);
    gpio_set_pin(&TCCR1A,1);
    OCR1A=1250;
    TCNT1=0;
     gpio_set_pin(&TCCR1B,4);
    gpio_set_pin(&TCCR1B,3);
     gpio_set_pin(&TIMSK1,1);
     gpio_set_pin(&SREG,7);

}
#endif