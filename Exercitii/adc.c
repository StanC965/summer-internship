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
          ADMUX=1<<6; //pini ref 7 /6   , combinatia 01 selecteaza AVCC adica 3.3V 
          ADMUX|=1<<5; //setam adlar pe 1
          ADMUX|=1<<2; 
          ADCSRA=1<<7;
          ADCSRA|=1<<ADCSRA_ADIE;
          PRR0&=~(1<<PRR0_PRADC);
          ADCSRA|=1<<3;
       }
void adc_start_conversie()
{
      ADCSRA |= (1 << 6); // 6 este ADSC
}

ADC_reader_8bits adc_adapter(ADC_reader_8bits value)
{
    return (255 - value);
}

ADC_reader_8bits adc_get_result(void)
{
    return ADCH; 
}

#endif