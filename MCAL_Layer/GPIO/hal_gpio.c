/* 
 * File:   hal_gpio.c
 * Author: Mohammed
 *
 * Created on August 21, 2023, 3:26 PM
 */

#include "hal_gpio.h"
volatile uint8 *tris_registers[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
volatile uint8 *lat_registers[] = {&LATA, &LATB, &LATC, &LATD, &LATE};
volatile uint8 *port_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};
/**
 * @brief Initialize the direction of the a specific pin @ref direction_t
 * @param _pin_config pointer to configuration @ref pin_config_t
 * @return The status of the function
 *          (E_OK) The : The function done successfully
 *          (E_NOT_OK) : The function has an issue to perform the action
 */
#if PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || (_pin_config->pin > PORT_PIN_MAX_NUM -1)){
        ret = E_NOT_OK;
    }else{
        switch(_pin_config->direction){
            case GPIO_DIRECTION_OUTPUT:
                CLEAR_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
                break;
            case GPIO_DIRECTION_INPUT:
                SET_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
                break;
            default:
                ret = E_NOT_OK;   
        }
    } 
    return ret;
    
}
#endif
/**
 * 
 * @param _pin_config
 * @param dir_status
 * @return The status of the function
 *          (E_OK) The function done successfully
 *          (E_NOT_OK) The function has an issue to perform the action
 */
#if PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_git_direction_status(const pin_config_t *_pin_config, direction_t *dir_status){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || (_pin_config->pin > PORT_PIN_MAX_NUM -1)){
        ret = E_NOT_OK;
    }
    else{
        *dir_status = READ_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
    }
    return ret;   
}
#endif
/**
 * 
 * @param _pin_config
 * @param logic
 * @return The status of the function
 *          (E_OK) The function done successfully
 *          (E_NOT_OK) The function has an issue to perform the action
 */
#if PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || (_pin_config->pin > PORT_PIN_MAX_NUM -1)){
        ret = E_NOT_OK;
    }
    else{
        switch(logic){
            case GPIO_LOW:
                CLEAR_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
                break;
            case GPIO_HIGH:
                SET_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
                break;
        }
    }
    return ret;
}
#endif
/**
 * 
 * @param _pin_config
 * @param logic
 * @return The status of the function
 *          (E_OK) The function done successfully
 *          (E_NOT_OK) The function has an issue to perform the action
 */
#if PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || (_pin_config->pin > PORT_PIN_MAX_NUM -1)){
        ret = E_NOT_OK;
    }
    else{
        *logic = READ_BIT(*port_registers[_pin_config->port], _pin_config->pin);
    }
    return ret;  
}
#endif
/**
 * 
 * @param _pin_config
 * @return The status of the function
 *          (E_OK) The function done successfully
 *          (E_NOT_OK) The function has an issue to perform the action
 */
#if PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || (_pin_config->pin > PORT_PIN_MAX_NUM -1)){
        ret = E_NOT_OK;
    }
    else{
        TOGGLE_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
    }
    return ret; 
}
#endif

/**
 * 
 * @param _pin_config
 * @return The status of the function
 *          (E_OK) The function done successfully
 *          (E_NOT_OK) The function has an issue to perform the action
 */
#if PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || (_pin_config->pin > PORT_PIN_MAX_NUM -1)){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_initialize(_pin_config);
        ret = gpio_pin_write_logic(_pin_config, _pin_config->logic);// By default is GPIO_LOW logic .....
    }
    return ret; 
}
#endif
/**
 * 
 * @param port : Initialize the port @ref port_index_t
 * @param direction uint8 datatype variable to assign it to the specific port
 * @return The status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has an issue to perform the action
 */
#if PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_direction_initialize(port_index_t port, uint8 direction){
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUM -1)
    {
        ret = E_NOT_OK;
    }
    else{
        *tris_registers[port] = direction;
    }
    return ret;
}
#endif
/**
 * 
 * @param port
 * @param direction_status
 * @return The status of the function
 *          (E_OK) The function done successfully
 *          (E_NOT_OK) The function has an issue to perform the action
 */
#if PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_git_direction_status(port_index_t port, uint8 *direction_status){
    Std_ReturnType ret = E_OK;
    if((NULL == direction_status) || (port > PORT_MAX_NUM -1))
    {
        ret = E_NOT_OK;
    }
    else{
        *direction_status = *tris_registers[port];
    }
    return ret;
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return The status of the function
 *          (E_OK) The function done successfully
 *          (E_NOT_OK) The function has an issue to perform the action
 */
#if PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic){
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUM -1){
        ret = E_NOT_OK;
    }
    else{
        *lat_registers[port] = logic;
    }
    return ret;
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return The status of the function
 *          (E_OK) The function done successfully
 *          (E_NOT_OK) The function has an issue to perform the action
 */
#if PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic){
    Std_ReturnType ret = E_OK;
    if((NULL == logic) || (port > PORT_MAX_NUM -1)){
        ret = E_NOT_OK;
    }
    else{
         *logic = *lat_registers[port];
    }
    return ret;
}
#endif
/**
 * 
 * @param port
 * @return The status of the function
 *          (E_OK) The function done successfully
 *          (E_NOT_OK) The function has an issue to perform the action
 */
#if PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic(port_index_t port){
    Std_ReturnType ret = E_OK;
    if((port > PORT_MAX_NUM -1)){
        ret = E_NOT_OK;
    }
    else{
        *lat_registers[port] ^= PORT_MASK;
    }
    return ret;
}
#endif