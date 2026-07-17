#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "timer.h"
#include "scheduler.h"
#include "scheduler_cfg.h"
#include "adc.h"

#define ADC_USE_8_BIT_RESOLUTION




void setup()
{
  
    leds_initialize(1,1,1,1,0);
    led_Set(LED_ZERO);
    
    if (Timer1_ales_exact_8Mhz(10) == 1) {
   
  
      
      
    } else {
        Timer1_ales_aprox_8Mhz(10);
    }
  adc_init_LIGHT();
  adc_start_conversie();

}

int main( void )
{
setup();

  schedule_tasks_dispatcher();
    return 0;
}

