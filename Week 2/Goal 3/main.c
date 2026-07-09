//315
#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include <intrinsics.h>

#define PCIE2   2
#define PCINT22 6

volatile int buton=0;

#pragma vector=PCINT2_vect
__interrupt void Button_ISR(void) 
{
    if(read_pin(&PINC,6)==0){
        if(buton==0){ //toggle la buton
          buton=1;
        }
        else {
          buton=0;
        }
        //while(read_pin(&PINC,6)==0); //cat timp e apasat 
        for(volatile long i=0; i<3000; i++);
      }
}

void setup(void) {
    Init_LED(&DDRC, 7, 1);
    PowerOff_LED(&PORTC, 7); 
    set_direction(&DDRC, 6, 0);
    set_pin(&PORTC, 6); 

    // activam intreruperile pentru tot portul C
    PCICR |= (1 << PCIE2);   
    // pin 6
    PCMSK2 |= (1 << PCINT22);
    __enable_interrupt(); 
}

void main(void) {
    setup(); 

    while(1){
      if(buton==1){
        SOS(&PORTC,7);
        PowerOff_LED(&PORTC, 7);
        for(long i=0;i<300000;i++);
      }
      else{
        PowerOff_LED(&PORTC, 7);
      } 
    }
}