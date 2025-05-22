/* 
 * File:   ecu_layer_initialize.c
 * Author: moham
 *
 * Created on September 17, 2023, 11:34 AM
 */
#include "ecu_layer_initialize.h"

led_t led_1 = {
    .port = PORTC_INDEX,
    .pin = pin0,
    .led_status = LED_OFF
};
led_t led_2 = {
    .port = PORTC_INDEX,
    .pin = pin1,
    .led_status = LED_OFF
};
led_t led_3 = {
    .port = PORTC_INDEX,
    .pin = pin2,
    .led_status = LED_OFF
};
led_t led_4 = {
    .port = PORTC_INDEX,
    .pin = pin3,
    .led_status = LED_OFF
};
chr_lcd_4bit_t lcd_1 = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = pin0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = pin1,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    
    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = pin2,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    
    .lcd_data[1].port = PORTC_INDEX,
    .lcd_data[1].pin = pin3,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    
    .lcd_data[2].port = PORTC_INDEX,
    .lcd_data[2].pin = pin4,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = pin5,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW,
    
};

chr_lcd_8bit_t lcd_2 = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = pin6,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = pin7,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    
    .lcd_data[0].port = PORTD_INDEX,
    .lcd_data[0].pin = pin0,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    
    .lcd_data[1].port = PORTD_INDEX,
    .lcd_data[1].pin = pin1,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    
    .lcd_data[2].port = PORTD_INDEX,
    .lcd_data[2].pin = pin2,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    
    .lcd_data[3].port = PORTD_INDEX,
    .lcd_data[3].pin = pin3,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW,
    
    .lcd_data[4].port = PORTD_INDEX,
    .lcd_data[4].pin = pin4,
    .lcd_data[4].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[4].logic = GPIO_LOW,
    
    .lcd_data[5].port = PORTD_INDEX,
    .lcd_data[5].pin = pin5,
    .lcd_data[5].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[5].logic = GPIO_LOW,
    
    .lcd_data[6].port = PORTD_INDEX,
    .lcd_data[6].pin = pin6,
    .lcd_data[6].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[6].logic = GPIO_LOW,
    
    .lcd_data[7].port = PORTD_INDEX,
    .lcd_data[7].pin = pin7,
    .lcd_data[7].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[7].logic = GPIO_LOW,
};
keypad_t keypad1 = {
    .keypad_rows_pins[0].port = PORTC_INDEX,
    .keypad_rows_pins[0].pin = pin0,
    .keypad_rows_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[0].logic = GPIO_LOW,
    .keypad_rows_pins[1].port = PORTC_INDEX,
    .keypad_rows_pins[1].pin = pin1,
    .keypad_rows_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[1].logic = GPIO_LOW,
    .keypad_rows_pins[2].port = PORTC_INDEX,
    .keypad_rows_pins[2].pin = pin2,
    .keypad_rows_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[2].logic = GPIO_LOW,
    .keypad_rows_pins[3].port = PORTC_INDEX,
    .keypad_rows_pins[3].pin = pin3,
    .keypad_rows_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[3].logic = GPIO_LOW,
    
    .keypad_columns_pins[0].port = PORTC_INDEX,
    .keypad_columns_pins[0].pin = pin4,
    .keypad_columns_pins[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[0].logic = GPIO_LOW,
    .keypad_columns_pins[1].port = PORTC_INDEX,
    .keypad_columns_pins[1].pin = pin5,
    .keypad_columns_pins[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[1].logic = GPIO_LOW,
    .keypad_columns_pins[2].port = PORTC_INDEX,
    .keypad_columns_pins[2].pin = pin6,
    .keypad_columns_pins[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[2].logic = GPIO_LOW,
    .keypad_columns_pins[3].port = PORTC_INDEX,
    .keypad_columns_pins[3].pin = pin7,
    .keypad_columns_pins[3].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[3].logic = GPIO_LOW
    
};









void Ecu_interfaces_initialize(void){
    Std_ReturnType ret = E_NOT_OK;
    //ret = lcd_4bit_intialize(&lcd_1);
    //ret = lcd_8bit_intialize(&lcd_2);
    ret = led_intialize(&led_1);
    ret = led_intialize(&led_2);
    ret = led_intialize(&led_3);
    ret = led_intialize(&led_4);
}