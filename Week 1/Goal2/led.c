#ifndef LED_C
#define LED_C

#include "led.h"
#include "gpio.h"

void Init_LED(volatile unsigned char *ddr, unsigned char pin,unsigned char direction) {
    set_direction(ddr, pin, direction); 
}

void PowerOn_LED(volatile unsigned char *port, unsigned char pin) {
    reset_pin(port, pin);
}

void PowerOff_LED(volatile unsigned char *port, unsigned char pin) {
    set_pin(port, pin);
}

void Toggle_LED(volatile unsigned char *port, unsigned char pin) {
    toggle_pin(port, pin);
}

#endif