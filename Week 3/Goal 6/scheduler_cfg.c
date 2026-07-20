#include "iom324pb.h"
#include "scheduler_cfg.h"
#include "adc.h"
#include "led.h"
#include "gpio.h"
#include "pwm.h"

#define PWM_PIN 3 //pb3
#define OUTPUT 1
#define INPUT 0

void task_10ms(void) {
  static unsigned char levels[]={0,25,50,75,100};
  static unsigned char step=0;
  
  pwm_dc(levels[step]);
  step++;
  if(step>=5){
    step=0;
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