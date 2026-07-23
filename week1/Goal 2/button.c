#include "button.h"

unsigned volatile int prescale=0;
static unsigned char buf_btn0 = 0xFF;
static unsigned char buf_btn1 = 0xFF;
static unsigned char buf_btn2 = 0xFF;
static unsigned char buf_btn3 = 0xFF;
volatile unsigned char btn0_debounced = 0;
volatile unsigned char btn1_debounced = 0;
volatile unsigned char btn2_debounced = 0;
volatile unsigned char btn3_debounced = 0;

__interrupt void buton_apasat(void)
{
  
}

__interrupt void Button3(void)
{
  
  
}

void btn_init(){
   PCMSK0=0x03;
   PCMSK2=0x42;
   PCICR =0x05;
   SREG_I=1;
   prescale=0;
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
  if(btn0_debounced){
    led0_set_state(ON);
    if(state) {LedBlinkFast(&PORTC,PIN7);state=0;}
    
  }
  else{
    led0_set_state(OFF);
    if(btn1_debounced){ LedOn(&PORTD,PIN5); }else{LedOff(&PORTD,PIN5);}
    if(btn2_debounced){ LedOn(&PORTD,PIN4);}else {LedOff(&PORTD,PIN4);}
    if(btn3_debounced){ LedOn(&PORTA,PIN3);}else{LedOff(&PORTA,PIN3);}
    
  }
}
void Button_Debounce_Task_10ms()
{
 
    buf_btn0 = ((buf_btn0 << 1) | !PINC_PINC6) & 0x1F;
    buf_btn1=((buf_btn1 << 1) | !PINC_PINC1) & 0x1F;
    buf_btn2 = ((buf_btn2 << 1) | !PINA_PINA0) & 0x1F;
    buf_btn3 = ((buf_btn3 << 1) | !PINA_PINA1) & 0x1F;

 
    if (buf_btn0 == 0x1f) btn0_debounced ^= 1;
    if(!btn0_debounced){
      if (buf_btn1 == 0x1f){ 
        btn1_debounced ^= 1;
      }
      if (buf_btn2 == 0x1f) {btn2_debounced ^= 1;}
      if (buf_btn3 == 0x1f){(btn3_debounced ^= 1);}
    }
    if(btn0_debounced){
      if (buf_btn1 == 0x1f)state=1;
      if (buf_btn2 == 0x1f)state=1;
      if (buf_btn3 == 0x1f)state=1;
    }
    
  
}
