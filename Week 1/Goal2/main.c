//243
#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
//sw0 pc6
void setup(void) {
    DDRC =0xBF;
    
}

void main(void) {
    setup(); 
    PORTC=0xFF;
    PORTC=PORTC | (1<<6);
    
    unsigned char buton;
    while(1){
      buton=PINC;
      if((buton & (1<<6))==0){
      PORTC=0x7F;
      }
      else{
      PORTC=0xFF;
      }
    }
}