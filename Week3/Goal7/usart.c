#ifndef USART_C
#define USART_C

#include "gpio.h"
#define F_CPU      8000000UL
#define BAUD_RATE  9600UL

#define bufferSize 128

#define UBRR_VALUE ((F_CPU/(16UL*BAUD_RATE))-1)
#define RXCIE 7
#define UDRIE 5
#define RXEN 4
#define TXEN 3

#define USBS 3
#define UCSZ1 2
#define UCSZ0 1

#define INPUT 0
#define OUTPUT 1

#define PE3 3
#define PE2 2

static unsigned char overflow = 0;
static unsigned char receiveBuffer[bufferSize];
static unsigned char rxHead = 0;
static unsigned char rxTail = 0;

static unsigned char txBuffer[bufferSize];

static unsigned char txHead = 0;
static unsigned char txTail = 0;

#pragma vector = USART2_RX_vect    
__interrupt void receiveInterrupt(void){
    unsigned char next = (rxHead+1) %bufferSize;
    if(overflow == 0){
      if(next != rxTail){
        receiveBuffer[rxHead] = UDR2;
        rxHead = next;
      }
      else
        overflow = 1;
    }
    else
    {
      if(rxHead != rxTail){
          overflow = 0;
      }
    }
}

#pragma vector = USART2_UDRE_vect    
__interrupt void transmitInterrupt(void){
   if(txHead == txTail)
    {
        resetPin(&UCSR2B,UDRIE);  
    }
    else
    {
        UDR2 = txBuffer[txTail];
        txTail = (txTail + 1) % bufferSize;
    }

}

void initUsart(){
  //Receive interrupt enable
    setPin(&UCSR2B,RXCIE);
    //Empty Interrupt Enable
    setPin(&UCSR2B,RXEN);//Receive enable
    setPin(&UCSR2B,TXEN);//Transmitter enable
    
    
    setPin(&UCSR2C,USBS); // 2 bit stop
    setPin(&UCSR2C,UCSZ1); 
    setPin(&UCSR2C,UCSZ0);//pentru 8 biti 
    
    UBRR2H = (unsigned char)(UBRR_VALUE >> 8);//setam BAUD
    UBRR2L = (unsigned char)UBRR_VALUE;
    
    setDirection(&DDRE,PE3,OUTPUT);

    
    setDirection(&DDRE,PE2,INPUT);
}

unsigned char receiveUsart(){
  if(rxTail != rxHead){
    unsigned char c = receiveBuffer[rxTail];
    rxTail = (rxTail+1)%bufferSize;
    return c;
  }
  else
      return -1;
}

void transmitUsartChar(unsigned char trans){
  txBuffer[txHead] = trans;
  txHead = (txHead + 1)%bufferSize;
  setPin(&UCSR2B,UDRIE);

}

void transmitUsartString(unsigned char str[]){
  while(*str != '\0'){
    transmitUsartChar(*str);
    str++;
  }

}



#endif