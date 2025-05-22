/* 
 * File:   mcal_external_interrupt.h
 * Author: moham
 *
 * Created on September 24, 2023, 2:34 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* -------------------- Includes -------------------- */
#include "mcal_interrupt_config.h"

/* -------------------- MACRO Declarations -------------------- */

/* These MACROS to set INTx Interrupts configuration */
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURES_ENABLE
/* This routine Enable the External interrupt , INT0 */
#define EXT_INT0_InterruptEnable()                  (INTCONbits.INT0IE = 1)
/* This routine Disable the External interrupt , INT0 */
#define EXT_INT0_InterruptDisable()                 (INTCONbits.INT0IE = 0)
/* This routine Clear the Interrupt Flag , INT0 */
#define EXT_INT0_InterruptFlagClear()               (INTCONbits.INT0IF = 0) 
/* This routine set edge detected of the External Interrupt to Positive edge */
#define EXT_INT0_InerruptRisingEdge()               (INTCON2bits.INTEDG0 = 1)
/* This routine set edge detected of the External Interrupt to Negative edge */
#define EXT_INT0_InerruptFallingEdge()              (INTCON2bits.INTEDG0 = 0)

/* This routine Enable the External interrupt , INT1 */
#define EXT_INT1_InterruptEnable()                  (INTCON3bits.INT1IE = 1)
/* This routine Disable the External interrupt , INT1 */
#define EXT_INT1_InterruptDisable()                 (INTCON3bits.INT1IE = 0)
/* This routine Clear the Interrupt Flag , INT1 */
#define EXT_INT1_InterruptFlagClear()               (INTCON3bits.INT1IF = 0) 
/* This routine set edge detected of the External Interrupt to Positive edge */
#define EXT_INT1_InerruptRisingEdge()               (INTCON2bits.INTEDG1 = 1)
/* This routine set edge detected of the External Interrupt to Negative edge */
#define EXT_INT1_InerruptFallingEdge()              (INTCON2bits.INTEDG1 = 0)

/* This routine Enable the External interrupt , INT2 */
#define EXT_INT2_InterruptEnable()                  (INTCON3bits.INT2IE = 1)
/* This routine Disable the External interrupt , INT2 */
#define EXT_INT2_InterruptDisable()                 (INTCON3bits.INT2IE = 0)
/* This routine Clear the Interrupt Flag , INT2 */
#define EXT_INT2_InterruptFlagClear()               (INTCON3bits.INT2IF = 0) 
/* This routine set edge detected of the External Interrupt to Positive edge */
#define EXT_INT2_InerruptRisingEdge()               (INTCON2bits.INTEDG2 = 1)
/* This routine set edge detected of the External Interrupt to Negative edge */
#define EXT_INT2_InerruptFallingEdge()              (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURES_ENABLE
/*This routine to set priority High of INT1 */
#define EXT_INT1_PriorityLevelHIGH()                (INTCON3bits.INT1IP = 1)
/*This routine to set priority Low of INT1 */
#define EXT_INT1_PriorityLevelLOW()                 (INTCON3bits.INT1IP = 0)
/*This routine to set priority High of INT2 */
#define EXT_INT2_PriorityLevelHIGH()                (INTCON3bits.INT2IP = 1)
/*This routine to set priority Low of INT2 */
#define EXT_INT2_PriorityLevelLOW()                 (INTCON3bits.INT2IP = 0)
#endif

#endif

/* These MACROS to set ONChange Interrupts configuration */
#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURES_ENABLE
/* This routine to Enable the PORTB RBx interrupt */
#define EXT_RBx_InterruptEnabel()                   (INTCONbits.RBIE = 1)
/* This routine to Disable the PORTB RBx interrupt */
#define EXT_RBx_InterruptDisabel()                  (INTCONbits.RBIE = 0)
/* This routine to Clear the PORTB RBx interrupt Flag */
#define EXT_RBx_InterruptFlagClear()                (INTCONbits.RBIF = 0)



#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURES_ENABLE
/* This routine to Set the PORTB RBx interrupt High Priority */
#define EXT_RBx_InterruptHighPrioriy()              (INTCON2bits.RBIP = 1)
/* This routine to Set the PORTB RBx interrupt Low Priority */
#define EXT_RBx_InterruptLowPrioriy()               (INTCON2bits.RBIP = 0)
#endif

#endif
/* -------------------- MACROS FUNCTIONS Declarations -------------------- */

/* -------------------- Data Type Declarations -------------------- */

typedef enum{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE
}interrupt_INTx_edg;
typedef enum{
    INTERRUPT_EXT_INT0 = 0,
    INTERRUPT_EXT_INT1, 
    INTERRUPT_EXT_INT2        
}interrupt_INTx_src;
typedef struct{
    void(* EXT_InterruptHandler)(void);
    pin_config_t mcu_pin;
    interrupt_INTx_edg edge;
    interrupt_INTx_src source;
    interrupt_priority_cfg priority;
}interrupt_INTx_t;
    
typedef struct{
    void(* EXT_InterruptHandler_High)(void);
    void(* EXT_InterruptHandler_Low)(void);
    pin_config_t mcu_pin;
    interrupt_priority_cfg priority;
}interrupt_RBx_t;
/* -------------------- Software Interface Declarations -------------------- */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj);
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj);
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj);
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj);


#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

