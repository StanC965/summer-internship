#ifndef PWM_H
#define PWM_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  Module specific null pointer */
#define sd            ((void*)0x00U)


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  
/** \fn     void pwm_init_LED()

    \brief      [ Aceasta functie configureaza un led pwm]   
*/
extern void pwm_init_LED();

/** \fn     void pwm_test_led()

    \brief      [ Aceasta functie testeaza  5 intensitati ale led-ului]   
*/
extern void pwm_test_led();


#endif