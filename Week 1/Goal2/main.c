//252
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
    while(1){
      if(read_pin(&PINC,6) ==0){
        PowerOn_LED(&PORTC,7);
      }
      else{
        PowerOff_LED(&PORTC,7);
      }
    }
}