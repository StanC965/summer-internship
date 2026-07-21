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

typedef enum {
  STATE_OFF,
  STATE_ON
} blinking;

volatile unsigned char btn0=1;

void task_10ms(void) {
  static blinking state=STATE_OFF;
  static int timer=0;
  timer++;
  
  switch(state){
  case STATE_OFF:
    if(timer>=100){
      timer=0;
      set_pin(&PORTC,LED0_PIN);
      state=STATE_ON;
    }
    break;
    
  case STATE_ON:
    if(timer>=100){
      timer=0;
      reset_pin(&PORTC,LED0_PIN);
      state=STATE_OFF;
    }
    break;
    
  default:
    state=STATE_OFF;
    break;
  }
  
}

void task_50ms(void) {
  
}

void task_100ms(void) {

}

void task_500ms(void) {
}

void task_1000ms(void) {
}