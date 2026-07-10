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
    //led 2
    PORTE=0xff;
    //Led 1
    PORTB=0xff;
    //led 3
    PORTA=0xff;
    
    while(1)
    {
        
        PORTB=0xf7;
        PORTE =0xef; 
        PORTA=0xff;
        cycle(400000); 
        PORTA=0x7f;
        PORTB=0xff;
        cycle(400000);
        PORTE =0xff; 
        PORTB=0xf7;
        cycle(400000);
        
    }
    
  
  }
