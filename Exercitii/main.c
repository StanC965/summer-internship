#include "iom324pb.h"
#include "gpio.h" 
#include "led.h" 




#define  TOGGLE_NR       3
#define  DEBOUNCE        3000u
#define  BLINK_NUMBER    10

volatile int count1 = 0;
volatile int count2 = 0;
volatile int count3 = 0;
volatile _Bool sw0 = 0;

volatile unsigned char overflow_counter = 0;


#pragma vector=TIMER0_OVF_vect
__interrupt void timer0_isr(void)
{
    overflow_counter++;
}


#pragma vector = PCINT0_vect
__interrupt void PinChangePortA_ISR(void)
{
    
    for(volatile int i=0; i<DEBOUNCE; i++) {} 
  
    if(!sw0) 
    {
      TCCR0B = 0; 
         if ((PINA & (1 << 0)) == 0) // Buton 2
         {
             count1++;
             if(count1 == 1) led_Reset(LED_ONE);
             else if(count1 >= TOGGLE_NR)
             {
                 count1 = 0;
                 led_Set(LED_ONE);
             }
         }   
         
         if ((PINA & (1 << 1)) == 0) // Buton 3
         {
             count3++;
             if(count3 == 1) led_Reset(LED_THREE);
             else if(count3 >= TOGGLE_NR)
             {
                 count3 = 0;
                 led_Set(LED_THREE);
             }
         }
    }
    else{
    TCCR0B = 3; }
    
}


#pragma vector = PCINT2_vect
__interrupt void PinChangePortC_ISR(void)
{
    for(volatile int i=0; i<DEBOUNCE; i++) {}
    
   
    if ((PINC & (1 << 6)) == 0 )  
    {
         sw0 = !sw0; // Schimbam starea
         
         if(sw0)
         {
             
             overflow_counter = 0;
     
              led_Reset(LED_ZERO);   
               led_Set(LED_ONE);
                led_Set(LED_TWO);        
              led_Set(LED_THREE);
              count1=0;
              count2=0;count3=0;
         }
         else
         {
             //ooprim timerul si resetam tot
             TCCR0B = 0;
             led_Set(LED_ZERO);
        
         }
    }

    else if ((PINC & (1 << 1)) == 0 )
    {
        if (!sw0) 
        {
          TCCR0B = 0; 
            count2++;
            if (count2 == 1) led_Reset(LED_TWO);
            else if(count2 >= TOGGLE_NR)
            {
                count2 = 0;
                led_Set(LED_TWO);
            }
        }
        else{
        TCCR0B = 3; 
        }
    }
}

void setup(void)
{
    leds_initialize(1, 1, 1, 1, 0);  
    
    // Stingem ledurile (active low)
    led_Set(LED_ONE);
    led_Set(LED_TWO);        
    led_Set(LED_THREE);
    led_Set(LED_ZERO);
    
    /////// DIRECTIE BUTOANE /////////   
    gpio_set_direction(&DDRC, 1, GPIO_INPUT); // butonul 1 
    gpio_set_direction(&DDRA, 0, GPIO_INPUT); // butonul 2 
    gpio_set_direction(&DDRA, 1, GPIO_INPUT); // butonul 3 
    gpio_set_direction(&DDRC, 6, GPIO_INPUT); // SW0
    
    /////// PULL-UP RESISTORS //////     
    gpio_set_pin(&PORTC, 1);
    gpio_set_pin(&PORTA, 1);           
    gpio_set_pin(&PORTA, 0);
    gpio_set_pin(&PORTC, 6);

    ////// TIMER 0 SETUP //////
    TCCR0A = 0;
    TCCR0B = 0; // Il tinem oprit la inceput
    TIMSK0 |= (1 << TIMSK0_TOIE0); // Activam intreruperea de overflow
    TCNT0 = 0;
    
    /////// INTRERUPERI PORTURI /////////   
    gpio_set_pin(&PCICR, 2); // activam intreruperile pe port C (buton 1, SW0)
    gpio_set_pin(&PCICR, 0); // activam intreruperile pe port A (buton 2, 3) 
     
    //////// MASCA INTRERUPERI BUTOANE /////////
    gpio_set_pin(&PCMSK0, 1); // buton 3
    gpio_set_pin(&PCMSK0, 0); // buton 2
    gpio_set_pin(&PCMSK2, 1); // buton 1
    gpio_set_pin(&PCMSK2, 6); // SW0
     
    ////// INTRERUPERI GLOBALE ///////
    gpio_set_pin(&SREG, 7);
}

void main(void)
{
    setup();
    _Bool on = 0; 
     int durata=0;                                      
    while(1)    
    {
        if(sw0) // Blink-ul functioneaza doar cand SW0 este in modul activ
        {
            
            if(overflow_counter >= 4)
            {
                overflow_counter = 0; // Resetam contorul pentru urmatorul ciclu
                
                if(on)
                    led_Set(LED_ZERO);
                else
                    led_Reset(LED_ZERO);
                    
                on = !on;
                durata++;
            }
            if(durata>=BLINK_NUMBER)
            {
              durata=0;
              TCCR0B =0; 
              led_Reset(LED_ZERO);
            }; 
            
        }
      
    }
}



