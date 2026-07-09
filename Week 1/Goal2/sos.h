#ifndef SOS_H
#define SOS_H

extern void Morse_Point(volatile unsigned char *port, unsigned char pin);

extern void Morse_Line(volatile unsigned char *port, unsigned char pin);

extern void SOS_Sequence(volatile unsigned char *port, unsigned char pin);

#endif