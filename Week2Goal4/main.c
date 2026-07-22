#include "iom324pb.h"
#include <intrinsics.h>
#include "gpio.h"
#include "led.h"
#include "timer.h"

#define WAVE_TOP            (195U)   
#define HIGH_MATCHES        (14U)    
#define LOW_MATCHES         (6U)    

static volatile unsigned char match_count = 0;
static volatile unsigned char led_is_high = 1;

#pragma vector=TIMER0_COMPA_vect
__interrupt void timer0_compa_isr(void)
{
    match_count++;

    if (led_is_high && (match_count >= HIGH_MATCHES))
    {
        match_count = 0;
        led_is_high = 0;
        led_power_off(LED0_PORT, LED0_PIN);
    }
    else if (!led_is_high && (match_count >= LOW_MATCHES))
    {
        match_count = 0;
        led_is_high = 1;
        led_power_on(LED0_PORT, LED0_PIN);
    }
}

void main( void )
{
    gpio_init();
    led_init(LED0_DDR, LED0_PIN);
    led_power_on(LED0_PORT, LED0_PIN);  

    timer_init_ctc(WAVE_TOP);
    __enable_interrupt();
    timer_start(TIMER_PRESCALER_256);

    while(1)
    {
    }
}
