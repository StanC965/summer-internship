#include "iom324pb.h"
#include "gpio.h" 
#include "led.h" 
#include "sos.h"

void setup(void)
{
    
    leds_initialize(1, 0, 0, 0, 0); 
}

void main(void)
{
    setup();

    while(1)
    {
        SOS();                                  //Cum functioneaza:Initial m-am gandit sa aleg o unitate de timp egala cu 50 milisecunde ( printr-un timer)
                       //dar dupa mi-am dat seama ca perioadele literelor sunt inegale si nu am mai fi respectat cerinta cu point and line
    }               //varianta asta ia 20% dintr-o valoare pe care io dau ca sa-si creeze unitatea de timp,pe baza careia am creat punctul si linia. 
}