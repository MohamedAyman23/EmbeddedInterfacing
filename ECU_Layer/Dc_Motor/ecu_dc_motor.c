/* 
 * File:   ecu_dc_motor.c
 * Author: moham
 *
 * Created on September 13, 2023, 3:47 PM
 */
#include "ecu_dc_motor.h"
/**
 * 
 * @param _motor
 * @return 
 */
Std_ReturnType dc_motor_intialize(const dc_motor_t *_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _motor)
    {
        ret = E_NOT_OK;
    }else{
        gpio_pin_initialize(&(_motor->dc_motor_pin[DC_MOTOR_PIN1]));
        gpio_pin_initialize(&(_motor->dc_motor_pin[DC_MOTOR_PIN2]));
    }
    return ret;   
}
/**
 * 
 * @param _motor
 * @return 
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t *_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _motor)
    {
        ret = E_NOT_OK;
    }else{
        gpio_pin_write_logic(&(_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_HIGH);
        gpio_pin_write_logic(&(_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);
    }
    return ret; 
}
/**
 * 
 * @param _motor
 * @return 
 */
Std_ReturnType dc_motor_move_left(const dc_motor_t *_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _motor)
    {
        ret = E_NOT_OK;
    }else{
        gpio_pin_write_logic(&(_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);
        gpio_pin_write_logic(&(_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_HIGH);
    }
    return ret; 
}
/**
 * 
 * @param _motor
 * @return 
 */
Std_ReturnType dc_motor_stop(const dc_motor_t *_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _motor)
    {
        ret = E_NOT_OK;
    }else{
        gpio_pin_write_logic(&(_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);
        gpio_pin_write_logic(&(_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);
    }
    return ret; 
}
