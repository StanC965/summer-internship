#include "sos.h"


int main( void )
{
  set_direction(&DDRC,7,1);
  while(1){
    POINT(0);
    LINE(0);
    POINT(0);
    for(long i = 0 ;i<100000;i++);
  }
}
