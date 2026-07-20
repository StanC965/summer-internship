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
  static unsigned char sin_levels[]={0,2,10,21,35,50,65,79,90,98,100,98,90,79,65,50,35,21,10,2}; //50+50*sin(x)
  static unsigned char step=0;
  
  pwm_dc(sin_levels[step]);
  step++;
  if(step>=20){
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