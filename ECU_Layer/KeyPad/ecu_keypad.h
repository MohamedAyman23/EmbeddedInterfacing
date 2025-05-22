/* 
 * File:   ecu_keypad.h
 * Author: moham
 *
 * Created on September 15, 2023, 3:04 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* ---------- Section : Includes ---------- */
#include "ecu_keypad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* ---------- MACRO Declarations ---------- */
#define ECU_KEYPAD_ROWS     4
#define ECU_KEYPAD_COLUMNS  4
/* ---------- MACROS FUNCTIONS Declarations ---------- */

/* ---------- Section DataTypes ----------*/
typedef struct{
    pin_config_t keypad_rows_pins[ECU_KEYPAD_ROWS];
    pin_config_t keypad_columns_pins[ECU_KEYPAD_COLUMNS];
}keypad_t;

/* ---------- Software Interfaces Declarations ---------- */

Std_ReturnType keypad_intialize(const keypad_t *_keypad_obj);
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value);


#endif	/* ECU_KEYPAD_H */

