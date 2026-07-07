#include "sos.h"


int main( void )
{
  set_direction(&DDRC,7,1);
  set_direction(&DDRC,6,0);
  set_pin(&PORTC,6);
  int pressed = 0;
  int confidence_pressed= 0;
  int confidence_release = 0;
  
  while(1){
    if(!get_pin(&PINC,6)){
      confidence_pressed++;
      if(confidence_pressed >200)
      {
        if(pressed == 0){
          pressed = 1;
          while(pressed){
            if(!get_pin(&PINC,6)){
                pressed = ! pressed;
            }
          SOS(0);
          for(long i = 0 ;i<100000;i++);
          
          }
         
        }
        confidence_pressed = 0;
      }
    }
    
  }
}
