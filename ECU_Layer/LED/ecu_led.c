/* 
 * File:   ecu_led.c
 * Author: moham
 *
 * Created on August 21, 2023, 6:51 PM
 */
#include "ecu_led.h"

/**
 * @brief Intialize the  led status
 * @param led pointer to structure
 * @return standard return type with the status of the function execution
 */
Std_ReturnType led_intialize(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {
            .port = led->port,
            .pin = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = led->led_status      
        };
        ret = gpio_pin_initialize(&pin_obj);
    }
    return ret;
}

/**
 * @brief Turn off a led 
 * @param led pointer to structure
 * @return standard return type with the status of the function execution
 */
Std_ReturnType led_turn_off(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else{
         pin_config_t pin_obj = {
            .port = led->port,
            .pin = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = led->led_status      
        };
        ret = gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    return ret;
}
/**
 * @brief Turn on a led
 * @param Led pointer to structure
 * @return Standard return type with the status of the function execution
 */
Std_ReturnType led_turn_on(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else{
         pin_config_t pin_obj = {
            .port = led->port,
            .pin = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = led->led_status      
        };
         ret = gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    return ret;
}
/**
 * @brief Turn off a led
 * @param Led pointer to structure
 * @return Standard return type with the status of the function execution
 */
Std_ReturnType led_toggle(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else{
         pin_config_t pin_obj = {
            .port = led->port,
            .pin = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = led->led_status      
        };
        ret = gpio_pin_toggle_logic(&pin_obj);
    }
    return ret;
}