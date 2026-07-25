#include "iom324pb.h"
#include <intrinsics.h>
#include "gpio.h"
#include "led.h"
#include "timer.h"
#include "CarCrashDetection.h"

#define AIRBAG_DELAY_TOP    (87U)   /* (87+1)*8us = 704us, inside [650us, 800us] with prescaler 8 */

#define AIRBAG_PORT         LED0_PORT
#define AIRBAG_PIN          LED0_PIN
#define NOTIFY_PORT         LED4_PORT   
#define NOTIFY_PIN          LED4_PIN

#pragma vector=TIMER0_COMPA_vect
__interrupt void airbag_isr(void)
{
    timer_stop();                             
    led_power_on(AIRBAG_PORT, AIRBAG_PIN);    
}

void main( void )
{
    unsigned char armed = 1;

    gpio_init();
    led_init(LED0_DDR, LED0_PIN);
    led_init(LED4_DDR, LED4_PIN);
    led_power_off(AIRBAG_PORT, AIRBAG_PIN);
    led_power_off(NOTIFY_PORT, NOTIFY_PIN);

    timer_init_ctc(AIRBAG_DELAY_TOP);
    __enable_interrupt();

    while(1)
    {
        if (armed && (GetCarCrashDetectionStatus() == CRASH))
        {
            armed = 0;
            led_power_on(NOTIFY_PORT, NOTIFY_PIN);   
            timer_start(TIMER_PRESCALER_8);          
        }
    }
}
