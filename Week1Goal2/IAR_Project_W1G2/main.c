// 215 - CORE
#include <iom324pb.h>

void main( void )
{
  
  DDRC_DDRC7 = 1; //Configure PC7 as an output:
  
  PORTC_PORTC7 = 0; //Turn the LED ON (active LOW):
  
  while(1){
    
  }
}
