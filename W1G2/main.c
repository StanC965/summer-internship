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
    PORTD=0xFF;
    DDRA=0b00001000;
    PORTA=0xFF;
}

unsigned char sequence[6]={
  
  0b00010000,
   0b00010000,
   0b00100000,
      0b00100000,                               //am facut un sequence care este incrementat de fiecare data cand trec 0.5 sec
   0b00001000,
   0b00001000
};
      unsigned char i=0;
void main(void)
{
    setup();

    while(1)
    {
    
        if (TCNT1 >= OCR1A)
        {
            if(i<4)
            {
              PORTD^=sequence[i++];
            }
            else if(i>=4)
            {
              PORTA^=sequence[i++];
            }
            TCNT1 = 0;            //reset timer
            if(i==6)                    //reset sequence
              i=0;
        }
    }
}