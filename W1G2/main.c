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



void set_pinC(unsigned char bit)
{
    PORTC |= (1 << bit);  //functia trebuie sa primeasca pin-ul care vrem sa fie setat 
    
}


void reset_pinC(unsigned char bit)
{
  PORTC &= ~(1 << bit);                 //functia trebuie sa primeasca pin-ul care vrem sa fie resetat 
  
    
}

void toggle_pinC(unsigned char bit)
{
  PORTC ^=1<<bit;             
}

void set_direction(unsigned char bit,_Bool intrare)
{
  if(intrare)
  DDRC&=~(1<<bit);                              //spre deosebire de celelalte,functia asta trebuie sa aiba ca si parametru formal si un bool    
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
                                                      //TOATE 3 functiile nu trebuie sa returneze nimic caci modifica PORTC si atat;
      
        if (TCNT1 >= OCR1A)   
        {
            set_pinC(7);    
            
            if(state)
            {
              reset_pinC(7);
            }
            else                          // observam ca la a 5a perioada se opreste de tot led-ul => Set_direction face ce trebuie
              set_pinC(7);
            
            state=!state;
              
            TCNT1=0;
            counter++;
            if(counter==5)
              toggle_pinC(7); // observam ca la a 5a perioada se opreste LED-ul si dupa aceea REVINE, asta inseamna ca toggle-ul a functionat ;
             // set_direction(7,1);
        }
    }
}