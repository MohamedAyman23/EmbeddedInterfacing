/* 
 * File:   ecu_relay.c
 * Author: moham
 *
 * Created on September 12, 2023, 8:13 PM
 */

#include "ecu_relay.h"

/**
 * @brief Intialize the relay 
 * @param _relay pointer to structure object
 * @return Standard return type E_OK or E_NOT_OK
 */
Std_ReturnType relay_intialize(const relay_t *_relay){
    Std_ReturnType ret = E_OK;
    if(NULL == _relay)
    {
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {
            .port = _relay->port,
            .pin = _relay->pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _relay->relay_status
        };
        gpio_pin_initialize(&pin_obj);
    }
    
    return ret;
}

/**
 * @brief Turn on a Relay
 * @param _relay pointer to structure object
 * @return Standard return type E_OK or E_NOT_OK
 */
Std_ReturnType relay_turn_on(const relay_t *_relay){
    Std_ReturnType ret = E_OK;
    if(NULL == _relay)
    {
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {
            .port = _relay->port,
            .pin = _relay->pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _relay->relay_status
        };
        gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    return ret;
}


/**
 * @brief Turn off a Relay
 * @param _relay pointer to structure object
 * @return Standard return type E_OK or E_NOT_OK
 */
Std_ReturnType relay_turn_off(const relay_t *_relay){
    Std_ReturnType ret = E_OK;
    if(NULL == _relay)
    {
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {
            .port = _relay->port,
            .pin = _relay->pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _relay->relay_status
        };
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    return ret;
}
