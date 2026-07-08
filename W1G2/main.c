#include "iom324pb.h"

void setup()
{
    DDRC = 0b10000000;  
    PORTC = 0;         
    
    TCNT1 = 0;
    OCR1A = 15625;     // o sec
    
    TCCR1A = 0;
    
    TCCR1B = 0x03; 
    
 
    
    
}



void set_pinC(unsigned char bit)
{
    PORTC |= (1 << bit); 
    
}


void reset_pinC(unsigned char bit)
{
    PORTC &= ~(1 << bit); 
    
}
_Bool state=1;
void main(void)
{
    setup();

    while(1)
    {
        
      
        if (TCNT1 >= OCR1A)   
        {
            set_pinC(7);    
            
            if(state)
            {
              reset_pinC(7);
            }
            else
              set_pinC(7);
            
            state=!state;
              
            TCNT1=0;
            
        }
    }
}