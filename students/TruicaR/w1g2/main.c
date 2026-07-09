#include "iom324pb.h"

void main(void)
{
  
    DDRD_DDRD5 = 1;
    DDRD_DDRD4 = 1;
    DDRA_DDRA3 = 1;
    while (1)
    { 
      for(volatile int i=0; i<8000;i++){  
        PORTD_PORTD5=0;}
      for(volatile int i=0; i<8000;i++){
        PORTD_PORTD5=1;}
      for(volatile int i=0; i<8000;i++){
        PORTD_PORTD4=0;}
       for(volatile int i=0; i<8000;i++){
         PORTD_PORTD4=1;}
        for(volatile int i=0; i<8000;i++){
        
          PORTA_PORTA3=0;}
         for(volatile int i=0; i<8000;i++){
           PORTA_PORTA3=1;}
         for(volatile int i=0; i<8000;i++){}
        
    }
}