/* 
   225 - alternating LED sequence:
    A: LED1 and LED3 ON while LED2 OFF
    B: LED2 ON while LED1 and LED3 OFF
*/

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

    while(1)
    {
        /* A */
        PORTD &= ~(1 << LED1_PIN);   /* LED1 ON  */
        PORTA &= ~(1 << LED3_PIN);   /* LED3 ON  */
        PORTD |=  (1 << LED2_PIN);   /* LED2 OFF */
        delay();

        /* B */
        PORTD |=  (1 << LED1_PIN);   /* LED1 OFF */
        PORTA |=  (1 << LED3_PIN);   /* LED3 OFF */
        PORTD &= ~(1 << LED2_PIN);   /* LED2 ON  */
        delay();
    }
}