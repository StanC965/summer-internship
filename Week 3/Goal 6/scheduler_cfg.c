#include "iom324pb.h"
#include "scheduler_cfg.h"
#include "adc.h"
#include "led.h"
#include "gpio.h"
#include "pwm.h"

#define PWM_PIN 3 //pb3
#define OUTPUT 1
#define INPUT 0
#define WORKING 1
#define STOPPED 0

void task_10ms(void) {
  static unsigned char state=WORKING;
  static unsigned char level=0;
  static int counter=0;
  
  if(state==WORKING){
    pwm_dc(level);
    level++;
    if(level>100){
      level=0;
      pwm_dc(0);
      counter=0;
      state=STOPPED;
    }
  }
  else if(state==STOPPED){
    counter++;
    if(counter>=300){ //300*10ms=3000ms=3s
      state=WORKING;
    }
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