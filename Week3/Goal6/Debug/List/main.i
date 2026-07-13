#line 1 "D:\\Mircea\\Marqurdt\\summer-internship\\Week3\\Goal6\\main.c"
#line 1 "D:\\Mircea\\Marqurdt\\summer-internship\\Week3\\Goal6\\pwm.h"



extern void initializePwm();

extern void startPwm(unsigned short int prescale);

extern void pwmSetDutyCycle(unsigned char duty);

#line 2 "D:\\Mircea\\Marqurdt\\summer-internship\\Week3\\Goal6\\main.c"


void main( void )
{
  initializePwm();
  startPwm(1);
  while(1){
    pwmSetDutyCycle(100);

    for(long i=0;i<500000;i++);

    pwmSetDutyCycle(75);

    for(long i=0;i<500000;i++);

    pwmSetDutyCycle(50);

    for(long i=0;i<500000;i++);

    pwmSetDutyCycle(25);

    for(long i=0;i<500000;i++);

    pwmSetDutyCycle(0);

    for(long i=0;i<500000;i++);
}
    
  
}
