#ifndef ADC_C
#define ADC_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


#include "gpio.h"       
#include "iom324pb.h"
#include "adc.h"



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Implementation      */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

 void adc_init_LIGHT()
      {
        
         gpio_set_pin(&ADMUX,2);
         gpio_set_pin(&ADMUX,6);//pini ref 7 /6   , combinatia 01 selecteaza AVCC adica 3.3V 
         gpio_set_pin(&ADMUX,5); //setam adlar pe 1
         
          
          gpio_reset_pin(&PRR0,PRR0_PRADC);
          
          
          gpio_set_pin(&ADCSRA,7);
          gpio_set_pin(&ADCSRA,3);
          gpio_set_pin(&ADCSRA,1); //8
          gpio_set_pin(&ADCSRA,0); //8
        
       }
void adc_start_conversie()
{
      gpio_set_pin(&ADCSRA,6); // 6 este ADSC
}

ADC_reader_8bits adc_adapter8(ADC_reader_8bits value)
{
    return (255 - value);
}
ADC_reader_16bits adc_adapter16(ADC_reader_16bits value)
{
    
    return (1023 - value);
}


ADC_reader_16bits adc_get_result16(void)
{
  
 ADC_reader_16bits rezultat;
 ADC_reader_8bits low_nibble,high_nibble;
 low_nibble=ADCL;
 high_nibble=ADCH;
 rezultat=low_nibble|(high_nibble<<8);
  return rezultat;
  
}

ADC_reader_8bits adc_get_result8(void)
{
    return ADCH; 
}

void disable_input_buffer_for_lightSensor()
{
  
   gpio_set_pin(&DIDR0,4);
}
void enable_input_buffer_for_lightSensor()
{
  
  gpio_reset_pin(&DIDR0,4);
  
}



#endif