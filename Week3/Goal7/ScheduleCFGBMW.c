#ifndef SCDCFGBMW_C
#define SCDCFGBMW_C
#include "adc.h"
#include "led.h"
#include "gpio.h"
#include "usart.h"

#define led0 'A'
#define led1 'B'
#define led2 'C'
#define led3 'D'

#define led0Off 'E'
#define led1Off 'F'
#define led2Off 'G'
#define led3Off 'H'

#define ON 1
#define OFF 0

#define le

int led0State = 0;
int led1State = 0;
int led2State = 0;
int led3State = 0;

#define PC7 7
#define PC6 6
#define PC1 1
#define PA0 0
#define PA1 1

#define lim 10

volatile unsigned char blinkFast = 0;
unsigned char led0BlinkState = 0;
unsigned char cnt = 0;

unsigned char button0Buffer = 0;
unsigned char button1Buffer = 0;
unsigned char button2Buffer = 0;
unsigned char button3Buffer = 0;

unsigned char button0State = 0;
unsigned char button1State = 0;
unsigned char button2State = 0;
unsigned char button3State = 0;

unsigned char lastButton0State = 0;
unsigned char lastButton1State = 0;
unsigned char lastButton2State = 0;
unsigned char lastButton3State = 0;

#define PRESSED  1
#define RELEASED 0

#define top 50

#define step 5

#define debounceValUp 0x1F
#define debounceValDown 0x00

enum states {
  NORMAL_MODE,
  STOPPED_MODE,
  BLINKING_MODE
};

void led0Funtionality(){
  transmitUsartChar(led1Off);
  transmitUsartChar(led2Off);
  transmitUsartChar(led3Off);
 transmitUsartChar(led0);
  
}

enum states state = NORMAL_MODE;

void led0FunctionalityReversed(){
  transmitUsartChar(led0Off);
   if(led1State == ON)
            transmitUsartChar(led1);
        else
            transmitUsartChar(led1Off);
  if(led2State == ON)
          transmitUsartChar(led2); 
        else
          transmitUsartChar(led2Off);
  if(led3State == ON)
        transmitUsartChar(led3);
    else
      transmitUsartChar(led3Off);
}

void stateMachine(void){
  switch(state){
    
    
    case NORMAL_MODE:
        if(button1State == PRESSED && lastButton1State == RELEASED){
               led1State ^= 1;
               if(led1State == ON)
                   transmitUsartChar(led1);
               else
                  transmitUsartChar(led1Off);
        }
        lastButton1State = button1State;
        if(button2State == PRESSED && lastButton2State == RELEASED){
              led2State ^= 1;
              if(led2State == ON)
                transmitUsartChar(led2);
              else
                transmitUsartChar(led2Off);}
        lastButton2State = button2State;
        if(button3State == PRESSED && lastButton3State == RELEASED){
              led3State ^= 1;
              if(led3State == ON)
                transmitUsartChar(led3);
             else
               transmitUsartChar(led3Off);
        }
            
         
        lastButton3State = button3State;
        if(button0State == PRESSED && lastButton0State == RELEASED){
                led0Funtionality();
                state = STOPPED_MODE;
                cnt = 0;
        }
        lastButton0State = button0State;
        break;
        
        
    case STOPPED_MODE:
      if((button1State == PRESSED && lastButton1State == RELEASED)
         || (button2State == PRESSED && lastButton2State == RELEASED)
           ||(button3State == PRESSED && lastButton3State == RELEASED)){
               state = BLINKING_MODE;
               cnt = 0;
               
        }
        lastButton1State = button1State;
        lastButton2State = button2State;   
        lastButton3State = button3State;
        if(button0State == PRESSED && lastButton0State == RELEASED){
                led0FunctionalityReversed();
                state = NORMAL_MODE;
                cnt = 0;
        }
        lastButton0State = button0State;
        break;
        
    case BLINKING_MODE:
        if(cnt % step == 0)
            togglePin(&PORTC,PC7);
        cnt++;
        if(cnt >= top){
            led0Funtionality();
            state = STOPPED_MODE;
            cnt = 0;
            
        }    
        
        
        if(button0State == PRESSED && lastButton0State == RELEASED){
                led0FunctionalityReversed();
                state = NORMAL_MODE;
                cnt = 0;

        }
        lastButton0State = button0State;
        break;
        
        
  
  }
  
}


void debounceButton(volatile unsigned char *PIN,unsigned char pin,unsigned char *buffer,unsigned char *state)
{
    *buffer <<= 1;

    if(!getPin(PIN, pin))
        *buffer |= 1;

    if((*buffer & debounceValUp)== debounceValUp)
        *state =PRESSED;
    else if((*buffer & debounceValUp)== debounceValDown)
        *state = RELEASED;
}

void task10ms(){
  debounceButton(&PINC, PC6, &button0Buffer, &button0State);
  debounceButton(&PINC, PC1, &button1Buffer, &button1State);
  debounceButton(&PINA, PA0, &button2Buffer, &button2State);
  debounceButton(&PINA, PA1, &button3Buffer, &button3State);
  stateMachine();

}
      
void task50ms(){


}
      
void task100ms(){
  

}
      
void task500ms(){

}

void task1000ms(){

}

#endif