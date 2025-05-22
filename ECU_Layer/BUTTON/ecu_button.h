/* 
 * File:   ecu_button.h
 * Author: moham
 *
 * Created on September 11, 2023, 1:12 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* Section : Includes */
#include "ecu_button_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section DataTypes */
typedef enum{
    BUTTON_ACTIVE_LOW,
    BUTTON_ACTIVE_HIGH
}button_active_t;
typedef enum{
    BUTTON_RELEASED,
    BUTTON_PRESSED
}button_state_t;
typedef struct {
    pin_config_t button_pin;
    button_state_t button_state;
    button_active_t button_connection;
}button_t;
/* MACRO Declarations */

/* MACROS FUNCTIONS Declarations */
/* Functions Declarations */
/**
 * @brief Intialize the pin to assign it
 * @param Btn pointer to structure of button_t datatype
 * @return Ret status of the execution of the function
 */
Std_ReturnType button_intialize(const button_t *btn);
/**
 * @brief Read the state of the button
 * @param Btn pointer to structure of button_t datatype
 * @param Btn_state pointer to return the status of the button
 * @return Ret status of the execution of the function
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state);

#endif	/* ECU_BUTTON_H */

