#include "iom324pb.h"
#include "gpio.h" 
#include "adc.h"
#include "led.h"

volatile ADC_reader_16bits ADC_value = 0; 

#pragma vector = ADC_vect
__interrupt void ADC_ISR(void)
{
   
    ADC_reader_16bits hardware_value = adc_get_result16();
    ADC_value = adc_adapter16(hardware_value);
   
}

void setup(void)
{
  adc_init_LIGHT();
  gpio_set_pin(&SREG, 7);
  disable_input_buffer_for_lightSensor();
  //////in cazul asta trebuie sa scoatem alinierea la stanga) si sa fie by defaut dreapta)
  ADMUX&=~(1<<5);
   leds_initialize(0,1,1,1,0);
  
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
      
        
        
      if (ADC_value < 255) 
{
    // Interval 0 - 255
    led_Set(LED_ONE);
    led_Set(LED_TWO);
    led_Set(LED_THREE);
}
else if (ADC_value < 511) 
{
    // Interval 256 - 511
    led_Reset(LED_ONE);
    led_Set(LED_TWO);
    led_Set(LED_THREE);
}
else if (ADC_value < 767) 
{
    // Interval 512 - 767
    led_Reset(LED_ONE);
    led_Reset(LED_TWO);
    led_Set(LED_THREE);
}
else 
{
    // Interval 768-1023
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



