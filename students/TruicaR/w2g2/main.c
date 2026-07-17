#include "iom324pb.h"
#include "tc0.h"
#include "gpio.h"
#include "led.h"
#include <intrinsics.h>

#define LED0_PIN 7
#define OVERFLOWS_PER_TOGGLE 4

static volatile unsigned int overflow_count = 0;
static unsigned char led0_state = 0;

#pragma vector = TIMER0_OVF_vect
__interrupt void tc0_ovf_isr(void)
{
    overflow_count++;
    if (overflow_count >= OVERFLOWS_PER_TOGGLE)
    {
        overflow_count = 0;
        led0_state = !led0_state;
        if (led0_state) 
          led_on(&PORTC, LED0_PIN); 
        else 
          led_off(&PORTC, LED0_PIN);
    }
}

void main(void)
{
    gpio_set_direction(&DDRC, LED0_PIN, 1);
    led_off(&PORTC, LED0_PIN);

    TCCR0A_WGM01 = 0;
    TCCR0A_WGM00 = 0;
    TCCR0B_WGM02 = 0;
    TIMSK0_TOIE0 = 1;
    TCCR0B_CS02 = 1;
    TCCR0B_CS01 = 0;
    TCCR0B_CS00 = 1;    

    __enable_interrupt();
    while (1) {}
}