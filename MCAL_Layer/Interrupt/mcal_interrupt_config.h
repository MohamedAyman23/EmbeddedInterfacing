/* 
 * File:   mcal_interrupt_config.h
 * Author: moham
 *
 * Created on September 24, 2023, 2:33 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* -------------------- Includes -------------------- */
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/* -------------------- MACRO Declarations -------------------- */
#define INTERRUPT_ENABLE            1
#define INTERRUPT_DISABLE           0
#define INTERRUPT_OCCUR             1
#define INTERRUPT_NOT_OCCUR         0
#define INTERRUPT_PRIORITY_ENABLE   1
#define INTERRUPT_PRIORITY_DISABLE  0

/* -------------------- MACROS FUNCTIONS Declarations -------------------- */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURES_ENABLE
/* This MACRO will Enable Priority Level on Interrupts */
#define INTERRUPT_PriorityLevelEnable()         (RCONbits.IPEN = 1)
/* This MACRO will Disable Priority Level on Interrupts */
#define INTERRUPT_PriorityLevelDisable()        (RCONbits.IPEN = 0)

/* This MACRO will Enable the global interrupt High priority */
#define INTERRUPT_GlobalInterruptHighEnable()    (INTCONbits.GIEH = 1)
/* This MACRO will Disable the global interrupt High priority */
#define INTERRUPT_GlobalInterruptHighDisable()   (INTCONbits.GIEH = 0)

/* This MACRO will Enable the global interrupt Low priority */
#define INTERRUPT_GlobalInterruptLowEnable()     (INTCONbits.GIEL = 1)
/* This MACRO will Disable the global interrupt Low priority */
#define INTERRUPT_GlobalInterruptLowDisable()    (INTCONbits.GIEL = 0)
#else
/* This MACRO will Enable Peripheral Interrupt */
#define INTERRUPT_PeripheralInterruptEnable()   (INTCONbits.PEIE = 1)
/* This MACRO will Disable Peripheral Interrupt */
#define INTERRUPT_PeripheralInterruptDisable()  (INTCONbits.PEIE = 0)
/* This MACRO will Enable the global interrupt */
#define INTERRUPT_GlobalInterruptEnable()       (INTCONbits.GIE = 1)
/* This MACRO will Disable the global interrupt */
#define INTERRUPT_GlobalInterruptDisable()      (INTCONbits.GIE = 0)
#endif
/* -------------------- DataTypes -------------------- */
typedef enum{
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY
}interrupt_priority_cfg;
/* -------------------- Software Interfaces Declarations -------------------- */

#endif	/* MCAL_INTERRUPT_CONFIG_H */

  