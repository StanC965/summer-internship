#include "sos.h"
#include "iom324pb.h"



#pragma once
static unsigned volatile int btn0=0;
static unsigned volatile int btn1=0;
static unsigned volatile int btn2=0;
static unsigned volatile int btn3=0;
static unsigned volatile short state=0;
extern unsigned volatile int prescale;


#pragma vector=PCINT2_vect
__interrupt void buton_apasat(void);
#pragma vector=PCINT0_vect
__interrupt void Button3(void);
void PressToSos();
void SosStop();
void ButtonPlay();
void btn_init();

