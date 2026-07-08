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

void main(void)
{
    setup();

    while(1)
    {
        
      
        if (TCNT1 >= OCR1A)   //observam ca dupa o secunda led-ul se stinge =>functia mea e corecta
        {
            set_pinC(7);    
            
            
            TCCR1B = 0x00;  
            
        }
    }
}