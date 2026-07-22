#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "timer.h"
#include "scheduler.h"
#include "scheduler_cfg.h"
#include "button.h"
#include "usart.h"



#define  DEBOUNCE        3000u
#define  BLINK_NUMBER    10



void setup()
{
  
 USART_Init(72);
    
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





