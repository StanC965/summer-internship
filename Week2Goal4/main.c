#include "iom324pb.h"
#include <intrinsics.h>
#include "gpio.h"
#include "led.h"
#include "timer.h"

#define TIMER_CTC_TOP   (127U)

#pragma vector=TIMER0_COMPA_vect
__interrupt void timer0_compa_isr(void)
{
    led_toggle(LED0_PORT, LED0_PIN);
}

void main( void )
{
    gpio_init();
    led_init(LED0_DDR, LED0_PIN);
    led_power_off(LED0_PORT, LED0_PIN);

    timer_init_ctc(TIMER_CTC_TOP);
    __enable_interrupt();
    timer_start(TIMER_PRESCALER_1024);

    while(1)
    {
    }
}
