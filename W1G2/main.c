#include "iom324pb.h"

void setup()
{
    TCNT1 = 0;
    TCCR1A = 0;           //aici alegi fie normal fie ctc 
    OCR1A = 15625;             
    TCCR1B = (1<<1) | (1<<0);  //Desi pe placuta apare 16Mhz ,initial la un prescale de 1024 imi statea 16 secunde
    DDRC = 0b10000000;         //asa ca am am impartit prescale-ul la 16 si am obtinut 64
    PORTC = 0xFF;              //acuma sta o secunda, dupa ce am configurat in TCCR1B ca sa fie 64
    DDRD=(1<<5)|(1<<4);
    PORTD=0b11001111;
    DDRA=0b00001000;
    PORTA=0xf7;
}

void main(void)
{
    setup();

    while(1)
    {
        if (TCNT1 >= OCR1A)
        {
            PORTC ^= (1<<7);      //switch bit
            TCNT1 = 0;            //reset timer
        }
    }
}