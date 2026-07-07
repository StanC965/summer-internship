#include "iom324pb.h"


void toggle_pin(volatile unsigned char* reg, unsigned char pin){
    *reg ^= (1<< pin);
    
}

void main(void){

    PORTC = 0x00;
    DDRC = 0x00;
    toggle_pin(&DDRC,7);
    toggle_pin(&DDRC,7);
    while(1){}

}