#ifndef USART_C
#define USART_C

#include "gpio.h"        
#include "iom324pb.h"
#include "adc.h"
#include "usart.h"
#include "led.h"
#include "usart.h"


//command protocol


void USART0_Init( unsigned int ubrr)
{
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;

//rx interrupt
    UCSR0B = (1<<3) | (1<<4) | (1<<7);

   //  8 data bits, 1 stop bit
 
    UCSR0C = (1<<2) | (1<<1);  
}

void USART0_Transmit( unsigned char data )
{
   
    while ( !( UCSR0A & (1<<5)) );

    UDR0 = data;
}

/* 
 * VIRTUAL MCU2 (SLAVE): 
 * este mereu apelat cand primeste date pe 13 RX
 */
#pragma vector=USART0_RX_vect
__interrupt void Recieve(void)
{
    unsigned char cmd = UDR0; 
    
    switch(cmd) {
        case CMD_LED0_ON:     led_Set(LED_ZERO); break;
        case CMD_LED0_OFF:    led_Reset(LED_ZERO); break;
        case CMD_LED0_TOGGLE: led_TOGGLE(LED_ZERO); break;
            
        case CMD_LED1_ON:     led_Set(LED_ONE); break;
        case CMD_LED1_TOGGLE: led_TOGGLE(LED_ONE); break;
            
        case CMD_LED2_ON:     led_Set(LED_TWO); break;
        case CMD_LED2_TOGGLE: led_TOGGLE(LED_TWO); break;
            
        case CMD_LED3_ON:     led_Set(LED_THREE); break;
        case CMD_LED3_TOGGLE: led_TOGGLE(LED_THREE); break;
    }
}

#endif