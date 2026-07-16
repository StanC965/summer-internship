#ifndef LED_H
#define LED_H

extern void Init_LED(volatile unsigned char *ddr, unsigned char pin, unsigned char direction);

extern void PowerOn_LED(volatile unsigned char *port, unsigned char pin);

extern void PowerOff_LED(volatile unsigned char *port, unsigned char pin);

extern void Toggle_LED(volatile unsigned char *port, unsigned char pin);

extern void BlinkSlow_LED(volatile unsigned char *port, unsigned char pin);

extern void BlinkFast_LED(volatile unsigned char *port, unsigned char pin);

#endif