#include "iom324pb.h"
#include "gpio.h" 
#include "led.h" 



void setup(void)
{
    leds_initialize(1, 1, 1, 1, 1);
    led_Reset(LED_ZERO);
    
}

void main(void)
{
    setup();

    while(1)
    {
     led_TEST_Fast(LED_ZERO);

        
    }
}

//Explicatii: pentru a face cele doua teste cerute la 243 am facut o functie in gpio.c care seteaza un timer pe baza la cate secunde vreau sa fie o perioada 
// si pe baza la un prescale 
//dupa aceea am facut si functiile in care se activeaza acest timer si in care se numara ca aproximativ cele 12 perioade (6 on si 6 off) sa se intample intr-o secunda
//zic aproximativ deoarece OCR1A poate sa dea valori cu virgula care vor fi rotunjite,asta va induce o desincronizare si nu am implementat un mod de rezolvare a acestei desincronizari
// asa ca din cod va trebui sa calculez sa dea fara virgula.

//Pe langa asta , m-am folosit de functii de dinainte ca sa imi usurez munca cum ar fi toggle set etc...
// ca si detalii de siguranta in cod m-am asigurat ca registrii sunt mereu setati pe 0 dupa ce nu isi mai au vreo utilizare
//ex ar fi acel TCCR1B care inainte de a i se atribui vreun prescale ,ma asigur ca nu este nici un prescale deja setat 
