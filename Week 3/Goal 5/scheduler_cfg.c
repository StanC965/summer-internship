#include "iom324pb.h"
#include "scheduler_cfg.h"
#include "adc.h"
#include "led.h"
#include "gpio.h"

#define BTNSW0_PIN 6    //pc6
#define BTN1_PIN 1      //pc1
#define BTN2_PIN 0      //pa0
#define BTN3_PIN 1      //pa1
#define LED0_PIN 7      //pc7
#define LED1_PIN 5      //pd5
#define LED2_PIN 4      //pd4
#define LED3_PIN 3      //pa3
#define OUTPUT 1
#define INPUT 0

volatile unsigned char btn0=1;
volatile unsigned char btn1=1;
volatile unsigned char btn2=1;
volatile unsigned char btn3=1;

void task_10ms(void) {
  static unsigned char buffer0=0xFF;
  static unsigned char buffer1=0xFF;
  static unsigned char buffer2=0xFF;
  static unsigned char buffer3=0xFF;
  
  unsigned char stare_btn0=(PINC&(1<<BTNSW0_PIN))?1:0;
  unsigned char stare_btn1=(PINC&(1<<BTN1_PIN))?1:0;
  unsigned char stare_btn2=(PINA&(1<<BTN2_PIN))?1:0;
  unsigned char stare_btn3=(PINA&(1<<BTN3_PIN))?1:0;
  
  buffer0=(buffer0<<1)|stare_btn0;
  buffer1=(buffer1<<1)|stare_btn1;
  buffer2=(buffer2<<1)|stare_btn2;
  buffer3=(buffer3<<1)|stare_btn3;
  
  unsigned char window0=buffer0&0x1F; //00011111
  unsigned char window1=buffer1&0x1F;
  unsigned char window2=buffer2&0x1F;
  unsigned char window3=buffer3&0x1F;
  
  if(window0 == 0x00) 
    btn0 = 0; 
  else if(window0 == 0x1F) 
    btn0 = 1;
  if(window1 == 0x00) 
    btn1 = 0; 
  else if(window1 == 0x1F) 
    btn1 = 1;
  if(window2 == 0x00) 
    btn2 = 0; 
  else if(window2 == 0x1F) 
    btn2 = 1;
  if(window3 == 0x00) 
    btn3 = 0; 
  else if(window3 == 0x1F) 
    btn3 = 1;
  
  
}

void task_50ms(void) {
  static int panel_blocat=0;
  static int stare_led1 = 0;
  static int stare_led2 = 0;
  static int stare_led3 = 0;
  static int stare_btn0=1;
  static int stare_btn1=1;
  static int stare_btn2=1;
  static int stare_btn3=1;
  
  //btn0
  if(btn0==0 && stare_btn0==1){
    if(panel_blocat==0){
      panel_blocat=1;
    reset_pin(&PORTC,LED0_PIN);
    set_pin(&PORTD,LED1_PIN);
    set_pin(&PORTD,LED2_PIN);
    set_pin(&PORTA,LED3_PIN);
    stare_led1=0;
    stare_led2=0;
    stare_led3=0;   
    }
    else{
      set_pin(&PORTC,LED0_PIN);
      panel_blocat=0;
    }   
  }
  stare_btn0=btn0;

  //btn1
  if(btn1==0 && stare_btn1==1){
    if(panel_blocat==1){
      BlinkFast_LED(&PORTC, LED0_PIN);
      reset_pin(&PORTC,LED0_PIN);
    }
    else{
      if(stare_led1==0){
      reset_pin(&PORTD,LED1_PIN);
      stare_led1=1;
    }
  
    else{
      set_pin(&PORTD,LED1_PIN);
      stare_led1=0;
    }
    }
  }
   stare_btn1=btn1;
  
  //btn2
  if(btn2==0 && stare_btn2==1){
    if(panel_blocat==1){
      BlinkFast_LED(&PORTC, LED0_PIN);
      reset_pin(&PORTC,LED0_PIN);
    }
    else{
    if(stare_led2==0){
      reset_pin(&PORTD,LED2_PIN);
      stare_led2=1;
    }
  
    else{
      set_pin(&PORTD,LED2_PIN);
      stare_led2=0;
    }
    }
  }
  stare_btn2=btn2;
  
  //btn3
   if(btn3==0 && stare_btn3==1){
     if(panel_blocat==1){
       BlinkFast_LED(&PORTC, LED0_PIN);
       reset_pin(&PORTC,LED0_PIN);}
     else{
    if(stare_led3==0){
      reset_pin(&PORTA,LED3_PIN);
      stare_led3=1;
    }
  
    else{
      set_pin(&PORTA,LED3_PIN);
      stare_led3=0;
    }
     }
  }
  stare_btn3=btn3;
}

void task_100ms(void) {

}

void task_500ms(void) {
}

void task_1000ms(void) {
}