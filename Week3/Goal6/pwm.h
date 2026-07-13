#ifndef PWM_C
#define PWM_C

extern void initializePwm();

extern void startPwm(unsigned short int prescale);

extern void pwmSetDutyCycle(unsigned char duty);

extern void setPwmDc(unsigned char param);
#endif