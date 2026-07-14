#ifndef SCDHYU_C
#define SCDHYU_C
#include "pwm.h"
#include "led.h"
#include "adc.h"


#define PRESSED 1
#define RELEASED 0

#define led0 0
#define led1 1
#define led2 2

#define PC6 6


#define night 850
#define lightDay 500
#define day 300
#define brightDay 150

#define stateND 0
#define stateN 1
#define stateLD 2
#define stateD 3
#define stateSD 4
#define stateNDValue 15
#define stateNValue 20
#define stateLDValue 42
#define stateDValue 80
#define stateSDValue 90

unsigned char vect[] ={0,10,20,80,130,130,120,110,105,100};
volatile unsigned short int value =0;
volatile unsigned char dayMode =1;
unsigned char cnt = 0;
unsigned char cntVal = 0;
unsigned char lightValue = 0;
unsigned char targetValue = 0;
_Bool up = 1;

unsigned char state = -1;
unsigned char stateVal = 0;
 unsigned char lastState = -1;
_Bool dayTime = 0;

_Bool led0State = 0;
 unsigned char buffer0 = 0;
_Bool button0State = 0;
_Bool lastButton0State = 0;

#define debounceValUp 0x1F
#define debounceValDown 0x00

 unsigned char switching = 0;
 
 
void startTransition(unsigned char newState, unsigned char newValue, unsigned char isDay)
{
    if(state == newState)
        return;

    lastState = state;
    state = newState;
    stateVal = newValue;
    dayTime = isDay;

    if(stateVal >= lightValue)
    {
        up = 1;
        targetValue = stateVal - lightValue;
    }
    else
    {
        up = 0;
        targetValue = lightValue - stateVal;
    }

    cnt = 0;
    cntVal = 0;
    switching = 1;
}

void debounce(volatile unsigned char *PIN,unsigned char pin,unsigned char *buffer, unsigned char *state)
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
    
    debounce(&PINC,PC6,&buffer0,&button0State);
    if(button0State == PRESSED && lastButton0State == RELEASED){
        led0State ^= 1;
        if(led0State == 1){
          ledPowerOn(led0);
          
        }
        else{
          ledPowerOff(led0);
          ledPowerOff(led2);
          ledPowerOff(led1);
          setPwmDc(0);
        }
    }
    lastButton0State = button0State;
    if(led0State == 1){
      
      startConversionAdc();
    }
    
}
      
void task50ms(){
    if(led0State == 1)
    {
       value = getAdcValue();

        if(value > night)
        {
            startTransition(stateND, stateNDValue, 0);
            ledPowerOn(led2);
            ledPowerOff(led1);
        }
        else if(value > lightDay)
        {
            startTransition(stateN, stateNValue, 0);
            ledPowerOn(led2);
            ledPowerOff(led1);

        }
        else if(value > day)
        {
            startTransition(stateLD, stateLDValue, 1);
            ledPowerOn(led1);
            ledPowerOff(led2);
        }
        else if(value > brightDay)
        {
            startTransition(stateD, stateDValue, 1);
            ledPowerOn(led1);
            ledPowerOff(led2);
        }
        else
        {
            startTransition(stateSD, stateSDValue, 1);
            ledPowerOn(led1);
            ledPowerOff(led2);
        }
      }
    

}
      
void task100ms(){
  

    if(switching == 1){
      
      if(up == 1){
        short int val = lightValue + (vect[cntVal] * targetValue)/100;
        if(val < 0)
          val = 0;
        else
            if(val >100)
              val = 100;
        setPwmDc(val);
      }
      else{
        short int val = lightValue - (vect[cntVal] * targetValue)/100;
        if(val < 0)
          val = 0;
        else
            if(val >100)
              val = 100;
        setPwmDc(val);
      }
      cnt++;
       if(cnt %2 == 0)
         cntVal++;
          
       if(cntVal == 10)
       {
        switching = 0;
        lightValue = stateVal;
        setPwmDc(lightValue);
       }
                    
        
    }
  }

      
void task500ms(){

}

void task1000ms(){

}

#endif