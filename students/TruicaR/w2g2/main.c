#include "iom324pb.h"
#include "tc0.h"
#include "gpio.h"
#include "led.h"
#include <intrinsics.h>

#define LED0_PIN     7   
#define OC0A_PIN     3   

#pragma vector = TIMER0_COMPA_vect
__interrupt void tc0_compa_isr(void)
{
    gpio_read_pin(&PINC, LED0_PIN) ? led_off(&PORTC, LED0_PIN) : led_on(&PORTC, LED0_PIN);
}

void main(void)
{
    gpio_set_direction(&DDRC, LED0_PIN, 1);
    gpio_set_direction(&DDRB, OC0A_PIN, 1);

    led_off(&PORTC, LED0_PIN);
    led_off(&PORTB, OC0A_PIN);

    tc0_ctc_init(127);   

    __enable_interrupt();

    while (1) {}
}