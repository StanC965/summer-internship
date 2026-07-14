#include "iom324pb.h"
#include "gpio.h" 
#include "led.h" 
#include "sos.h"
#define  TOGGLE_NR       3
#define  DEBOUNCE        3000U
#define  BLINK_SPACE     500U


int volatile count1=0;
int volatile count2=0;
int volatile count3=0;
_Bool volatile sw0=0;


#pragma vector = PCINT0_vect
__interrupt void PinChangePortA_ISR(void)
{
     for(int i=0;i<DEBOUNCE;i++)  
       {}
  
     if(sw0)
     {
             
           led_Set(LED_ZERO);
           for(int i=0;i<BLINK_SPACE;i++)
           led_Reset(LED_ZERO);
           for(int i=0;i<BLINK_SPACE;i++)      //Bloc de clipire/blink
           led_Set(LED_ZERO);
           for(int i=0;i<BLINK_SPACE;i++)
           led_Reset(LED_ZERO);
           for(int i=0;i<BLINK_SPACE;i++)
           led_Set(LED_ZERO);
           for(int i=0;i<BLINK_SPACE;i++)
           led_Reset(LED_ZERO);
     }
   else
    {
    
          
         if ( ((PINA & (1 << 0)) == 0)&& count1==0 )    //daca e prima apasare 
          {
               led_Reset(LED_ONE);
               count1++;
        
          }   
         
         else if((PINA & (1 << 0)) == 0)    // daca e alta apasare decat prima
          {
                  count1++;
          }         
                
          if ( ((PINA & (1 << 1)) == 0)&& count3==0 )     //daca e prima apasare 
           {
                  led_Reset(LED_THREE);
                  count3++;
           }
          else if ((PINA & (1 << 1)) == 0)   // daca e alta apasare decat prima
           {
                count3++;
           }
          
          if(count1 == TOGGLE_NR)       // daca am apasat de destule ori ca sa se stinga
           {
                  count1=0;
                  led_Set(LED_ONE);
           }
           if(count3== TOGGLE_NR)
            {
                  led_Set(LED_THREE);
                  count3=0;
            }
    }

  
}

#pragma vector = PCINT2_vect
__interrupt void PinChangePortC_ISR(void)
{
  

             
             
             
            
    for(int i=0;i<DEBOUNCE;i++)
    {}
          if ( ((PINC & (1 << 6)) == 0 ))  
              {
                     sw0=!sw0;
                     if(sw0)
                     {
                      
                         led_Reset(LED_ZERO);  
                     }
                     else
                        led_Set(LED_ZERO);
                      led_Set(LED_ONE);
                      led_Set(LED_TWO);       
                      led_Set(LED_THREE);         //resetam tot la LEDs
                      count1=0;
                      count2=0;
                      count3=0;
                     
                     
                     
              }
         
   else if ( (PINC & (1 << 1)) == 0 )
    {
        if (sw0) // Daca e blocat facem blink
        {
              led_Set(LED_ZERO);
           for(int i=0;i<BLINK_SPACE;i++)
           led_Reset(LED_ZERO);
           for(int i=0;i<BLINK_SPACE;i++)      //Bloc de clipire/blink
           led_Set(LED_ZERO);
           for(int i=0;i<BLINK_SPACE;i++)
           led_Reset(LED_ZERO);
           for(int i=0;i<BLINK_SPACE;i++)
           led_Set(LED_ZERO);
           for(int i=0;i<BLINK_SPACE;i++)
           led_Reset(LED_ZERO);
        }
        else // Daca NU este blocat avemomportamentul normal
        {
            if (count2 == 0)  
            {
                led_Reset(LED_TWO);
                count2++;
            }
            else 
            {
                count2++;
            }
              
            if(count2 == TOGGLE_NR)
            {
                count2 = 0;
                led_Set(LED_TWO);
            }
        }


      }
}




void setup(void)
{
    leds_initialize(1, 1, 1, 1, 0);  //initializam cele 3 led-uri  in manual spune ca sunt active low 
    
    led_Set(LED_ONE);
    led_Set(LED_TWO);        //le punem pe high(le stingem)
    led_Set(LED_THREE);
    led_Set(LED_ZERO);
    
    ///////DIRECTIE BUTOANE/////////   
    gpio_set_direction(&DDRC, 1, GPIO_INPUT); //punem butonul 1 ca intrare
    gpio_set_direction(&DDRA, 0, GPIO_INPUT); //punem butonul 2 ca intrare
    gpio_set_direction(&DDRA, 1, GPIO_INPUT); //punem butonul 3 ca intrare
    gpio_set_direction(&DDRC,6, GPIO_INPUT); //SW0
    
    
    
    
     ///////INTRERUPERI PORTURI/////////   
     gpio_set_pin(&PCICR, 2); //activam intreruperile pe port C   butonul 1
     gpio_set_pin(&PCICR, 0); // activam intreruperile pe port A  butonul 2 si 3 
     
     
     //////PULL-UP RESISTOR//////     
       gpio_set_pin(&PORTC, 1);
       gpio_set_pin(&PORTA, 1);            //fara asta led-urile se comporta instabil
       gpio_set_pin(&PORTA, 0);
       gpio_set_pin(&PORTC, 6);
     
     ////////INTRERUPERI BUTOANE/////////
    
     gpio_set_pin(&PCMSK0, 1); //buton 2
     gpio_set_pin(&PCMSK0, 0); //buton 3
     gpio_set_pin(&PCMSK2, 1); //buton 1
     gpio_set_pin(&PCMSK2, 6); //SW0
     
     //////INTRERUPERI GLOBALE///////
     gpio_set_pin(&SREG, 7);
    
}

void main(void)
{
    setup();
                                                                      
    while(1)    
    {
  
    }
}
/*
Pin on EXT connector Silk screen marking
7 LED1 PD05
8 LED2 PD04                         <----- din document      De iesire
6 LED3 PA03


PC1 SDA0 (two-wire Serial Bus0 Data Input/Output Line)
PCINT17 (Pin Change Interrupt 17)

PA1 ADC1 (ADC input channel 1)                                  De intrare
PCINT1 (Pin Change Interrupt 1)

PA0 ADC0 (ADC input channel 0)
PCINT0 (Pin Change Interrupt 0)

*/



