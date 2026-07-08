#line 1 "C:\\MQ_Summer_Internship\\summer-internship\\Week 1\\Goal2\\sos.c"



#line 1 "C:\\MQ_Summer_Internship\\summer-internship\\Week 1\\Goal2\\sos.h"



extern void Morse_Point(volatile unsigned char *port, unsigned char pin);

extern void Morse_Line(volatile unsigned char *port, unsigned char pin);

extern void SOS_Sequence(volatile unsigned char *port, unsigned char pin);

#line 5 "C:\\MQ_Summer_Internship\\summer-internship\\Week 1\\Goal2\\sos.c"
#line 1 "C:\\MQ_Summer_Internship\\summer-internship\\Week 1\\Goal2\\led.h"



extern void Init_LED(volatile unsigned char *ddr, unsigned char pin, unsigned char direction);

extern void PowerOn_LED(volatile unsigned char *port, unsigned char pin);

extern void PowerOff_LED(volatile unsigned char *port, unsigned char pin);

extern void Toggle_LED(volatile unsigned char *port, unsigned char pin);

extern void BlinkSlow_LED(volatile unsigned char *port, unsigned char pin);

extern void BlinkFast_LED(volatile unsigned char *port, unsigned char pin);

#line 6 "C:\\MQ_Summer_Internship\\summer-internship\\Week 1\\Goal2\\sos.c"

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
    
    delay(3);

    Linie(port, pin);
    Linie(port, pin);
    Linie(port, pin);
    
    delay(3);

    Punct(port, pin);
    Punct(port, pin);
    Punct(port, pin);
    
    delay(8); 
}

