#ifndef ADC_C
#define ADC_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


#include "gpio.h"       
#include "iom324pb.h"
#include "adc.h"


static volatile ADC_result ADC_value ; 
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Implementation      */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



 void adc_init_LIGHT()
      {
        
       #ifdef ADC_USE_8_BIT_RESOLUTION
        gpio_set_pin(&ADMUX, 5);   
    #else
        gpio_reset_pin(&ADMUX, 5);
    #endif

        
         gpio_set_pin(&ADMUX,2);
         gpio_set_pin(&ADMUX,6);//pini ref 7 /6   , combinatia 01 selecteaza AVCC adica 3.3V 
        // gpio_set_pin(&ADMUX,5); //setam adlar pe 1
         
          
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


unsigned short adc_get_data(void)
{
    return (unsigned short)ADC_value;
}



void disable_input_buffer_for_lightSensor()
{
  
   gpio_set_pin(&DIDR0,4);
}
void enable_input_buffer_for_lightSensor()
{
  
  gpio_reset_pin(&DIDR0,4);
  
}


void adc_read_and_update(void)
{
    #ifdef ADC_USE_8_BIT_RESOLUTION
        ADC_value = 255 - ADCH; 
    #else
        unsigned char low_byte = ADCL;
        unsigned char high_byte = ADCH;
        ADC_result rezultat = low_byte | (high_byte << 8);
        ADC_value = 1023 - rezultat; 
    #endif
}


#endif