//427
#include "iom324.h"
#include "led.h"
#include "gpio.h"
#include <intrinsics.h>

#define LED0_PIN 7 //pc7
#define SW0_PIN 6 //pc6
#define OUTPUT 1
#define INPUT 0

const unsigned char prescale[5]={
  0b00000001, //1
  0b00000010, //8
  0b00000011, //64
  0b00000100, //256
  0b00000101, //1024
};

volatile unsigned char viteza_prescale=4;

void timer0_init(void){
  TCCR0A=0b00000000; //COM0A[1:0]- no compare mode, COM0B[1:0]- normal mode operation, 0x00 , WGM0[1:0]-normal mode operation
  TIMSK0=0b00000001; //Overflow Interrupt Enable
  TCCR0B=prescale[viteza_prescale];
  __enable_interrupt();
}

void led0_init(void){
  Init_LED(&DDRC,LED0_PIN,OUTPUT);
  set_pin(&PORTC,LED0_PIN);
}

void sw0_init(void){
  set_direction(&DDRC,SW0_PIN,INPUT);
  set_pin(&PORTC,SW0_PIN);
}

#pragma vector=TIMER0_OVF_vect
__interrupt void timer0_ovf_interrupt(void){
    Toggle_LED(&PORTC,LED0_PIN);

}
void main( void )
{
  led0_init();
  sw0_init();
  timer0_init();
  unsigned char buton_vechi=1;
  while(1){
    unsigned char buton_curent=read_pin(&PINC,SW0_PIN);
    if(buton_vechi==1 && buton_curent==0){
      for(volatile int i=0; i<3000; i++); //debounce
      
      if(read_pin(&PINC, SW0_PIN) == 0){
        viteza_prescale++;
        if(viteza_prescale > 4){
        viteza_prescale = 0;
        }
        TCCR0B=prescale[viteza_prescale];
      }
    
   }
   buton_vechi=buton_curent;
  }
}
