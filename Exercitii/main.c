#include "iom324pb.h"
#include "gpio.h" 
#include "led.h" 
#include "sos.h"


#pragma vector = PCINT0_vect
__interrupt void PinChangePortA_ISR(void)
{
  

    
    if ( (PINA & (1 << 0)) == 0 )  
    {
        led_Reset(LED_ONE);
    }   
    else
    {
        led_Set(LED_ONE);
    }         
                
    if ( (PINA & (1 << 1)) == 0 )  
    {
        led_Reset(LED_THREE);
    }
    else
    {
        led_Set(LED_THREE);
    }
   
  
}

#pragma vector = PCINT2_vect
__interrupt void PinChangePortC_ISR(void)
{
  

    
    if ( (PINC & (1 << 1)) == 0 )  
    {
        led_Reset(LED_TWO);
    }
    else
    {
        led_Set(LED_TWO);
    }
  
}




void setup(void)
{
    leds_initialize(0, 1, 1, 1, 0);  //initializam cele 3 led-uri  in manual spune ca sunt active low 
    
    led_Set(LED_ONE);
    led_Set(LED_TWO);        //le punem pe high(le stingem)
    led_Set(LED_THREE);
    
    ///////DIRECTIE BUTOANE/////////   
    gpio_set_direction(&DDRC, 1, GPIO_INPUT); //punem butonul 1 ca intrare
    gpio_set_direction(&DDRA, 0, GPIO_INPUT); //punem butonul 2 ca intrare
    gpio_set_direction(&DDRA, 1, GPIO_INPUT); //punem butonul 3 ca intrare
    
    
    
    
     ///////INTRERUPERI PORTURI/////////   
     gpio_set_pin(&PCICR, 2); //activam intreruperile pe port C   butonul 1
     gpio_set_pin(&PCICR, 0); // activam intreruperile pe port A  butonul 2 si 3 
     
     
     //////PULL-UP RESISTOR//////     
       gpio_set_pin(&PORTC, 1);
       gpio_set_pin(&PORTA, 1);            //fara asta led-urile se comporta instabil
       gpio_set_pin(&PORTA, 0);
     
     ////////INTRERUPERI BUTOANE/////////
    
     gpio_set_pin(&PCMSK0, 1); //buton 2
     gpio_set_pin(&PCMSK0, 0); //buton 3
     gpio_set_pin(&PCMSK2, 1); //buton 1
     
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



