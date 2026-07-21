/**
 * @file sos.h
 * @brief Header file for Morse code SOS optical signaling module[cite: 14].
 * @details Contains delay duration macros and function prototypes for playing dot/dash sequences[cite: 14].
 */

#ifndef SOS_H
#define SOS_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "led.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** @name Morse Code Timing Constants */
/**@{*/
#define SOS_TIME_POINT_DURATION  150000UL 
#define SOS_TIME_LINE_DURATION   450000UL 
#define SOS_TIME_ELEMENT_GAP     150000UL
#define SOS_TIME_CHARACTER_GAP   700000UL
/**@}*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Public Functions                                                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/**
 * @brief Initializes the SOS module by configuring the status LED output[cite: 14].
 */
void sos_init(void);

/**
 * @brief Plays a Morse code 'dot' (.) signal using the status LED[cite: 14].
 */
extern void sos_play_point(void);

/**
 * @brief Plays a Morse code 'dash' (-) signal using the status LED[cite: 14].
 */
extern void sos_play_line(void);

/**
 * @brief Executes a full SOS Morse sequence ("S-O-S") with appropriate inter-character delays[cite: 14].
 */
extern void sos_play_sos(void);

/**
 * @brief Plays the letter 'S' (three dots) with internal element gaps[cite: 14].
 */
extern void sos_play_letter_s(void);

/**
 * @brief Plays the letter 'O' (three dashes) with internal element gaps[cite: 14].
 */
extern void sos_play_letter_o(void);

#endif