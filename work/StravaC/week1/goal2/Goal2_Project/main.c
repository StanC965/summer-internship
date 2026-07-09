#include "iom324pb.h"
#include "gpio.h"
#include "led.h"

/*
244:
Constructiile de forma #ifndef, #define si #endif se numesc include guards.

Rolul lor este sa protejeze fisierul header ca sa nu fie inclus de mai multe ori
in acelasi fisier sursa.

Daca gpio.h este inclus o singura data, continutul lui este preluat normal
de preprocesor.

Daca gpio.h este inclus de doua ori si are include guards,
continutul lui apare doar o singura data in fisierul .i generat de preprocesor.

Daca gpio.h este inclus de doua ori si nu are include guards,
continutul lui apare de doua ori in fisierul .i.

Asta poate produce probleme precum redefiniri de tipuri, redefiniri de constante
sau declaratii duplicate.

De aceea folosim include guards in fisierele .h.
Ele fac codul mai sigur si permit includerea aceluiasi header din mai multe locuri
fara erori de compilare.
*/

void main(void)
{
    gpio_set_direction(&DDRC, 7, GPIO_OUTPUT);

    while (1)
    {
      led_blink_slow(&PORTC, 7);
    }
}