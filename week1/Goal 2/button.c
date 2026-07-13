#include "button.h"


__interrupt void buton_apasat(void)
{
  if(PINC_PINC6==0){
 btn ^= 1;
  }
}

void PressToSos(){
  if(btn==1){
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
     btn=0;
  }
  }
void SosStop(){
   if(btn==1){
     delay(2);
     while(1){
       if(btn==0){
         break;}
     Point(&PORTC,PIN7);
     if(btn==0){
       
       break;}
     Point(&PORTC,PIN7);
     if(btn==0){
         
         break;}
     Point(&PORTC,PIN7);
    if(btn==0){
         
         break;}
     Line(&PORTC,PIN7);
     if(btn==0){
        
         break;}
     Line(&PORTC,PIN7);
     if(btn==0)
         break;
     Line(&PORTC,PIN7);
     if(btn==0){
         
         break;}
     Point(&PORTC,PIN7);
     if(btn==0){
         
         break;}
     Point(&PORTC,PIN7);
    if(btn==0){
         
         break;}
     Point(&PORTC,PIN7);
     
     }
     btn=0;
   }
}