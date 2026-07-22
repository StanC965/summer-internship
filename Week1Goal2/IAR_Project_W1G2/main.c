// 334 - CORE
#include "main.h"

void System_Init(void){
  
  BUTTON_Init();
  LED_Init();
  
  button_interrupt_init(SW0);
  button_interrupt_init(BUTTON1);
  button_interrupt_init(BUTTON2);
  button_interrupt_init(BUTTON3);
  
  adc_init();
  
  __enable_interrupt();
}

void HVAC_app(){
  Handle_MasterControl_Event();
        
  Handle_VentControl_Event(BUTTON1, LED1, &button_events.btn1_pressed);
  Handle_VentControl_Event(BUTTON2, LED2, &button_events.btn2_pressed);
  Handle_VentControl_Event(BUTTON3, LED3, &button_events.btn3_pressed);
}

void ADC_app(unsigned int *light_intensity){
  if (*light_intensity > SEMI_DARK_LIMIT) {
      //full dark interval
        PowerOff_LED(LED1);
        PowerOff_LED(LED2);
        PowerOff_LED(LED3);
    } else if(*light_intensity > SEMI_LIGHT_LIMIT &&  *light_intensity <= SEMI_DARK_LIMIT){
      //semi-dark interval
        PowerOn_LED(LED1);
        PowerOff_LED(LED2);
        PowerOff_LED(LED3);
    }else if(*light_intensity > FULL_LIGHT_LIMIT &&  *light_intensity <= SEMI_LIGHT_LIMIT){
      //semi-light interval
        PowerOn_LED(LED1);
        PowerOn_LED(LED2);
        PowerOff_LED(LED3);
    }else if(*light_intensity <= FULL_LIGHT_LIMIT){
      //full light interval
      PowerOn_LED(LED1);
      PowerOn_LED(LED2);
      PowerOn_LED(LED3);
    }
    
    *light_intensity = adc_get_result();
    
    adc_start_conversion();
    
    delay(ONE_SECOND_DELAY/20);
}

void main( void )
{
  System_Init();
  
  tc0_prescaler_t current_prescaler = TC0_PRESCALER_1024;
  tc0_config_t my_timer;
  my_timer.mode                = TC0_MODE_NORMAL;
  my_timer.prescaler           = current_prescaler; 
  my_timer.interrupt_overflow  = 1;
  my_timer.interrupt_compare_a = 0;
  my_timer.interrupt_compare_b = 0;
  
  tc0_init(&my_timer);
  
  
  while(1){
    
    if(button_events.sw0_pressed){
      current_prescaler++;
      if (current_prescaler > TC0_PRESCALER_1024) {
        current_prescaler = TC0_PRESCALER_1;
      }
      my_timer.prescaler = current_prescaler;
      tc0_init(&my_timer);
      button_events.sw0_pressed =0;
    }

  
  }
}
