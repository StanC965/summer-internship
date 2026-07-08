#line 1 "C:\\MQ_Summer_Internship\\summer-internship\\Week 1\\Goal2\\led.c"



#line 1 "C:\\MQ_Summer_Internship\\summer-internship\\Week 1\\Goal2\\led.h"



extern void Init_LED(volatile unsigned char *ddr, unsigned char pin, unsigned char direction);

extern void PowerOn_LED(volatile unsigned char *port, unsigned char pin);

extern void PowerOff_LED(volatile unsigned char *port, unsigned char pin);

extern void Toggle_LED(volatile unsigned char *port, unsigned char pin);

#line 5 "C:\\MQ_Summer_Internship\\summer-internship\\Week 1\\Goal2\\led.c"
#line 1 "C:\\MQ_Summer_Internship\\summer-internship\\Week 1\\Goal2\\gpio.h"



extern void set_pin(volatile unsigned char *port, unsigned char pin);

extern void reset_pin(volatile unsigned char *port, unsigned char pin);

extern void set_direction(volatile unsigned char *ddr, unsigned char pin, unsigned char direction);

extern void toggle_pin(volatile unsigned char *port, unsigned char pin);

#line 6 "C:\\MQ_Summer_Internship\\summer-internship\\Week 1\\Goal2\\led.c"

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

