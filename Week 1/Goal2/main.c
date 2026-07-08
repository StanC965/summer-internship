//262

#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
//sw0 pc6

void setup(void) {
    Init_LED(&DDRC,7,1);
    set_direction(&DDRC,6,0);
    set_pin(&PORTC,6);
}

void main(void) {
    setup(); 
    PowerOff_LED(&PORTC, 7);
    int buton=0;   

    while(1){
        if(read_pin(&PINC,6)==0)
          buton=1;
        
        if(buton==1){
          SOS(&PORTC,7);
          PowerOff_LED(&PORTC,7);
          for(long i=0;i<300000;i++);        
        }  
    }
} 