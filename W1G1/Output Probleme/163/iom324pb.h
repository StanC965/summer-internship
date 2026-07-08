/****************************************************************************
 **             - iom324pb.h -
 **
 **     This file declares the internal register addresses for ATmega324PB.
 **
 **     Used with iccAVR and aAVR.
 **
 **     Copyright 2025 IAR Systems AB. All rights reserved.
 **
 **     File version: $Revision: 20234 $
 **
 ***************************************************************************/

#ifdef  __IAR_SYSTEMS_ICC__
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#endif

#include "iomacro.h"

#if TID_GUARD(3)
#error This file should only be compiled with iccavr or aavr with processor option -v3
#endif /* TID_GUARD(3) */
#ifdef __HAS_RAMPZ__
#error This file should not have RAMPZ enabled, use --cpu or --64k_flash
#endif /* __HAS_RAMPZ__ */

#ifndef __IOM324PB_H


/* SFRs are local in assembler modules (so this file may need to be */
/* included in more than one module in the same source file), */
/* but #defines must only be made once per source file. */

/*==============================*/
/* Interrupt Vector Definitions */
/*==============================*/

/* NB! vectors are specified as byte addresses */

#define RESET_vect               (0x00) /* External Pin,Power-on Reset,Brown-out Reset,Watchdog Reset,and JTAG AVR Reset. See Datasheet.      */
#define INT0_vect                (0x04) /* External Interrupt Request 0 */
#define INT1_vect                (0x08) /* External Interrupt Request 1 */
#define INT2_vect                (0x0C) /* External Interrupt Request 2 */
#define PCINT0_vect              (0x10) /* Pin Change Interrupt Request 0 */
#define PCINT1_vect              (0x14) /* Pin Change Interrupt Request 1 */
#define PCINT2_vect              (0x18) /* Pin Change Interrupt Request 2 */
#define PCINT3_vect              (0x1C) /* Pin Change Interrupt Request 3 */
#define WDT_vect                 (0x20) /* Watchdog Time-out Interrupt */
#define TIMER2_COMPA_vect        (0x24) /* Timer/Counter2 Compare Match A */
#define TIMER2_COMPB_vect        (0x28) /* Timer/Counter2 Compare Match B */
#define TIMER2_OVF_vect          (0x2C) /* Timer/Counter2 Overflow */
#define TIMER1_CAPT_vect         (0x30) /* Timer/Counter1 Capture Event */
#define TIMER1_COMPA_vect        (0x34) /* Timer/Counter1 Compare Match A */
#define TIMER1_COMPB_vect        (0x38) /* Timer/Counter1 Compare Match B */
#define TIMER1_OVF_vect          (0x3C) /* Timer/Counter1 Overflow */
#define TIMER0_COMPA_vect        (0x40) /* Timer/Counter0 Compare Match A */
#define TIMER0_COMPB_vect        (0x44) /* Timer/Counter0 Compare Match B */
#define TIMER0_OVF_vect          (0x48) /* Timer/Counter0 Overflow */
#define SPI0_STC_vect            (0x4C) /* SPI0 Serial Transfer Complete */
#define USART0_RX_vect           (0x50) /* USART0 Rx Complete */
#define USART0_UDRE_vect         (0x54) /* USART0 Data register Empty */
#define USART0_TX_vect           (0x58) /* USART0 Tx Complete */
#define ANALOG_COMP_vect         (0x5C) /* Analog Comparator */
#define ADC_vect                 (0x60) /* ADC Conversion Complete */
#define EE_READY_vect            (0x64) /* EEPROM Ready */
#define TWI0_vect                (0x68) /* 2-wire Serial Interface 0 */
#define SPM_READY_vect           (0x6C) /* Store Program Memory Read */
#define USART1_RX_vect           (0x70) /* USART1 RX complete */
#define USART1_UDRE_vect         (0x74) /* USART1 Data Register Empty */
#define USART1_TX_vect           (0x78) /* USART1 TX complete */
#define TIMER3_CAPT_vect         (0x7C) /* Timer/Counter3 Capture Event */
#define TIMER3_COMPA_vect        (0x80) /* Timer/Counter3 Compare Match A */
#define TIMER3_COMPB_vect        (0x84) /* Timer/Counter3 Compare Match B */
#define TIMER3_OVF_vect          (0x88) /* Timer/Counter3 Overflow */
#define USART0_RXS_vect          (0x8C) /* USART0 RX start edge detect */
#define USART0_START_vect        (0x8C) /* USART0 RX start edge detect */
#define USART1_RXS_vect          (0x90) /* USART1 RX start edge detect */
#define USART1_START_vect        (0x90) /* USART1 RX start edge detect */
#define PCINT4_vect              (0x94) /* Pin Change Interrupt Request 4 */
#define XOSCFD_vect              (0x98) /* Crystal failure detect */
#define PTC_EOC_vect             (0x9C) /* PTC end of conversion */
#define PTC_WCOMP_vect           (0xA0) /* PTC window comparator interrupt */
#define SPI1_STC_vect            (0xA4) /* SPI1 Serial Transfer Complete */
#define TWI1_vect                (0xA8) /* 2-wire Serial Interface 1 */
#define TIMER4_CAPT_vect         (0xAC) /* Timer/Counter4 Capture Event */
#define TIMER4_COMPA_vect        (0xB0) /* Timer/Counter4 Compare Match A */
#define TIMER4_COMPB_vect        (0xB4) /* Timer/Counter4 Compare Match B */
#define TIMER4_OVF_vect          (0xB8) /* Timer/Counter4 Overflow */
#define USART2_RX_vect           (0xBC) /* USART2 Rx Complete */
#define USART2_UDRE_vect         (0xC0) /* USART2 Data register Empty */
#define USART2_TX_vect           (0xC4) /* USART2 Tx Complete */
#define USART2_RXS_vect          (0xC8) /* USART2 RX start edge detect */
#define USART2_START_vect        (0xC8) /* USART2 RX start edge detect */


#ifdef __IAR_SYSTEMS_ASM__   
#ifndef ENABLE_BIT_DEFINITIONS
#define  ENABLE_BIT_DEFINITIONS
#endif /* ENABLE_BIT_DEFINITIONS */
#include "bitdefinitions/iom324pb.inc"
#endif /* __IAR_SYSTEMS_ASM__ */

#endif /* __IOM324PB_H (define part) */


/* Include the SFR part if this file has not been included before,
 * OR this file is included by the assembler (SFRs must be defined in
 * each assembler module). */
#if !defined(__IOM324PB_H) || defined(__IAR_SYSTEMS_ASM__)
#define __IOM324PB_H

#pragma language=save
#pragma language=extended

/*==========================*/
/* Predefined SFR Addresses */
/*==========================*/

/****************************************************************************
 * An example showing the SFR_B() macro call, 
 * the expanded result and usage of this result:
 *
 * SFR_B_R(0x1F,   AVR) Expands to:
 * __io union {
 *             unsigned char AVR;                 // The sfrb as 1 byte
 *             struct {                           // The sfrb as 8 bits
 *                     unsigned char AVR_Bit0:1,
 *                                   AVR_Bit1:1,
 *                                   AVR_Bit2:1,
 *                                   AVR_Bit3:1,
 *                                   AVR_Bit4:1,
 *                                   AVR_Bit5:1,
 *                                   AVR_Bit6:1,
 *                                   AVR_Bit7:1;
 *                    };
 *            } @ 0x1F;
 * Examples of how to use the expanded result:
 * AVR |= (1<<5);
 * or like this:
 * AVR_Bit5 = 1;
 *
 *
 *
 * An example showing the SFR_B_N() macro call, 
 * the expanded result and usage of this result:
 * SFR_B_N(0x25,  TCCR2, FOC2, WGM20, COM21, COM20, WGM21, CS22, CS21, CS20)
 *  Expands to:
 *  __io union { 
 *              unsigned char TCCR2; 
 *              struct { 
 *                      unsigned char TCCR2_Bit0:1, 
 *                                    TCCR2_Bit1:1, 
 *                                    TCCR2_Bit2:1, 
 *                                    TCCR2_Bit3:1, 
 *                                    TCCR2_Bit4:1, 
 *                                    TCCR2_Bit5:1, 
 *                                    TCCR2_Bit6:1, 
 *                                    TCCR2_Bit7:1; 
 *                     }; 
 *              struct { 
 *                      unsigned char TCCR2_CS20:1, 
 *                                    TCCR2_CS21:1, 
 *                                    TCCR2_CS22:1, 
 *                                    TCCR2_WGM21:1, 
 *                                    TCCR2_COM20:1, 
 *                                    TCCR2_COM21:1, 
 *                                    TCCR2_WGM20:1, 
 *                                    TCCR2_FOC2:1; 
 *                     }; 
 *             } @ 0x25;
 * Examples of how to use the expanded result:
 * TCCR2 |= (1<<5); 
 * or if ENABLE_BIT_DEFINITIONS is defined   
 * TCCR2 |= (1<<COM21);
 * or like this:
 * TCCR2_Bit5 = 1;
 * or like this:
 * TCCR2_COM21 = 1;
 ***************************************************************************/

 SFR_B_N(0xDD, TWAMR1, TWAM16, TWAM15, TWAM14, TWAM13, TWAM12, TWAM11, TWAM10, Dummy0)
 SFR_B_N(0xDC, TWCR1, TWINT, TWEA, TWSTA, TWSTO, TWWC, TWEN, Dummy1, TWIE)
 SFR_B_N(0xDB, TWDR1, TWDR17, TWDR16, TWDR15, TWDR14, TWDR13, TWDR12, TWDR11, TWDR10)
 SFR_B_N(0xDA, TWAR1, TWA6, TWA5, TWA4, TWA3, TWA2, TWA1, TWA0, TWGCE)
 SFR_B_N(0xD9, TWSR1, TWS07, TWS06, TWS05, TWS04, TWS03, Dummy2, TWPS1, TWPS0)
 SFR_B_N(0xD8, TWBR1, TWBR17, TWBR16, TWBR15, TWBR14, TWBR13, TWBR12, TWBR11, TWBR10)
 SFR_B_N(0xD6, UDR2, UDR27, UDR26, UDR25, UDR24, UDR23, UDR22, UDR21, UDR20)
 SFR_W_N(0xD4, UBRR2, Dummy15, Dummy14, Dummy13, Dummy12, UBRR211, UBRR210, UBRR29, UBRR28, UBRR27, UBRR26, UBRR25, UBRR24, UBRR23, UBRR22, UBRR21, UBRR20)
 SFR_B_N(0xD3, UCSR2D, RXSIE, RXS, SFDE, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)
 SFR_B_N(0xD2, UCSR2C, UMSEL1, UMSEL0, UPM1, UPM0, USBS, UCSZ1, UCSZ0, UCPOL)
 SFR_B_N(0xD1, UCSR2B, RXCIE, TXCIE, UDRIE, RXEN, TXEN, UCSZ2, RXB8, TXB8)
 SFR_B_N(0xD0, UCSR2A, RXC, TXC, UDRE, FE, DOR, UPE, U2X, MPCM)
 SFR_B_N(0xCE, UDR1, UDR17, UDR16, UDR15, UDR14, UDR13, UDR12, UDR11, UDR10)
 SFR_W_N(0xCC, UBRR1, Dummy15, Dummy14, Dummy13, Dummy12, UBRR111, UBRR110, UBRR19, UBRR18, UBRR17, UBRR16, UBRR15, UBRR14, UBRR13, UBRR12, UBRR11, UBRR10)
 SFR_B_N(0xCB, UCSR1D, RXSIE, RXS, SFDE, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)
 SFR_B_N(0xCA, UCSR1C, UMSEL1, UMSEL0, UPM1, UPM0, USBS, UCSZ1, UCSZ0, UCPOL)
 SFR_B_N(0xC9, UCSR1B, RXCIE, TXCIE, UDRIE, RXEN, TXEN, UCSZ2, RXB8, TXB8)
 SFR_B_N(0xC8, UCSR1A, RXC, TXC, UDRE, FE, DOR, UPE, U2X, MPCM)
 SFR_B_N(0xC6, UDR0, UDR07, UDR06, UDR05, UDR04, UDR03, UDR02, UDR01, UDR00)
 SFR_W_N(0xC4, UBRR0, Dummy15, Dummy14, Dummy13, Dummy12, UBRR011, UBRR010, UBRR09, UBRR08, UBRR07, UBRR06, UBRR05, UBRR04, UBRR03, UBRR02, UBRR01, UBRR00)
 SFR_B_N(0xC3, UCSR0D, RXSIE, RXS, SFDE, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)
 SFR_B_N(0xC2, UCSR0C, UMSEL1, UMSEL0, UPM1, UPM0, USBS, UCSZ1, UCSZ0, UCPOL)
 SFR_B_N(0xC1, UCSR0B, RXCIE, TXCIE, UDRIE, RXEN, TXEN, UCSZ2, RXB8, TXB8)
 SFR_B_N(0xC0, UCSR0A, RXC, TXC, UDRE, FE, DOR, UPE, U2X, MPCM)
 SFR_B_N(0xBD, TWAMR0, TWAM06, TWAM05, TWAM04, TWAM03, TWAM02, TWAM01, TWAM00, Dummy0)
 SFR_B_N(0xBC, TWCR0, TWINT, TWEA, TWSTA, TWSTO, TWWC, TWEN, Dummy1, TWIE)
 SFR_B_N(0xBB, TWDR0, TWDR07, TWDR06, TWDR05, TWDR04, TWDR03, TWDR02, TWDR01, TWDR00)
 SFR_B_N(0xBA, TWAR0, TWA6, TWA5, TWA4, TWA3, TWA2, TWA1, TWA0, TWGCE)
 SFR_B_N(0xB9, TWSR0, TWS07, TWS06, TWS05, TWS04, TWS03, Dummy2, TWPS1, TWPS0)
 SFR_B_N(0xB8, TWBR0, TWBR07, TWBR06, TWBR05, TWBR04, TWBR03, TWBR02, TWBR01, TWBR00)
 SFR_B_N(0xB6, ASSR, Dummy7, EXCLK, AS2, TCN2UB, OCR2AUB, OCR2BUB, TCR2AUB, TCR2BUB)
 SFR_B_N(0xB4, OCR2B, OCR2B7, OCR2B6, OCR2B5, OCR2B4, OCR2B3, OCR2B2, OCR2B1, OCR2B0)
 SFR_B_N(0xB3, OCR2A, OCR2A7, OCR2A6, OCR2A5, OCR2A4, OCR2A3, OCR2A2, OCR2A1, OCR2A0)
 SFR_B_N(0xB2, TCNT2, TCNT27, TCNT26, TCNT25, TCNT24, TCNT23, TCNT22, TCNT21, TCNT20)
 SFR_B_N(0xB1, TCCR2B, FOC2A, FOC2B, Dummy5, Dummy4, WGM22, CS22, CS21, CS20)
 SFR_B_N(0xB0, TCCR2A, COM2A1, COM2A0, COM2B1, COM2B0, Dummy3, Dummy2, WGM21, WGM20)
 SFR_B_N(0xAE, SPDR1, SPDR17, SPDR16, SPDR15, SPDR14, SPDR13, SPDR12, SPDR11, SPDR10)
 SFR_B_N(0xAD, SPSR1, SPIF, WCOL, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, SPI2X)
 SFR_B_N(0xAC, SPCR1, SPIE, SPE, DORD, MSTR, CPOL, CPHA, SPR1, SPR0)
 SFR_W_N(0xAA, OCR4B, OCR4B15, OCR4B14, OCR4B13, OCR4B12, OCR4B11, OCR4B10, OCR4B9, OCR4B8, OCR4B7, OCR4B6, OCR4B5, OCR4B4, OCR4B3, OCR4B2, OCR4B1, OCR4B0)
 SFR_W_N(0xA8, OCR4A, OCR4A15, OCR4A14, OCR4A13, OCR4A12, OCR4A11, OCR4A10, OCR4A9, OCR4A8, OCR4A7, OCR4A6, OCR4A5, OCR4A4, OCR4A3, OCR4A2, OCR4A1, OCR4A0)
 SFR_W_N(0xA6, ICR4, ICR415, ICR414, ICR413, ICR412, ICR411, ICR410, ICR49, ICR48, ICR47, ICR46, ICR45, ICR44, ICR43, ICR42, ICR41, ICR40)
 SFR_W_N(0xA4, TCNT4, TCNT415, TCNT414, TCNT413, TCNT412, TCNT411, TCNT410, TCNT49, TCNT48, TCNT47, TCNT46, TCNT45, TCNT44, TCNT43, TCNT42, TCNT41, TCNT40)
 SFR_B_N(0xA2, TCCR4C, FOC4A, FOC4B, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)
 SFR_B_N(0xA1, TCCR4B, ICNC4, ICES4, Dummy5, WGM43, WGM42, CS42, CS41, CS40)
 SFR_B_N(0xA0, TCCR4A, COM4A1, COM4A0, COM4B1, COM4B0, Dummy3, Dummy2, WGM41, WGM40)
 SFR_W_N(0x9A, OCR3B, OCR3B15, OCR3B14, OCR3B13, OCR3B12, OCR3B11, OCR3B10, OCR3B9, OCR3B8, OCR3B7, OCR3B6, OCR3B5, OCR3B4, OCR3B3, OCR3B2, OCR3B1, OCR3B0)
 SFR_W_N(0x98, OCR3A, OCR3A15, OCR3A14, OCR3A13, OCR3A12, OCR3A11, OCR3A10, OCR3A9, OCR3A8, OCR3A7, OCR3A6, OCR3A5, OCR3A4, OCR3A3, OCR3A2, OCR3A1, OCR3A0)
 SFR_W_N(0x96, ICR3, ICR315, ICR314, ICR313, ICR312, ICR311, ICR310, ICR39, ICR38, ICR37, ICR36, ICR35, ICR34, ICR33, ICR32, ICR31, ICR30)
 SFR_W_N(0x94, TCNT3, TCNT315, TCNT314, TCNT313, TCNT312, TCNT311, TCNT310, TCNT39, TCNT38, TCNT37, TCNT36, TCNT35, TCNT34, TCNT33, TCNT32, TCNT31, TCNT30)
 SFR_B_N(0x92, TCCR3C, FOC3A, FOC3B, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)
 SFR_B_N(0x91, TCCR3B, ICNC3, ICES3, Dummy5, WGM33, WGM32, CS32, CS31, CS30)
 SFR_B_N(0x90, TCCR3A, COM3A1, COM3A0, COM3B1, COM3B0, Dummy3, Dummy2, WGM31, WGM30)
 SFR_W_N(0x8A, OCR1B, OCR1B15, OCR1B14, OCR1B13, OCR1B12, OCR1B11, OCR1B10, OCR1B9, OCR1B8, OCR1B7, OCR1B6, OCR1B5, OCR1B4, OCR1B3, OCR1B2, OCR1B1, OCR1B0)
 SFR_W_N(0x88, OCR1A, OCR1A15, OCR1A14, OCR1A13, OCR1A12, OCR1A11, OCR1A10, OCR1A9, OCR1A8, OCR1A7, OCR1A6, OCR1A5, OCR1A4, OCR1A3, OCR1A2, OCR1A1, OCR1A0)
 SFR_W_N(0x86, ICR1, ICR115, ICR114, ICR113, ICR112, ICR111, ICR110, ICR19, ICR18, ICR17, ICR16, ICR15, ICR14, ICR13, ICR12, ICR11, ICR10)
 SFR_W_N(0x84, TCNT1, TCNT115, TCNT114, TCNT113, TCNT112, TCNT111, TCNT110, TCNT19, TCNT18, TCNT17, TCNT16, TCNT15, TCNT14, TCNT13, TCNT12, TCNT11, TCNT10)
 SFR_B_N(0x82, TCCR1C, FOC1A, FOC1B, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)
 SFR_B_N(0x81, TCCR1B, ICNC1, ICES1, Dummy5, WGM13, WGM12, CS12, CS11, CS10)
 SFR_B_N(0x80, TCCR1A, COM1A1, COM1A0, COM1B1, COM1B0, Dummy3, Dummy2, WGM11, WGM10)
 SFR_B_N(0x7F, DIDR1, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, Dummy2, AIN1D, AIN0D)
 SFR_B_N(0x7E, DIDR0, ADC7D, ADC6D, ADC5D, ADC4D, ADC3D, ADC2D, ADC1D, ADC0D)
 SFR_B_N(0x7C, ADMUX, REFS1, REFS0, ADLAR, MUX4, MUX3, MUX2, MUX1, MUX0)
 SFR_B_N(0x7B, ADCSRB, GPIOEN, ACME, Dummy5, Dummy4, Dummy3, ADTS2, ADTS1, ADTS0)
 SFR_B_N(0x7A, ADCSRA, ADEN, ADSC, ADATE, ADIF, ADIE, ADPS2, ADPS1, ADPS0)
 SFR_W_N(0x78, ADC, ADC15, ADC14, ADC13, ADC12, ADC11, ADC10, ADC9, ADC8, ADC7, ADC6, ADC5, ADC4, ADC3, ADC2, ADC1, ADC0)
 SFR_B_N(0x75, PCMSK4, Dummy7, PCINT38, PCINT37, PCINT36, PCINT35, PCINT34, PCINT33, PCINT32)
 SFR_B_N(0x73, PCMSK3, PCINT31, PCINT30, PCINT29, PCINT28, PCINT27, PCINT26, PCINT25, PCINT24)
 SFR_B_N(0x72, TIMSK4, Dummy7, Dummy6, ICIE4, Dummy4, Dummy3, OCIE4B, OCIE4A, TOIE4)
 SFR_B_N(0x71, TIMSK3, Dummy7, Dummy6, ICIE3, Dummy4, Dummy3, OCIE3B, OCIE3A, TOIE3)
 SFR_B_N(0x70, TIMSK2, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, OCIE2B, OCIE2A, TOIE2)
 SFR_B_N(0x6F, TIMSK1, Dummy7, Dummy6, ICIE1, Dummy4, Dummy3, OCIE1B, OCIE1A, TOIE1)
 SFR_B_N(0x6E, TIMSK0, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, OCIE0B, OCIE0A, TOIE0)
 SFR_B_N(0x6D, PCMSK2, PCINT23, PCINT22, PCINT21, PCINT20, PCINT19, PCINT18, PCINT17, PCINT16)
 SFR_B_N(0x6C, PCMSK1, PCINT15, PCINT14, PCINT13, PCINT12, PCINT11, PCINT10, PCINT9, PCINT8)
 SFR_B_N(0x6B, PCMSK0, PCINT7, PCINT6, PCINT5, PCINT4, PCINT3, PCINT2, PCINT1, PCINT0)
 SFR_B_N(0x69, EICRA, Dummy7, Dummy6, ISC21, ISC20, ISC11, ISC10, ISC01, ISC00)
 SFR_B_N(0x68, PCICR, Dummy7, Dummy6, Dummy5, PCIE4, PCIE3, PCIE2, PCIE1, PCIE0)
 SFR_B_N(0x66, OSCCAL, OSCCAL7, OSCCAL6, OSCCAL5, OSCCAL4, OSCCAL3, OSCCAL2, OSCCAL1, OSCCAL0)
 SFR_B_N(0x65, PRR1, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, Dummy2, PRTIM4, PRTIM3)
 SFR_B_N(0x64, PRR0, PRTWI0, PRTIM2, PRTIM0, PRUSART1, PRTIM1, PRSPI0, PRUSART0, PRADC)
 SFR_B_N(0x63, PRR2, Dummy7, Dummy6, Dummy5, Dummy4, PRPTC, PRUSART2, PRSPI1, PRTWI1)
 SFR_B_N(0x62, XFDCSR, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, Dummy2, XFDIF, XFDIE)
 SFR_B_N(0x61, CLKPR, CLKPCE, Dummy6, Dummy5, Dummy4, CLKPS3, CLKPS2, CLKPS1, CLKPS0)
 SFR_B_N(0x60, WDTCSR, WDIF, WDIE, WDP3, WDCE, WDE, WDP2, WDP1, WDP0)
 SFR_B_N(0x3F, SREG, I, T, H, S, V, N, Z, C)
 SFR_W_N(0x3D, SP, Dummy15, Dummy14, Dummy13, SP12, SP11, SP10, SP9, SP8, SP7, SP6, SP5, SP4, SP3, SP2, SP1, SP0)
 SFR_B_N(0x37, SPMCSR, SPMIE, RWWSB, SIGRD, RWWSRE, BLBSET, PGWRT, PGERS, SPMEN)
 SFR_B_N(0x35, MCUCR, JTD, BODS, BODSE, PUD, Dummy3, Dummy2, IVSEL, IVCE)
 SFR_B_N(0x34, MCUSR, Dummy7, Dummy6, Dummy5, JTRF, WDRF, BORF, EXTRF, PORF)
 SFR_B_N(0x33, SMCR, Dummy7, Dummy6, Dummy5, Dummy4, SM2, SM1, SM0, SE)
 SFR_B_N_EXTRA(0x31, OCDR, OCDR7, OCDR6, OCDR5, OCDR4, OCDR3, OCDR2, OCDR1, OCDR0, \
              struct{unsigned char :7;unsigned char OCDR_IDRD:1;};)
 SFR_B_N(0x30, ACSR, ACD, ACBG, ACO, ACI, ACIE, ACIC, ACIS1, ACIS0)
 SFR_B_N(0x2F, ACSRB, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, ACOE)
 SFR_B_N(0x2E, SPDR0, SPDR07, SPDR06, SPDR05, SPDR04, SPDR03, SPDR02, SPDR01, SPDR00)
 SFR_B_N(0x2D, SPSR0, SPIF, WCOL, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, SPI2X)
 SFR_B_N(0x2C, SPCR0, SPIE, SPE, DORD, MSTR, CPOL, CPHA, SPR1, SPR0)
 SFR_B_N(0x2B, GPIOR2, GPIOR27, GPIOR26, GPIOR25, GPIOR24, GPIOR23, GPIOR22, GPIOR21, GPIOR20)
 SFR_B_N(0x2A, GPIOR1, GPIOR17, GPIOR16, GPIOR15, GPIOR14, GPIOR13, GPIOR12, GPIOR11, GPIOR10)
 SFR_B_N(0x28, OCR0B, OCR0B7, OCR0B6, OCR0B5, OCR0B4, OCR0B3, OCR0B2, OCR0B1, OCR0B0)
 SFR_B_N(0x27, OCR0A, OCR0A7, OCR0A6, OCR0A5, OCR0A4, OCR0A3, OCR0A2, OCR0A1, OCR0A0)
 SFR_B_N(0x26, TCNT0, TCNT07, TCNT06, TCNT05, TCNT04, TCNT03, TCNT02, TCNT01, TCNT00)
 SFR_B_N(0x25, TCCR0B, FOC0A, FOC0B, Dummy5, Dummy4, WGM02, CS02, CS01, CS00)
 SFR_B_N(0x24, TCCR0A, COM0A1, COM0A0, COM0B1, COM0B0, Dummy3, Dummy2, WGM01, WGM00)
 SFR_B_N(0x23, GTCCR, TSM, Dummy6, Dummy5, Dummy4, Dummy3, Dummy2, PSRASY, PSRSYNC)
 SFR_W_N(0x21, EEAR, Dummy15, Dummy14, Dummy13, Dummy12, EEAR11, EEAR10, EEAR9, EEAR8, EEAR7, EEAR6, EEAR5, EEAR4, EEAR3, EEAR2, EEAR1, EEAR0)
 SFR_B_N(0x20, EEDR, EEDR7, EEDR6, EEDR5, EEDR4, EEDR3, EEDR2, EEDR1, EEDR0)
 SFR_B_N(0x1F, EECR, Dummy7, Dummy6, EEPM1, EEPM0, EERIE, EEMPE, EEPE, EERE)
 SFR_B_N(0x1E, GPIOR0, GPIOR07, GPIOR06, GPIOR05, GPIOR04, GPIOR03, GPIOR02, GPIOR01, GPIOR00)
 SFR_B_N(0x1D, EIMSK, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, INT2, INT1, INT0)
 SFR_B_N(0x1C, EIFR, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, INTF2, INTF1, INTF0)
 SFR_B_N(0x1B, PCIFR, Dummy7, Dummy6, Dummy5, PCIF4, PCIF3, PCIF2, PCIF1, PCIF0)
 SFR_B_N(0x19, TIFR4, Dummy7, Dummy6, ICF4, Dummy4, Dummy3, OCF4B, OCF4A, TOV4)
 SFR_B_N(0x18, TIFR3, Dummy7, Dummy6, ICF3, Dummy4, Dummy3, OCF3B, OCF3A, TOV3)
 SFR_B_N(0x17, TIFR2, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, OCF2B, OCF2A, TOV2)
 SFR_B_N(0x16, TIFR1, Dummy7, Dummy6, ICF1, Dummy4, Dummy3, OCF1B, OCF1A, TOV1)
 SFR_B_N(0x15, TIFR0, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, OCF0B, OCF0A, TOV0)
 SFR_B_N(0x0E, PORTE, Dummy7, PORTE6, PORTE5, PORTE4, PORTE3, PORTE2, PORTE1, PORTE0)
 SFR_B_N(0x0D, DDRE, Dummy7, DDRE6, DDRE5, DDRE4, DDRE3, DDRE2, DDRE1, DDRE0)
 SFR_B_N(0x0C, PINE, Dummy7, PINE6, PINE5, PINE4, PINE3, PINE2, PINE1, PINE0)
 SFR_B_N(0x0B, PORTD, PORTD7, PORTD6, PORTD5, PORTD4, PORTD3, PORTD2, PORTD1, PORTD0)
 SFR_B_N(0x0A, DDRD, DDRD7, DDRD6, DDRD5, DDRD4, DDRD3, DDRD2, DDRD1, DDRD0)
 SFR_B_N(0x09, PIND, PIND7, PIND6, PIND5, PIND4, PIND3, PIND2, PIND1, PIND0)
 SFR_B_N(0x08, PORTC, PORTC7, PORTC6, PORTC5, PORTC4, PORTC3, PORTC2, PORTC1, PORTC0)
 SFR_B_N(0x07, DDRC, DDRC7, DDRC6, DDRC5, DDRC4, DDRC3, DDRC2, DDRC1, DDRC0)
 SFR_B_N(0x06, PINC, PINC7, PINC6, PINC5, PINC4, PINC3, PINC2, PINC1, PINC0)
 SFR_B_N(0x05, PORTB, PORTB7, PORTB6, PORTB5, PORTB4, PORTB3, PORTB2, PORTB1, PORTB0)
 SFR_B_N(0x04, DDRB, DDRB7, DDRB6, DDRB5, DDRB4, DDRB3, DDRB2, DDRB1, DDRB0)
 SFR_B_N(0x03, PINB, PINB7, PINB6, PINB5, PINB4, PINB3, PINB2, PINB1, PINB0)
 SFR_B_N(0x02, PORTA, PORTA7, PORTA6, PORTA5, PORTA4, PORTA3, PORTA2, PORTA1, PORTA0)
 SFR_B_N(0x01, DDRA, DDRA7, DDRA6, DDRA5, DDRA4, DDRA3, DDRA2, DDRA1, DDRA0)
 SFR_B_N(0x00, PINA, PINA7, PINA6, PINA5, PINA4, PINA3, PINA2, PINA1, PINA0)

#pragma language=restore

#ifndef __IAR_SYSTEMS_ASM__
#include "bitdefinitions/iom324pb.inc"
#endif

#endif /* __IOM324PB_H (SFR part) */

