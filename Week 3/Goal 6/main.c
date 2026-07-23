//681
#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include <intrinsics.h>
#include "scheduler.h"
#include "scheduler_cfg.h"


#define PCIE2   2
#define PCIE0   0
#define BTNSW0_PIN 6    //pc6
#define BTN1_PIN 1      //pc1
#define BTN2_PIN 0      //pa0
#define BTN3_PIN 1      //pa1
#define LED0_PIN 7      //pc7
#define LED1_PIN 5      //pd5
#define LED2_PIN 4      //pd4
#define LED3_PIN 3      //pa3
#define OUTPUT 1
#define INPUT 0

void setup(void) {
    Init_LED(&DDRD, LED1_PIN, OUTPUT);
    Init_LED(&DDRD, LED2_PIN, OUTPUT);
    Init_LED(&DDRA, LED3_PIN, OUTPUT);
    Init_LED(&DDRC, LED0_PIN, OUTPUT);
    set_pin(&PORTD, LED1_PIN); 
    set_pin(&PORTD, LED2_PIN); 
    set_pin(&PORTA, LED3_PIN); 
    set_pin(&PORTC, LED0_PIN);
    set_direction(&DDRC, BTN1_PIN, INPUT); 
    set_direction(&DDRA, BTN2_PIN, INPUT);
    set_direction(&DDRA, BTN3_PIN, INPUT);
    set_direction(&DDRC, BTNSW0_PIN, INPUT);
    set_pin(&PORTC, BTN1_PIN);
    set_pin(&PORTA, BTN2_PIN);
    set_pin(&PORTA, BTN3_PIN);
    set_pin(&PORTC, BTNSW0_PIN);
}

void timer1_init(void) {
    TCCR1A = 0b00000000; 
    TCCR1B = 0b00001001; //mod CTC, prescaler 1
    OCR1A = 9999;        //numarul de pasi pentru 10ms 
    TIMSK1 = 0b00000010;
    __enable_interrupt();
}

#pragma vector=TIMER1_COMPA_vect
__interrupt void Timer1_Tick_ISR(void) {
    scheduler_flags_management(); 
}

void main(void) {
    setup(); 
    timer1_init();
    schedule_tasks_dispatcher();

}