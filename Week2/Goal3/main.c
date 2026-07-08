#include "sos.h"

#include <intrinsics.h>

#define led1 1
#define led2 2
#define led3 3

#define pinLed1 5
#define pinLed2 4
#define pinLed3 3

#define pinButton1 1
#define pinButton2 0
#define pinButton3 1

#define OUTPUT 1
#define INPUT 0

#define PCINT17 1
#define PCIE2 2

#define PCINT0 0
#define PCINT1 1
#define PCIE0 0

#pragma vector = PCINT2_vect
__interrupt void myInterruption1(void){
  //pentru ledul 1/butonul 1
  if(!getPin(&PINC,pinButton1)){
        ledPowerOn(led1); 
    
    }
  else
      ledPowerOff(led1);
     

}

#pragma vector = PCINT0_vect
__interrupt void myInterruption2(void){
  //pentru buton2,3/led2,3
    if(!getPin(&PINA,pinButton2)){
        ledPowerOn(led2); 
    
    }
  else
      ledPowerOff(led2);
    
    if(!getPin(&PINA,pinButton3)){
        ledPowerOn(led3); 
    
    }
  else
      ledPowerOff(led3);
      
}




void initialize(){
  //initializam pinii ledurilor ca iesiri
    setDirection(&DDRD,pinLed1,OUTPUT);
  setDirection(&DDRD,pinLed2,OUTPUT);
  setDirection(&DDRA,pinLed3,OUTPUT);
  
  //ii setam la 1
  setPin(&PORTD,pinLed1);
  setPin(&PORTD,pinLed2);
  setPin(&PORTA,pinLed3);
  
  //initializam pinii butoanelor ca intrari
  setDirection(&DDRC,pinButton1,INPUT);
  setDirection(&DDRA,pinButton2,INPUT);
  setDirection(&DDRA,pinButton3,INPUT);
  
  //setam acesti pini a butoanelor
  setPin(&PORTC,pinButton1);
  setPin(&PORTA,pinButton2);
  setPin(&PORTA,pinButton3);
  
  
  //activam intreruperile pentru butonul 1
  setPin(&PCICR,PCIE2);
  setPin(&PCMSK2,PCINT17);
  
  //activam pentru butonul 1 si 2
  setPin(&PCICR,PCIE0);
  setPin(&PCMSK0,PCINT1);
  setPin(&PCMSK0,PCINT0);
  
  
}

int main( void )
{
  initialize();
  __enable_interrupt();
  
  while(1){
    
  
  
  
  }
  
}