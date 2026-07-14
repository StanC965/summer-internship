#include "adc.h"
#include "pwm.h"
#include "led.h"

#include "scheduler.h"

#define PA4 4
#define ADMUX4 2
#define REF0 6
#define ADIE 3
#define ADPS0 0
#define NADPS0 -1

#define PC7 7
#define PC6 6
#define PD4 4
#define PD5 5
#define INPUT 0

#pragma vector = ADC_vect
__interrupt void adcInterrupt(void){
    setAdcValue(ADC);
}

#pragma vector = TIMER1_COMPA_vect
__interrupt void schedInterrupt(void){
  schedulerFlasgsManagement();
}


void main( void )
{
  initAdc(&DDRA,&PORTA,PA4,ADMUX4,REF0,0,ADIE,0,ADPS0,0,0);
  ledInit(&DDRC,&PORTC,PC7);
  ledInit(&DDRD,&PORTD,PD4);
  ledInit(&DDRD,&PORTD,PD5);
  setDirection(&DDRC,PC6,INPUT);
  setPin(&PORTC,PC6);
  initializePwm();
  setPwmDc(0);
  startPwm(1);
  
  enableAdc();
  SREG |= 1<<7;
  
  startConversionAdc();
  
  scheduleTaskDispatcher();
  
    
}
