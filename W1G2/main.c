#include "iom324pb.h"

void setup()
{
    DDRC = 0b10000000;  
    PORTC = 0;         
    
    TCNT1 = 0;
    OCR1A = 15625;     // o sec
    
    TCCR1A = 0;
    
    TCCR1B = 0x03; 
    
 
    
    
}



void set_pin(volatile unsigned char *PORT,unsigned char bit)
{
    *PORT |= (1 << bit);  //functia trebuie sa primeasca pin-ul care vrem sa fie setat 
    
}


void reset_pin(volatile unsigned char *port,unsigned char bit)
{
  (*port) &= ~(1 << bit);                 //functia trebuie sa primeasca pin-ul care vrem sa fie resetat 
  
    
}

void toggle_pin(volatile unsigned char *PORT,unsigned char bit)
{
  *PORT ^=1<<bit;             
}

void set_direction(volatile unsigned char *DDR,unsigned char bit,_Bool intrare)
{
  if(intrare)
  *DDR &=~(1<<bit);                              //spre deosebire de celelalte,functia asta trebuie sa aiba ca si parametru formal si un bool    
  else                                 //care sa specifice daca pin-ul setat sa fie de intrare sau iesire in DDR;
 DDRC|=1<<bit;
  
}
int counter =0;
_Bool state=1;
void main(void)
{
    setup();

    while(1)
    {
                                                     
      
        if (TCNT1 >= OCR1A)   
        {
            set_pin(&PORTC,7);    
                                                                  
            if(state)
            {
              reset_pin(&PORTC,7);              //AM folosit pointer catre adresa de memorie specifica PORT-ului /DDR-ului astfel am crescut flexibilitatea codului
            }
            else                        
              set_pin(&PORTC,7);
            
            state=!state;
              
            TCNT1=0;
            counter++;
            if(counter==5)
              set_direction(    &DDRC,7,1);
             // toggle_pin(&PORTC,7); 
              
        }
    }
    
}

