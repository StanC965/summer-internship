#include "led.h"
#include "usart.h"
#include "scheduler.h"
#include "scheduleCFG.h"

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



#define varM 80

#define TOIE0 0
#define CS00 0


#pragma vector=TIMER1_COMPA_vect
__interrupt void myInterrupt(void){
  
  schedulerFlasgsManagement();
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
  
  
}

int main( void )
{
  initialize();
  initUsart();
  SREG |= 1<<7;
  scheduleTaskDispatcher();
 
  
  
}