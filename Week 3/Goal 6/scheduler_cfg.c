#include "iom324pb.h"
#include "scheduler_cfg.h"
#include "adc.h"
#include "led.h"
#include "gpio.h"
#include "pwm.h"

#define BTNSW0_PIN 6    //pc6
#define LED0_PIN 7      //pc7
#define LED1_PIN 5      //pd5
#define LED2_PIN 4      //pd4
//#define PWM_PIN 3 //pb3
#define OUTPUT 1
#define INPUT 0
#define NIGHT_MODE 0
#define DAY_MODE 1
#define STATE_IDLE 0
#define STATE_START 1

volatile unsigned char btn0=1;

void task_10ms(void) {
}

void task_50ms(void) {
  static unsigned char pwm=0;
  static unsigned char mode=0;
  static unsigned char timer=0;
  static unsigned char index=0;
  static const unsigned char night[] = {0, 1, 1, 3, 7, 16, 16, 14, 12, 10, 8};
  static const unsigned char day[] = {0, 4, 7, 16, 44, 59, 59, 55, 50, 45, 40};
  static unsigned char stare=STATE_IDLE;
  static unsigned char sw0_anterior=1;
  
  adc_start_conversion();
  
  unsigned char sw0_curent=(PINC&(1<<BTNSW0_PIN))?1:0;
  if(sw0_anterior==1 && sw0_curent==0){
    stare=STATE_START;
    index=0;
    timer=0;
    
    unsigned char driver_cockpit_light=adc_scale();
    if(driver_cockpit_light<=40){
      mode=NIGHT_MODE;
      pwm=(driver_cockpit_light<=20)?15:20; //din tabel
      
      set_pin(&PORTD,LED1_PIN);
      reset_pin(&PORTD,LED2_PIN);
    }
    
    else{
      mode=DAY_MODE;
      if(driver_cockpit_light<=50){
        pwm=42;
      }
      else if(driver_cockpit_light<=70){
        pwm=80;
      }
      else{
        pwm=90;
      
      }
      set_pin(&PORTD,LED2_PIN);
      reset_pin(&PORTD,LED1_PIN);
    }
  }
  sw0_anterior=sw0_curent;
  
  switch(stare){
    case STATE_IDLE:
      break;
    case STATE_START:
      timer++;
      if(timer>=4){ //4*50ms=200ms
        timer=0;
      
      int pwm_nou=0;
      if(mode==NIGHT_MODE){
        pwm_nou=pwm+night[index];
      }
      else{
        pwm_nou=pwm+day[index];
      }
      
      if(pwm_nou>100){
        pwm_nou=100;
      }
      
      pwm_dc(pwm_nou);
      index++;
      
      if(index>=11){
        stare=STATE_IDLE;
      }
     } 
      break;
  }
  
  
}

void task_100ms(void) {

}

void task_500ms(void) {
}

void task_1000ms(void) {
}