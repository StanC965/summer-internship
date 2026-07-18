#include "timer.h"
#include "led.h"
#include "button.h"
#include "CarCrashDetection.h"
#include "intrinsics.h"

volatile unsigned char airbag_deployed = 0;

#pragma vector = TIMER0_COMPA_vect
__interrupt void timer0_compare_a_isr(void)
{
    timer_stop_t0();
    
    led_power_on(LED_LED0_PORT, LED_LED0_PIN);
    
    airbag_deployed = 1;
    
}

void init_system(void)
{
    gpio_init();
    timer_init();   
    led_init();
    
    __enable_interrupt();
}

void main(void)
{
    init_system();
    
    timer_init_ctc_t0(87);
    
    timer_start_t0(8);
  
    
    while (1)
    {
        if (!airbag_deployed)
        {
            if (GetCarCrashDetectionStatus() == CRASH)
            {
                timer_start_t0(8);
                
                while (!airbag_deployed)
                {
                    
                }
            }
        }
    }
}