/* 
 * File:   ecu_seven_segment.c
 * Author: moham
 *
 * Created on September 14, 2023, 8:40 PM
 */
#include "ecu_seven_segment.h"




/**
 * @brief Fuction to intialize the pins of the seven segment
 * @param Seg pointer to the sturcture to intialize the seven segment
 * @param Number the value to be written on the decoder and the seven segment
 * @return E_OK : if the function has executed successfully 
 *         E_NOT_OK : if the function has and error
 */
Std_ReturnType seven_segment_intialize(const segment_t *seg){
    Std_ReturnType ret = E_OK;
    if(NULL == seg)
    {
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN0]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN1]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN2]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN3]));

    }
    return ret;
}
/**
 * @brief Fuction to write the number of the seven segment
 * @param seg pointer to the sturcture to intialize the seven segment
 * @param number the value to be written on the decoder and the seven segment
 * @return E_OK : if the function has executed successfully 
 *         E_NOT_OK : if the function has and error 
 */
Std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 number){
     Std_ReturnType ret = E_OK;
    if((NULL == seg) || (number > 9))
    {
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN0]), (((uint8)1 ) & (number)));
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN1]), (((number) >> SEGMENT_PIN1) & 0x01));
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN2]), (((number) >> SEGMENT_PIN2) & 0x01));
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN3]), (((number) >> SEGMENT_PIN3) & 0x01));
    }
    return ret;
}