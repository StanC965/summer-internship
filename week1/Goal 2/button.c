#include "button.h"

void PressToSos(){
  if(PINC_PINC6==0){
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
  }