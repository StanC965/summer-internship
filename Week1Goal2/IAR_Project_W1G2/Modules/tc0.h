#ifndef TC0_H
#define TC0_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Module Information
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
 *  \file       tc0.h
 *  \brief      Modular Timer/Counter 0 (TC0) Driver
 *  \author     Chirila Viorel
 *  \date       23.07.2026
 */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Data Types & Structures
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief Available operating modes for TC0 */
typedef enum {
  TC0_MODE_NORMAL = 0,
  TC0_MODE_PWM_PHASE_CORRECT = 1,
  TC0_MODE_CTC = 2,
  TC0_MODE_FAST_PWM = 3
} tc0_mode_t;

/** \brief Prescaler options (Clock Selection)
    These values map to the CS0[2:0] bits in hardware */ 
typedef enum {
  TC0_PRESCALER_OFF = 0,      // Timer stopped
  TC0_PRESCALER_1 = 1,        // No prescaling (System Clock)
  TC0_PRESCALER_8 = 2,        // System Clock / 8
  TC0_PRESCALER_64 = 3,       // System Clock / 64
  TC0_PRESCALER_256 = 4,      // System Clock / 256
  TC0_PRESCALER_1024 = 5      // System Clock / 1024
} tc0_prescaler_t;

/** \brief Configuration structure */
typedef struct {
  tc0_mode_t      mode;                   // Operating mode
  tc0_prescaler_t prescaler;              // Clock divider
  unsigned char   interrupt_overflow;     // 1 = Enable, 0 = Disable
  unsigned char   interrupt_compare_a;    // 1 = Enable, 0 = Disable
  unsigned char   interrupt_compare_b;    // 1 = Enable, 0 = Disable
  unsigned char   ocr0a_value;            // OCR0A value for CTC mode
} tc0_config_t;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void tc0_init(const tc0_config_t *config)
    \brief      Initializes TC0 hardware based on the provided configuration.
    \param[in]  config Pointer to the configuration structure.
    \param[out] None.
    \return     None.
*/
extern void tc0_init(const tc0_config_t *config);

#endif 