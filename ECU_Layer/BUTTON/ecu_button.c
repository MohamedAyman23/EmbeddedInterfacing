/* 
 * File:   ecu_button.c
 * Author: moham
 *
 * Created on September 11, 2023, 1:12 PM
 */

/* Section : Includes */
#include "ecu_button.h"

/**
 * @brief Intialize the pin to assign it
 * @param Btn pointer to structure of button_t datatype
 * @return Ret status of the execution of the function
 */
Std_ReturnType button_intialize(const button_t *btn){
    Std_ReturnType ret = E_OK;
    if((NULL == btn))
    {
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_initialize(&(btn->button_pin));
    }
    return ret;
}

/**
 * @brief Read the state of the button
 * @param Btn pointer to structure of button_t datatype
 * @param Btn_state pointer to return the status of the button
 * @return Ret status of the execution of the function
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state){
    Std_ReturnType ret = E_NOT_OK;
    logic_t pin_logic_status = GPIO_LOW;
    if((NULL == btn) || (NULL == btn_state))
    {
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_read_logic(&(btn->button_pin), &pin_logic_status);
        if(BUTTON_ACTIVE_HIGH == (btn->button_connection)){
            if(GPIO_LOW == pin_logic_status)
            {
                *btn_state = BUTTON_RELEASED; 
            }
            else{
                *btn_state = BUTTON_PRESSED;
            }
        }
        else if(BUTTON_ACTIVE_LOW == (btn->button_connection)){
            if(GPIO_LOW == pin_logic_status)
            {
                *btn_state = BUTTON_PRESSED;
            }
            else{
                *btn_state = BUTTON_RELEASED;
            }
              
        }
        else{ /* Nothing */}
        ret = E_OK;
    }
    return ret;
}