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

221:
Da, in schematic exista un rezistor conectat cu LED0 pentru protectie.

LED0 este D200 in schematic, iar rezistorul de protectie este R214.
Valoarea lui R214 este 330R, adica 330 ohmi.

222:
Din schematicile pentru OLED1 si IO1 se vede ca LED-urile sunt legate la VCC_TARGET
prin cate un rezistor, iar celalalt capat al LED-ului ajunge la semnalul LEDx.

Asta inseamna ca LED-urile sunt active-low:
se aprind cand pinul este configurat ca output si scriem 0 logic pe el,
si se sting cand scriem 1 logic pe el.

Pe OLED1 exista 3 LED-uri:
LED1 este conectat la pinul 7 de pe conectorul EXT.
LED2 este conectat la pinul 8 de pe conectorul EXT.
LED3 este conectat la pinul 6 de pe conectorul EXT.

223:
OLED1 trebuie sa fie conectata pe header-ul EXT1 al placii ATmega324PB Xplained Pro.

Pe EXT1, semnalele pentru cele 3 LED-uri ajung astfel:
LED3, de pe EXT pin 6, ajunge la PA3.
LED1, de pe EXT pin 7, ajunge la PD5.
LED2, de pe EXT pin 8, ajunge la PD4.

User Guide-ul pentru OLED1 confirma informatia din schematic:
LED-urile sunt active-low, deci se aprind cand scriem 0 logic pe pin.

227:
Nu a fost nevoie sa adaugam noi rezistoare externe pentru LED-uri,
deoarece acestea exista deja pe placile folosite.

LED0 de pe placa ATmega324PB Xplained Pro are deja un rezistor de protectie de 330 ohmi.

LED-urile de pe OLED1 Xplained Pro au deja rezistoare de limitare a curentului de 680 ohmi.

LED-ul de pe IO1 Xplained Pro are deja rezistor de limitare a curentului de 680 ohmi.

De aceea LED-urile functioneaza corect si in siguranta:
noi nu conectam LED-ul direct la pinul microcontroller-ului,
ci folosim circuitul deja proiectat pe placa.
*/

void delay_half_second(void)
{
    volatile unsigned long i;

    for (i = 0; i < 50000UL; i++)
    {

    }
}

void main(void)
{
    DDRA |= (1 << 3);
    DDRD |= (1 << 5);
    DDRD |= (1 << 4);

    PORTA |= (1 << 3);
    PORTD |= (1 << 5);
    PORTD |= (1 << 4);

    while (1)
    {
        PORTD &= ~(1 << 5);
        PORTD &= ~(1 << 4);
        PORTA |= (1 << 3);

        delay_half_second();

        PORTD |= (1 << 5);
        PORTD &= ~(1 << 4);
        PORTA &= ~(1 << 3);

        delay_half_second();

        PORTD &= ~(1 << 5);
        PORTD |= (1 << 4);
        PORTA &= ~(1 << 3);

        delay_half_second();
    }
}