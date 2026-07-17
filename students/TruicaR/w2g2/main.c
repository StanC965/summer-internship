#include "iom324pb.h"
#include "tc0.h"
#include "gpio.h"
#include "led.h"
#include <intrinsics.h>

#define LED0_PIN               7
#define TICKS_FOR_400MS_PERIOD 200   

static volatile unsigned int tick_count = 0;

#pragma vector = TIMER0_COMPA_vect
__interrupt void tc0_compa_isr(void)
{
    tick_count++;
    if (tick_count >= TICKS_FOR_400MS_PERIOD)
    {
        tick_count = 0;
        gpio_read_pin(&PINC, LED0_PIN) ? led_off(&PORTC, LED0_PIN) : led_on(&PORTC, LED0_PIN);
    }
}

void main(void)
{
    gpio_set_direction(&DDRC, LED0_PIN, 1);
    led_off(&PORTC, LED0_PIN);

    tc0_ctc_init_interrupt_only(124);   

    __enable_interrupt();

    while (1) {}
}