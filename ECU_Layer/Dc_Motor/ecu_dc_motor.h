/* 
 * File:   ecu_dc_motor.h
 * Author: moham
 *
 * Created on September 13, 2023, 3:47 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/* ---------- SECTION : INCLUDES ---------- */
#include "ecu_dc_motor_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* ---------- MACRO DECLARATIONS ---------- */
#define DC_MOTOR_ON     0x01U
#define DC_MOTOR_OFF    0x00U

#define DC_MOTOR_PIN1   0x00U
#define DC_MOTOR_PIN2   0x01U

/* ---------- MACROS FUNCTIONS DECLARATIONS ---------- */

/* ---------- SECTION DATATYPES ----------*/
typedef struct {
    pin_config_t dc_motor_pin[2];
}dc_motor_t;

/* ---------- SOFTWARE INTERFACES DECLARATIONS ---------- */
Std_ReturnType dc_motor_intialize(const dc_motor_t *_motor);
Std_ReturnType dc_motor_move_right(const dc_motor_t *_motor);
Std_ReturnType dc_motor_move_left(const dc_motor_t *_motor);
Std_ReturnType dc_motor_stop(const dc_motor_t *_motor);




#endif	/* ECU_DC_MOTOR_H */

