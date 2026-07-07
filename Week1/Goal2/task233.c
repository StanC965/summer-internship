#include "iom324pb.h"


void set_direction(volatile unsigned char* ddr, unsigned char pin,_Bool dir){
    if(dir == 0)
       *ddr &= ~(1<<pin);
    else
      *ddr |= (1<<pin);
    
}

void main(void){

    PORTC = 0x00;
    DDRC = 0x00;
    set_direction(&DDRC,7,1);
    
    while(1){}

}