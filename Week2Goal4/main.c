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

    led_init(LED4_DDR, LED4_PIN);           
    led_init(LED0_DDR, LED0_PIN);
    led_power_on(LED0_PORT, LED0_PIN);      

    timer_init_ctc(TIMER_CTC_TOP);
    timer_ctc_enable_oc0a_toggle();
    __enable_interrupt();
    timer_start(TIMER_PRESCALER_1024);

    while(1)
    {
    }
}
