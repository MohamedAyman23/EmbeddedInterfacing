/* 
 * File:   ecu_keypad.c
 * Author: moham
 *
 * Created on September 15, 2023, 3:04 PM
 */
#include "ecu_keypad.h"

static const uint8 keypad_btn_values[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS] ={
                                            {'7', '8', '9', '/'},
                                            {'4', '5', '6', '*'},
                                            {'1', '2', '3', '-'},
                                            {'#', '0', '=', '+'}};
                                                                

/**
 * @brief Intialize the configuration of the keypad pins
 * @param _keypad_obj pointer to structure of type keypad_t
 * @return The status of the function
 *          (E_OK) The function done successfully
 *          (E_NOT_OK) The function has an issue to perform the action
 */
Std_ReturnType keypad_intialize(const keypad_t *_keypad_obj){
    Std_ReturnType ret = E_OK;
    uint8 rows_counter =0, columns_counter =0;
    if(NULL == _keypad_obj)
    {
        ret = E_NOT_OK;
    }
    else{
        for(rows_counter =0; rows_counter < ECU_KEYPAD_ROWS; rows_counter++)
        {
            ret = gpio_pin_initialize(&(_keypad_obj->keypad_rows_pins[rows_counter]));//pass the address of the pins to be initialized as output pins (rows) 
        }
        for(columns_counter =0; columns_counter < ECU_KEYPAD_ROWS; columns_counter++)
        {
            ret = gpio_pin_direction_initialize(&(_keypad_obj->keypad_columns_pins[columns_counter]));//pass the address of the pins to be initialized as input pins(columns)  
        }
    }
        
   return ret;     
}
/**
 * @brief Get the value of the pressed button
 * @param _keypad_obj pointer to structure of type keypad_t
 * @param value pointer which store the value of the pressed button
 * @return The status of the function
 *          (E_OK) The function done successfully
 *          (E_NOT_OK) The function has an issue to perform the action 
 */
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value){
    Std_ReturnType ret = E_OK;
    uint8 rows_counter =0, columns_counter =0, l_rows =0;
    logic_t columns_logic;
    if(NULL == _keypad_obj)
    {
        ret = E_NOT_OK;
    }
    else{
        for(rows_counter =0; rows_counter < ECU_KEYPAD_ROWS; rows_counter++)
        {
            for(l_rows = 0; l_rows < ECU_KEYPAD_ROWS ; l_rows++)
            {
               ret =  gpio_pin_write_logic(&(_keypad_obj->keypad_rows_pins[l_rows]), GPIO_LOW);
            }
            ret = gpio_pin_write_logic(&(_keypad_obj->keypad_rows_pins[rows_counter]), GPIO_HIGH);
            for(columns_counter =0; columns_counter < ECU_KEYPAD_COLUMNS; columns_counter++)
            {
                ret =  gpio_pin_read_logic(&(_keypad_obj->keypad_columns_pins[columns_counter]), &columns_logic);
                __delay_ms(5);
                if(GPIO_HIGH  == columns_logic)
                {
                    *value = keypad_btn_values[rows_counter][columns_counter];
                }
            }
        }
    }
        
   return ret;  
}