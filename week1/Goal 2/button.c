#include "button.h"


__interrupt void buton_apasat(void)
{
  if(PINC_PINC6==0){
    btn0 ^=1;
  }
  if(PINC_PINC1==0){
    btn0 ? (state=1) : (btn1^=1);
  }
}

__interrupt void Button3(void)
{
  if(PINA_PINA1==0){
   btn0 ? (state=1) : (btn3^=1);
  }
  if(PINA_PINA0==0){
   btn0 ? (state=1) : (btn2^=1);
  }
  
}

void btn_init(){
   PCMSK0=0x03;
   PCMSK2=0x42;
   PCICR =0x05;
   SREG_I=1;
}

void PressToSos(){
  if(btn0==1){
     Point(&PORTC,PIN7);
     Point(&PORTC,PIN7);
     Point(&PORTC,PIN7);
     Line(&PORTC,PIN7);
     Line(&PORTC,PIN7);
     Line(&PORTC,PIN7);
     Point(&PORTC,PIN7);
     Point(&PORTC,PIN7);
     Point(&PORTC,PIN7);
     delay(5);
     btn0=0;
  }
  }
void SosStop(){
   if(btn0==1){
     delay(2);
     while(1){
       if(btn0==0){
         break;}
     Point(&PORTC,PIN7);
     if(btn0==0){
       
       break;}
     Point(&PORTC,PIN7);
     if(btn0==0){
         
         break;}
     Point(&PORTC,PIN7);
    if(btn0==0){
         
         break;}
     Line(&PORTC,PIN7);
     if(btn0==0){
        
         break;}
     Line(&PORTC,PIN7);
     if(btn0==0)
         break;
     Line(&PORTC,PIN7);
     if(btn0==0){
         
         break;}
     Point(&PORTC,PIN7);
     if(btn0==0){
         
         break;}
     Point(&PORTC,PIN7);
    if(btn0==0){
         
         break;}
     Point(&PORTC,PIN7);
     
     }
     btn0=0;
   }
}
void ButtonPlay(){
  if(btn0){
    led0_set_state(ON);
    if(state) {LedBlinkFast(&PORTC,PIN7);state=0;}
    
  }
  else{
    led0_set_state(OFF);
    if(btn1){ LedOn(&PORTD,PIN5); }else{LedOff(&PORTD,PIN5);}
    if(btn2){ LedOn(&PORTD,PIN4);}else {LedOff(&PORTD,PIN4);}
    if(btn3){ LedOn(&PORTA,PIN3);}else{LedOff(&PORTA,PIN3);}
    
  }
}
