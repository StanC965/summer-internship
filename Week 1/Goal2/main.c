//241
#include "iom324pb.h"
#include "gpio.h"

void setup(void) {
    set_direction(&DDRC, 7, 1);
}

void main(void) {
    setup(); 
    while(1);
}