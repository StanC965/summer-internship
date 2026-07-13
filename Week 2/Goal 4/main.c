//424
//Cand extindem timpul real maxim introducem Jitter, acesta fiind timpul pe care procesorul il rezerva pentru a termina instructiunea curenta, pentru a salva contextul curent si pentru a rezolva alte intreruperi in curs
#include "iom324.h"

#define TMIN 0.000256; // (1*256)/1M
#define TMAX 0.262144; //(1024*256)/1M 
//423
// Folosim o variabila pe care o incrementam la fiecare intrerupere, inmultind cu durata unui overflow aflam timpul real masurat


void timer0_init(void){
  TCCR0A=0b00000000; //COM0A[1:0]- no compare mode, COM0B[1:0]- normal mode operation, 0x00 , WGM0[1:0]-normal mode operation
  TIMSK0=0b00000001; //Overflow Interrupt Enable
  TCCR0B=0b00000001; //FOC0A[1:0]- normal mode, 0x00, WGM0[2], CS0[2:0]=001- no prescaling 
}

#pragma vector=TIMER0_OVF_vect
__interrupt void timer0_ovf_interrupt(void){
}
void main( void )
{
  timer0_init();
  while(1);
}
