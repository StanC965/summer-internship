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
    leds_initialize(1,0,0,0,0);
    led_Set(LED_ZERO);
   
}

void setup(void)
{
  adc_init_LIGHT();
  gpio_set_pin(&SREG, 7);
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

  
        if(ADC_value >(0xff/2))
      {
              led_Reset(LED_ZERO);
      }
        else{
            led_Set(LED_ZERO);
        }
    
        TCNT1=0;
        counter++;
      }
      if(counter==20)
        gpio_Timer1_stop();
    }
}



