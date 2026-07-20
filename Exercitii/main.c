#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "timer.h"
#include "scheduler.h"
#include "scheduler_cfg.h"
#include "button.h"



#define  DEBOUNCE        3000u
#define  BLINK_NUMBER    10



void setup()
{
  
       leds_initialize(1, 1, 1, 1, 0);  
    
    
    led_Set(LED_ONE);
    led_Set(LED_TWO);        
    led_Set(LED_THREE);
    led_Set(LED_ZERO);leds_initialize(1,1,1,1,0);
    led_Set(LED_ZERO);
    
      buttons_initialize(1,1,1,1);
    
    
    if (Timer1_ales_exact_8Mhz(10) == 1) {
   
  
      
      
    } else {
        Timer1_ales_aprox_8Mhz(10);
    }


}

int main( void )
{
setup();

  schedule_tasks_dispatcher();
    return 0;
}





