#include "iom324pb.h"
#include "gpio.h" 
#include "adc.h"
#include "led.h"

volatile ADC_result ADC_value = 0; 

#pragma vector = ADC_vect
__interrupt void ADC_ISR(void)
{
   
ADC_result hardware_value = adc_get_result();
    ADC_value = adc_adapter(hardware_value);
   
}

void setup(void)
{
  adc_init_LIGHT();
  gpio_set_pin(&SREG, 7);
  disable_input_buffer_for_lightSensor();
  //////in cazul asta trebuie sa scoatem alinierea la stanga) si sa fie by defaut dreapta)
  //ADMUX&=~(1<<5); nu mai e nevoie la compilare se alege varainta corecta
   leds_initialize(0,1,1,1,0);
  
}
    
int counter=0;

#ifdef ADC_USE_8_BIT_RESOLUTION
    #define THRESHOLD_1 64
    #define THRESHOLD_2 128
    #define THRESHOLD_3 192
#else
    #define THRESHOLD_1 255    //bloc decizie rezolutiede 8 sau 10
    #define THRESHOLD_2 511
    #define THRESHOLD_3 767
#endif
void main(void)
{
    setup();
    gpio_Timer1_start(1, 64);
    
    while(1)    
    {
        if(TCNT1 >= OCR1A)
        {
            adc_start_conversie();
            
            
            if (ADC_value < THRESHOLD_1) 
            {
                led_Set(LED_ONE);
                led_Set(LED_TWO);
                led_Set(LED_THREE);
            }
            else if (ADC_value < THRESHOLD_2) 
            {
                led_Reset(LED_ONE);
                led_Set(LED_TWO);
                led_Set(LED_THREE);
            }
            else if (ADC_value < THRESHOLD_3) 
            {
                led_Reset(LED_ONE);
                led_Reset(LED_TWO);
                led_Set(LED_THREE);
            }
            else 
            {
                led_Reset(LED_ONE);
                led_Reset(LED_TWO);
                led_Reset(LED_THREE);
            }
            
            TCNT1 = 0;
        }
    }
}


