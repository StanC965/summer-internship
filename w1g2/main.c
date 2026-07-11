/* Exercitiul 211-216: Control LED0
   
   212: PORTC are 8 pini (PC0-PC7).
   213: ATmega324PB are 4 porturi (PORTA, PORTB, PORTC, PORTD) x 8 pini = 32 pini GPIO total.
   214: LED0 este conectat pe placa la pinul PB0 . 
        
*/

#include <iom324pb.h>

//  216
void delay(void) {
    long i;
    for(i = 0; i < 500000; i++); 
}

void main(void) {
    // 215: Configurare LED0 (PB0) ca iesire
    DDRB_DDRB0 = 1; 

    // 216: Bucla infinita pentru blink
    while(1) {
        PORTB_PORTB0 = 1; // LED0 Aprins
        delay();
        
        PORTB_PORTB0 = 0; // LED0 Stins
        delay();
    }
}