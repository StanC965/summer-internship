#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "timer.h"

/**
 * @brief Adds two numbers.
 *
 * @param a First number.
 * @param b Second number.
 * @return The sum of a and b.
 */


void setup()
{
  
    leds_initialize(1,0,0,0,0);
    led_Set(LED_ZERO);
    
   

    
}

int main( void )
{
setup();

    
    if (Timer1_ales_exact_8Mhz(10) ==1) {
        
    } else {
     
        Timer1_ales_aprox_8Mhz(10);
    }

    while(1)
    {
      
      
      
      
    }
    return 0;
}
