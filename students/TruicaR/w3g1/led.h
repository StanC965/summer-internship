#ifndef LED_H
#define LED_H

void led_on(volatile unsigned char *port, unsigned char pin);
void led_off(volatile unsigned char *port, unsigned char pin);

#endif