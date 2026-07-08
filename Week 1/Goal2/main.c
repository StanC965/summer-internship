//231
#include "iom324pb.h"

void setup(){
  DDRC=0x80;
}

void set_pin(unsigned char pin){
  PORTC=PORTC | (1<<pin);
}

void reset_pin(unsigned char pin){
  PORTC= PORTC & ~(1<<pin);
}

void main(void){
    setup();
    PORTC=0xFF; //il stingem pentru a testa daca se aprinde, adica verificam daca pinul 7 a fost resetat corect
    for(long i=0;i<200000;i++);
    reset_pin(7);
    

  while(1);
}