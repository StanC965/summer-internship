#include <iom324pb.h>

/*
 * Explicatie expansiune macro-uri (task 164):
 *
 * SFR_B_N(0x08,PORTC,PORTC7,...,PORTC0)
 * -> defineste o variabila "PORTC" de tip union, mapata la adresa 0x08,
 *    cu biti individuali accesibili ca PORTC.PORTC7 ... PORTC.PORTC0
 *
 * SFR_B_N(0x07, DDRC, DDRC7,...,DDRC0)
 * -> variabila "DDRC" mapata la adresa 0x07 (Data Direction Register pentru portul C)
 *
 * SFR_B_N(0x06, PINC, PINC7,...,PINC0)
 * -> variabila "PINC" mapata la adresa 0x06 (citire valori pini portul C)
 */

void main(void)
{
    while(1)
    {
    }
}