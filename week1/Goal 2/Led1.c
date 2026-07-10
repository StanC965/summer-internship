#include <iom324pb.h>


void cycle(unsigned long i){
  
  while(i>0){
  i--;
  }
}

void main (void)
{
  
  

    
    DDRE =0x10; 
    DDRB=0x08;
    DDRA=0x80;
    PORTE=0xff;
    PORTB=0xff;
    PORTA=0xff;
    
    while(1)
    {
        
        PORTE =0xff; 
        PORTA=0x7f;
        PORTB=0xf7;
        cycle(400000);
        PORTE =0xef; 
        PORTA=0xff;
        PORTB=0xff;
        cycle(400000);
    }
    
  
  }