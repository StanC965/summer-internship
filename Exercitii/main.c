#include "iom324pb.h"
#include "gpio.h" 
#include "adc.h"

volatile ADC_reader_8bits ADC_value = 0; 

#pragma vector = ADC_vect
__interrupt void ADC_ISR(void)
{
   
   ADC_reader_8bits hardware_value = adc_get_result();
    ADC_value = adc_adapter(hardware_value);
   
}

void setup(void)
{
  adc_init_LIGHT();
  gpio_set_pin(&SREG, 7);
}
    

void main(void)
{
    setup();
    adc_start_conversie();                                                   
    while(1)    
    {
  
    }
}



