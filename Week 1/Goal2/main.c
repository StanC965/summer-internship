//242
#include "iom324pb.h"
#include "gpio.h"
#include "led.h"

void setup(void) {
    Init_LED(&DDRC,7,1);
}

void main(void) {
    setup(); 
    PowerOff_LED(&PORTC, 7);
    while(1){
      BlinkFast_LED(&PORTC, 7);
    }
}