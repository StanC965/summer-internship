#ifndef SCHEDULER_H
#define SCHEDULER_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  

/** \fn     void task_10ms(void);

    \brief      [ This function completes a task every 10ms]  
extern void task_10ms(void);

/** \fn     void task_50ms(void);

    \brief      [  This function completes a task every 50ms]  
*/
extern void task_50ms(void);

/** \fn     void task_100ms(void);

    \brief      [  This function completes a task every 100ms]  
*/
extern void task_100ms(void);

/** \fn     void task_500ms(void);

    \brief      [  This function completes a task every 500ms]  
*/
extern void task_500ms(void);

/** \fn     void task_1000ms(void);

    \brief      [  This function completes a task every 1000ms]  
*/
extern void task_1000ms(void);


#endif

