#include "usart.h"
#include "gpio.h"



void main(void){
  initUsart();
  SREG |= (1<<7);
  transmitUsartString("Hello world!");
  while(1){
    
    unsigned char v = receiveUsart();
    int a = 0;
  }
  
}