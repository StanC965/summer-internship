#include "iom324pb.h"
#include "scheduler_cfg.h"
#include "adc.h"
#include "led.h"
#include "gpio.h"

#define LED1_PIN 5      
#define LED2_PIN 4      
#define LED3_PIN 3
#define FULL_DARK 255
#define SEMI_DARK 225
#define SEMI_LIGHT 98
#define FULL_LIGHT 30

void turn_on_leds(unsigned char lumina){
  if(lumina>=SEMI_DARK && lumina <=FULL_DARK){
    set_pin(&PORTD, LED1_PIN); 
    set_pin(&PORTD, LED2_PIN); 
    set_pin(&PORTA, LED3_PIN);
  }
  if(lumina>=SEMI_LIGHT && lumina <SEMI_DARK){
    reset_pin(&PORTD, LED1_PIN); 
    set_pin(&PORTD, LED2_PIN); 
    set_pin(&PORTA, LED3_PIN);
  }
  if(lumina>=FULL_LIGHT && lumina <SEMI_LIGHT){
    reset_pin(&PORTD, LED1_PIN); 
    reset_pin(&PORTD, LED2_PIN); 
    set_pin(&PORTA, LED3_PIN);
  }
  if(lumina<FULL_LIGHT){
    reset_pin(&PORTD, LED1_PIN); 
    reset_pin(&PORTD, LED2_PIN); 
    reset_pin(&PORTA, LED3_PIN);
  }
}

void task_10ms(void) {
}

void task_50ms(void) {
}

void task_100ms(void) {
  unsigned char lumina=adc_get_data();
  turn_on_leds(lumina);
  adc_start_conversion();
}

void task_500ms(void) {
}

void task_1000ms(void) {
}