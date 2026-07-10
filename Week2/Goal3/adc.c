#ifndef ADC_C
#define ADC_C
#include "gpio.h"
#define INPUT 0
#define ADCS 6
#define ADEN 7

//aici sunt definite toate porturile care sunt folosite penrtu exercitii-le pe care le-am intampinat pana acum acum 
//acestea se vor defini cu numarul bitului care va trebuii schimbat sau numele DDR sau portul care treuie folosit
void initAdc(volatile unsigned char* DDR,volatile unsigned char* port,unsigned char pin,unsigned char ADMUXn,unsigned char REF0,unsigned char REF1,unsigned char ADIE,unsigned char ADPS0,unsigned char ADPS1,unsigned char ADPS2){
  setDirection(DDR,pin,INPUT);
  resetPin(port,pin);
  
  setPin(&ADMUX,ADMUXn);
  if(REF0 !=0)
    setPin(&ADMUX,REF0);
  if(REF1 != 0)
    setPin(&ADMUX,REF1);
  
  #if defined(Adc8Bit)
      setPin(&ADMUX, ADLAR);      
  #elif defined(Adc10Bit)
      resetPin(&ADMUX, ADLAR);    
  #endif
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

void enableAdc(){
  setPin(&ADCSRA,ADEN);
}
void disableAdc(){
  resetPin(&ADCSRA,ADEN);
}



#endif

/*
initAdc()

This function initializes the ADC peripheral. It configures the selected analog input pin, the voltage reference, the ADC prescaler and the interrupt option (if enabled).

8-bit resolution: The ADC result is configured to be left aligned (ADLAR = 1), allowing the application to read only the ADCH register.
10-bit resolution: The ADC result is configured to be right aligned (ADLAR = 0), allowing the application to read the complete 10-bit conversion result from the ADC register.
enableAdc()

This function enables the ADC peripheral by setting the ADEN bit in the ADCSRA register.

8-bit resolution: Enables the ADC before an 8-bit conversion.
10-bit resolution: Enables the ADC before a 10-bit conversion.

The implementation is identical for both configurations.

disableAdc()

This function disables the ADC peripheral by clearing the ADEN bit in the ADCSRA register, reducing the power consumption when no conversion is required.

8-bit resolution: Disables the ADC after the conversion.
10-bit resolution: Disables the ADC after the conversion.

The implementation is identical for both configurations.

startConversionAdc()

This function starts an ADC conversion by setting the ADSC bit.

8-bit resolution: Starts an 8-bit ADC conversion.
10-bit resolution: Starts a 10-bit ADC conversion.

The implementation is identical for both configurations.

readAdc()

This function returns the ADC conversion result.

8-bit resolution: Returns the value stored in the ADCH register (0–255).
10-bit resolution: Returns the complete ADC result from the ADC register (0–1023). The returned value is stored in an unsigned int.

This is the only function that differs significantly between the two configurations.
*/