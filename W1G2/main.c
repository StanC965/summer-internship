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
   
unsigned char sequenceOfThree[4][2]=
{
  {0xff,0xff},
{0xCF,0xff},
{0xEF,0},
{0xDF,0}
};
unsigned char i=0;
void main(void)
{
    setup();

    while(1)
    {
    
        if (TCNT1 >= OCR1A)
        {
           PORTD=sequenceOfThree[i][0];
           PORTA=sequenceOfThree[i++][1];
            if(i>3)
              i=0;
            
            TCNT1 = 0;            //reset timer

        }
    }
}