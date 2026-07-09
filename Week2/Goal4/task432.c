//Pinul de la OC0A este PB3
//este connectat ledul de pe I/O Xplained Pro
// ledurile nu se deschid in acelasi timp
//sunt destul de sincronizate ledul I/O Xplained Pro se aprinde putin mai repede dar e normal
//0.131 s este calculat cu 127 cu presacle de 1024
//putem sa masuram orice timp doar ca trebuie sa adaptam pentru timpul scos de acesta
#include <intrinsics.h>
#include "led.h"
#define COM0A0 6
#define WGM01 1
#define CS00 0
#define OCIE0A 1
#define PB3 3
#define PC7 7
#define led0 0
int state = 0;

#pragma vector= TIMER0_COMPA_vect
__interrupt void myInterrupt(void){

    state ^= 1;
    if(state == 1)
       ledPowerOn(led0);
    else
      ledPowerOff(led0);

    

}

void main(void){
    OCR0A = 127;
    ledInit(&DDRB,&PORTB,PB3);
    ledInit(&DDRC,&PORTC,PC7);
    setPin(&TCCR0A,COM0A0);
    setPin(&TCCR0A,WGM01);
    setPin(&TIMSK0,OCIE0A);
    setPin(&TCCR0B,CS00);
    setPin(&TCCR0B,2);
    __enable_interrupt();
    while(1){
    }

}
