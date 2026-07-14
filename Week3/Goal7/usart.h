#ifndef USART_H
#define USART_H

extern void initUsart();

unsigned char receiveUsart();

extern void transmitUsartChar(unsigned char trans);

extern void transmitUsartString(unsigned char str[]);

#endif