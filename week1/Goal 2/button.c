#include "button.h"


__interrupt void buton_apasat(void)
{
  if(PINC_PINC6==0){
    btn0^=1;
  }
  if(PINC_PINC1==0){
  btn1^=1;
  PORTD_PORTD5^=1;
  }
}

__interrupt void Button3(void)
{
  if(PINA_PINA0==0){
 btn2 ^= 1;PORTD_PORTD4^=1;
  }
  if(PINA_PINA1==0){
    btn3 ^= 1;PORTA_PORTA3^=1;
  }
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
