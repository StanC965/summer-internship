#include "iom324pb.h"
#include "gpio.h" 
#include "led.h"
#include "pwm.h"
#include "scheduler_cfg.h"
#include "scheduler.h"
#include "button.h"


#pragma vector=TIMER1_COMPA_vect
__interrupt void Scheduler_Tick()
{
    
    scheduler_flags_management();
}

void setup(void)
{

      leds_initialize(1,0,0,0,0);
    led_Set(LED_ZERO);
 
    gpio_Timer1_start(0.01f, 64);
    

    gpio_set_pin(&TIMSK1, 1); 
    gpio_set_pin(&SREG, 7); 


}
    
void main(void)
{
 
    setup();
    

    schedule_tasks_dispatcher(); 
}


