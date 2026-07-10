#include "led.h"

#include <intrinsics.h>

#define led0 0
#define led1 1
#define led2 2
#define led3 3

#define pinLed0 7
#define pinLed1 5
#define pinLed2 4
#define pinLed3 3

#define pinButton0 6
#define pinButton1 1
#define pinButton2 0
#define pinButton3 1

#define OUTPUT 1
#define INPUT 0
#define PCINT22 6

#define PCINT17 1
#define PCIE2 2

#define PCINT0 0
#define PCINT1 1
#define PCIE0 0

int led0State = 0;
int led1State = 0;
int led2State = 0;
int led3State = 0;

int cnt = 0;
#define varM 80

#define TOIE0 0
#define CS00 0

void led0Funtionality(){
  ledPowerOn(led0);
  ledPowerOff(led1);
  ledPowerOff(led2);
  ledPowerOff(led3);
}

void led0FunctionalityReversed(){
  ledPowerOff(led0);
   if(led1State == 1)
            ledPowerOn(led1);
        else
            ledPowerOff(led1);
  if(led2State == 1)
          ledPowerOn(led2); 
        else
          ledPowerOff(led2);
  if(led3State == 1)
        ledPowerOn(led3);
    else
      ledPowerOff(led3);
}

#pragma vector=TIMER0_OVF_vect
__interrupt void timInterrupt(void){
    cnt++;
    if(cnt == varM){
      if(!getPin(&PINC,pinButton0)){
      led0State ^= 1;
      if(led0State == 1){
        led0Funtionality();
      }
      else
          led0FunctionalityReversed();
  }
     if(!getPin(&PINC,pinButton1)){
    if(led0State == 1){
        ledBlinkFast(led0);
        ledPowerOn(led0);}
    else{
        led1State ^= 1;
        if(led1State == 1)
            ledPowerOn(led1);
        else
          ledPowerOff(led1);}
  }
     if(!getPin(&PINA,pinButton2)){
      if(led0State == 1){
        ledBlinkFast(led0);
        ledPowerOn(led0);}
    else{
        led2State ^= 1;
        if(led2State == 1)
          ledPowerOn(led2); 
        else
          ledPowerOff(led2);}
    }
    
    if(!getPin(&PINA,pinButton3)){
      if(led0State == 1){
        ledBlinkFast(led0);
        ledPowerOn(led0);}
    else{
      led3State ^= 1;
      if(led3State == 1)
        ledPowerOn(led3);
    else
      ledPowerOff(led3);
    }
      
}
    cnt = 0;
    resetPin(&TCCR0B,CS00);
    
    
    }

}

#pragma vector = PCINT2_vect
__interrupt void myInterruption1(void){
  //pentru sw0 adaugam functionalitatea
  
  setPin(&TCCR0B,CS00);
          
  
  
  //pentru ledul 1/butonul 1
 

}

#pragma vector = PCINT0_vect
__interrupt void myInterruption2(void){
  //pentru buton2,3/led2,3
    
setPin(&TCCR0B,CS00);
}


void initialize(){
  //initializam pinii ledurilor ca iesiri
    setDirection(&DDRD,pinLed1,OUTPUT);
  setDirection(&DDRD,pinLed2,OUTPUT);
  setDirection(&DDRA,pinLed3,OUTPUT);
  setDirection(&DDRC,pinLed0,OUTPUT);
  
  //ii setam la 1
  setPin(&PORTC,pinLed0);
  setPin(&PORTD,pinLed1);
  setPin(&PORTD,pinLed2);
  setPin(&PORTA,pinLed3);
  
  //initializam pinii butoanelor ca intrari
  setDirection(&DDRC,pinButton0,INPUT);
  setDirection(&DDRC,pinButton1,INPUT);
  setDirection(&DDRA,pinButton2,INPUT);
  setDirection(&DDRA,pinButton3,INPUT);
  
  //setam acesti pini a butoanelor
   setPin(&PORTC,pinButton0);
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
  
  setPin(&PCMSK2,PCINT22);
  
  
}

int main( void )
{
  initialize();
  setPin(&TIMSK0,TOIE0);
  __enable_interrupt();
  
  while(1){
    
  
  
  
  }
  
}