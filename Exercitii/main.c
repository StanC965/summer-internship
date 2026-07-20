#include "iom324pb.h"
#include "gpio.h" 
#include "adc.h"
#include "led.h"
#include "pwm.h"

void setup(void)
{
    
    pwm_test_led();
}
    
int counter = 0;

void main(void)
{
    setup();
    
    while(1)    
    {
        
    }
}