#include <intrinsics.h>
#include "led.h"
#include "gpio.h"
#include "adc.h"

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

#define led0 0
#define led1 1
#define led2 2
#define led3 3
#define Adc10bit

#define dark 120
#define semiDark 80
#define semiLight 40
//curentul se masoara cu un ampermetru


#pragma vector = ADC_vect
__interrupt void myInterrupt(void){
 
  unsigned int value = ADC;
  disableAdc();
  
  if(value < semiLight)
  {
    ledPowerOn(led1);
      ledPowerOn(led2);
      ledPowerOn(led3);
  }
  else
    if(value >= semiLight && value < semiDark){
      ledPowerOn(led1);
      ledPowerOn(led2);
      ledPowerOff(led3);
    }
  else
    if(value >= semiDark && value < dark){
      ledPowerOn(led1);
      ledPowerOff(led2);
      ledPowerOff(led3);
    }
    else{
    ledPowerOff(led1);
      ledPowerOff(led2);
      ledPowerOff(led3);
    }
  enableAdc();
  startConversionAdc();
      
}



//senzorul nu mai citeste asa bine datele
//prescale de 128 sau 64
void main( void )
{
  DIDR0 |= (1 << ADC4DIDR);
  initAdc(&DDRA,&PORTA,PA4,ADC4,REF0,0,ADIE,0,ADPS01,ADPS02);
  ledInit(&DDRA,&PORTA,PA3);
  ledInit(&DDRD,&PORTD,PD4);
  ledInit(&DDRD,&PORTD,PD5);
  enableAdc();
  startConversionAdc();
  
  __enable_interrupt();
  while(1){
  
  }
  
}
