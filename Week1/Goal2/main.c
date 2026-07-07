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
          while(1){
          POINT(0);
          LINE(0);
          POINT(0);
          for(long i = 0 ;i<100000;i++);
          pressed = 1;
          }
        }
      }
    }
    
  }
}
