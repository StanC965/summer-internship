#ifndef ADC_C
#define ADC_C
#include "gpio.h"
#define INPUT 0
#define ADCS 6

//aici sunt definite toate porturile care sunt folosite penrtu exercitii-le pe care le-am intampinat pana acum acum 
//acestea se vor defini cu numarul bitului care va trebuii schimbat sau numele DDR sau portul care treuie folosit
void initAdc(volatile unsigned char* DDR,volatile unsigned char* port,unsigned char pin,unsigned char ADMUXn,unsigned char REF0,unsigned char REF1,unsigned char ADLAR,unsigned char ADIE,unsigned char ADPS0,unsigned char ADPS1,unsigned char ADPS2){
  setDirection(*DDR,pin,INPUT);
  resetPin(*port,pin);
  
  setPin(&ADMUX,ADMUXn);
  if(REF0 !=0)
    setPin(&ADMUX,REF0);
  if(REF1 != 0)
    setPin(&ADMUX,REF1);
  if(ADLAR != 0){
    setPin(&ADMUX,ADLAR);
  }
  setPin(&ADCSRA,ADEN);
  if(ADIE != 0)
    setPin(&ADCSRA,ADIE);
  if(ADPS0!= 0)
      setPin(&ADCSRA,ADPS0);
  if(ADPS1!= 0)
      setPin(&ADCSRA,ADPS1);
  if(ADPS2!= 0)
      setPin(&ADCSRA,ADPS2);
  
  


}


void startConversionAdc(){
  setPin(&ADCSRA,ADCS);

}


#endif