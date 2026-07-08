#include "iom324pb.h"

/*
212:
PORTC are 8 pini: PC0, PC1, PC2, PC3, PC4, PC5, PC6 si PC7.

213:
Microcontroller-ul ATmega324PB are in total 5 porturi GPIO:
PORTA, PORTB, PORTC, PORTD si PORTE.

PORTA, PORTB, PORTC si PORTD sunt porturi pe 8 biti.
PORTE este un port pe 7 biti: PE0 - PE6.

214:
Conform User Guide-ului si schematicii placii ATmega324PB Xplained Pro,
LED0 este conectat la pinul PC7, adica bitul 7 din PORTC.

Pentru a controla LED0, pinul PC7 trebuie configurat ca output folosind registrul DDRC.

LED0 este active-low, ceea ce inseamna ca se aprinde atunci cand scriem 0 logic pe PC7
si se stinge atunci cand scriem 1 logic pe PC7.
*/

void delay_1_second(void)
{
    volatile unsigned long i;

    for (i = 0; i < 100000UL; i++)
    {

    }
}

void main(void)
{
   DDRC |= (1 << 7);

    while (1)
    {
        PORTC &= ~(1 << 7);
        delay_1_second();

        PORTC |= (1 << 7);
        delay_1_second();
    }
}