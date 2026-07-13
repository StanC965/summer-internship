/* 224 - turn LEDs on and off individually, in a repetitive sequence (0.5s each) */
#include "iom324pb.h"

#define LED1_PIN 5   /* LED1 on PD5 */
#define LED2_PIN 4   /* LED2 on PD4 */
#define LED3_PIN 3   /* LED3 on PA3 */

#define DELAY_HALF_SECOND 15000UL   

void delay(void)
{
    volatile unsigned long i;
    for (i = 0; i < DELAY_HALF_SECOND; i++) { }
}

void main( void )
{
    /* configure the LED pins as outputs */
    DDRD |= (1 << LED1_PIN);
    DDRD |= (1 << LED2_PIN);
    DDRA |= (1 << LED3_PIN);

    /* all LEDs off */
    PORTD |= (1 << LED1_PIN);
    PORTD |= (1 << LED2_PIN);
    PORTA |= (1 << LED3_PIN);

    while(1)
    {
        /* LED1 on and off */
        PORTD &= ~(1 << LED1_PIN);   delay();
        PORTD |=  (1 << LED1_PIN);   delay();

        /* LED2 on and off */
        PORTD &= ~(1 << LED2_PIN);   delay();
        PORTD |=  (1 << LED2_PIN);   delay();

        /* LED3 on and off */
        PORTA &= ~(1 << LED3_PIN);   delay();
        PORTA |=  (1 << LED3_PIN);   delay();
    }
}