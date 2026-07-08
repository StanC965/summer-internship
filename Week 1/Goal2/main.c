//255
#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "sos.h"

void setup(void) {
    Init_LED(&DDRC, 7, 1);
    PowerOff_LED(&PORTC, 7);
}

void main(void) {
    setup();
    
    while(1) {
        SOS(&PORTC, 7);
    }
}