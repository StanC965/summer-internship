#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "timer.h"
#include "scheduler.h"

void task_10ms(void);
void task_50ms(void);
void task_100ms(void);
void task_500ms(void);
void task_1000ms(void);


void setup()
{
  
    leds_initialize(1,1,1,1,0);
    led_Set(LED_ZERO);
    
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


void task_10ms(void)
{
  


  
}

void task_50ms(void)
{
    
}

void task_100ms(void)
{
    
}

void task_500ms(void)
{
   
}

void task_1000ms(void)
{
    
}