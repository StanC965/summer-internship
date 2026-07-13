#ifndef PWM_C
#define PWM_C

#include "led.h"
#include "gpio.h"

#define PB3 3
#define COM0A1 7
#define COM0A0 6
#define WGM00 0
#define WGM01 1
#define CS00 0
#define CS01 1
#define CS02 2

#define duty0 255
#define duty25 191
#define duty50 127
#define duty75 64
#define duty100 0 
void initializePwm(){
    ledInit(&DDRB,&PORTB,PB3);
    setPin(&TCCR0A,COM0A1); 
   // setPin(&TCCR0A,COM0A0);//set on compare match, clear at bottom
    setPin(&TCCR0A,WGM00);
    setPin(&TCCR0A,WGM01);
}

void startPwm(unsigned short int prescale){
  if(prescale == 1){
    setPin(&TCCR0B,CS00);
    resetPin(&TCCR0B,CS01);
    resetPin(&TCCR0B,CS02);
  }
  if(prescale == 8){
    resetPin(&TCCR0B,CS00);
    setPin(&TCCR0B,CS01);
    resetPin(&TCCR0B,CS02);
  }
  if(prescale == 64){
    setPin(&TCCR0B,CS00);
    setPin(&TCCR0B,CS01);
    resetPin(&TCCR0B,CS02);
  }
  if(prescale == 256){
      resetPin(&TCCR0B,CS00);
      resetPin(&TCCR0B,CS01);
      setPin(&TCCR0B,CS02);
    }  
  if(prescale == 1024){
    setPin(&TCCR0B,CS00);
    resetPin(&TCCR0B,CS01);
    setPin(&TCCR0B,CS02);
  }
}

void pwm100(){
    OCR0A = duty100;
}

void pwm75(){
    OCR0A = duty75;
}

void pwm50(){
    OCR0A = duty50;
}

void pwm25(){
    OCR0A = duty25;
}

void pwm0(){
  OCR0A = duty0;
}

void pwmSetDutyCycle(unsigned char duty)
{
    switch(duty)
    {
        case 0:
            pwm0();
            break;

        case 25:
            pwm25();
            break;

        case 50:
           pwm50(); 
          break;

        case 75:
            pwm75();
            break;

        case 100:
            pwm100();
            break;
    }
}


#endif