/* 
 * File:   mcal_interrupt_manger.h
 * Author: moham
 *
 * Created on September 24, 2023, 2:31 PM
 */

#ifndef MCAL_INTERRUPT_MANGER_H
#define	MCAL_INTERRUPT_MANGER_H

/* -------------------- Includes -------------------- */
#include "mcal_interrupt_config.h"

/* -------------------- MACRO Declarations -------------------- */

/* -------------------- MACROS FUNCTIONS Declarations -------------------- */

/* -------------------- DataTypes -------------------- */

/* -------------------- Software Interfaces Declarations -------------------- */
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 RB4_source);
void RB5_ISR(uint8 RB5_source);
void RB6_ISR(uint8 RB6_source);
void RB7_ISR(uint8 RB7_source);


#endif	/* MCAL_INTERRUPT_MANGER_H */

