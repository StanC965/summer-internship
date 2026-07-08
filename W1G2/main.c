#include "iom324pb.h"

void setup()
{
    TCNT1 = 0;
    TCCR1A = 0;           
    OCR1A = 62500;             
    TCCR1B = (1<<1) ;   // pentru jumate de secunda avem 0.5 * 1000000/prescale; l-am setat pe 8 deci avem 62500
    DDRC = 0b10000000;         
    PORTC = 0xFF;              
    DDRD=(1<<5)|(1<<4);
    PORTD=0xEF;  //initial pornim cu led-ul din mijloc aprins 
    DDRA=0b00001000; 
    PORTA=0xFF;
}

_Bool state=0;
   
void main(void)
{
    setup();

    while(1)
    {
    
        if (TCNT1 >= OCR1A)
        {
            if(!state)
            {
              PORTD^=0b00110000;
              PORTA^=0b00001000;
              
              
            }
            else{
               PORTD^=0b00110000;
              PORTA^=0b00001000;
            }
            state=!state;
            
            TCNT1 = 0;            //reset timer

        }
    }
}