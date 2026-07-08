//253
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
    int pressed_confidence_level = 0;
    int released_confidence_level = 0;
    while(1){
      if(read_pin(&PINC,6) ==0){
        released_confidence_level=0;
        pressed_confidence_level++;
        if(pressed_confidence_level>200){
          PowerOn_LED(&PORTC,7);
          pressed_confidence_level=200;
        }
        
      }
      else{
        pressed_confidence_level=0;
        released_confidence_level++;
        if(released_confidence_level>200){
          PowerOff_LED(&PORTC,7);
          released_confidence_level=200;
        }
      }
    }
}