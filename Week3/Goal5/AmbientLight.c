#include <intrinsics.h>
#include "led.h"
#include "gpio.h"
#include "adc.h"
#include "scheduler.h"

#define PA3 3
#define PD4 4
#define PD5 5
#define PA4 4
#define ADC4 2
#define ADC4DIDR 2
#define REF0 6
#define ADLAR 5
#define ADIE 3
#define ADPS00 0
#define ADPS01 1
#define ADPS02 2
#define Adc8Bit 



void initProgram(){
  //initializam ledurile ADC si deconectam ceilalti pini pentru a consuma mai putin
  DIDR0 = 0xff;
  DIDR0 &= ~(1 << ADC4DIDR);
#if defined(Adc8Bit)
  initAdc(&DDRA,&PORTA,PA4,ADC4,REF0,0,ADIE,ADLAR,0,ADPS01,ADPS02);
#elif defined(Adc10Bit)
     initAdc(&DDRA,&PORTA,PA4,ADC4,REF0,0,ADIE,0,0,ADPS01,ADPS02);
#endif
  ledInit(&DDRA,&PORTA,PA3);
  ledInit(&DDRD,&PORTD,PD4);
  ledInit(&DDRD,&PORTD,PD5);
}
    
  

#pragma vector = ADC_vect
__interrupt void myInterrupt(void){
  
 #if defined(Adc8Bit)
  setAdcValue(ADCH);
#elif defined(Adc10Bit)
     setAdcValue(ADC);
#endif
  
 
      
}

#pragma vector=TIMER1_COMPA_vect
__interrupt void myInterrupt1(void){
  
  schedulerFlasgsManagement();
}





void main( void )
{
  initProgram();
  
  
  __enable_interrupt();
  scheduleTaskDispatcher();
}
