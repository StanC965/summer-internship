#include "iom324pb.h"
#include "gpio.h" 
#include "led.h"
#include "pwm.h"
#include "scheduler_cfg.h"
#include "scheduler.h"
#include "button.h"

void test_bitfield_vs_bitmask(void) {

  PORTB_Bit0=1;

    PORTB |= 0x07;  
}
#pragma vector=TIMER1_COMPA_vect
__interrupt void Scheduler_Tick()
{
    
    scheduler_flags_management();
}

void setup(void)
{
    buttons_initialize(0,0,0,1);
    pwm_init_LED(); 
      leds_initialize(1,1,1,1,1);
    led_Set(LED_ZERO);
 
    gpio_Timer1_start(0.01f, 64);
    

    gpio_set_pin(&TIMSK1, 1); 
    gpio_set_pin(&SREG, 7); 
      adc_init_LIGHT();
  adc_start_conversie();

}
    
void main(void)
{
  test_bitfield_vs_bitmask();
    setup();
    

    schedule_tasks_dispatcher(); 
}


