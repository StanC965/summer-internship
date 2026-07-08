#ifndef SOS_C
#define SOS_C

#include "sos.h"
#include "led.h"

static void delay(int numar) {
    for(int u = 0; u < numar; u++) {
        for(long i = 0; i < 90000; i++); 
    }
}

void Punct(volatile unsigned char *port, unsigned char pin) {
    PowerOn_LED(port, pin);
    delay(2);
    PowerOff_LED(port, pin);
    delay(2);
}

void Linie(volatile unsigned char *port, unsigned char pin) {
    PowerOn_LED(port, pin);
    delay(4);
    PowerOff_LED(port, pin);
    delay(2);
}

void SOS(volatile unsigned char *port, unsigned char pin) {
    Punct(port, pin);
    Punct(port, pin);
    Punct(port, pin);
    
    delay(2);

    Linie(port, pin);
    Linie(port, pin);
    Linie(port, pin);
    
    delay(2);

    Punct(port, pin);
    Punct(port, pin);
    Punct(port, pin);
    
    delay(6); 
}

#endif