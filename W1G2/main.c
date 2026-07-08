#include "iom324pb.h"

void setup()
{
   
    TCNT1 = 0;
    TCCR1A = 0;           
    OCR1A = 62500;             
    TCCR1B = (1 << 1);   
    
    

 
    DDRC = 0b10000000;         
    DDRD = (1 << 5) | (1 << 4);
    DDRA = 0b00001000; 
    DDRB = (1 << 3);    
    PORTC = 0xFF;              
    PORTD = 0xEF;        
    PORTA = 0xFF;
    PORTB = 0xFF;        
}


unsigned char sequence[5][4] =
{
    {0xFF, 0xFF, 255,0xff}, 
    {0xCF, 0xFF, 128,0xff}, 
    {0xEF, 0,    0  ,0x7f},
    {0xDF, 0,    64 ,0xff} ,
     {0xEF, 0,    0,0x7f  }
};

unsigned char i = 0;

void main(void)
{
    setup();

    
    unsigned char counter_LED = 0;
    unsigned char LED_dutyCycle = 255; 

    while(1)
    {
        
        counter_LED++; 
        
       
        if (counter_LED < LED_dutyCycle)            //cum functioneaza: daca ne uitam pe datasheet-ul IO1_Xplained_Pro_design_documentation_release_rev3.pdf
        {                                          //vedem la pg 2 ca LED PWM e conectat la pinul 7 care la placuta de baza este PB03
            PORTB &= ~(1 << 3);                    // un pulse width modulation functioneaza prin modificarea duty cycle-ului ,adica cat la suta din perioada unei unde 
        }                                           // ne aflam in high, ceea ce da iluzia la ochi ca are o intensitate mai mica sau mai mare 
        else                                    // ca sa fac duty_cycle-ul am ales ca 255 de cicli de while(1) in main sa fie duty cycle-ul ,iar la fiecare iteratie se incrementeaza
        {                                 //counter-ul ,acest 255 initial poate fi modificat ulterior pe baza la sequence,adica ii setez ce intensitate sa aiba
            PORTB |= (1 << 3);  
        }

 
        if (TCNT1 >= OCR1A)
        {
            PORTD = sequence[i][0];
            PORTA = sequence[i][1];
            
            
            LED_dutyCycle = sequence[i][2];
            PORTC=sequence[i++][3];    
            
            if (i > 3)
                i = 0;
            
            TCNT1 = 0; // Reset timer 1
        }
    }
}