#include "iom324pb.h"
#include "gpio.h"

/*
241:
Codul a fost reorganizat modular.

Am creat doua fisiere noi:
gpio.c si gpio.h.

Fisierul gpio.h este interfata modulului gpio.
Aici sunt declarate tipurile, constantele si functiile publice.

Fisierul gpio.c contine implementarea functiilor din modulul gpio.

Modulul gpio contine doar functii de baza pentru lucrul cu pini si porturi:
set pin, reset pin, toggle pin si set direction.

main.c ramane modulul central al aplicatiei.
El nu mai contine detalii despre cum se modifica bitii din registre,
ci doar foloseste functiile oferite de modulul gpio.

Organizarea modulara este importanta deoarece face codul mai clar,
mai usor de inteles, mai usor de testat si mai usor de modificat.

Daca in viitor vrem sa schimbam modul in care controlam pinii,
modificam doar modulul gpio, fara sa rescriem toata aplicatia.
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
    gpio_set_direction(&DDRC, 7, GPIO_OUTPUT);

    gpio_set_pin(&PORTC, 7);

    while (1)
    {
        gpio_toggle_pin(&PORTC, 7);
        delay_half_second();
    }
}