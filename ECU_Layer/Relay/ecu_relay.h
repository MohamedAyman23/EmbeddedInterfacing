/* 
 * File:   ecu_relay.h
 * Author: moham
 *
 * Created on September 12, 2023, 8:13 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/* ---------- Section : Includes ---------- */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_relay_cfg.h"


/* ---------- MACRO Declarations ---------- */
#define RELAY_ON_STATUS         0x01U
#define RELAY_OFF_STATUS        0x00U
/* ---------- Section DataTypes ----------*/
typedef struct{
    uint8 port          :4;
    uint8 pin           :3;
    uint8 relay_status  :1;
}relay_t;
/* ---------- MACROS FUNCTIONS Declarations ---------- */

/* ---------- Functions Declarations ---------- */
/**
 * @brief Intialize the relay 
 * @param _relay pointer to structure object
 * @return Standard return type E_OK or E_NOT_OK
 */
Std_ReturnType relay_intialize(const relay_t *_relay);
/**
 * @brief Turn on a Relay
 * @param _relay pointer to structure object
 * @return Standard return type E_OK or E_NOT_OK
 */
Std_ReturnType relay_turn_on(const relay_t *_relay);
/**
 * @brief Turn off a Relay
 * @param _relay pointer to structure object
 * @return Standard return type E_OK or E_NOT_OK
 */
Std_ReturnType relay_turn_off(const relay_t *_relay);

#endif	/* ECU_RELAY_H */

