#include "iom324pb.h"
#include "gpio.h" 
#include "adc.h"
#include "led.h"

volatile ADC_reader_8bits ADC_value = 0; 

#pragma vector = ADC_vect
__interrupt void ADC_ISR(void)
{
   
    ADC_reader_8bits hardware_value = adc_get_result();
    ADC_value = adc_adapter(hardware_value);
    leds_initialize(1,1,1,1,0);
    led_Set(LED_ZERO);
    led_Set(LED_ONE);
    led_Set(LED_TWO);
    led_Set(LED_THREE);
    
   
}

void setup(void)
{
  adc_init_LIGHT();
  gpio_set_pin(&SREG, 7);
  disable_input_buffer_for_lightSensor();
}
    
int counter=0;
void main(void)
{
    setup();
                
          gpio_Timer1_start(1,64);
    while(1)    
    {
      
      
      
      if(TCNT1>=OCR1A)
      {
        adc_start_conversie();
      
        
        
      if (ADC_value < 64) 
{
    // Interval 0 - 63
    led_Set(LED_ONE);
    led_Set(LED_TWO);
    led_Set(LED_THREE);
}
else if (ADC_value < 128) 
{
    // Interval 64 - 127
    led_Reset(LED_ONE);
    led_Set(LED_TWO);
    led_Set(LED_THREE);
}
else if (ADC_value < 192) 
{
    // Interval 128 - 191
    led_Reset(LED_ONE);
    led_Reset(LED_TWO);
    led_Set(LED_THREE);
}
else 
{
    // Interval 192 - 255
    led_Reset(LED_ONE);
    led_Reset(LED_TWO);
    led_Reset(LED_THREE);
}
        
  

        TCNT1=0;
        counter++;
      }
      if(counter==100)
        gpio_Timer1_stop();
    }
}



